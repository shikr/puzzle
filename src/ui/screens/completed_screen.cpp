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
  auto buttons = Button(
                     "Salir", [&] { app->exit(); }, ButtonOption::Animated(Color::Red)) |
                 borderEmpty;

  return Renderer(buttons, [&, buttons] {
    return vbox(
        {filler(),
         hbox({filler(),
               vbox({paragraph(LABEL), hbox({filler(), buttons->Render(), filler()})}),
               filler()}),
         filler()});
  });
}
