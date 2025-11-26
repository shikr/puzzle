#pragma once

#include <ftxui/component/component.hpp>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class CompletedScreen final : public BaseScreen {
 public:
  CompletedScreen(AppManager*);

  ftxui::Component render() override;
};
