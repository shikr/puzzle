#pragma once

#include <ftxui/component/component.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class GameScreen final : public BaseScreen {
  ftxui::Component container;
  std::vector<std::vector<std::string>> labels;

 public:
  GameScreen(AppManager*);
  ftxui::Component render();
};
