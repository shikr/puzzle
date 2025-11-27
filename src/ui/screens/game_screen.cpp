#include "game_screen.hpp"

#include <cmath>
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
static std::uniform_int_distribution board_index(0, 8);

GameScreen::GameScreen(AppManager* appManager) : BaseScreen(appManager) {
  shuffleBoard();
}

int GameScreen::countInversions() {
  int inversions = 0;
  int size = std::pow(board.size(), 2);
  for (int i = 0; i < size - 1; ++i) {
    int ix = i / 3;
    int iy = i % 3;
    for (int j = i + 1; j < size; ++j) {
      int jx = j / 3;
      int jy = j % 3;
      auto icell = board[ix][iy];
      auto jcell = board[jx][jy];
      if (icell != 0 && jcell != 0 && icell > jcell) inversions++;
    }
  }

  return inversions;
}

bool GameScreen::validBoard() {
  std::set<int> numbers;

  for (auto row : board) {
    for (auto cell : row) {
      if (cell < 0 || cell > 8 || !numbers.insert(cell).second) return false;
    }
  }

  if (countInversions() % 2 != 0) return false;

  return true;
}

void GameScreen::shuffleBoard() {
  std::set<int> numbers;
  int i = 0;

  while (numbers.size() < 9) {
    int n = board_index(eng);
    if (numbers.insert(n).second) {
      int row = i / 3;
      int col = i % 3;
      board[row][col] = n;
      i++;
    }
  }

  if (!validBoard()) shuffleBoard();
}

bool GameScreen::isEmpty(int i, int j) {
  if (i < 0 || j < 0 || i > 2 || j > 2) return false;
  return board[i][j] == 0;
}

bool GameScreen::swapEmpty(int i, int j) {
  if (board[i][j] == 0) return false;

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
      if (cell != (row.size() * i + j + 1) % 9) return false;
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

      curr->Add(Button(" " + (cell == 0 ? " " : std::to_string(cell)) + " ", [&, i, j] {
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
