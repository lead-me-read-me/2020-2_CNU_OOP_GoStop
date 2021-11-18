#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <string>
#include <list>

#include "card.h"
#include "state.h"
#include "pocket.h"

class Player {
 public:
  // Constructor
  Player();

  // Destructor
  ~Player();
  
  // �ָӴϿ� ī�带 �ִ´�.
  void AddCard(Card* a_card);

  // �ָӴϿ��� ��ī�带 �ϳ� ������.
  Card* GetPIfPossible();

  // �� �����ϰ� ���� ���¸� �����Ѵ�.
  void DeclareGo(int score_when_declare_go);

  // ���� �÷��̾ �� �� �ִ� ī�带 ���ڿ��� ��´�.
  const std::string ToStringForAvailableCards();

  // �ָӴϿ� �ִ� ī����� ������ ���ڿ��� ��ȯ�Ѵ�.
  const std::string ToStringForPockets();

  // �÷��̾ �� ī�带 �����Ͽ� ����.
  // ������ �÷��̾ �� �Ͽ� �ѹ��� ī�带 ������ �����Ѵ�.
  Card* DropCard(int selected_card_order);

  // �÷��̾��� �ָӴϸ� ����.
  void CleanPocketsAndResetScore();

  // Getters
  std::vector<Card*>* available_cards();
  Pocket* pockets_for_cards();
  State* current_state();

  // Setters
  void set_avilable_cards(std::vector<Card*>* new_available_cards);
  

 private:
  std::vector<Card*>* available_cards_;
  Pocket* pockets_for_cards_;
  State* current_state_;
};

#endif  // _PLAYER_H_
