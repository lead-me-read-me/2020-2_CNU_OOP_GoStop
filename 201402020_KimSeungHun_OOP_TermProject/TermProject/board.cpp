#include "board.h"

#include <list>
#include <string>
#include <vector>

#include "view.h"

// dack�� ���� ������ ���ڿ��� ��ȯ�Ѵ�.
// (ex) =================
//      | Deck ( 20�� ) |
//      -----------------
std::string Board::ToStringForDeck() {
  std::string answer = " =================\n ";
  answer += "| Deck ( " + std::to_string(deck_->size()) + "�� ) |\n";
  answer += " -----------------";
  return answer;
}

// �ٴڿ� �� ī����� ���ڿ��� ��ȯ�Ѵ�.
// (ex) | 8(gwang_normal) | 1(p_normal) | 3(p_noraml) |
//      | 7(animal_normal) |
//      ===============================================
std::string Board::ToStringForFloor() {
  if (floor_->empty()) {
    std::string answer = "!! ���� �ٴڿ� ī�尡 �����ϴ�. !!\n";
    answer +=
        "======================================================================"
        "==";
    return answer;

  } else {
    std::string answer = "";
    std::list<Card*>::iterator it_for_floor = floor_->begin();
    int count = 0;

    for (; it_for_floor != floor_->end(); it_for_floor++) {
      answer += "| " + (*it_for_floor)->ToString() + " ";
      count++;
      if (count % 5 == 0) {
        answer += "|\n";
      }
    }
    if (count % 5 != 0) {
      answer += "|\n";
    }
    answer +=
        "======================================================================"
        "==";
    return answer;
  }
}

// card�� ��Ī�Ǵ� ī����� floor�� �ִ��� Ȯ���Ͽ� vector�� ��� ��ȯ�Ѵ�.
std::vector<Card*> Board::MatchedCardsWith(Card* card) {
  std::vector<Card*> answer = std::vector<Card*>();

  std::vector<std::list<Card*>::iterator> iterators_will_be_deleted =
      std::vector<std::list<Card*>::iterator>();
  std::list<Card*>::iterator it;
  for (it = floor_->begin(); it != floor_->end(); it++) {
    if ((*it)->month() == card->month()) {
      answer.push_back(*it);
      iterators_will_be_deleted.push_back(it);
    }
  }

  for (std::list<Card*>::iterator it : iterators_will_be_deleted) {
    floor_->erase(it);
  }

  return answer;
}

// deck���� ī�带 �ϳ� ������.
Card* Board::DrawCardFromDeck() {
  if (deck_->empty()) {
    return nullptr; // delete Board::CardsToPlayer
  } else {
    Card* answer = deck_->top();
    deck_->pop();
    return answer;
  }
}

// �������κ��� �Ǹ� �ϳ� ���Ҿ� �´�.
bool Board::StealPIfPossible(Player* opponent_player,
                             std::list<Card*>* from_board_to_player) {
  Card* p_from_opponent_player = opponent_player->GetPIfPossible();
  if (p_from_opponent_player) {
    from_board_to_player->push_back(p_from_opponent_player);
    View::PrintStringWithLine("!! [Board says] ���濡�� ������ ��: " +
                              p_from_opponent_player->ToString());
    return true;

  } else {
    View::PrintStringWithLine(
        "!! [Board says] ���濡�Լ� ������ �ǰ� �����ϴ�.");
    return false;
  }
}

