#pragma once
#include <vector>
#include <string>
#include "food.h"
using namespace std;

// Split a CSV line by comma
vector<string> splitLine(const string& line);

// Build a Food from a parsed row (expects 8 fields)
Food createFood(const vector<string>& data);

// Load all foods from CSV file, skipping the header row
vector<Food> loadCSV(const string& filename);
