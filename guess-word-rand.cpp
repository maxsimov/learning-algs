#include "guess-word-solution.h"

namespace GuessWord {

class BruteForce : public Solution
{
public:
  static bool once;

  void findSecretWord(vector<string>& wordlist, Master& master)
  {
    list<string> mayUsed(wordlist.begin(), wordlist.end());

    int found = 0;
    while (!mayUsed.empty() && found != 6)
    {
      found = master.guess(mayUsed.front());
      mayUsed.pop_front();
    }
  }
};

bool BruteForce::once = BruteForce::regSolution("BruteForce", BruteForce::createSolution<BruteForce> );


};
