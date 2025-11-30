#pragma once

#include <array>
#include <list>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef array<array<int, 3>, 3> Board;
typedef pair<pair<Board, Board>, int> State;

struct Cmp {
  bool operator()(State&, State&);
};

class Solver {
  Board* board;
  Board* goal;
  set<Board> visited;
  map<Board, Board> parent;
  list<Board> paths;
  list<Board>::iterator path;

  bool visit(Board);
  void savePath(Board);
  void solve(int);

  static bool isSafe(int i, int j);
  static int manhattan(Board board, Board goal, int moves);
  static vector<Board> neighbours(Board);

 public:
  Solver(Board* board, Board* goal);
  void solve();
  Board getStep();
  void firstStep();
  void prevStep();
  void nextStep();
  void lastStep();

  friend Cmp;
};
