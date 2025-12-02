#pragma once

#include <ftxui/component/component.hpp>
#include <string>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

class CompletedScreen final : public BaseScreen {
  bool input = false;
  std::string name;
  std::string errorMessage;

  ftxui::Component inputModal();

 public:
  CompletedScreen(AppManager*);

  ftxui::Component render() override;
};
