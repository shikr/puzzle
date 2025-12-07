#pragma once

#include <array>
#include <list>
#include <map>
#include <vector>

using namespace std;

typedef array<array<int, 3>, 3> Board;
typedef pair<int, Board> State;

class Solver {
  Board* board;
  Board* goal;
  list<Board> paths;
  list<Board>::iterator path;

  int manhattan(Board state);
  void savePath(map<Board, Board>, Board);

  static bool isSafe(int i, int j);
  static vector<Board> neighbours(Board);

 public:
  Solver(Board* board, Board* goal);
  void solve();
  Board getStep();
  void firstStep();
  void prevStep();
  void nextStep();
  void lastStep();
};
