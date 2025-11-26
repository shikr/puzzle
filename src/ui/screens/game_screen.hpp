#pragma once

#include <ftxui/component/component.hpp>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class GameScreen final : public BaseScreen {
  std::array<std::array<int, 3>, 3> board;
  ftxui::Component container;

  void shuffleBoard();
  bool isEmpty(int i, int j);
  bool swapEmpty(int i, int j);
  bool completed();
  void rebuild();

 public:
  GameScreen(AppManager*);
  ftxui::Component render();
};
