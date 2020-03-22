#include "guess-word-master.h"
#include "guess-word-solution.h"

using namespace GuessWord;

const int maxTestCases = 100;

struct TestSuite
{
  TestSuite(const SolutionList &solutions)
  {
    for (auto c: solutions)
    {
      masters.push_back(make_pair(c.first, c.second()));
    }
  }

  ~TestSuite()
  {
    for (auto c: masters)
    {
      delete c.second;
    }
  }

private:
  list<pair<string,Solution *>> masters;
};

int main()
{
  TestSuite tests(solutionLists());

  return 0;
}