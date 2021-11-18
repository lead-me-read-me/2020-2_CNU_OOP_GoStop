#ifndef _CARD_H_
#define _CARD_H_

#include <string>

class Card {
 public:
  // Constructors
  Card();
  Card(int month, std::string property, std::string special);

  // Destructor
  ~Card();

  // ī��(this)�� ��ȿ���� �Ǵ��Ѵ�.
  bool IsCardValid();

  // ī���� ������ ���ڿ��� ��ȯ�Ѵ�.
  std::string ToString();

  // Getters
  int month();
  const std::string& property();
  const std::string& special();
  const std::string& special() const;

 private:
  const int month_;
  const std::string property_;  // gwang, dan, animal, p
  const std::string special_;  // normal except bird(����), blue(û��), red(ȫ��),
                         // rain(��), double(����)
};

#endif  // _CARD_H_
