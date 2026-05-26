#pragma once
#include <vector>
#include <string>
#include "food.h"
using namespace std;

// Returns foods that pass all three filters:
//   1. Diet tag match (veg / non-veg / lactose-free / any)
//   2. No blacklisted allergens
//   3. Single-item price <= 40% of total budget
vector<Food> filterFoods(const vector<Food>& foods,
                          const string& dietTag,
                          const vector<string>& blacklist,
                          double budget);

// Print the filtered candidate list to stdout
void printFilteredList(const vector<Food>& foods);
