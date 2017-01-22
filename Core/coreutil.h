#ifndef UTIL_H
#define UTIL_H

#include <QString>

const char alphabit[] = {
    '0', '1', '2', '3', '4', '5', '6',  '7', '8', '9', ':', ';', '<', '=', '>',
    '?', '@', 'A', 'B', 'C', 'D', 'E',  'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T',  'U', 'V', 'W', 'X', 'Y', 'Z', '[', ']',
    '^', '_', '`', 'a', 'b', 'c', 'd',  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's',  't', 'u', 'v', 'w', 'x', 'y', 'z', '{',
    '|', '}', '~', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.'};

const int alphabetSize = sizeof(alphabit) / sizeof(char);

inline QString codingNum(uint64_t num) {
  QString result = "";
  if (num == 0)
    result = "0";
  while (num > 0) {
    result += alphabit[num % alphabetSize];
    num = num / alphabetSize;
  }
  return result;
}

#endif  // UTIL_H
