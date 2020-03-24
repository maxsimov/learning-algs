#include <memory>
#include <iostream>
#include "guess-word-master.h"
#include "guess-word-solution.h"
#include <fmt/format.h>

using namespace GuessWord;
using namespace fmt;

const int maxTestCases = 100;
const int maxWords = 100;

struct TestSuite
{
  struct Test
  {
    Test(const string &n, unique_ptr<Solution> s)
      : name(n)
      , sol(move(s))
    {
    }
    
    string name;
    unique_ptr<Solution> sol;

    unsigned successful;
    unsigned failed;

    unsigned minAttempts;
    unsigned maxAttempts;
    unsigned avgAttempts;

    Clock::duration duration;
  };

  TestSuite(const SolutionList &solutions)
  {
    for (auto c: solutions)
    {
      unique_ptr<Solution> sol(c.second());
      sols.emplace_back(new Test(c.first, move(sol) ) );
    }
  }

  ~TestSuite()
  {
  }

  void run()
  {
    master.init(maxWords);
    for (auto &s: sols)
    {
      master.start();
      s->sol->findSecretWord(master.getWordList(), master);
      master.end();

      const auto &r = master.result();

      if (r.found) s->successful++;
       else s->failed++;

      if (s->failed)
        continue;

      if (firstTime)
      {
        s->minAttempts = r.attemps.size();
        s->maxAttempts = r.attemps.size();
        s->avgAttempts = r.attemps.size();
        s->duration = r.timeEnd-r.timeStart;
      } else {
        if (r.attemps.size() < s->minAttempts)
          s->minAttempts = r.attemps.size();
        if (r.attemps.size() > s->maxAttempts)
          s->maxAttempts = r.attemps.size();
        s->avgAttempts += r.attemps.size();
        s->duration += r.timeEnd-r.timeStart;
      }
    }

    firstTime = false;
  }

  void report()
  {
    for (auto &s: sols)
    {
      cout << format("Solution: {}", s->name);

      if (s->failed)
      {
        cout << format(" failed\n");
        continue;
      }

      cout << format(" Avg attempts: {} Min attempts: {} Max attempts: {} Duration: {}\n", 
        double(s->avgAttempts) / double(s->successful),
        s->minAttempts,
        s->maxAttempts,
        chrono::duration_cast<std::chrono::microseconds> (s->duration).count()
        );
    }
  }

private:
  list<unique_ptr<Test>> sols;
  Master master;
  bool firstTime = true;
};

int main()
{
  TestSuite tests(solutionLists());

  for (int i=0; i<maxTestCases; i++)
    tests.run();

  tests.report();

  return 0;
}