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

class Random : public Solution
{
public:
  static bool once;

  void findSecretWord(vector<string>& wordlist, Master& master)
  {
    list<string> mayUsed(wordlist.begin(), wordlist.end());

    int found = 0;
    while (!mayUsed.empty() && found != 6)
    {
      string cur = mayUsed.front();
      mayUsed.pop_front();

      found = master.guess(cur);

      for (auto i=mayUsed.begin(); i!=mayUsed.end(); )
        if (match(cur, mayUsed.front()) != found)
          i = mayUsed.erase(i);
        else
          i++;
    }
  }
};

bool Random::once = Random::regSolution("Random", Random::createSolution<Random> );


};
