#pragma once

#include <ftxui/component/component_base.hpp>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class ScoresScreen final : public BaseScreen {
 public:
  ScoresScreen(AppManager*);
  ftxui::Component render();
};
