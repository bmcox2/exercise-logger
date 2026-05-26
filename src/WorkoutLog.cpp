#include "WorkoutLog.h"

void WorkoutLog::addWorkout(const Workout& workout) {
    _workouts.push_back(workout);
}

void WorkoutLog::displayWorkouts() const {
    for (const auto& workout : _workouts) {
        workout.displayWorkout();
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
    nlohmann::json j;
    inFile >> j;

    for (const auto& workout : j.at("workouts")) {
        addWorkout(Workout::fromJson(workout));
    }
}