// card_from_player�� ���� Board��
// player���� ������ ī�� ����Ʈ�� ��ȯ�Ѵ�.
std::list<Card*>* Board::CardsToPlayer(Card* card_from_player,
                                       Player* opponent_player) {
  std::list<Card*>* answer = new std::list<Card*>();

  Card* card_from_deck = DrawCardFromDeck();
  if (!card_from_deck) return nullptr;
  
  View::PrintStringWithLine(">> [Board says] �÷��̾ �� ī��: " +
                            card_from_player->ToString());
  View::PrintStringWithLine(">> [Board says] ������ ���� ī��: " +
                            card_from_deck->ToString());

  if (card_from_player->month() == card_from_deck->month()) {
    std::vector<Card*> matched_cards = MatchedCardsWith(card_from_player);

    if (matched_cards.size() == 2) {
      // �ٴڿ� 2���� ī�尡 ��ħ ... ����
      View::PrintStringWithLine(
          ">> [Board says] �ѹ��� 4�� �̻��� ī�带 �������ϴ�.");
      StealPIfPossible(opponent_player, answer);
      answer->push_back(card_from_player);
      answer->push_back(card_from_deck);
      for (Card* card : matched_cards) {
        answer->push_back(card);
      }

    } else if (matched_cards.size() == 1) {
      // �ٴڿ� 1���� ī�尡 ��ħ ... ��
      View::PrintStringWithLine(">> [Board says] ���Դϴ�.");
      floor_->push_back(card_from_player);
      floor_->push_back(card_from_deck);
      for (Card* card : matched_cards) {
        floor_->push_back(card);
      }

    } else if (matched_cards.size() == 0) {
      // �ٴڿ� 0���� ī�尡 ��ħ ... ��
      View::PrintStringWithLine(">> [Board says] ���Դϴ�.");
      StealPIfPossible(opponent_player, answer);
      answer->push_back(card_from_player);
      answer->push_back(card_from_deck);
    }
    
  } else {
    // 1. �÷��̾ �� ī�� ó��
    std::vector<Card*> matched_cards_with_player_card =
        MatchedCardsWith(card_from_player);
    InsertCardsInto(opponent_player, matched_cards_with_player_card, answer);
    if (matched_cards_with_player_card.size() == 0) {
      floor_->push_back(card_from_player);
    } else {
      answer->push_back(card_from_player);
    }

    // 2. ������ ���� ī�� ó��
    std::vector<Card*> matched_cards_with_deck_card =
        MatchedCardsWith(card_from_deck);
    InsertCardsInto(opponent_player, matched_cards_with_deck_card, answer);
    if (matched_cards_with_deck_card.size() == 0) {
      floor_->push_back(card_from_deck);
    } else {
      answer->push_back(card_from_deck);
    }
  }

  return answer;
}

// from�� �ִ� ī����� ��쿡 ���� to�� �Ű� ��´�.
void Board::InsertCardsInto(Player* opponent_player, const std::vector<Card*>& from, std::list<Card*>* to) {
  // ��ġ�� ī�尡 ���� ���� ���� ó���Ѵ�.
  if (from.size() == 3 || from.size() == 1) {
    if (from.size() == 3) {
      View::PrintStringWithLine(">> [Board says] �ѹ��� 4�� �̻��� ī�带 �������ϴ�.");
      StealPIfPossible(opponent_player, to);
    }
    for (Card* card : from) {
      to->push_back(card);
    }

  } else if (from.size() == 2) {
    Card* card_0 = from[0];
    Card* card_1 = from[1];
    int player_choice = View::PrintChoicesAndGetCardOrder(card_0->ToString(), card_1->ToString());
    to->push_back(from[player_choice]);
    floor_->push_back(from[(player_choice+1) % 2]);
  }
}

// dack�� ����ִ��� Ȯ���Ѵ�.
bool Board::DeckIsEmpty() { return deck_->empty(); }

// Getters
std::stack<Card*>* Board::deck() { return deck_; }

// Setters
void Board::set_floor(std::list<Card*>* new_floor) { floor_ = new_floor; }
void Board::set_deck(std::stack<Card*>* new_deck) { deck_ = new_deck; }

