#pragma once

#include <array>
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
  Component buttons;

  std::array<std::string, 2> boards;
  std::array<std::string, 2>::iterator it;
  std::string boardInput;
  std::string modalTitle;
  std::string errorMessage;
  bool showModal = false;

  ftxui::Component inputModal();
  void resetInput();

 public:
  StartScreen(AppManager*);
  ftxui::Component render();
};
