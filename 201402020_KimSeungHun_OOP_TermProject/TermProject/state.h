#ifndef _STATE_H_
#define _STATE_H_

class State {
 public:
  // Constructor
  State();
  // Destructor
  ~State();

  // �� ��ĥ������ �� Ƚ���� 1 �ø��� 
  // �¸� �ּ� ������ �� ��ģ ������ �������� 1�� �ø���.
  void ChangeStateForGo(int score_when_declare_go);

  // Getters
  const int number_of_go();
  const int std_for_win();

  // Setters
  void set_number_of_go(int new_number_of_go);
  void set_std_for_win(int new_std_score_for_win);

 private:
  int number_of_go_; // �� ��ģ Ƚ��
  int std_score_for_win_; // �¸��ϱ� ���� ���� �ּ� ����
};

#endif  // _STATE_H_
