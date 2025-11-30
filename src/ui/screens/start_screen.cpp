#include "start_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "../../app/app_manager.hpp"
#include "../../app/puzzle.hpp"
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
           "Iniciar",
           [&] {
             app->newRandomGame();
             app->redirect("game");
           },
           ButtonOption::Animated(Color::Green)) |
           borderEmpty,
       Button(
           "Resolver",
           [&] {
             modalTitle = "Inicio:";
             showModal = true;
           },
           ButtonOption::Animated(Color::Yellow)) |
           borderEmpty,
       Button(
           "Salir", [&] { app->exit(); }, ButtonOption::Animated(Color::Red)) |
           borderEmpty});

  menuOption.on_enter = [&] { buttons->TakeFocus(); };
  menu = Menu(&level_entries, &selected, menuOption);

  layout = Container::Vertical({menu, buttons});

  return Renderer(layout,
                  [&] {
                    return vbox({
                        filler(),
                        hbox({filler(),
                              vbox({paragraph(LOGO), menu->Render(),
                                    hbox({filler(), buttons->Render(), filler()})}),
                              filler()}),
                        filler(),
                    });
                  }) |
         Modal(inputModal(), &showModal);
}

Component StartScreen::inputModal() {
  it = boards.begin();
  auto button = Button("Aceptar", [&] {
    *it = boardInput;
    boardInput = "";
    errorMessage = "";
    if (++it != boards.end()) {
      if (!Puzzle::validBoard(Puzzle::deserialize(boards[0]))) {
        errorMessage = "Tabla inicial inválida.";
        it = boards.begin();
      } else
        modalTitle = "Meta:";
    } else if (!Puzzle::validBoard(Puzzle::deserialize(boards[1]))) {
      errorMessage = "Tabla meta inválida.";
      it--;
    } else if (boards[0].substr(0, 9) == boards[1].substr(0, 9)) {
      errorMessage = "Ambos tableros son iguales.";
      resetInput();
    } else if (!app->setBoard(Puzzle::deserialize(boards[0]),
                              Puzzle::deserialize(boards[1]))) {
      errorMessage = "No se puede resolver el tablero.";
      resetInput();
    } else {
      showModal = false;
      app->solve();
      resetInput();
    }
  });
  auto input = Input(&boardInput, "Ejemplo: 013425786") | size(WIDTH, GREATER_THAN, 30);
  auto content = Container::Vertical({input, button});

  return Renderer(content, [&, input, button] {
    std::vector<Element> elements;

    elements.push_back(text(modalTitle));
    if (!errorMessage.empty()) elements.push_back(text(errorMessage) | color(Color::Red));
    elements.push_back(input->Render());
    elements.push_back(hbox({filler(), button->Render(), filler()}));

    return vbox(std::move(elements)) | borderRounded;
  });
}

void StartScreen::resetInput() {
  modalTitle = "Inicio:";
  boards.fill("");
  it = boards.begin();
}
