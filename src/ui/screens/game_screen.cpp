#include "game_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

GameScreen::GameScreen(AppManager* appManager, int s)
    : BaseScreen(appManager),
      labels(s, std::vector<std::string>(s)),
      container(Container::Vertical({})),
      size(s) {
  for (int i = 0; i < size; ++i) {
    Component row = Container::Horizontal({});
    for (int j = 0; j < size; ++j) {
      ButtonOption opt;

      opt.label = &labels[i][j];
      opt.on_click = [&, i, j] {
        suggestion = INT_MAX;
        if (app->moveTile(i, j) && app->isCompleted()) app->redirect("completed");
      };
      opt.transform = [&, i, j](const EntryState s) {
        auto element = text(s.label) | borderRounded;
        if (s.focused) element |= bgcolor(Color::White) | color(Color::Black);
        if (app->getBoard()[i][j] == suggestion) element |= color(Color::Blue);
        return element;
      };

      row->Add(Button(opt));
    }
    container->Add(row);
  }
}

Component GameScreen::render() {
  auto button = Button(
      "Sugerencia", [&] { suggestion = app->suggest(); },
      ButtonOption::Animated(Color::Yellow));
  auto layout = Container::Vertical({container, button});

  return Renderer(layout, [&, button] {
    Board board = app->getBoard();

    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        int value = board[i][j];

        labels[i][j] = " " + (value == 0 ? " " : std::to_string(value)) + " ";
      }
    }

    return vbox(filler(),
                hbox(filler(), vbox({container->Render(), button->Render()}), filler()),
                filler());
  });
}
