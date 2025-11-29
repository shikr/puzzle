#pragma once

#include <ftxui/component/screen_interactive.hpp>
#include <string>

#include "puzzle.hpp"

class AppManager {
  ftxui::ScreenInteractive screen;
  Puzzle puzzle;
  int screenId = 0;

 public:
  AppManager();

  void run();
  void newRandomGame();
  bool isCompleted();
  bool moveTile(int i, int j);
  Board getBoard();
  void exit();
  void redirect(std::string screenName);
};
