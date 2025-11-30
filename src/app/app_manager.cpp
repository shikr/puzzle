#include "app_manager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <string>
#include <thread>

#include "../ui/screens/completed_screen.hpp"
#include "../ui/screens/game_screen.hpp"
#include "../ui/screens/solver_screen.hpp"
#include "../ui/screens/start_screen.hpp"

AppManager::AppManager()
    : screen(ftxui::ScreenInteractive::FullscreenAlternateScreen()) {}

void AppManager::run() {
  StartScreen startScreen(this);
  GameScreen gameScreen(this);
  SolverScreen solverScreen(this);
  CompletedScreen completedScreen(this);

  auto component =
      ftxui::Container::Tab({startScreen.render(), gameScreen.render(),
                             solverScreen.render(), completedScreen.render()},
                            &screenId) |
      ftxui::Modal(Renderer([&] { return ftxui::text("Resolviendo..."); }), &loading);

  screen.Loop(component);
}

void AppManager::solve() {
  loading = true;
  std::thread([&] {
    puzzle.solve();
    loading = false;
    redirect("solver");
  }).detach();
}

Board AppManager::getStep() { return puzzle.getStep(); }

void AppManager::firstStep() { puzzle.firstStep(); }

void AppManager::prevStep() { puzzle.prevStep(); }

void AppManager::nextStep() { puzzle.nextStep(); }

void AppManager::lastStep() { puzzle.lastStep(); }

void AppManager::newRandomGame() { puzzle.useRandomBoard(); }

bool AppManager::setBoard(Board board, Board goal) {
  return puzzle.useBoard(board, goal);
}

bool AppManager::isCompleted() { return puzzle.isCompleted(); }

bool AppManager::moveTile(int i, int j) { return puzzle.swapEmpty(i, j); }

Board AppManager::getBoard() { return puzzle.getBoard(); }

void AppManager::exit() { screen.Exit(); }

void AppManager::redirect(std::string name) {
  if (name == "start") screenId = 0;
  if (name == "game") screenId = 1;
  if (name == "solver") screenId = 2;
  if (name == "completed") screenId = 3;
}
