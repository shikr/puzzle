#include "puzzle.hpp"

#include <cmath>
#include <random>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static random_device rd;
static mt19937 eng(rd());
static uniform_int_distribution board_index(0, 8);

void Puzzle::useRandomBoard() {
  goal = defaultBoard();
  board = randomBoard(goal);
}

bool Puzzle::useBoard(Board b, Board g) {
  if (!validBoard(g)) return false;

  if (validBoard(b, g)) {
    goal = g;
    board = b;
    return true;
  }

  return false;
}

bool Puzzle::swapEmpty(int i, int j) {
  if (isEmpty(i, j)) return false;

  vector<pair<int, int>> pairs = {{i - 1, j}, {i, j - 1}, {i, j + 1}, {i + 1, j}};

  for (const auto pair : pairs) {
    if (isEmpty(pair.first, pair.second)) {
      swap(board[i][j], board[pair.first][pair.second]);
      return true;
    }
  }

  return false;
}

bool Puzzle::isCompleted() {
  for (int i = 0; i < board.size(); i++) {
    const auto row = board[i];
    for (int j = 0; j < row.size(); j++) {
      const auto cell = row[j];
      if (cell != (row.size() * i + j + 1) % 9) return false;
    }
  }

  return true;
}

Board Puzzle::getBoard() { return board; }

bool Puzzle::isEmpty(int i, int j) { return isSafe(i, j) && board[i][j] == 0; }

bool Puzzle::isSafe(int i, int j) { return (i >= 0 && i < 3 && j >= 0 && j < 3); }

Board Puzzle::randomBoard() {
  Board board;
  set<int> numbers;
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

  return board;
}

Board Puzzle::randomBoard(Board goal) {
  Board board = randomBoard();

  if (!validBoard(board, goal)) return randomBoard(goal);

  return board;
}

Board Puzzle::defaultBoard() {
  Board goal;
  int n = 1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      goal[i][j] = n % 9;
      n++;
    }
  }
  return goal;
}

int Puzzle::countInversions(Board board) {
  int inversions = 0;
  int size = pow(board.size(), 2);

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

bool Puzzle::validBoard(Board board) {
  set<int> numbers;

  for (auto row : board) {
    for (auto cell : row) {
      if (cell < 0 || cell > 8 || !numbers.insert(cell).second) return false;
    }
  }

  return true;
}

bool Puzzle::validBoard(Board board, Board goal) {
  if (!validBoard(board)) return false;

  int x = countInversions(board) % 2;
  int y = countInversions(goal) % 2;

  return x == y;
}
