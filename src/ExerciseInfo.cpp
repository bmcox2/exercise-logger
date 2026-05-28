#include "ExerciseInfo.h"

ExerciseInfo::ExerciseInfo(const std::string& name, const std::vector<std::string>& primaryMuscles, const std::vector<std::string>& secondaryMuscles, const std::string& equipment) 
    : _name(name), _primaryMuscles(primaryMuscles), _secondaryMuscles(secondaryMuscles), _equipment(equipment) {}

const std::string& ExerciseInfo::getName() const {
    return _name;
}
const std::vector<std::string>& ExerciseInfo::getPrimaryMuscles() const {
    return _primaryMuscles;
}
const std::vector<std::string>& ExerciseInfo::getSecondaryMuscles() const {
    return _secondaryMuscles;
}
const std::string& ExerciseInfo::getEquipment() const {
    return _equipment;
}

ExerciseInfo ExerciseInfo::fromJson(const nlohmann::json& j) {
    std::string name = j.at("name").get<std::string>();
    std::vector<std::string> primaryMuscles = j.at("primaryMuscles").get<std::vector<std::string>>();
    std::vector<std::string> secondaryMuscles = j.at("secondaryMuscles").get<std::vector<std::string>>();
    std::string equipment = j.at("equipment").is_null() ? "unknown" : j.at("equipment").get<std::string>();

    return ExerciseInfo(name, primaryMuscles, secondaryMuscles, equipment);
}