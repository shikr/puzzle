#include "game_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "../../app/puzzle.hpp"
#include "base_screen.hpp"

using namespace ftxui;

GameScreen::GameScreen(AppManager* appManager)
    : BaseScreen(appManager),
      labels(3, std::vector<std::string>(3)),
      container(Container::Vertical({})) {
  for (int i = 0; i < 3; ++i) {
    Component row = Container::Horizontal({});
    for (int j = 0; j < 3; ++j) {
      ButtonOption opt;

      opt.label = &labels[i][j];
      opt.on_click = [&, i, j] {
        if (app->moveTile(i, j) && app->isCompleted()) app->redirect("completed");
      };

      row->Add(Button(opt));
    }
    container->Add(row);
  }
}

Component GameScreen::render() {
  return Renderer(container, [&] {
    Board board = app->getBoard();

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        int value = board[i][j];

        labels[i][j] = " " + (value == 0 ? " " : std::to_string(value)) + " ";
      }
    }

    return vbox(filler(), hbox(filler(), container->Render(), filler()), filler());
  });
}
