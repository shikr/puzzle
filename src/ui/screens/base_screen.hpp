#pragma once

#include <ftxui/component/component_base.hpp>

#include "../../app/app_manager.hpp"

class BaseScreen {
 protected:
  AppManager* app;

 public:
  BaseScreen(AppManager*);
  virtual ~BaseScreen() = default;

  virtual ftxui::Component render() = 0;
};
