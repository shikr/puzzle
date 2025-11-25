#pragma once

#include <ftxui/component/screen_interactive.hpp>
#include <string>

class AppManager {
  ftxui::ScreenInteractive screen;
  int screenId = 0;

 public:
  AppManager();

  void run();
  void exit();
  void redirect(std::string screenName);
};
