#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

// RDA Constants
const int RDA_CALORIES = 2000;
const int RDA_PROTEIN  = 50;
const int RDA_FATS     = 65;
const int RDA_CARBS    = 300;

// Food Struct
struct Food {
    string name;
    double price;
    int calories;
    double protein;
    double fats;
    double carbs;
    string tag;
    string allergens;
};

// Nutrition
struct Nutrition {
    double price = 0;
    int calories = 0;
    double protein = 0;
    double fats = 0;
    double carbs = 0;
};

// CSV split
vector<string> split(const string& line) {
    vector<string> result;
    string temp;
    stringstream ss(line);
    while (getline(ss, temp, ',')) {
        result.push_back(temp);
    }
    return result;
}

// Create Food
Food createFood(const vector<string>& data) {
    Food f;
    f.name = data[0];
    f.price = stod(data[1]);
    f.calories = stoi(data[2]);
    f.protein = stod(data[3]);
    f.fats = stod(data[4]);
    f.carbs = stod(data[5]);
    f.tag = data[6];
    f.allergens = data[7];
    return f;
}

//  Load CSV
vector<Food> loadCSV(const string& filename) {
    vector<Food> foods;

    ifstream file(filename);
    if (!file.is_open()) return foods;

    string line;
    bool first = true;

    while (getline(file, line)) {
        if (first) { first = false; continue; }

        vector<string> data = split(line);
        if (data.size() == 8)
            foods.push_back(createFood(data));
    }

    return foods;
}

// Filter
vector<Food> filterFoods(const vector<Food>& foods,
                         const string& dietTag,
                         const vector<string>& blacklist,
                         double maxItemPrice)
{
    vector<Food> result;

    for (auto f : foods) {

        if (!dietTag.empty() && f.tag != dietTag) continue;

        bool blocked = false;
        for (auto allergen : blacklist) {
            if (f.allergens.find(allergen) != string::npos) {
                blocked = true;
                break;
            }
        }

        if (blocked) continue;

        if (f.price > maxItemPrice) continue;

        result.push_back(f);
    }

    return result;
}

// Health Score
double calculateHealthScore(const Nutrition& n) {
    double s1 = abs(n.calories - RDA_CALORIES) / (double)RDA_CALORIES * 100;
    double s2 = abs(n.protein  - RDA_PROTEIN)  / (double)RDA_PROTEIN  * 100;
    double s3 = abs(n.fats     - RDA_FATS)     / (double)RDA_FATS     * 100;
    double s4 = abs(n.carbs    - RDA_CARBS)    / (double)RDA_CARBS    * 100;

    double avg = (s1 + s2 + s3 + s4) / 4.0;
    return max(0.0, 100.0 - avg);
}

// Best result
vector<Food> bestSolution;
double bestScore = -1;

// Backtracking
void backtrack(const vector<Food>& candidates, size_t index,
               Nutrition current, vector<Food>& selected, double budget)
{
    if (index >= candidates.size()) {

        if (selected.empty()) return;

        double score = calculateHealthScore(current);

        if (score > bestScore) {
            bestScore = score;
            bestSolution = selected;
        }
        return;
    }

    if (current.price > budget) {
        // SKIP
        backtrack(candidates, index + 1, current, selected, budget);
        return;
    }

    // TAKE
    Food f = candidates[index];

    selected.push_back(f);

    current.price += f.price;
    current.calories += f.calories;
    current.protein += f.protein;
    current.fats += f.fats;
    current.carbs += f.carbs;

    backtrack(candidates, index + 1, current, selected, budget);

    // UNDO
    selected.pop_back();

    current.price -= f.price;
    current.calories -= f.calories;
    current.protein -= f.protein;
    current.fats -= f.fats;
    current.carbs -= f.carbs;

    // SKIP
    backtrack(candidates, index + 1, current, selected, budget);
}

// Print
void printSolution(const vector<Food>& solution, double score) {

    if (solution.empty()) {
        cout << "No meal found\n";
        return;
    }

    cout << "\nBest Meal:\n";

    for (auto f : solution) {
        cout << f.name << " (Rs " << f.price << ")\n";
    }

    cout << "Score: " << score << endl;
}

// MAIN
int main() {

    vector<Food> foods = loadCSV("foods.csv");

    if (foods.empty()) {
        cout << "Error loading file\n";
        return 0;
    }

    double budget;
    cout << "Enter budget: ";
    cin >> budget;

    vector<string> blacklist;
    string dietTag = "";

    vector<Food> candidates = filterFoods(foods, dietTag, blacklist, 1000);

    vector<Food> selected;
    Nutrition current;

    backtrack(candidates, 0, current, selected, budget);

    printSolution(bestSolution, bestScore);

    return 0;
}
