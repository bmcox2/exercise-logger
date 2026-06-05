#include <fstream>
#include <iostream>
#include <stdexcept>
#include "WorkoutLog.h"

void WorkoutLog::addWorkout(const Workout& workout) {
    _workouts.push_back(workout);
}

void WorkoutLog::displayWorkouts() const {
    for (int i = 0; i < static_cast<int>(_workouts.size()); ++i) {
        std::cout << i + 1 << ". " << _workouts[i].getName() << " - " << _workouts[i].getDate() << "\n";
    }
}

const std::vector<Workout>& WorkoutLog::getWorkouts() const {
    return _workouts;
}

void WorkoutLog::saveToFile(const std::string& filename) const {
    nlohmann::json j;
    nlohmann::json workouts = nlohmann::json::array();
    for (const auto& workout : _workouts) {
        workouts.push_back(workout.toJson());
    }
    j["workouts"] = workouts;

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Could not open file\n";
        return;
    }
    outFile << j.dump(2);
}

void WorkoutLog::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }
    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        return;
    }
    nlohmann::json j;
    inFile >> j;

    for (const auto& workout : j.at("workouts")) {
        addWorkout(Workout::fromJson(workout));
    }
}

void WorkoutLog::deleteWorkout(int index) {
    if (index < 0 || index >= static_cast<int>(_workouts.size())) {
        std::cerr << "Invalid workout index\n";
        return;
    }
    _workouts.erase(_workouts.begin() + index);
}
Workout& WorkoutLog::getWorkout(int index) {
    if (index < 0 || index >= static_cast<int>(_workouts.size())) {
        std::cerr << "Invalid workout index\n";
        throw std::out_of_range("Index out of bounds");
    }
    return _workouts[index];
}