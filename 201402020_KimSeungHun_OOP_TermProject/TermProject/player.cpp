#include "player.h"

// Constructor
Player::Player() {
  available_cards_ = new std::vector<Card*>();
  pockets_for_cards_ = new Pocket();
  current_state_ = new State();
}

// Destructor
Player::~Player() {
  delete available_cards_;
  delete pockets_for_cards_;
  delete current_state_;
}

// �ָӴϿ� ī�带 �ִ´�.
void Player::AddCard(Card* a_card) { pockets_for_cards_->AddCard(a_card); }

// �ָӴϿ��� ��ī�带 �ϳ� ������.
Card* Player::GetPIfPossible() { return pockets_for_cards_->GetPIfPossible(); }

// �� �����ϰ� ���� ���¸� �����Ѵ�.
void Player::DeclareGo(int score_when_declare_go) {
  current_state_->ChangeStateForGo(score_when_declare_go);
}

// ���� �÷��̾ �� �� �ִ� ī�带 ���ڿ��� ��´�.
const std::string Player::ToStringForAvailableCards() {
  std::string answer = "";
  int index = 0;
  for (Card* card : *available_cards_) {
    answer += "| " + card->ToString() + "_\'" + std::to_string(index) + "\' ";
    index++;
    if (index % 5 == 0) {
      answer += "|\n";
    }
  }
  if (index % 5 != 0) answer += " |";
  // answer += "\n----------------------------------";
  return answer;
}

// �ָӴϿ� �ִ� ī����� ������ ���ڿ��� ��ȯ�Ѵ�.
const std::string Player::ToStringForPockets() {
  return pockets_for_cards_->ToStringForPockets();
}

// �÷��̾ �� ī�带 �����Ͽ� ����.
// ������ �÷��̾ �� �Ͽ� �ѹ��� ī�带 ������ �����Ѵ�.
Card* Player::DropCard(int selected_card_order) {
  Card* answer = (*available_cards_)[selected_card_order];
  available_cards_->erase(available_cards_->begin() + selected_card_order);
  return answer;
}

// �÷��̾��� �ָӴϿ� ���¸� �����ϰ� �ٽ� �����. (�Ǹ��� ȣ��ȴ�.)
void Player::CleanPocketsAndResetScore() {
  if (pockets_for_cards_) {
    pockets_for_cards_->DeleteAllCardsInEachPocket();
  }

  delete pockets_for_cards_;
  delete current_state_;

  pockets_for_cards_ = new Pocket(); // delete in Player::CleanPocketsAndResetScore
  current_state_ = new State(); // delete in Player::CleanPocketsAndResetScore

}

// Getters
std::vector<Card*>* Player::available_cards() { return available_cards_; }
Pocket* Player::pockets_for_cards() { return pockets_for_cards_; }
State* Player::current_state() { return current_state_; }

// Setters
void Player::set_avilable_cards(std::vector<Card*>* new_available_cards) {
  available_cards_ = new_available_cards;
}
