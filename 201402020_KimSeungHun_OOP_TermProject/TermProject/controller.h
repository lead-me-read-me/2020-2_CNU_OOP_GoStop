#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//#include "player.h"
#include "board.h"
#include "judge.h"

class Controller {
 public:
  // Constructor
  Controller();

  // Destructor
  ~Controller();

  // a_player�� �����̴�.
  void PlayOf(Player* a_player, Player* opponent_player);
  
  // 1. ī�� ����� (48��)
  // 2. ī�带 �÷��̾�� 10�徿 �������ֱ�.
  // 3. ī�� 8���� ���� �ٴڿ� ��Ƶα�.
  void InitSetting();

  // ������ ���� �����Ѵ�.
  void PlayGame();

  void Run();

 private:
  Player player_A_;
  Player player_B_;
  Board board_;
  Judge judge_;
};

#endif  // _CONTROLLER_H_
