
#include <iostream>
#include <sstream>
#include <algorithm>
#include "include/food.h"
#include "include/parser.h"
#include "include/filter.h"
#include "include/solver.h"
#include "include/output.h"

using namespace std;

static string toLowerCase(string s) {

    transform(
        s.begin(),
        s.end(),
        s.begin(),
        ::tolower
    );

    return s;
}

static vector<string> parseAllergens(
    string input
) {

    vector<string> blacklist;

    if (
        toLowerCase(input) == "none"
        || input.empty()
    )
        return blacklist;

    stringstream ss(input);

    string token;

    while (getline(ss, token, ',')) {

        token.erase(
            0,
            token.find_first_not_of(" ")
        );

        token.erase(
            token.find_last_not_of(" ")
            + 1
        );

        blacklist.push_back(
            toLowerCase(token)
        );
    }

    return blacklist;
}

int main(
    int argc,
    char* argv[]
) {

    if (argc < 5) {

        cout
            << "[ERROR] Missing arguments.\n";

        return 1;
    }

    double budget =
        stod(argv[1]);

    string dietTag =
        argv[2];

    string allergenInput =
        argv[3];

    vector<string> blacklist =
        parseAllergens(
            allergenInput
        );

    vector<Food> foods =
        loadCSV(
"/home/aryan-raturi/Desktop/DAA-PBL/backend/data/foods.csv"
        );

    if (foods.empty()) {

        cout
            << "[ERROR] Food database empty.\n";

        return 1;
    }

    vector<Food> candidates =

        filterFoods(
            foods,
            dietTag,
            blacklist,
            budget
        );

    if (candidates.empty()) {

        cout
            << "[ERROR] No valid foods found.\n";

        return 1;
    }

    applyVarietyPenalty(
        candidates
    );

    bestScore = -1.0;

    bestSolution.clear();

    vector<Food> selected;

    Nutrition current;

    backtrack(
        candidates,
        0,
        current,
        selected,
        budget
    );

    printSolution(
        bestSolution,
        bestScore,
        budget
    );

    if (!bestSolution.empty()) {

        saveVarietyHistory(
            bestSolution
        );
    }

    return 0;
}