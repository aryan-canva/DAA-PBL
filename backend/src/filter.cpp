#include "../include/filter.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

static bool hasAllergen(const string& allergens, const vector<string>& blacklist) {
    for (const auto& a : blacklist)
        if (allergens.find(a) != string::npos)
            return true;
    return false;
}

vector<Food> filterFoods(const vector<Food>& foods,
                          const string& dietTag,
                          const vector<string>& blacklist,
                          double budget)
{
    vector<Food> result;
    for (const auto& f : foods) {
        if (!dietTag.empty() && dietTag != "any" && f.tag != dietTag)
            continue;
        if (hasAllergen(f.allergens, blacklist))
            continue;
        if (f.price > budget * 0.4)
            continue;
        result.push_back(f);
    }
    return result;
}

void printFilteredList(const vector<Food>& foods) {
    cout << "\n-- Filtered Food Pool (" << foods.size() << " items) ------------\n";
    cout << left
         << setw(28) << "Name"
         << setw(8)  << "Price"
         << setw(10) << "Calories"
         << setw(10) << "Protein"
         << setw(8)  << "Tag"
         << "\n";
    cout << string(64, '-') << "\n";
    for (const auto& f : foods) {
        cout << setw(28) << f.name
             << setw(8)  << f.price
             << setw(10) << f.calories
             << setw(10) << f.protein
             << setw(8)  << f.tag
             << "\n";
    }
    cout << string(64, '-') << "\n\n";
}