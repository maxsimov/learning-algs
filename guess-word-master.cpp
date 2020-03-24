#include "guess-word-master.h"

namespace GuessWord {

int match(const string &a, const string &b)
{
  if (a.size() != b.size())
    return 0;

  int res = 0;
  int len = a.size();
  for (int i=0; i<len; i++)
    if (a[i] == b[i])
      res++;
  
  return res;
}

Master::Master()
{
}

void Master::init(int words)
{
  wordList.clear();

  wordList.resize(words, string(wordSize, 'a'));
  for (int i=0; i<words; i++)
    for (int j=0; j<wordSize; ++j)
      wordList[i][j] = 'a' + (gen() % 26);
  secret = wordList[gen() % wordList.size()];
}

void Master::start()
{
  res = Result();
  res.timeStart = Clock::now();
}

int Master::guess(string word)
{
  res.attemps.push_back(word);
  int n = match(word, secret);
  if (n == wordSize)
    res.found = true;

  return n;
}
  
void Master::end()
{
  res.timeEnd = Clock::now();
}

};