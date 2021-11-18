#include "judge.h"

#include <time.h>

#include <random>
#include <string>
#include <vector>

#include "view.h"

// �Ʒ� ��ũ�ο� �ּ��� cpplint���� ��� �޾�����
// �������� ���� �̴�� �ξ����ϴ�.

#define NUMBER_OF_CARDS 48                  // ���ӿ� ���̴� ī��� �� 48���̴�.
#define NUMBER_OF_CARDS_FOR_PLAYER 10       // �� �÷��̾�� 10���� ī�带 �޴´�.
#define NUMBER_OF_CARDS_FOR_BOARD_FLOOR 8   // �ٴڿ��� 8���� ī�带 ��Ƴ��´�.

#define STD_OF_SCORE_WITH_P 15      // �ǰ� 15�� �̻��� ���, ������ ����.
#define STD_OF_SCORE_WITH_DAN 5     // ���� 5�� �̻��� ���, ������ ����.
#define STD_OF_SCORE_WITH_ANIMAL 5  // ������ 5�� �̻��� ���, ������ ����.
#define STD_OF_SCORE_WITH_GWANG 3   // ���� 3�� �̻��� ���, ������ ����.

#define STD_OF_DOUBLE_SCORE_WITH_ANIMALS 8  // ������ 8�� �̻��� ���, �۵��� �� ������ 2�踦 ���ش�.
#define STD_OF_P_BAK 7                      // �Ƿ� ������ �� ���, ������ �ǰ� 7�� �̸��̸� �ǹ��� �߻��Ѵ�.
#define STD_OF_SCORE_FOR_WIN 7              // 7�� �̻��� ������ ���� �̱��.
#define STD_OF_GODORI_WITH_BIRD 3           // ������ ���� 3�� ���� ���� 5���� ȹ���Ѵ�.

#define SCORE_GODIRI 5                      // ������ 5���̴�.
#define SCORE_RED_DAN 3                     // ȫ���� 3���̴�.
#define SCORE_BLUE_DAN 3                    // û���� 3���̴�.
#define SCORE_GRASS_DAN 3                   // �ʴ��� 3���̴�.
#define SCORE_THREE_GWANG_WITH_RAIN 2       // �� ���� 3���� ���� 2���̴�.
#define SCORE_THREE_GWANG_WITHOUT_RAIN 3    // �� ������ 3���� ���� 2���̴�.

#define INCREMENT_FOR_DOUBLE_P 2  // ������ �� ������ 2�̴�.

// Constructor
Judge::Judge() : is_game_over_(false) {}

// Destructor
Judge::~Judge() {}

// player���� 10���� ī�带 �����´�.
std::vector<Card*>* Judge::CardsForPlayerFromInitDeck(std::stack<Card*>* a_deck) {
  std::vector<Card*>* answer = new std::vector<Card*>();
  View::PrintStringWithLine(
      ">>> [Judge says] �÷��̾�� 10���� ī�带 �й��մϴ�.");
  for (int i = 0; i < NUMBER_OF_CARDS_FOR_PLAYER; i++) {
    answer->push_back(a_deck->top());
    a_deck->pop();
  }

  return answer;
}

// board�� �ٴڿ� �� 8���� ī�带 �����´�.
std::list<Card*>* Judge::CardsForBoardFloor(std::stack<Card*>* a_deck) {
  std::list<Card*>* answer = new std::list<Card*>();
  View::PrintStringWithLine(">>> [Judge says] �ٴڿ� 8���� ī�带 �����Ӵϴ�.");
  for (int i = 0; i < NUMBER_OF_CARDS_FOR_BOARD_FLOOR; i++) {
    answer->push_back(a_deck->top());
    a_deck->pop();
  }

  return answer;
}

// �ʱ� ��(deck)�� �����Ѵ�.
std::stack<Card*>* Judge::InitDeck() { return Suffle(MakeAllCards()); }

// ���� �ִ� ī��� ���� �����Ѵ�.
void Judge::ClearDeck(std::stack<Card*>* a_deck) { 
  if (a_deck) {
    while (!a_deck->empty()) {
      delete a_deck->top(); // new in Judge::MakeAllCards()
      a_deck->pop();
    }
    delete a_deck;  // new in Judge::Shuffle()
  }
}

