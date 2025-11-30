#include "solver_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ranges>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

SolverScreen::SolverScreen(AppManager* appManager) : BaseScreen(appManager) {}

Component SolverScreen::render() {
  auto container = Container::Horizontal({Button(" << ", [&] { app->firstStep(); }),
                                          Button(" < ", [&] { app->prevStep(); }),
                                          Button(" > ", [&] { app->nextStep(); }),
                                          Button(" >> ", [&] { app->lastStep(); })});

  return Renderer(container, [&, container] {
    std::vector<std::vector<Element>> rows;

    for (auto row : app->getStep()) {
      auto t =
          row | std::views::transform([](int n) {
            return text(" " + (n != 0 ? std::to_string(n) : " ") + " ") | borderRounded;
          });

      rows.push_back(std::vector<Element>(t.begin(), t.end()));
    }

    return hbox({filler(), vbox({filler(), gridbox(rows), container->Render(), filler()}),
                 filler()});
  });
}
