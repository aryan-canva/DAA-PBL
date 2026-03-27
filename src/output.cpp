#include "../include/output.h"
#include "../include/food.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

const string HISTORY_FILE = "data/used_foods.txt";

// ── Health Score ───────────────────────────────────────────────────────────────
double calculateHealthScore(const Nutrition& n) {
    double d1 = abs(n.calories - RDA_CALORIES) / (double)RDA_CALORIES * 100.0;
    double d2 = abs(n.protein  - RDA_PROTEIN)  / (double)RDA_PROTEIN  * 100.0;
    double d3 = abs(n.fats     - RDA_FATS)     / (double)RDA_FATS     * 100.0;
    double d4 = abs(n.carbs    - RDA_CARBS)    / (double)RDA_CARBS    * 100.0;
    double avg = (d1 + d2 + d3 + d4) / 4.0;
    return max(0.0, 100.0 - avg);
}

// ── Variety Logic ──────────────────────────────────────────────────────────────
void applyVarietyPenalty(vector<Food>& foods) {
    set<string> usedLastSession;
    ifstream f(HISTORY_FILE);
    string name;
    while (getline(f, name))
        if (!name.empty()) usedLastSession.insert(name);

    if (usedLastSession.empty()) return;

    cout << "[INFO] Deprioritizing recently used items for variety.\n";

    stable_sort(foods.begin(), foods.end(), [&](const Food& a, const Food& b) {
        return usedLastSession.count(a.name) < usedLastSession.count(b.name);
    });
}

void saveVarietyHistory(const vector<Food>& solution) {
    set<string> existing;
    ifstream in(HISTORY_FILE);
    string line;
    while (getline(in, line))
        if (!line.empty()) existing.insert(line);
    in.close();

    for (const auto& f : solution) existing.insert(f.name);

    ofstream out(HISTORY_FILE);
    int count = 0;
    for (auto it = existing.rbegin(); it != existing.rend() && count < 15; ++it, ++count)
        out << *it << "\n";
}

// ── Recipe Suggestions ─────────────────────────────────────────────────────────
void suggestRecipes(const vector<Food>& solution) {
    vector<pair<vector<string>, string>> recipes = {
        {{"Dal", "Rice"},      "Dal Chawal"},
        {{"Paneer", "Roti"},   "Paneer Roti Thali"},
        {{"Egg", "Toast"},     "Egg Toast"},
        {{"Chicken", "Rice"},  "Chicken Rice Bowl"},
        {{"Oats", "Banana"},   "Oats Banana Bowl"},
        {{"Sprouts", "Chaat"}, "Sprout Chaat Plate"},
        {{"Dahi", "Roti"},     "Dahi Roti"},
        {{"Idli", "Sambar"},   "Idli Sambar"},
        {{"Tofu", "Rice"},     "Tofu Rice Bowl"},
        {{"Chana", "Roti"},    "Chana Roti"},
    };

    set<string> selectedNames;
    for (const auto& f : solution) {
        string lower = f.name;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        selectedNames.insert(lower);
    }

    vector<string> matched;
    for (const auto& recipe : recipes) {
        const auto& keywords = recipe.first;
        const auto& dish     = recipe.second;
        bool allFound = true;
        for (const auto& kw : keywords) {
            string lowKw = kw;
            transform(lowKw.begin(), lowKw.end(), lowKw.begin(), ::tolower);
            bool found = false;
            for (const auto& sn : selectedNames)
                if (sn.find(lowKw) != string::npos) { found = true; break; }
            if (!found) { allFound = false; break; }
        }
        if (allFound) matched.push_back(dish);
    }

    if (!matched.empty()) {
        cout << "\n  Possible Dishes from your meal:\n";
        for (const auto& dish : matched)
            cout << "    -> " << dish << "\n";
    }
}

// ── Display Helpers ────────────────────────────────────────────────────────────
static void printBar(const string& label, double actual, double rda) {
    int filled = min((int)(actual / rda * 20), 20);
    cout << "  " << left << setw(10) << label << " [";
    for (int i = 0; i < 20; i++) cout << (i < filled ? '#' : '-');
    cout << "] " << fixed << setprecision(1) << actual << " / " << rda << "\n";
}

// ── Print Final Solution ───────────────────────────────────────────────────────
void printSolution(const vector<Food>& solution, double score, double budget) {
    if (solution.empty()) {
        cout << "\n[RESULT] No valid meal found within budget.\n";
        return;
    }

    Nutrition total;
    for (const auto& f : solution) {
        total.price    += f.price;
        total.calories += f.calories;
        total.protein  += f.protein;
        total.fats     += f.fats;
        total.carbs    += f.carbs;
    }

    cout << "\n========================================\n";
    cout << "           YOUR MEAL PLAN\n";
    cout << "========================================\n";

    for (const auto& f : solution)
        cout << "  * " << left << setw(26) << f.name << " Rs " << f.price << "\n";

    cout << "----------------------------------------\n";
    cout << "  Total Cost  : Rs " << total.price << " / Rs " << budget << "\n";
    cout << "  Health Score: " << fixed << setprecision(1) << score << " / 100\n";
    cout << "----------------------------------------\n";
    cout << "  Nutritional Coverage (vs RDA):\n";
    printBar("Calories", total.calories, RDA_CALORIES);
    printBar("Protein",  total.protein,  RDA_PROTEIN);
    printBar("Fats",     total.fats,     RDA_FATS);
    printBar("Carbs",    total.carbs,    RDA_CARBS);

    suggestRecipes(solution);

    cout << "========================================\n";
}