#include "state.h"

#define STD_FOR_WIN 7

State::State() : number_of_go_(0), std_score_for_win_(STD_FOR_WIN) {}
State::~State() {}

// �� ��ĥ������ �� Ƚ���� 1 �ø��� �¸��� ���� ������ 1 �ø���.
void State::ChangeStateForGo(int score_when_declare_go) {
  set_number_of_go(number_of_go() + 1);
  set_std_for_win(score_when_declare_go + 1);
}

// Getters
const int State::number_of_go() { return number_of_go_; }
const int State::std_for_win() { return std_score_for_win_; }

// Setters
void State::set_number_of_go(int new_number_of_go) {
  number_of_go_ = new_number_of_go;
}
void State::set_std_for_win(int new_std_score_for_win) {
  std_score_for_win_ = new_std_score_for_win;
}
