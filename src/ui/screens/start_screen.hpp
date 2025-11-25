#pragma once

#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

class StartScreen final : public BaseScreen {
  static std::vector<std::string> level_entries;
  int selected;
  MenuOption menuOption;
  Component buttons;
  Component menu;
  Component layout;

 public:
  StartScreen(AppManager*);
  ftxui::Component render();
};