// �ٴ�(floor_)�� �ִ� ī��� �ٴ��� �����Ѵ�.
void Judge::ClearFloor(std::list<Card*>* a_floor) {
  if (a_floor) {
    for (Card* card_in_floor : *a_floor) {
      delete card_in_floor;
    }
    delete a_floor;
  }
}

// ���� ���� ������ ����Ѵ�.
int Judge::CalcScoreForGwang(Player* a_player) {
  int answer = 0;

  int count_gwang = 0;
  bool has_rain_gwang = false;

  const std::list<Card*>* gwangs = a_player->pockets_for_cards()->pocket_for_gwang();

  for (const Card* card : *gwangs) {
    count_gwang++;
    if (card->special().compare("rain") == 0) {
      has_rain_gwang = true;
    }
  }
  if (count_gwang == 3) {
    if (has_rain_gwang)
      answer += SCORE_THREE_GWANG_WITH_RAIN;
    else
      answer += SCORE_THREE_GWANG_WITHOUT_RAIN;

  } else if (count_gwang >= 4) {
    answer += count_gwang;
  }

  return answer;
}
// ������ ���� ������ ����Ѵ�.
int Judge::CalcScoreForAnimal(Player* a_player, bool& is_mung) {
  int answer = 0;

  int count_animal = 0;
  int count_bird = 0;

  const std::list<Card*>* animals = a_player->pockets_for_cards()->pocket_for_animals();

  for (const Card* card : *animals) {
    count_animal++;
    if (card->special().compare("bird") == 0) count_bird++;
  }
  if (count_bird == STD_OF_GODORI_WITH_BIRD) answer += SCORE_GODIRI;
  if (count_animal >= STD_OF_SCORE_WITH_ANIMAL)
    answer += (count_animal - STD_OF_SCORE_WITH_ANIMAL + 1);

  // �۵� : �������� ���ϱ� 2 ... !
  if (count_animal >= STD_OF_DOUBLE_SCORE_WITH_ANIMALS) is_mung = true;

  return answer;
}
// �ܿ� ���� ������ ����Ѵ�.
int Judge::CalcScoreForDan(Player* a_player) {
  int answer = 0;

  const std::list<Card*>* dan = a_player->pockets_for_cards()->pocket_for_dan();

  int count_dan = 0;
  int count_red_dan = 0;
  int count_blue_dan = 0;
  int count_grass_dan = 0;

  for (const Card* card : *dan) {
    count_dan++;
    if (card->special().compare("red") == 0) {
      count_red_dan++;
    } else if (card->special().compare("blue") == 0) {
      count_blue_dan++;
    } else if (card->special().compare("grass") == 0) {
      count_grass_dan++;
    }
  }
  if (count_dan >= STD_OF_SCORE_WITH_DAN)
    answer += (count_dan - STD_OF_SCORE_WITH_DAN + 1);
  
  // ȫ�� : 3��
  if (count_red_dan == 3)
    answer += SCORE_RED_DAN;
  // û�� : 3��
  if (count_blue_dan == 3)
    answer += SCORE_BLUE_DAN;
  // �ʴ� : 3��
  if (count_grass_dan == 3)
    answer += SCORE_GRASS_DAN;
  
  return answer;
}

// �ǿ� ���� ������ ����Ѵ�.
int Judge::CalcScoreForP(Player* a_player) {
  int answer = 0;
  int count_p = 0;

  const std::list<Card*>* p = a_player->pockets_for_cards()->pocket_for_p();

  for (const Card* card : *p) {
    if (card->special().compare("double") == 0)
      count_p += INCREMENT_FOR_DOUBLE_P;
    else
      count_p++;
  }
  if (count_p >= STD_OF_SCORE_WITH_P)
    answer += (count_p - STD_OF_SCORE_WITH_P + 1);

  return answer;
}

