#include "guess-word-solution.h"

namespace GuessWord {

static SolutionList solList;

Solution::Solution()
{

}

Solution::~Solution()
{
}

bool Solution::regSolution(const string &name, Solution * (*ctor)())
{
  solList.push_back(make_pair(name, ctor));
  return true;
}

const SolutionList &solutionLists()
{
  return solList;
}


};