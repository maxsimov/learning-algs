#include <algorithm>
#include <array>
#include <cinttypes>
#include "guess-word-solution.h"

namespace GuessWord {

class Freq : public Solution
{
public:
  static bool once;

  void findSecretWord(vector<string>& wordlist, Master& master)
  {
    const int MChars = 26;
    const int WLen = 6;

    array<array<int, MChars>, WLen> freq;

    for (const auto &w: wordlist)
    {
      for (int i=0; i<WLen; i++)
        freq[i][w[i]-'a']++;
    }

    vector<int> notUsed(wordlist.size());
    iota(notUsed.begin(), notUsed.end(), 0);

    const auto &getScore = [&](int a) -> int64_t
    {
      int64_t score = 1;
      for (int i=0; i<WLen; i++)
        score *= freq[i][wordlist[a][i]-'a'];
      return score;
    };

    while (!notUsed.empty())
    {
      int next = *max_element(notUsed.begin(), notUsed.end(), [&](int a, int b) -> bool { return getScore(a) < getScore(b); } );
      int distance = master.guess(wordlist[next]);

      if (distance == WLen)
        break;

      const auto &filterWords = [&](int a) -> bool
      {
        bool needRemove = (a == next) || match(wordlist[next], wordlist[a]) != distance;

        if (needRemove)
        {
          for (int i=0; i<WLen; i++)
            --freq[i][wordlist[a][i]-'a'];
        }

        return needRemove;
      }; 

      notUsed.erase(remove_if(notUsed.begin(), notUsed.end(), filterWords), notUsed.end());
    }
  }
};

bool Freq::once = Freq::regSolution("Freq", Freq::createSolution<Freq> );


class Freq2 : public Solution
{
public:
  static bool once;

  string bestCandidate(list<string>& words, vector<vector<int>> &probs, int m_scr = 0, string best = "") {
    for (auto w : words) 
    {
      int score = 1;
      for (auto i = 0; i < 6; ++i) 
        score *= probs[i][w[i] - 'a'];
      if (score > m_scr) 
        m_scr = score, best = w;
    }
    return best;
  }

  void findSecretWord(vector<string>& wordlist, Master& master)
  {
    int res = 0;
    vector<vector<int>> probs(6, vector<int>(26));
    list<string> remWords;
    for (auto w : wordlist) {
      remWords.push_back(w);
      for (auto i = 0; i < 6; ++i) 
        probs[i][w[i] - 'a'] += 1;
    }
  
    while (res < 6) 
    {
      auto candidate = bestCandidate(remWords, probs);
      res = master.guess(candidate);
      for (auto it = remWords.begin(); it != remWords.end();) {
        if (match(*it, candidate) != res) {
          for (auto i = 0; i < 6; ++i) probs[i][(*it)[i] - 'a'] -= 1;
          it = remWords.erase(it);
        }
        else ++it;
      }
    }

  }
};

bool Freq2::once = Freq2::regSolution("Freq2", Freq2::createSolution<Freq2> );

};
