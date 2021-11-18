#include "controller.h"

#include <iostream>
#include <list>

//#include "player.h"
#include "view.h"

// Constructor
Controller::Controller() : player_A_(), player_B_(), board_(), judge_(){}

// Destructor
Controller::~Controller() {}

// a_player�� �����̴�.
void Controller::PlayOf(Player* a_player, Player* opponent_player) {
  // �� ���ʸ��� deck�� floor�� ������ ����Ѵ�.
  View::PrintBoardDeck(board_.ToStringForDeck());
  View::PrintBoardfloor(board_.ToStringForFloor());

  // ī�带 ���� ��, ���� ī�带 ����Ѵ�.
  View::PrintPlayerAllGettingCards(a_player->ToStringForPockets());

  // �÷��̾ �� �� �ִ� ī�� ������ ����Ѵ�.
  View::PrintStringWithLine(
      "\nAvailable Cards(month_property_specieal_ORDER) : ");
  View::PrintPlayerAvailableCards(a_player->ToStringForAvailableCards());

  // ����ڷκ��� ���ڸ� �Է¹޾� ī�带 ����.
  int player_choice_card_order = View::InputOrderFromPlayerAvailableCards(
      static_cast<int>(a_player->available_cards()->size()));
  Card* selected_card = a_player->DropCard(player_choice_card_order);

  // 1. �� ī�带 ������ ���� �� �ִ� ī����� �÷��̾��� �ָӴϿ� �ִ´�.
  // 2. ���� ī�� ����� ����Ѵ�.
  std::list<Card*>* to_player =
      board_.CardsToPlayer(selected_card, opponent_player);
  View::PrintStringWithoutLine("!! �÷��̾ ������ ī�� ��� : ");
  if (to_player->empty()) {
    View::PrintStringWithLine("����.");
  } else {
    for (Card* card : *to_player) {
      View::PrintStringWithoutLine(card->ToString() + ", ");
      a_player->AddCard(card);
    }
    View::PrintStringWithLine("��.");
  }
  delete to_player; // new in Board::CardsToPlayer

  // ī�带 �� ��, ���� ī�带 ����Ѵ�.
  View::PrintPlayerAllGettingCards(a_player->ToStringForPockets());

  // ������ ����ϰ� ����Ѵ�.
  int score_of_player = judge_.CalcScore(a_player, opponent_player);
  score_of_player += a_player->current_state()->number_of_go();
  View::PrintScore(score_of_player);

  // ������ 7�� �̻��̸� �ش� �÷��̾��� �¸��� �����ϰ� ������ ���� ���� ������
  // �̷������.
  judge_.set_is_game_over(judge_.IsGameOver(score_of_player));

  if (judge_.is_game_over()) {
    char answer_about_go = View::InputUserAnswerAboutGo();
    if (answer_about_go == 'Y' || answer_about_go == 'y') {
      judge_.set_is_game_over(false);
      a_player->DeclareGo(score_of_player);
    }
  }

  // ���� ���� ��, pause�� �ɾ� ����� Ȯ���ϵ��� �Ѵ�.
  View::PrintStringWithoutLine("[ ����� Ȯ���ϰ� �Ѿ����. ]");
  system("PAUSE");
}

// 1. ī�� ����� (48��)
// 2. ī�带 �÷��̾�� 10�徿 �������ֱ�.
// 3. ī�� 8���� ���� �ٴڿ� ��Ƶα�.
void Controller::InitSetting() {
  // deck�� ����.
  judge_.ClearDeck(board_.deck());
  //judge_.Cl

  // �÷��̾ ������ ��� �ִ� �и� ��� ���� ������ 0������ �ʱ�ȭ�Ѵ�.
  player_A_.CleanPocketsAndResetScore();
  player_B_.CleanPocketsAndResetScore();

  // Board deck setting
  board_.set_deck(judge_.InitDeck());

  // Player setting
  player_A_.set_avilable_cards(judge_.CardsForPlayerFromInitDeck(board_.deck()));
  player_B_.set_avilable_cards(judge_.CardsForPlayerFromInitDeck(board_.deck()));

  // Board floor setting
  board_.set_floor(judge_.CardsForBoardFloor(board_.deck()));

  judge_.set_is_game_over(false);
}

// ������ ���� �����Ѵ�.
void Controller::PlayGame() {
  InitSetting();
  while (!judge_.is_game_over()) {
    // A ��
    View::PrintStringWithLine("\n>>> Player A�� �����Դϴ�.");
    PlayOf(&player_A_, &player_B_);
    if (judge_.is_game_over()) {
      View::PrintStringWithLine(
          "\n[ANNOUNCE] Player A�� �¸��� ������ �����մϴ�!");
      break;
    }

    // B ��
    View::PrintStringWithLine("\n>>> Player B�� �����Դϴ�.");
    PlayOf(&player_B_, &player_A_);
    if (judge_.is_game_over()) {
      View::PrintStringWithLine(
          "\n[ANNOUNCE] Player B�� �¸��� ������ �����մϴ�!");
      break;
    }

    if (board_.DeckIsEmpty()) {
      judge_.set_is_game_over(true);
      View::PrintStringWithLine("\n[ANNOUNCE] ���ºη� ������ �����մϴ�!");
    }
  }
}

void Controller::Run() {
  char answer = View::InputUserAnswerAboutGameStart();
  while (answer == 'Y' || answer == 'y') {
    PlayGame();
    answer = View::InputUserAnswerAboutGameStart();
  }
}
