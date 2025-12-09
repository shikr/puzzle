#pragma once

#include <list>
#include <map>
#include <vector>

using namespace std;

typedef vector<vector<int>> Board;
typedef pair<int, Board> State;

class Solver {
  Board* board;
  Board* goal;
  list<Board> paths;
  list<Board>::iterator path;

  bool isSafe(int i, int j);
  int manhattan(Board state);
  vector<Board> neighbours(Board);
  void savePath(map<Board, Board>, Board);

 public:
  Solver(Board* board, Board* goal);
  void solve();
  Board getStep();
  void firstStep();
  void prevStep();
  void nextStep();
  void lastStep();
};
