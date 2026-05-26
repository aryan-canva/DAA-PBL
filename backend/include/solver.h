#pragma once
#include <vector>
#include "food.h"
using namespace std;

// ── Globals (defined in solver.cpp, reset before each run) ────────────────────
extern vector<Food> bestSolution;
extern double       bestScore;

// ── Backtracking Solver ────────────────────────────────────────────────────────
// Explores all TAKE/SKIP combinations for candidates[index..end].
// Prunes branches that exceed budget or cannot improve bestScore.
// Updates bestSolution and bestScore whenever a better selection is found.
void backtrack(const vector<Food>& candidates,
               int index,
               Nutrition current,
               vector<Food>& selected,
               double budget);
