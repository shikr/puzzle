#include "game_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

#include "../../app/app_manager.hpp"
#include "../../app/puzzle.hpp"
#include "base_screen.hpp"

using namespace ftxui;

GameScreen::GameScreen(AppManager* appManager) : BaseScreen(appManager) {}

void GameScreen::rebuild() {
  container->DetachAllChildren();

  Board board = app->getBoard();

  for (int i = 0; i < board.size(); i++) {
    const auto row = board[i];
    Component curr = Container::Horizontal({});

    for (int j = 0; j < row.size(); j++) {
      const auto cell = row[j];

      curr->Add(Button(" " + (cell == 0 ? " " : std::to_string(cell)) + " ", [&, i, j] {
        if (app->moveTile(i, j)) {
          if (app->isCompleted()) app->redirect("completed");
          rebuild();
        }
      }));
    }
    container->Add(curr);
  }
}

Component GameScreen::render() {
  container = Container::Vertical({});
  rebuild();

  return Renderer(container, [&] {
    return vbox(filler(), hbox(filler(), container->Render(), filler()), filler());
  });
}
