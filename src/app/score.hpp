#pragma once

#include <chrono>
#include <set>
#include <string>

typedef std::chrono::time_point<std::chrono::system_clock> Timestamp;

class Score {
  char name[32];
  char date[11];
  double score;
  static std::string fileName;
  static double scale;

 public:
  void save(std::string, Timestamp, int);
  std::string getName();
  std::string getDate();
  double getScore();
  bool operator<(const Score&) const;

  static std::set<Score> getAll();
};
