#include "../include/ScoringModule.h"
#include <iostream>
#include <iomanip>
#include <cmath>

ScoringModule::ScoringModule() {}

HealthScore ScoringModule::calculateHealthScore(const MealCombination& combo) {
    HealthScore score;
    
    double calorieScore = scoreCalories(combo.totalCalories);
    double proteinScore = scoreProtein(combo.totalProtein);
    double fatsScore = scoreFats(combo.totalFats);
    double carbsScore = scoreCarbs(combo.totalCarbs);
    
    score.nutritionScores["Calories"] = calorieScore;
    score.nutritionScores["Protein"] = proteinScore;
    score.nutritionScores["Fats"] = fatsScore;
    score.nutritionScores["Carbs"] = carbsScore;
    
    // Weighted average
    score.score = (calorieScore * CALORIE_WEIGHT) +
                  (proteinScore * PROTEIN_WEIGHT) +
                  (fatsScore * FATS_WEIGHT) +
                  (carbsScore * CARBS_WEIGHT);
    
    score.rating = getRating(score.score);
    score.recommendations = generateRecommendations(combo);
    
    return score;
}

double ScoringModule::scoreCalories(double calories) {
    double deviation = std::abs(calories - RECOMMENDED_CALORIES) / RECOMMENDED_CALORIES;
    return std::max(0.0, 100 * (1 - deviation * 0.5));
}

double ScoringModule::scoreProtein(double protein) {
    if (protein < RECOMMENDED_PROTEIN * 0.5) return 20;
    if (protein > RECOMMENDED_PROTEIN * 1.5) return 80;
    
    double normalized = (protein / RECOMMENDED_PROTEIN) * 100;
    return std::min(100.0, normalized);
}

double ScoringModule::scoreFats(double fats) {
    if (fats < RECOMMENDED_FATS * 0.5) return 50;
    if (fats > RECOMMENDED_FATS * 1.5) return 40;
    
    double normalized = (fats / RECOMMENDED_FATS) * 100;
    return std::min(100.0, normalized * 0.8);
}

double ScoringModule::scoreCarbs(double carbs) {
    if (carbs < RECOMMENDED_CARBS * 0.5) return 40;
    if (carbs > RECOMMENDED_CARBS * 1.5) return 60;
    
    double normalized = (carbs / RECOMMENDED_CARBS) * 100;
    return std::min(100.0, normalized * 0.9);
}

std::map<std::string, std::string> ScoringModule::generateRecommendations(const MealCombination& combo) {
    std::map<std::string, std::string> recommendations;
    
    if (combo.totalProtein < RECOMMENDED_PROTEIN) {
        recommendations["Protein"] = "Increase protein intake - add lean meats, eggs, or legumes";
    } else if (combo.totalProtein > RECOMMENDED_PROTEIN * 1.5) {
        recommendations["Protein"] = "Protein is high - balance with other nutrients";
    } else {
        recommendations["Protein"] = "Protein intake is optimal";
    }
    
    if (combo.totalCalories < RECOMMENDED_CALORIES * 0.8) {
        recommendations["Calories"] = "Meal is below recommended calories - consider larger portions";
    } else if (combo.totalCalories > RECOMMENDED_CALORIES * 1.2) {
        recommendations["Calories"] = "Meal exceeds recommended calories - consider portion control";
    } else {
        recommendations["Calories"] = "Calorie intake is well-balanced";
    }
    
    if (combo.totalFats < RECOMMENDED_FATS * 0.5) {
        recommendations["Fats"] = "Fat intake is low - add healthy fats (nuts, oils)";
    } else if (combo.totalFats > RECOMMENDED_FATS * 1.5) {
        recommendations["Fats"] = "Fat intake is high - reduce fried foods";
    } else {
        recommendations["Fats"] = "Fat intake is balanced";
    }
    
    return recommendations;
}

std::string ScoringModule::getRating(double score) {
    if (score >= 85) return "Excellent";
    if (score >= 70) return "Good";
    if (score >= 55) return "Fair";
    return "Poor";
}

void ScoringModule::displayHealthReport(const MealCombination& combo) {
    HealthScore health = calculateHealthScore(combo);
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "HEALTH SCORE REPORT" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Overall Score: " << health.score << "/100" << std::endl;
    std::cout << "Rating: " << health.rating << std::endl;
    
    std::cout << "\nNutrition Breakdown:" << std::endl;
    for (const auto& pair : health.nutritionScores) {
        std::cout << "  " << pair.first << ": " << pair.second << "/100" << std::endl;
    }
    
    std::cout << "\nRecommendations:" << std::endl;
    for (const auto& pair : health.recommendations) {
        std::cout << "  • " << pair.second << std::endl;
    }
    
    std::cout << std::string(50, '=') << std::endl;
}

void ScoringModule::displayNutritionSummary(const MealCombination& combo) {
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "NUTRITION SUMMARY" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Calories: " << combo.totalCalories << " (Recommended: " << RECOMMENDED_CALORIES << ")" << std::endl;
    std::cout << "Protein: " << combo.totalProtein << "g (Recommended: " << RECOMMENDED_PROTEIN << "g)" << std::endl;
    std::cout << "Fats: " << combo.totalFats << "g (Recommended: " << RECOMMENDED_FATS << "g)" << std::endl;
    std::cout << "Carbs: " << combo.totalCarbs << "g (Recommended: " << RECOMMENDED_CARBS << "g)" << std::endl;
    std::cout << "Total Cost: ₹" << combo.totalCost << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}