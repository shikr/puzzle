#include "solver.hpp"

#include <cmath>
#include <queue>
#include <utility>
#include <vector>

bool Cmp::operator()(State& a, State& b) {
  int am = Solver::manhattan(a.first.first, a.first.second, a.second);
  int bm = Solver::manhattan(b.first.first, b.first.second, b.second);

  return am < bm;
}

Solver::Solver(Board* b, Board* g) : board(b), goal(g) {}

void Solver::solve(int moves) {
  priority_queue<State, vector<State>, Cmp> qu;

  qu.push(State({*board, *goal}, moves));
  while (!qu.empty()) {
    Board s = qu.top().first.first;
    qu.pop();
    visited.insert(s);

    if (s == *goal) {
      savePath(s);
      break;
    }

    vector<Board> ns = neighbours(s);
    vector<Board>::iterator it;

    for (it = ns.begin(); it != ns.end(); ++it) {
      Board temp = *it;
      if (!visit(temp)) {
        parent.insert(pair<Board, Board>(temp, s));
        qu.push(State({temp, *goal}, moves + 1));
      }
    }
  }

  path = paths.begin();
}

void Solver::solve() { solve(0); }

bool Solver::isSafe(int i, int j) { return (i >= 0 && i < 3 && j >= 0 && j < 3); }

Board Solver::getStep() {
  if (paths.empty()) return *board;
  if (path == paths.end()) path--;
  return *path;
}

void Solver::firstStep() { path = paths.begin(); }

void Solver::prevStep() {
  if (path != paths.begin()) path--;
}

void Solver::nextStep() {
  if (path != paths.end()) path++;
}

void Solver::lastStep() { path = paths.end(); }

int Solver::manhattan(Board a, Board goal, int moves) {
  int dist = moves;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (a[i][j] != 0) {
        for (int k = 0; k < 3; ++k) {
          for (int h = 0; h < 3; ++h) {
            if (a[i][j] == goal[k][h]) dist += abs(i - k) + abs(j - h);
          }
        }
      }
    }
  }

  return dist;
}

bool Solver::visit(Board a) { return visited.contains(a); }

vector<Board> Solver::neighbours(Board a) {
  pair<int, int> pos;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (a[i][j] == 0) {
        pos.first = i;
        pos.second = j;
        break;
      }
    }
  }

  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, 1, -1};
  vector<Board> ans;

  for (int k = 0; k < 4; ++k) {
    int cx = pos.first;
    int cy = pos.second;
    Board n = a;
    if (isSafe(cx + dx[k], cy + dy[k])) {
      swap(n[cx + dx[k]][cy + dy[k]], n[cx][cy]);
      ans.push_back(n);
    }
  }

  return ans;
}

void Solver::savePath(Board s) {
  if (parent.contains(s)) savePath(parent[s]);

  paths.push_back(s);
  path = paths.begin();
}
