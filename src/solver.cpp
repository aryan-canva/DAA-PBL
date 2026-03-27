#include "../include/solver.h"
#include "../include/output.h"
#include <climits>
using namespace std;

// Global best — reset before each run
vector<Food> bestSolution;
double       bestScore = -1.0;

// ── Bound Check ────────────────────────────────────────────────────────────────
// Estimates the maximum possible score improvement remaining.
// If even taking all remaining items can't beat current bestScore, prune.
static bool canImprove(const vector<Food>& candidates,
                        int index,
                        const Nutrition& current,
                        double budget)
{
    // Optimistic: add all remaining items that fit in budget
    Nutrition optimistic = current;
    for (int i = index; i < (int)candidates.size(); i++) {
        if (optimistic.price + candidates[i].price <= budget) {
            optimistic.price    += candidates[i].price;
            optimistic.calories += candidates[i].calories;
            optimistic.protein  += candidates[i].protein;
            optimistic.fats     += candidates[i].fats;
            optimistic.carbs    += candidates[i].carbs;
        }
    }
    double optimisticScore = calculateHealthScore(optimistic);
    return optimisticScore > bestScore;
}

// ── Backtracking ───────────────────────────────────────────────────────────────
// At each index we make a binary choice: TAKE or SKIP the current food item.
// Pruning conditions:
//   1. Current cost already exceeds budget → prune entire branch
//   2. Bound check says no improvement possible → prune
void backtrack(const vector<Food>& candidates,
               int index,
               Nutrition current,
               vector<Food>& selected,
               double budget)
{
    // ── Evaluate current selection (at every node, not just leaves)
    if (!selected.empty()) {
        double score = calculateHealthScore(current);
        if (score > bestScore) {
            bestScore    = score;
            bestSolution = selected;
        }
    }

    // ── Base case: all items considered
    if (index >= (int)candidates.size()) return;

    // ── Prune 1: already over budget
    if (current.price > budget) return;

    // ── Prune 2: bound check — can remaining items improve best?
    if (!canImprove(candidates, index, current, budget)) return;

    Food f = candidates[index];

    // ── TAKE (only if fits in budget)
    if (current.price + f.price <= budget) {
        selected.push_back(f);
        current.price    += f.price;
        current.calories += f.calories;
        current.protein  += f.protein;
        current.fats     += f.fats;
        current.carbs    += f.carbs;

        backtrack(candidates, index + 1, current, selected, budget);

        // ── UNDO (backtrack)
        selected.pop_back();
        current.price    -= f.price;
        current.calories -= f.calories;
        current.protein  -= f.protein;
        current.fats     -= f.fats;
        current.carbs    -= f.carbs;
    }

    // ── SKIP
    backtrack(candidates, index + 1, current, selected, budget);
}