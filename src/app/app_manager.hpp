#pragma once

#include <ftxui/component/screen_interactive.hpp>
#include <set>
#include <string>

#include "puzzle.hpp"
#include "score.hpp"

class AppManager {
  ftxui::ScreenInteractive screen;
  Puzzle puzzle;
  std::set<Score> scores;
  Timestamp start;
  int moves;
  int screenId = 0;
  bool loading = false;

 public:
  AppManager();

  void run();
  void solve();
  void save(std::string);
  set<Score> getScores();
  Board getStep();
  void firstStep();
  void prevStep();
  void nextStep();
  void lastStep();
  void newRandomGame();
  bool setBoard(Board board, Board goal);
  bool isCompleted();
  bool moveTile(int i, int j);
  Board getBoard();
  void exit();
  void redirect(std::string screenName);
};
