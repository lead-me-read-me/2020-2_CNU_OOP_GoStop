#ifndef _POCKET_H_
#define _POCKET_H_

#include <list>

#include "card.h"

class Pocket {
 public:
  // Constructor
  Pocket();

  // Destuctor
  ~Pocket();

  // �� �ָӴ��� ī�带 ����(delete)�Ѵ�.
  void DeleteAllCardsInEachPocket();

  // �ָӴϿ� ī�带 �ִ´�.
  void AddCard(Card* a_card);
  
  // �ָӴϿ� �ִ� ī����� ���ڿ��� ��´�.
  const std::string ToStringForPockets();

  // �Ǹ� ��� �ָӴϿ��� �Ǹ� �ϳ� ������.
  Card* GetPIfPossible();

  // Getters
  const std::list<Card*>* pocket_for_gwang();
  const std::list<Card*>* pocket_for_animals();
  const std::list<Card*>* pocket_for_dan();
  const std::list<Card*>* pocket_for_p();

 private:
  std::list<Card*>* pocket_for_gwang_;
  std::list<Card*>* pocket_for_animals_;
  std::list<Card*>* pocket_for_dan_;
  std::list<Card*>* pocket_for_p_;

  // ��, ����, ��, �� �ָӴϿ� �ִ� ���ڿ��� ��´�.
  const std::string ToStringForGwangPocket();
  const std::string ToStringForAnimalsPocket();
  const std::string ToStringForDanPocket();
  const std::string ToStringForPPocket();

  // ī�� �ĺ� ��, �´� �ָӴϿ� ī�带 �ִ´�.
  void AddGwang(Card* a_card);
  void AddAnimal(Card* a_card);
  void AddDan(Card* a_card);
  void AddP(Card* a_card);

  // �Ǹ� ��� �ָӴϰ� ����ִ��� Ȯ���Ѵ�.
  bool PocketPIsEmpty();
};

#endif  // _POCKET_H_
