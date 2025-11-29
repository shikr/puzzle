#include "app_manager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>

#include "../ui/screens/completed_screen.hpp"
#include "../ui/screens/game_screen.hpp"
#include "../ui/screens/start_screen.hpp"

AppManager::AppManager()
    : screen(ftxui::ScreenInteractive::FullscreenAlternateScreen()) {}

void AppManager::run() {
  StartScreen startScreen(this);
  GameScreen gameScreen(this);
  CompletedScreen completedScreen(this);

  auto component = ftxui::Container::Tab(
      {startScreen.render(), gameScreen.render(), completedScreen.render()}, &screenId);

  screen.Loop(component);
}

void AppManager::newRandomGame() { puzzle.useRandomBoard(); }

bool AppManager::isCompleted() { return puzzle.isCompleted(); }

bool AppManager::moveTile(int i, int j) { return puzzle.swapEmpty(i, j); }

Board AppManager::getBoard() { return puzzle.getBoard(); }

void AppManager::exit() { screen.Exit(); }

void AppManager::redirect(std::string name) {
  if (name == "start") screenId = 0;
  if (name == "game") screenId = 1;
  if (name == "completed") screenId = 2;
}
