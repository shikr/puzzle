#include "app_manager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>

#include "../ui/screens/game_screen.hpp"
#include "../ui/screens/start_screen.hpp"

AppManager::AppManager()
    : screen(ftxui::ScreenInteractive::FullscreenAlternateScreen()) {}

void AppManager::run() {
  auto component = ftxui::Container::Tab(
      {StartScreen(this).render(), GameScreen(this).render()}, &screenId);

  screen.Loop(component);
}

void AppManager::exit() { screen.Exit(); }

void AppManager::redirect(std::string name) {
  if (name == "start") screenId = 0;
  if (name == "game") screenId = 1;
}
