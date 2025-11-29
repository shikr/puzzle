#pragma once

#include <ftxui/component/component.hpp>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class GameScreen final : public BaseScreen {
  ftxui::Component container;
  void rebuild();

 public:
  GameScreen(AppManager*);
  ftxui::Component render();
};
