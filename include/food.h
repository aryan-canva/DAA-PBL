#pragma once
#include <string>
using namespace std;

// ── RDA Constants ──────────────────────────────────────────────────────────────
const int    RDA_CALORIES = 2000;
const double RDA_PROTEIN  = 50.0;
const double RDA_FATS     = 70.0;
const double RDA_CARBS    = 260.0;

// ── Nutrition Accumulator ──────────────────────────────────────────────────────
struct Nutrition {
    double price    = 0.0;
    int    calories = 0;
    double protein  = 0.0;
    double fats     = 0.0;
    double carbs    = 0.0;
};

// ── Food Item ──────────────────────────────────────────────────────────────────
struct Food {
    string name;
    double price;
    int    calories;
    double protein;
    double fats;
    double carbs;
    string tag;       // "veg", "non-veg", "lactose-free", etc.
    string allergens; // comma-separated allergen keywords
};
