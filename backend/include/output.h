#pragma once
#include <vector>
#include "food.h"
using namespace std;

double calculateHealthScore(const Nutrition& n);
void applyVarietyPenalty(vector<Food>& foods);
void saveVarietyHistory(const vector<Food>& solution);
void suggestRecipes(const vector<Food>& solution);
void printSolution(const vector<Food>& solution, double score, double budget);