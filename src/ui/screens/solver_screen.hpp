#pragma once

#include <ftxui/component/component.hpp>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class SolverScreen final : public BaseScreen {
 public:
  SolverScreen(AppManager*);
  ftxui::Component render();
};
