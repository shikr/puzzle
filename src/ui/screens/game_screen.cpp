#include "game_screen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../app/app_manager.hpp"
#include "base_screen.hpp"

using namespace ftxui;

static std::random_device rd;
static std::mt19937 eng(rd());
static std::uniform_int_distribution board_number(1, 8);
static std::uniform_int_distribution board_index(0, 8);

GameScreen::GameScreen(AppManager* appManager) : BaseScreen(appManager) {
  shuffleBoard();
}

void GameScreen::shuffleBoard() {
  std::set<int> numbers;
  int i = 0;

  while (numbers.size() < 8) {
    int n = board_number(eng);
    if (numbers.insert(n).second) {
      int row = i / 3;
      int col = i % 3;
      board[row][col] = n;
      i++;
    }
  }
  // El ultimo siempre sera 9 (vacio)
  board[2][2] = 9;

  // Coloca el 9 en un lugar aleatorio
  int empty = board_index(eng);
  int row = empty / 3;
  int col = empty % 3;
  std::swap(board[2][2], board[row][col]);
}

bool GameScreen::isEmpty(int i, int j) {
  if (i < 0 || j < 0 || i > 2 || j > 2) return false;
  return board[i][j] == 9;
}

bool GameScreen::swapEmpty(int i, int j) {
  if (board[i][j] == 9) return false;

  std::vector<std::pair<int, int>> pairs = {
      {i - 1, j}, {i, j - 1}, {i, j + 1}, {i + 1, j}};

  for (const auto pair : pairs) {
    if (isEmpty(pair.first, pair.second)) {
      std::swap(board[i][j], board[pair.first][pair.second]);
      return true;
    }
  }

  return false;
}

bool GameScreen::completed() {
  for (int i = 0; i < board.size(); i++) {
    const auto row = board[i];
    for (int j = 0; j < row.size(); j++) {
      const auto cell = row[j];
      if (cell - 1 != row.size() * i + j) return false;
    }
  }
  return true;
}

void GameScreen::rebuild() {
  container->DetachAllChildren();

  for (int i = 0; i < board.size(); i++) {
    const auto row = board[i];
    Component curr = Container::Horizontal({});

    for (int j = 0; j < row.size(); j++) {
      const auto cell = row[j];

      curr->Add(Button(" " + (cell == 9 ? " " : std::to_string(cell)) + " ", [&, i, j] {
        if (swapEmpty(i, j)) {
          if (completed()) app->redirect("completed");
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
