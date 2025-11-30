#pragma once

#include <array>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef array<array<int, 3>, 3> Board;
typedef pair<pair<Board, Board>, int> State;

struct Cmp {
  bool operator()(State&, State&);
};

class Puzzle {
  Board board;
  Board goal;
  set<Board> visited;
  map<Board, Board> parent;
  list<Board> paths;
  list<Board>::iterator path;

  bool isEmpty(int i, int j);
  bool visit(Board);
  void savePath(Board);
  void solve(int);

  static bool isSafe(int i, int j);
  static int countInversions(Board);
  static bool validBoard(Board board, Board goal);
  static Board randomBoard();
  static Board randomBoard(Board goal);
  static Board defaultBoard();
  static int manhattan(Board board, Board goal, int moves);
  static vector<Board> neighbours(Board);

 public:
  void useRandomBoard();
  bool useBoard(Board board, Board goal);
  void solve();
  bool swapEmpty(int i, int j);
  bool isCompleted();

  Board getBoard();
  Board getStep();
  void firstStep();
  void prevStep();
  void nextStep();
  void lastStep();

  static bool validBoard(Board);
  static Board deserialize(string);
  static string serialize(Board);

  friend Cmp;
};
