#ifndef _JUDGE_H_
#define _JUDGE_H_

#include <stack>
#include <list>
#include <vector>

//#include "card.h"
#include "player.h"

class Judge {
 public:
  // Constructor
  Judge();

  // Destructor
  ~Judge();


  // 10���� ī�带 player���� �ش�.
  std::vector<Card*>* CardsForPlayerFromInitDeck(std::stack<Card*>* a_deck);

  // 8���� ī�带 board�� �ٴڿ� ���.
  std::list<Card*>* CardsForBoardFloor(std::stack<Card*>* a_deck);
  
  // �ʱ� ��(deck)�� �����Ѵ�.
  std::stack<Card*>* InitDeck();

  // ���� �����Ѵ�.
  void ClearDeck(std::stack<Card*>* a_deck);

  // �ٴ�(floor_)�� �ִ� ī��� �ٴ��� �����Ѵ�.
  void ClearFloor(std::list<Card*>* a_floor);

  // �÷��̾��� ������ ����Ѵ�.
  int CalcScore(Player* a_player, Player* opponent_player);

  // ������ 7�� �̻��̸� ������ �����Ѵ�.
  bool IsGameOver(int a_score);

  // Getters & Setters
  bool is_game_over();
  void set_is_game_over(bool new_is_game_over);


 private:
  bool is_game_over_;

  // ���ӿ� �� ī�� 48���� �����.
  std::vector<Card*>* MakeAllCards();

  // ������� 48���� ī�带 ���´�.
  std::stack<Card*>* Suffle(std::vector<Card*>* all_cards);

  // ���� ���� ������ ����Ѵ�.
  int CalcScoreForGwang(Player* a_player);
  // ������ ���� ������ ����Ѵ�.
  int CalcScoreForAnimal(Player* a_player, bool& is_mung);
  // �ܿ� ���� ������ ����Ѵ�.
  int CalcScoreForDan(Player* a_player);
  // �ǿ� ���� ������ ����Ѵ�.
  int CalcScoreForP(Player* a_player);
};

#endif  // !_JUDGE_H_
