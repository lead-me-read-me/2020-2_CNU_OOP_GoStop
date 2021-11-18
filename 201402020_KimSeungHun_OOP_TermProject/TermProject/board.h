#ifndef _BOARD_H_
#define _BOARD_H_

#include <list>
#include <stack>
#include <string>
#include <vector>

//#include "card.h"
#include "player.h"

class Board {
 public:
  // dack�� ���� ������ ���ڿ��� ��ȯ�Ѵ�.
  // (ex) ===============
  //      | Deck (20��) |
  //      ---------------
  std::string ToStringForDeck();

  // �ٴڿ� �� ī����� ���ڿ��� ��ȯ�Ѵ�.
  // (ex) | 8(gwang_normal) | 1(p_normal) | 3(p_noraml) |
  //      | 7(animal_normal) |
  //      ===============================================
  std::string ToStringForFloor();

  // dack���� ī�带 �ϳ� ������.
  Card* DrawCardFromDeck();

  // ���κ��� �Ǹ� �ϳ� ���Ѿƿ´�.
  bool StealPIfPossible(Player* opponent_player,
                        std::list<Card*>* from_board_to_player);

  // Board�� player���� ������ ī�� ����Ʈ�� ��ȯ�Ѵ�.
  std::list<Card*>* CardsToPlayer(Card* card_from_player,
                                Player* opponent_player);

  // dack�� ����ִ��� Ȯ���Ѵ�.
  bool DeckIsEmpty();

  // card�� ��Ī�Ǵ� ī����� floor�� �ִ��� Ȯ���Ͽ� vector�� ��� ��ȯ�Ѵ�.
  std::vector<Card*> MatchedCardsWith(Card* card);

  // from�� �ִ� ī����� ��쿡 ���� to�� �Ű� ��´�.
  void InsertCardsInto(Player* opponent_player, const std::vector<Card*>& from,
                       std::list<Card*>* to);

  // Getters
  std::stack<Card*>* deck();

  // Setters
  void set_floor(std::list<Card*>* new_floor);
  void set_deck(std::stack<Card*>* new_deck);

 private:
  std::stack<Card*>* deck_;
  std::list<Card*>* floor_;
};

#endif  // _BOARD_H_
