#include <algorithm>
#include "guess-word-solution.h"

namespace GuessWord {

class MinMax : public Solution
{
public:
  static bool once;

  void findSecretWord(vector<string>& wordlist, Master& master)
  {
    vector<vector<int>> matchTable;
    int len = wordlist.size();

    matchTable.resize(len, vector<int>(len));

    for (int i=0; i<len; i++)
      for (int j=0; j<len; j++)
        matchTable[i][j] = match(wordlist[i], wordlist[j]);

    list<int> notUsed(len);
    iota(notUsed.begin(), notUsed.end(), 0);

    while (!notUsed.empty())
    {
      auto next = notUsed.begin();
      int maxMatches = notUsed.size();
      
      for (auto i=notUsed.begin(); i != notUsed.end(); i++)
      {
        if (i == next)
          continue;

        vector<int> freq(Master::wordSize);
        
        for (auto j=notUsed.begin(); j != notUsed.end(); j++)
        {
          if (j == i)
            continue;
          freq[matchTable[*i][*j]]++;
        }

        int largest = *max_element(freq.begin(), freq.end());

        if (largest < maxMatches)
        {
          maxMatches = largest;
          next = i;
        }
      }

      int guessIndex = *next;
      notUsed.erase(next);

      int distance = master.guess(wordlist[guessIndex]);

      for (auto i=notUsed.begin(); i!=notUsed.end(); )
        if (matchTable[guessIndex][*i] != distance)
          i = notUsed.erase(i);
        else
          i++;
    }

  }
};

bool MinMax::once = MinMax::regSolution("MinMax", MinMax::createSolution<MinMax> );



};
