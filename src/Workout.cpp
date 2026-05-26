#include "Workout.h"

Workout::Workout(const std::string& date, const std::string& name, double length) 
    : _date(date), _name(name), _length(length) {}

void Workout::addExercise(const Exercise& exercise) {
    _exercises.push_back(exercise);
} 

void Workout::displayWorkout() const {
    std::cout << std::string(35, '-') << "\n";
    std::cout << _name << " | " << _date << " | " << std::fixed << std::setprecision(1) << _length << " min\n";
    std::cout << std::string(35, '-') << "\n";
    for (const auto& exercise : _exercises) {
        std::cout << " - " << exercise.getName()
                  << " - " << exercise.getReps() << " reps @ "
                  << std::fixed << std::setprecision(1)
                  << exercise.getWeight() << " lbs\n";
    }
    std::cout << "\n";
}

const std::string& Workout::getDate() const {
    return _date;
}

const std::string& Workout::getName() const {
    return _name;
}

double Workout::getLength() const {
    return _length;
}

nlohmann::json Workout::toJson() const {
    nlohmann::json j;
    j["date"] = _date;
    j["name"] = _name;
    j["length"] = _length;

    nlohmann::json exercises = nlohmann::json::array();
    for (const auto& exercise : _exercises) {
        exercises.push_back(exercise.toJson());
    }
    j["exercises"] = exercises;

    return j;
}

Workout Workout::fromJson(const nlohmann::json& j) {
    std::string date = j.at("date").get<std::string>();
    std::string name = j.at("name").get<std::string>();
    double length = j.at("length").get<double>();

    Workout workout = Workout(date, name, length);
    for (const auto& exercise : j.at("exercises")) {
        workout.addExercise(Exercise::fromJson(exercise));
    }

    return workout;
}