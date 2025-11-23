#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

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

int main() {
  auto screen = ScreenInteractive::FullscreenAlternateScreen();
  int selected = 0;

  std::vector<std::string> entries = {"Fácil", "Normal", "Difícil"};

  auto buttons = Container::Horizontal(
      {Button(
           "Iniciar", [] {}, ButtonOption::Animated(Color::Green)) |
           borderEmpty,
       Button("Salir", screen.ExitLoopClosure(), ButtonOption::Animated(Color::Red)) |
           borderEmpty});

  MenuOption menuOption;
  menuOption.on_enter = [&] { buttons->TakeFocus(); };
  auto menu = Menu(&entries, &selected, menuOption);

  auto layout = Container::Vertical({menu, buttons});

  auto component = Renderer(layout, [&] {
    return vbox({
        filler(),
        hbox({filler(),
              vbox({paragraph(LOGO), menu->Render(),
                    hbox({filler(), buttons->Render(), filler()})}),
              filler()}),
        filler(),
    });
  });

  screen.Loop(component);
}
