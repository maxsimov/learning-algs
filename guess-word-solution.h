#pragma once

#include "guess-word-master.h"

namespace GuessWord {

class Solution
{
protected:
  template <class T>
  static Solution *createSolution()
  {
    return new T;
  }
  static bool regSolution(const string &name, Solution * (*ctor)());

public:
  Solution();
  virtual ~Solution();
  virtual void findSecretWord(vector<string>& wordlist, Master& master) = 0;
};

typedef list<pair<string, Solution * (*)()>> SolutionList;

const SolutionList &solutionLists();

};