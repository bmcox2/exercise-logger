#include "Exercise.h"


Exercise::Exercise(const std::string& name, int reps, double weight, const std::vector<std::string>& primaryMuscles, const std::vector<std::string>& secondaryMuscles)
    : _name(name), _reps(reps), _weight(weight), _primaryMuscles(primaryMuscles), _secondaryMuscles(secondaryMuscles) {}

const std::string& Exercise::getName() const {
    return _name;
}

int Exercise::getReps() const {
    return _reps;
}

double Exercise::getWeight() const {
    return _weight;
}

const std::vector<std::string>& Exercise::getPrimaryMuscles() const {
    return _primaryMuscles;
}

const std::vector<std::string>& Exercise::getSecondaryMuscles() const {
    return _secondaryMuscles;
}

nlohmann::json Exercise::toJson() const {
    nlohmann::json j;
    j["name"] = _name;
    j["reps"] = _reps;
    j["weight"] = _weight;
    j["primaryMuscles"] = _primaryMuscles;
    j["secondaryMuscles"] = _secondaryMuscles;
    return j;
}

Exercise Exercise::fromJson(const nlohmann::json& j) {
    std::string name = j.at("name").get<std::string>();
    int reps = j.at("reps").get<int>();
    double weight = j.at("weight").get<double>();
    std::vector<std::string> primaryMuscles = j.at("primaryMuscles").get<std::vector<std::string>>();
    std::vector<std::string> secondaryMuscles = j.at("secondaryMuscles").get<std::vector<std::string>>();

    return Exercise(name, reps, weight, primaryMuscles, secondaryMuscles);
}

void Exercise::setReps(int reps) { 
    _reps = reps;
}
void Exercise::setWeight(double weight) {
    _weight = weight;
}
void Exercise::setName(const std::string& name) {
    _name = name;
}
void Exercise::setPrimaryMuscles(const std::vector<std::string>& muscles) {
    _primaryMuscles = muscles;
}
void Exercise::setSecondaryMuscles(const std::vector<std::string>& muscles) {
    _secondaryMuscles = muscles;
}