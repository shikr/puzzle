#pragma once

#include <ftxui/component/screen_interactive.hpp>
#include <list>
#include <string>

#include "puzzle.hpp"

class AppManager {
  ftxui::ScreenInteractive screen;
  Puzzle puzzle;
  list<Board>::iterator step;
  int screenId = 0;
  bool loading = false;

 public:
  AppManager();

  void run();
  void solve();
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
