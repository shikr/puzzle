#pragma once

#include <string>

#include "solver.hpp"

using namespace std;

class Puzzle : public Solver {
  Board board;
  Board goal;

  bool isEmpty(int i, int j);
  bool isSafe(int i, int j);

  static int countInversions(Board);
  static bool validBoard(Board board, int size);
  static bool validBoard(Board board, Board goal, int size);
  static Board randomBoard(int size);
  static Board randomBoard(Board goal, int size);
  static Board defaultBoard(int size);

 public:
  Puzzle();
  void useRandomBoard(int size);
  bool useBoard(Board board, Board goal);
  bool swapEmpty(int i, int j);
  bool isCompleted();
  Board getBoard();

  static bool validBoard(Board);
  static Board deserialize(string);
  static string serialize(Board);
};
