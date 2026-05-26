#include "Exercise.h"


Exercise::Exercise(const std::string& name, int reps, double weight) 
    : _name(name), _reps(reps), _weight(weight) {}

const std::string& Exercise::getName() const {
    return _name;
}

int Exercise::getReps() const {
    return _reps;
}

double Exercise::getWeight() const {
    return _weight;
}

nlohmann::json Exercise::toJson() const {
    nlohmann::json j;
    j["name"] = _name;
    j["reps"] = _reps;
    j["weight"] = _weight;
    return j;
}

Exercise Exercise::fromJson(const nlohmann::json& j) {
    std::string name = j.at("name").get<std::string>();
    int reps = j.at("reps").get<int>();
    double weight = j.at("weight").get<double>();

    return Exercise(name, reps, weight);
}