// �÷��̾��� ������ ����Ѵ�.
int Judge::CalcScore(Player* a_player, Player* opponent_player) {
  int answer = 0;
  
  // 1. ���� ���� ���� ����� �ϰ� �����Ѵ�.
  int score_for_gwang = CalcScoreForGwang(a_player);    // ���� �Ǵܿ� ����
  answer += score_for_gwang;

  // 2. �ܿ� ���� ���� ����� �ϰ� �����Ѵ�.
  answer += CalcScoreForDan(a_player);

  // 3. �ǿ� ���� ���� ����� �ϰ� �����Ѵ�.
  int score_for_p = CalcScoreForP(a_player);    // �ǹ� �Ǵܿ� ����
  answer += score_for_p;

  // 4-1. ������ ���� ���� ����� �ϰ� �����Ѵ�.
  bool is_mung = false; // �۵� �Ǵܿ� ����
  answer += CalcScoreForAnimal(a_player, is_mung);

  // 4-2. �۵�(���� 8�� �̻� ����) : ���� ������ ���ϱ� 2 ... !
  if (is_mung) {
    answer *= 2;
    View::PrintStringWithLine("[Judge says] �۵��� �ι��� ������ ����ϴ�.");
  }

  // 5. ������ 7�� �̻� ���� ����, �ǹ��� ��������.
  if (answer >= STD_OF_SCORE_FOR_WIN) {
    // ���� : �������� ���ϱ� 2 ... !
    if (score_for_gwang >= 1 && opponent_player->pockets_for_cards()->pocket_for_gwang()->empty()) {
      answer *= 2;
      View::PrintStringWithLine(
          "[Judge says] ����� �������� �ι��� ������ ����ϴ�.");
    }

    // �ǹ� : �������� ���ϱ� 2 ... !
    if (score_for_p >= 1 &&
        opponent_player->pockets_for_cards()->pocket_for_p()->size() < STD_OF_P_BAK) {
      answer *= 2;
      View::PrintStringWithLine(
          "[Judge says] ����� �ǹ����� �ι��� ������ ����ϴ�.");
    }

  }

  return answer;
}

// ������ 7�� �̻��̸� ������ �����Ѵ�.
bool Judge::IsGameOver(int a_score) {
  if (a_score >= STD_OF_SCORE_FOR_WIN)
    return true;
  else
    return false;
}

// Getters & Setters
bool Judge::is_game_over() { return is_game_over_; }
void Judge::set_is_game_over(bool new_is_game_over) {
  is_game_over_ = new_is_game_over;
}

// -------------------------------------
// ---------- Private methods ----------
// -------------------------------------

// ���ӿ� �� ī�� 48���� �����.
std::vector<Card*>* Judge::MakeAllCards() {
  std::string all_cards_properties[] = {
      "gwang",  "dan", "p", "p", "animal", "dan",    "p",   "p",
      "gwang",  "dan", "p", "p", "animal", "dan",    "p",   "p",
      "animal", "dan", "p", "p", "animal", "dan",    "p",   "p",
      "animal", "dan", "p", "p", "gwang",  "animal", "p",   "p",
      "animal", "dan", "p", "p", "animal", "dan",    "p",   "p",
      "gwang",  "p",   "p", "p", "gwang",  "animal", "dan", "p"};
  std::string all_cards_special[] = {
      "normal", "red",    "normal", "normal", "bird",   "red",    "normal",
      "normal", "normal", "red",    "normal", "normal", "bird",   "grass",
      "normal", "normal", "normal", "grass",  "normal", "normal", "normal",
      "blue",   "normal", "normal", "normal", "grass",  "normal", "normal",
      "normal", "bird",   "normal", "normal", "normal", "blue",   "normal",
      "normal", "normal", "blue",   "normal", "normal", "normal", "double",
      "normal", "normal", "rain",   "normal", "normal", "double"};

  View::PrintStringWithLine(
      "\n>>> [Judge says] ���ӿ� ����� ī�� 48���� ���� �����մϴ�.");
  std::vector<Card*>* a_card_list = new std::vector<Card*>(); // delete in Judge::Suffle
  for (int index = 0; index < NUMBER_OF_CARDS; index++) {
    int month = (index / 4) + 1;
    a_card_list->push_back(
        new Card(month, all_cards_properties[index], all_cards_special[index])); 
    // delete in ... ��, �ٴ�, �÷��̾��� �ָӴϸ� ���鼭 ��������.
  }

  return a_card_list;
}

// ������� 48���� ī�带 ���´�.
std::stack<Card*>* Judge::Suffle(std::vector<Card*>* all_cards) {
  std::stack<Card*>* deck = new std::stack<Card*>();  // delete in Judge::ClearDeck()
  View::PrintStringWithLine(">>> [Judge says] ī�带 �����ϴ�.");

  srand((unsigned int)time(0));
  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    int random_index = rand() % all_cards->size();
    deck->push((*all_cards)[random_index]);
    all_cards->erase(all_cards->begin() + random_index);
  }

  delete all_cards;  // new in Judge::MakeAllCards()

  return deck;
}
