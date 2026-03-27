#include <iostream>
#include <sstream>
#include <algorithm>
#include "include/food.h"
#include "include/parser.h"
#include "include/filter.h"
#include "include/solver.h"
#include "include/output.h"
using namespace std;

// ── Input Helpers ──────────────────────────────────────────────────────────────
static string toLowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

static vector<string> getAllergens() {
    vector<string> blacklist;
    cout << "Allergens to avoid (comma-separated, or 'none'): ";
    cin.ignore();
    string input;
    getline(cin, input);
    if (toLowerCase(input) == "none" || input.empty()) return blacklist;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);
        blacklist.push_back(toLowerCase(token));
    }
    return blacklist;
}

// ── Main ───────────────────────────────────────────────────────────────────────
int main() {
    cout << "========================================\n";
    cout << "   Budget-Constrained Meal Planner\n";
    cout << "           DAA PBL Project\n";
    cout << "========================================\n\n";

    // Module 1: Load data
    vector<Food> foods = loadCSV("data/foods.csv");
    if (foods.empty()) return 1;

    // Budget input
    double budget;
    cout << "Enter daily budget (Rs): ";
    cin >> budget;

    // Diet preference
    string dietTag;
    cout << "Diet preference (veg / non-veg / lactose-free / any): ";
    cin >> dietTag;

    // Module 2: Allergens + Filter
    vector<string> blacklist = getAllergens();
    vector<Food> candidates = filterFoods(foods, dietTag, blacklist, budget);
    printFilteredList(candidates);

    if (candidates.empty()) {
        cout << "[ERROR] No candidates after filtering. Relax your constraints.\n";
        return 1;
    }

    // Module 4 (variety): deprioritize recently used foods
    applyVarietyPenalty(candidates);

    // Module 3: Backtracking
    cout << "[INFO] Running backtracking solver...\n";
    bestScore = -1.0;
    bestSolution.clear();
    vector<Food> selected;
    Nutrition current;
    backtrack(candidates, 0, current, selected, budget);

    // Module 4: Output
    printSolution(bestSolution, bestScore, budget);

    // Save for variety next session
    if (!bestSolution.empty())
        saveVarietyHistory(bestSolution);

    return 0;
}