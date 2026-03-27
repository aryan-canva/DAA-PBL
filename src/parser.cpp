#include "../include/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Split a CSV line by comma
vector<string> splitLine(const string& line) {
    vector<string> result;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ','))
        result.push_back(token);
    return result;
}

// Build a Food from a parsed row
Food createFood(const vector<string>& data) {
    Food f;
    f.name      = data[0];
    f.price     = stod(data[1]);
    f.calories  = stoi(data[2]);
    f.protein   = stod(data[3]);
    f.fats      = stod(data[4]);
    f.carbs     = stod(data[5]);
    f.tag       = data[6];
    f.allergens = data[7];
    return f;
}

// Load all foods from CSV, skip header row
vector<Food> loadCSV(const string& filename) {
    vector<Food> foods;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "[ERROR] Cannot open file: " << filename << "\n";
        return foods;
    }

    string line;
    bool firstRow = true;

    while (getline(file, line)) {
        if (firstRow) { firstRow = false; continue; } // skip header
        if (line.empty()) continue;

        vector<string> data = splitLine(line);
        if (data.size() == 8)
            foods.push_back(createFood(data));
    }

    cout << "[INFO] Loaded " << foods.size() << " food items from " << filename << "\n";
    return foods;
}