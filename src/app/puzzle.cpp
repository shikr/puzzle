#include "puzzle.hpp"

#include <algorithm>
#include <cmath>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "solver.hpp"

using namespace std;

static random_device rd;
static mt19937 eng(rd());

static int random(int size) {
  uniform_int_distribution dist(0, (int)pow(size, 2) - 1);
  return dist(eng);
}

Puzzle::Puzzle() : Solver(&board, &goal) {}

void Puzzle::useRandomBoard(int size) {
  goal = defaultBoard(size);
  board = randomBoard(goal, size);
}

bool Puzzle::useBoard(Board b, Board g) {
  if (!validBoard(g)) return false;

  if (validBoard(b, g, b.size())) {
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
      if (cell != (row.size() * i + j + 1) % (int)pow(board.size(), 2)) return false;
    }
  }

  return true;
}

Board Puzzle::getBoard() { return board; }

bool Puzzle::isEmpty(int i, int j) { return isSafe(i, j) && board[i][j] == 0; }

bool Puzzle::isSafe(int i, int j) {
  return (i >= 0 && i < board.size() && j >= 0 && j < board[i].size());
}

Board Puzzle::deserialize(string board) {
  Board res(3, vector<int>(3));

  if (board.size() < 9) return res;

  for (int i = 0; i < 9; ++i) {
    int row = i / 3;
    int col = i % 3;

    res[row][col] = board[i] - '0';
  }

  return res;
}

string Puzzle::serialize(Board board) {
  string res;
  for (auto row : board) {
    for (auto cell : row) {
      res.push_back(cell + '0');
    }
  }

  return res;
}

Board Puzzle::randomBoard(int size) {
  Board board(size, vector<int>(size));
  set<int> numbers;
  int i = 0;

  while (numbers.size() < pow(size, 2)) {
    int n = random(size);
    if (numbers.insert(n).second) {
      int row = i / size;
      int col = i % size;
      board[row][col] = n;
      i++;
    }
  }

  return board;
}

Board Puzzle::randomBoard(Board goal, int size) {
  Board board = randomBoard(size);

  if (!validBoard(board, goal, size)) return randomBoard(goal, size);

  return board;
}

Board Puzzle::defaultBoard(int size) {
  Board goal(size, vector<int>(size));
  int n = 1;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      goal[i][j] = n % (int)pow(size, 2);
      n++;
    }
  }
  return goal;
}

int Puzzle::countInversions(Board board) {
  int inversions = 0;
  int size = pow(board.size(), 2);

  for (int i = 0; i < size - 1; ++i) {
    int ix = i / board.size();
    int iy = i % board[ix].size();
    for (int j = i + 1; j < size; ++j) {
      int jx = j / board.size();
      int jy = j % board[jx].size();
      auto icell = board[ix][iy];
      auto jcell = board[jx][jy];
      if (icell != 0 && jcell != 0 && icell > jcell) inversions++;
    }
  }

  return inversions;
}

// usado para verificar al establecer un nuevo tablero
bool Puzzle::validBoard(Board board) {
  int size = board.size();

  if (size < 3) return false;

  if (any_of(board.begin(), board.end(), [=](vector<int> r) { return r.size() != size; }))
    return false;

  return validBoard(board, size);
}

bool Puzzle::validBoard(Board board, int size) {
  set<int> numbers;

  for (auto row : board) {
    for (auto cell : row) {
      if (cell < 0 || cell > pow(size, 2) - 1 || !numbers.insert(cell).second)
        return false;
    }
  }

  return true;
}

// usado al generar un tablero aleatorio y al establecer un tablero a resolver
bool Puzzle::validBoard(Board board, Board goal, int size) {
  if (!validBoard(board, size)) return false;

  int x = countInversions(board) % 2;
  int y = countInversions(goal) % 2;

  return x == y;
}
