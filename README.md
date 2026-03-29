# Budget-Constrained Meal Planning System

## Project Overview
This project is a smart meal planning system that helps users create nutritionally balanced meals within a limited budget. Instead of manually calculating calories, protein, fats, and costs, the system uses optimization algorithms to generate efficient meal combinations.

It considers budget, nutrition, dietary preferences, and restrictions to produce practical meal plans.

The project is developed using **C++**, STL, and algorithmic techniques.

---

## Problem Statement
Planning meals that are both **affordable and nutritious** is difficult.

Common issues:
- Budget constraints are ignored  
- Nutrition is not optimized properly  
- Apps focus only on calorie tracking  
- Dietary restrictions are not handled well  
- Lack of variety  

This project solves these issues using algorithm-based optimization instead of guesswork.

---

## How the System Works

1. User inputs budget and dietary preferences  
2. Food dataset is loaded (price, nutrition, tags)  
3. Invalid items are filtered out  
4. Backtracking generates possible combinations  
5. Branch and Bound prunes inefficient solutions  
6. Best combination is selected  
7. Health score is calculated  
8. Final meal plan is displayed  


## Technologies Used

### C++
Core programming language used for implementation.

### STL (Standard Template Library)
Used for:
- Data structures  
- Sorting and searching  
- Efficient computation  

### File Handling
Used for reading datasets (CSV/JSON).

### Optional: Qt
For graphical user interface (if implemented).

---

## Why This Project Uses C++
Most similar systems are built using Python. This project uses C++ to:

- Align with academic curriculum  
- Strengthen understanding of algorithms  
- Provide better control over performance  
- Apply DAA concepts practically  

---

## Main Features

- Budget-based meal planning  
- Nutritional optimization (Protein, Calories, Fats, Carbs)  
- Dietary filters (Veg, Non-Veg, Lactose-Free)  
- Allergen filtering  
- Health score (0–100%)  
- Optimized food selection  
- Variety-aware planning  
- Recipe suggestions  

---

## Project Modules

### 1. Input and Filtering Module
Handles user input and preprocessing.

**Responsibilities:**
- Accept user inputs  
- Filter food items  
- Remove invalid entries  

---

### 2. Optimization Module
Core logic of the system.

**Responsibilities:**
- Generate combinations using backtracking  
- Apply Branch and Bound  
- Optimize cost vs nutrition  

---

### 3. Scoring and Output Module
Handles evaluation and display.

**Responsibilities:**
- Calculate health score  
- Display meal plan  
- Show nutritional summary  

---

## Applications

- Student meal planning  
- Budget diet management  
- Fitness planning  
- Health-focused systems  
- Algorithm-based decision tools  

---

## Future Improvements

- AI-based recommendations  
- Real-time pricing updates  
- Mobile/Web app version  
- Personalized diet learning  
- Integration with fitness platforms  

---

## Project Goal
To demonstrate how algorithmic techniques like **Backtracking** and **Branch & Bound** can solve real-world optimization problems efficiently.And to create a C++-based meal planning system that uses Backtracking and Branch & Bound to generate cost-effective, nutritionally balanced meal plans based on user constraints.

---

## Authors

**Team Name:** Avengers  

**Team Members:**
- Aryan Raturi
- Sanskriti Bhardwaj    
- Akhil Padiyar  
- Divyam Singh  

---

## Repository Updates

This repository will include:
- Source code  
- Algorithm implementations  
- Dataset files  
- Improvements and optimizations  
- Documentation  

---

## Repository Description
A C++-based meal planning system that uses Backtracking and Branch & Bound to generate cost-effective, nutritionally balanced meal plans based on user constraints.