// card_from_player�� ���� Board��
// player���� ������ ī�� ����Ʈ�� ��ȯ�Ѵ�.
// std::list<Card*>* Board::CardsToPlayer(Card* card_from_player,
//                                     Player* opponent_player) {
//  std::list<Card*>* answer = new std::list<Card*>(); // delete
//  Controller::PlayOf
//
//  bool complete_for_player_card = false;
//  bool complete_for_deck_card = false;
//
//  Card* card_from_deck = DrawCardFromDeck();
//
//  if (!card_from_deck) delete card_from_deck;
//
//  View::PrintStringWithLine(">> [Board says] �÷��̾ �� ī��: " +
//                            card_from_player->ToString());
//  View::PrintStringWithLine(">> [Board says] ������ ���� ī��: " +
//                            card_from_deck->ToString());
//
//  std::vector<Card*> matched_cards_with_player =
//      MatchedCardWith(card_from_player);
//  if (static_cast<int>(matched_cards_with_player.size()) == 3) {
//    // 1-1. �÷��̾� ī��� ���� �ִ� 3���� �� ���� ��������.
//    View::PrintStringWithLine(
//        ">> [Board says] �ѹ��� 4�� �̻��� ī�带 �������ϴ�.");
//    complete_for_player_card = true;
//
//    answer->push_back(card_from_player);
//    for (Card* card : matched_cards_with_player) {
//      answer->push_back(card);
//    }
//    StealPIfPossible(opponent_player, answer);
//  }
//
//  std::vector<Card*> matched_cards_with_deck =
//  MatchedCardWith(card_from_deck); if
//  (static_cast<int>(matched_cards_with_deck.size()) == 3) {
//    // 1-2. �� ī��� ���� �ִ� 3���� �� ���� ��������.
//    View::PrintStringWithLine(
//        ">> [Board says] �ѹ��� 4�� �̻��� ī�带 �������ϴ�.");
//    complete_for_deck_card = true;
//
//    answer->push_back(card_from_deck);
//    for (Card* card : matched_cards_with_player) {
//      answer->push_back(card);
//    }
//    StealPIfPossible(opponent_player, answer);
//  }
//  // CheckPoint 1. �÷��̾� ī��, �� ī�忡 ���� ó���� ��� ��ġ�� ������.
//  if (complete_for_player_card && complete_for_deck_card) return answer;
//
//  // 2-1. �÷��̾� ī��� 4���� ì�� ��,
//  if (complete_for_player_card && !complete_for_deck_card) {
//    // �� ī�忡 ���� ó��
//    if (static_cast<int>(matched_cards_with_deck.size()) == 2) {
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_deck[0]);
//      floor_->push_back(matched_cards_with_deck[1]);
//    }
//    if (static_cast<int>(matched_cards_with_deck.size()) == 1) {
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_deck[0]);
//    }
//    if (static_cast<int>(matched_cards_with_deck.size()) == 0) {
//      floor_->push_back(card_from_deck);
//    }
//    complete_for_deck_card = true;
//  }
//
//  // 2-2. �� ī��� 4���� ì�� ��,
//  if (complete_for_deck_card && !complete_for_player_card) {
//    // �÷��̾� ī�忡 ���� ó��
//    if (static_cast<int>(matched_cards_with_player.size()) == 2) {
//      answer->push_back(card_from_player);
//      answer->push_back(matched_cards_with_player[0]);
//      floor_->push_back(matched_cards_with_player[1]);
//    }
//    if (static_cast<int>(matched_cards_with_player.size()) == 1) {
//      answer->push_back(card_from_player);
//      answer->push_back(matched_cards_with_player[0]);
//    }
//    if (static_cast<int>(matched_cards_with_player.size()) == 0) {
//      floor_->push_back(card_from_player);
//    }
//    complete_for_player_card = true;
//  }
//  // CheckPoint 2. �÷��̾� ī��, �� ī�忡 ���� ó���� ��� ��ġ�� ������.
//  if (complete_for_player_card && complete_for_deck_card) return answer;
//
//  // 3-1. floor_�� �÷��̾��� ī��� ��ġ�ϴ� ī�尡 2���� ���
//  if (static_cast<int>(matched_cards_with_player.size()) == 2) {
//    if (static_cast<int>(matched_cards_with_deck.size()) == 0 &&
//        card_from_player->month() == card_from_deck->month()) {
//      View::PrintStringWithLine(
//          ">> [Board says] �ѹ��� 4�� �̻��� ī�带 �������ϴ�.");
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(card_from_deck);
//      for (Card* card : matched_cards_with_player) {
//        answer->push_back(card);
//      }
//      StealPIfPossible(opponent_player, answer);
//
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 2) {
//      if (card_from_player->month() != card_from_deck->month()) {
//        complete_for_player_card = true;
//        complete_for_deck_card = true;
//
//        answer->push_back(card_from_player);
//        answer->push_back(card_from_deck);
//        answer->push_back(matched_cards_with_player[0]);
//        answer->push_back(matched_cards_with_deck[0]);
//
//        floor_->push_back(matched_cards_with_player[1]);
//        floor_->push_back(matched_cards_with_deck[1]);
//      }
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 1) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_player[0]);
//      answer->push_back(matched_cards_with_deck[0]);
//
//      floor_->push_back(matched_cards_with_player[1]);
//
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 0) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(matched_cards_with_player[0]);
//
//      floor_->push_back(matched_cards_with_player[1]);
//      floor_->push_back(card_from_deck);
//    }
//  }
//  // CheckPoint 3-1. �÷��̾� ī��, �� ī�忡 ���� ó���� ��� ��ġ�� ������.
//  if (complete_for_player_card && complete_for_deck_card) return answer;
//
//  // 3-2. floor_�� �� ī��� ��ġ�ϴ� ī�尡 2���� ���
//  if (static_cast<int>(matched_cards_with_deck.size()) == 2) {
//    if (static_cast<int>(matched_cards_with_player.size()) == 1) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(matched_cards_with_player[0]);
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_deck[0]);
//
//      floor_->push_back(matched_cards_with_deck[1]);
//
//    } else if (static_cast<int>(matched_cards_with_player.size()) == 0) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_deck[0]);
//
//      floor_->push_back(card_from_player);
//      floor_->push_back(matched_cards_with_deck[1]);
//    }
//  }
//  // CheckPoint 3-2. �÷��̾� ī��, �� ī�忡 ���� ó���� ��� ��ġ�� ������.
//  if (complete_for_player_card && complete_for_deck_card) return answer;
//
//  // 4. floor_�� �÷��̾� ī��� ��ġ�ϴ� ī�尡 1���� ���
//  if (static_cast<int>(matched_cards_with_player.size()) == 1) {
//    if (static_cast<int>(matched_cards_with_deck.size()) == 0 &&
//        card_from_player->month() == card_from_deck->month()) {
//      // ��
//      View::PrintStringWithLine(">> [Board says] ���Դϴ�.");
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      floor_->push_back(card_from_player);
//      floor_->push_back(card_from_deck);
//      floor_->push_back(matched_cards_with_player[0]);
//
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 1) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_player[0]);
//      answer->push_back(matched_cards_with_deck[0]);
//
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 0 &&
//               card_from_player->month() != card_from_deck->month()) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(matched_cards_with_player[0]);
//
//      floor_->push_back(card_from_deck);
//    }
//  }
//  // CheckPoint 4. �÷��̾� ī��, �� ī�忡 ���� ó���� ��� ��ġ�� ������.
//  if (complete_for_player_card && complete_for_deck_card) return answer;
//
//  // 5. floor_�� �÷��̾� ī��� ��ġ�ϴ� ī�尡 0���� ���
//  if (static_cast<int>(matched_cards_with_player.size()) == 0) {
//    if (static_cast<int>(matched_cards_with_deck.size()) == 1 &&
//        card_from_player->month() != card_from_deck->month()) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_deck);
//      answer->push_back(matched_cards_with_deck[0]);
//
//      floor_->push_back(card_from_player);
//
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 0 &&
//               card_from_player->month() != card_from_deck->month()) {
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      floor_->push_back(card_from_player);
//      floor_->push_back(card_from_deck);
//    } else if (static_cast<int>(matched_cards_with_deck.size()) == 0 &&
//               card_from_player->month() == card_from_deck->month()) {
//      // ��
//      View::PrintStringWithLine(">> [Board says] �� �Դϴ�.");
//      complete_for_player_card = true;
//      complete_for_deck_card = true;
//
//      answer->push_back(card_from_player);
//      answer->push_back(card_from_deck);
//      StealPIfPossible(opponent_player, answer);
//    }
//  }
//  // CheckPoint 5. �÷��̾� ī��, �� ī�忡 ���� ó���� ��� ��ġ�� ������.
//  if (complete_for_player_card && complete_for_deck_card) return answer;
//
//  return answer;
//}
