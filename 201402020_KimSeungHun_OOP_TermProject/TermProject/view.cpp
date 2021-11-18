#include "view.h"

#include <iostream>
#include <string>

void View::PrintScore(int a_score) {
  View::PrintStringWithLine(
      "�ش� �÷��̾��� ���� ���� : " + std::to_string(a_score) + "��.");
}

int View::PrintChoicesAndGetCardOrder(std::string card_0_info, std::string card_1_info) {
  View::PrintStringWithLine(">> ��ġ�� ī�� �߻�!");
  View::PrintStringWithLine(">> 0 -> [ " + card_0_info + " ]");
  View::PrintStringWithLine(">> 1 -> [ " + card_1_info + " ]");
  View::PrintStringWithoutLine(">> �� �� �� ī�带 ��� ����������. : ");
  int answer = View::InputInt();
  while (true) {
    if (answer == 0 || answer == 1) {
      return answer;

    } else {
      View::PrintStringWithoutLine(">> [�ٽ� �Է�] �� �� �� ī��(0 �Ǵ� 1)�� ��� ����������. : ");
    }
  }
}

void View::PrintPlayerAvailableCards(std::string available_cards_info) {
  View::PrintStringWithLine(available_cards_info);
}
void View::PrintPlayerAllGettingCards(std::string all_getting_cards_info) {
  View::PrintStringWithLine(all_getting_cards_info);
}

void View::PrintBoardDeck(std::string deck_info) {
  View::PrintStringWithLine(deck_info);
}
void View::PrintBoardfloor(std::string floor_info) {
  View::PrintStringWithLine(floor_info);
}

void View::PrintStringWithLine(std::string a_string) {
  std::cout << a_string << std::endl;
}
void View::PrintStringWithoutLine(std::string a_string) {
  std::cout << a_string;
}

std::string View::InputString() {
  std::string answer = "";
  std::cin >> answer;
  return answer;
}
char View::InputChar() {
  std::string answer = View::InputString();
  char answer_char = answer.at(0);
  return answer_char;
}

char View::InputUserAnswerAboutGameStart() {
  PrintStringWithoutLine(
      "\n!! ������ �����Ϸ��� \'Y\'�Ǵ� \'y\'�� �Է��ϼ���.(�����Ϸ��� "
      "�ƹ�Ű�� ��������.) : ");
  return View::InputChar();
}

char View::InputUserAnswerAboutGo() {
  PrintStringWithoutLine(
      "\n!! [ANNOUNCE] Go�� �Ϸ��� \'Y\'�Ǵ� \'y\'�� �Է��ϼ���.(Stop�Ϸ��� "
      "�ƹ�Ű�� ��������.) : ");
  return View::InputChar();
}

int View::InputInt() {
  int answer = 0;
  while (true) {
    std::cin >> answer;
    if (std::cin.fail()) {  // 1. std::cin �Է��� ���������� ó������ ���,
      std::cin.clear();           // 2. std::cin ���¸� �ʱ�ȭ�ϰ�
      fseek(stdin, 0, SEEK_END);  // 3. �Է� ���۸� �ʱ�ȭ�Ѵ�.
      View::PrintStringWithoutLine(">> [�ٽ� �Է�] ���ڸ� �Է��ؾ��մϴ�.");

      continue;

    } else {
      return answer;
    }
  }
}

int View::InputOrderFromPlayerAvailableCards(int bound) {
  View::PrintStringWithoutLine(">> �� ī���� �ε����� �Է��ϼ���. : ");
  while (true) {
    int answer = View::InputInt();

    if (answer < 0 || answer >= bound)
      View::PrintStringWithoutLine(
          ">> [�ٽ� �Է�] �� �� �ִ� ī����� �ε����� ������ϴ�. : ");
    else
      return answer;
  }
}

View::View() {}
