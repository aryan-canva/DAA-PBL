#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

const int RDA_CALORIES = 2000;
const int RDA_PROTEIN = 50;
const int RDA_FATS = 65;
const int RDA_CARBS = 300;

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

vector<string> split(string line) {
    vector<string> result;
    string temp;
    stringstream ss(line);
    while (getline(ss, temp, ',')) {
        result.push_back(temp);
    }
    return result;
}

Food createFood(vector<string> data) {
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

vector<Food> loadCSV(string filename) {
    vector<Food> foods;
    ifstream file(filename);
    string line;
    bool first = true;

    while (getline(file, line)) {
        if (first) {
            first = false;
            continue;
        }
        vector<string> data = split(line);
        if (data.size() == 8) {
            foods.push_back(createFood(data));
        }
    }

    return foods;
}

void saveCSV(string filename, vector<Food> foods) {
    ofstream file(filename);

    file << "name,price,calories,protein,fats,carbs,tag,allergens\n";

    for (auto f : foods) {
        file << f.name << ","
             << f.price << ","
             << f.calories << ","
             << f.protein << ","
             << f.fats << ","
             << f.carbs << ","
             << f.tag << ","
             << f.allergens << "\n";
    }
}

void addFood(string filename, Food f) {
    ofstream file(filename, ios::app);

    file << f.name << ","
         << f.price << ","
         << f.calories << ","
         << f.protein << ","
         << f.fats << ","
         << f.carbs << ","
         << f.tag << ","
         << f.allergens << "\n";
}
