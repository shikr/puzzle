#pragma once

#include <string>

#include "solver.hpp"

using namespace std;

class Puzzle : public Solver {
  Board board;
  Board goal;

  bool isEmpty(int i, int j);

  static bool isSafe(int i, int j);
  static int countInversions(Board);
  static bool validBoard(Board board, Board goal);
  static Board randomBoard();
  static Board randomBoard(Board goal);
  static Board defaultBoard();

 public:
  Puzzle();
  void useRandomBoard();
  bool useBoard(Board board, Board goal);
  bool swapEmpty(int i, int j);
  bool isCompleted();
  Board getBoard();

  static bool validBoard(Board);
  static Board deserialize(string);
  static string serialize(Board);
};
