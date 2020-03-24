#pragma once

#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <random>

namespace GuessWord {

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

struct Result
{
  list<string> attemps;
  Clock::time_point timeStart;
  Clock::time_point timeEnd;

  bool found;
};

int match(const string &a, const string &b);

class Master
{
  vector<string> wordList;
  string secret;
  Result res;
  mt19937 gen;
  int wordSize = 6;
public:
  Master();

  void init(int words);
  void start();
  int guess(string word);
  void end();

  const Result &result() const
  {
    return res;
  }

  vector<string> &getWordList() 
  {
    return wordList;
  }
};

};