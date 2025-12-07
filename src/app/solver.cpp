#include "solver.hpp"

#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

Solver::Solver(Board* b, Board* g) : board(b), goal(g) {}

void Solver::solve() {
  priority_queue<State, vector<State>, greater<State>> qu;
  set<Board> visited;
  map<Board, Board> parent;
  map<Board, int> cost;

  qu.push({0, *board});
  parent[*board] = Board();
  cost[*board] = 0;

  while (!qu.empty()) {
    auto [_, state] = qu.top();
    qu.pop();

    if (visited.contains(state)) continue;

    if (state == *goal) {
      paths.clear();
      savePath(parent, state);
      break;
    }

    visited.insert(state);

    for (auto child : neighbours(state)) {
      if (!visited.contains(child)) {
        int newCost = cost[state] + 1;
        if (!cost.contains(child) || newCost < cost[child]) {
          cost[child] = newCost;
          int priority = newCost + manhattan(child);
          qu.push({priority, child});
          parent[child] = state;
        }
      }
    }
  }

  path = paths.begin();
}

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

int Solver::manhattan(Board a) {
  int dist = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (a[i][j] != 0) {
        for (int k = 0; k < 3; ++k) {
          for (int h = 0; h < 3; ++h) {
            if (a[i][j] == (*goal)[k][h]) dist += abs(i - k) + abs(j - h);
          }
        }
      }
    }
  }

  return dist;
}

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

void Solver::savePath(map<Board, Board> parent, Board s) {
  if (parent.contains(s) && s != *board) savePath(parent, parent[s]);

  paths.push_back(s);
  path = paths.begin();
}
