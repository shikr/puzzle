#include "start_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

const std::string LOGO =
    " ██▓███   █    ██ ▒███████▒▒███████▒ ██▓    ▓█████ \n"
    "▓██░  ██▒ ██  ▓██▒▒ ▒ ▒ ▄▀░▒ ▒ ▒ ▄▀░▓██▒    ▓█   ▀ \n"
    "▓██░ ██▓▒▓██  ▒██░░ ▒ ▄▀▒░ ░ ▒ ▄▀▒░ ▒██░    ▒███   \n"
    "▒██▄█▓▒ ▒▓▓█  ░██░  ▄▀▒   ░  ▄▀▒   ░▒██░    ▒▓█  ▄ \n"
    "▒██▒ ░  ░▒▒█████▓ ▒███████▒▒███████▒░██████▒░▒████▒\n"
    "▒▓▒░ ░  ░░▒▓▒ ▒ ▒ ░▒▒ ▓░▒░▒░▒▒ ▓░▒░▒░ ▒░▓  ░░░ ▒░ ░\n"
    "░▒ ░     ░░▒░ ░ ░ ░░▒ ▒ ░ ▒░░▒ ▒ ░ ▒░ ░ ▒  ░ ░ ░  ░\n"
    "░░        ░░░ ░ ░ ░ ░ ░ ░ ░░ ░ ░ ░ ░  ░ ░      ░   \n"
    "            ░       ░ ░      ░ ░        ░  ░   ░  ░\n"
    "                  ░        ░                       \n";

StartScreen::StartScreen(AppManager* app) : BaseScreen(app), selected(0) {}

std::vector<std::string> StartScreen::level_entries = {"Fácil", "Normal", "Difícil"};

Component StartScreen::render() {
  buttons = Container::Horizontal(
      {Button(
           "Iniciar", [] {}, ButtonOption::Animated(Color::Green)) |
           borderEmpty,
       Button(
           "Salir", [&] { app->exit(); }, ButtonOption::Animated(Color::Red)) |
           borderEmpty});

  menuOption.on_enter = [&] { buttons->TakeFocus(); };
  menu = Menu(&level_entries, &selected, menuOption);

  layout = Container::Vertical({menu, buttons});

  return Renderer(layout, [&] {
    return vbox({
        filler(),
        hbox({filler(),
              vbox({paragraph(LOGO), menu->Render(),
                    hbox({filler(), buttons->Render(), filler()})}),
              filler()}),
        filler(),
    });
  });
}
