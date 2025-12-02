#include "score.hpp"

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

string Score::fileName = "scores.dat";
double Score::scale = 100000.0;

void Score::save(string n, Timestamp ts, int moves) {
  std::fstream file;

  strcpy(name, n.substr(0, 31).c_str());
  double duration =
      chrono::duration_cast<chrono::duration<double>>(chrono::system_clock::now() - ts)
          .count();

  file.open(fileName, ios::binary | ios::out | ios::app);

  if (file) {
    auto today = floor<chrono::days>(chrono::system_clock::now());
    std::chrono::year_month_day ymd{today};

    score = round(scale / (duration + moves));
    sprintf(date, "%.2d/%.2d/%.4d", (unsigned)ymd.day(), (unsigned)ymd.month(),
            (int)ymd.year());

    file.write(reinterpret_cast<char*>(this), sizeof(Score));

    file.close();
  }
}

string Score::getName() { return string(name); }

string Score::getDate() { return string(date); }

double Score::getScore() { return score; }

bool Score::operator<(const Score& comp) const { return score > comp.score; }

set<Score> Score::getAll() {
  set<Score> res;
  fstream file;
  int i = 0;

  file.open(fileName, ios::binary | ios::in);

  if (file)
    while (!file.eof()) {
      Score score;
      file.read(reinterpret_cast<char*>(&score), sizeof(Score));

      res.insert(score);
    }

  return res;
}
