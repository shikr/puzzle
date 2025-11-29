#pragma once

#include <array>

typedef std::array<std::array<int, 3>, 3> Board;

class Puzzle {
  Board board;
  Board goal;

  bool isEmpty(int i, int j);

  static bool isSafe(int i, int j);
  static int countInversions(Board);
  static bool validBoard(Board);
  static bool validBoard(Board board, Board goal);
  static Board randomBoard();
  static Board randomBoard(Board goal);
  static Board defaultBoard();

 public:
  void useRandomBoard();
  bool useBoard(Board board, Board goal);
  bool swapEmpty(int i, int j);
  bool isCompleted();

  Board getBoard();
};
