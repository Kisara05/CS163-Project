#ifndef DATA_H
#define DATA_H
#include <string>

class Data {
public:
  Data();
  Data(std::string word);
  virtual ~Data();
  virtual std::string getWord();
  std::string word;
};

class Word : Data {
public:
  Word();
  Word(std::string word);
  ~Word();
};

#endif // DATA_H
