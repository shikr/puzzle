#include "completed_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

const std::string LABEL =
    "▄████▄  ▒█████   ███▄ ▄███▓ ██▓███    ██▓    ▓█████▄▄▄█████▓ ▄▄▄     ▓█████▄  "
    "▒█████ \n"
    "▒██▀ ▀█ ▒██▒  ██▒▓██▒▀█▀ ██▒▓██░  ██  ▓██▒    ▓█   ▀▓  ██▒ ▓▒▒████▄   ▒██▀ ██▌▒██▒  "
    "██▒\n"
    "▒▓█    ▄▒██░  ██▒▓██    ▓██░▓██░ ██▓▒ ▒██░    ▒███  ▒ ▓██░ ▒░▒██  ▀█▄ ░██   █▌▒██░  "
    "██▒\n"
    "▒▓▓▄ ▄██▒██   ██░▒██    ▒██ ▒██▄█▓▒ ▒ ▒██░    ▒▓█  ▄░ ▓██▓ ░ ░██▄▄▄▄██░▓█▄   ▌▒██   "
    "██░\n"
    "▒ ▓███▀ ░ ████▓▒░▒██▒   ░██▒▒██▒ ░  ░▒░██████▒░▒████  ▒██▒ ░ ▒▓█   ▓██░▒████▓ ░ "
    "████▓▒░\n"
    "░ ░▒ ▒  ░ ▒░▒░▒░ ░ ▒░   ░  ░▒▓▒░ ░  ░░░ ▒░▓  ░░░ ▒░   ▒ ░░   ░▒▒   ▓▒█ ▒▒▓  ▒ ░ "
    "▒░▒░▒░ \n"
    "  ░  ▒    ░ ▒ ▒░ ░  ░      ░░▒ ░     ░░ ░ ▒  ░ ░ ░      ░    ░ ░   ▒▒  ░ ▒  ▒   ░ ▒ "
    "▒░ \n"
    "░       ░ ░ ░ ▒  ░      ░   ░░          ░ ░      ░    ░        ░   ▒   ░ ░  ░ ░ ░ ░ "
    "▒  \n"
    "░ ░         ░ ░         ░            ░    ░  ░   ░                 ░     ░        ░ "
    "░  \n";

CompletedScreen::CompletedScreen(AppManager* app) : BaseScreen(app) {}

Component CompletedScreen::render() {
  auto buttons = Container::Horizontal(
      {Button(
           "Inicio", [&] { app->redirect("start"); },
           ButtonOption::Animated(Color::Blue)) |
           borderEmpty,
       Button(
           "Guardar", [&] { input = true; }, ButtonOption::Animated(Color::Green)) |
           borderEmpty,
       Button(
           "Salir", [&] { app->exit(); }, ButtonOption::Animated(Color::Red)) |
           borderEmpty});

  return Renderer(
             buttons,
             [&, buttons] {
               return vbox({filler(),
                            hbox({filler(),
                                  vbox({paragraph(LABEL),
                                        hbox({filler(), buttons->Render(), filler()})}),
                                  filler()}),
                            filler()});
             }) |
         Modal(inputModal(), &input);
}

Component CompletedScreen::inputModal() {
  auto container = Container::Vertical({Input(&name), Button("Aceptar", [&] {
                                          if (name.empty())
                                            errorMessage = "Es necesario un nombre.";
                                          else {
                                            app->save(name);
                                            errorMessage = "";
                                            name = "";
                                            input = false;
                                            app->redirect("start");
                                          }
                                        })});

  return Renderer(container, [&, container] {
    std::vector<Element> elements;
    elements.push_back(text("Nombre:"));
    if (!errorMessage.empty()) elements.push_back(text(errorMessage) | color(Color::Red));
    elements.push_back(container->Render());

    return vbox(elements) | borderRounded;
  });
}
