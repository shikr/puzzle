#include "scores_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

ScoresScreen::ScoresScreen(AppManager* appManager) : BaseScreen(appManager) {}

Component ScoresScreen::render() {
  auto button = Button(
      "Inicio", [&] { app->redirect("start"); }, ButtonOption::Animated(Color::Blue));

  return Renderer(button, [&, button] {
    std::vector<std::vector<std::string>> entries = {{"Nombre", "Puntuacion", "Fecha"}};

    for (auto score : app->getScores()) {
      entries.push_back(
          {score.getName(), std::to_string((int)score.getScore()), score.getDate()});
    }

    auto table = Table(entries);

    table.SelectAll().Border();
    table.SelectRow(0).Border();
    table.SelectColumn(0).Border();
    table.SelectColumn(1).Border();

    return vbox(
        {filler(),
         hbox({filler(),
               vbox({table.Render(), hbox({filler(), button->Render(), filler()})}),
               filler()}),
         filler()});
  });
}
