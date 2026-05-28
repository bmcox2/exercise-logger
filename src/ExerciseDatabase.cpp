#include <fstream>
#include <algorithm>
#include "nlohmann/json.hpp"
#include "ExerciseDatabase.h"

ExerciseDatabase::ExerciseDatabase() {}

const std::vector<ExerciseInfo>& ExerciseDatabase::getExerciseInfos() const {
    return _exerciseInfos;
}

void ExerciseDatabase::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }
    nlohmann::json j;
    inFile >> j;

    for (const auto& exerciseJSON : j) {
        _exerciseInfos.push_back(ExerciseInfo::fromJson(exerciseJSON));
    }
}

std::vector<ExerciseInfo> ExerciseDatabase::searchByName(const std::string& input) const{
    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    std::vector<ExerciseInfo> matches;

    for (auto& exercise : _exerciseInfos) {
        std::string lowerName = exercise.getName();
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerInput) != std::string::npos) {
            matches.push_back(exercise);
        }
    }

    return matches;
}

std::vector<ExerciseInfo> ExerciseDatabase::searchByPrimaryMuscle(const std::string& input) const{
    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    std::vector<ExerciseInfo> matches;

    for (auto& exercise : _exerciseInfos) {
        for (auto& muscle : exercise.getPrimaryMuscles()) {
            std::string lowerMuscle = muscle;
            std::transform(lowerMuscle.begin(), lowerMuscle.end(), lowerMuscle.begin(), ::tolower);

            if (lowerMuscle.find(lowerInput) != std::string::npos) {
                matches.push_back(exercise);
                break;
            }
        }
        
    }

    return matches;
}

std::vector<ExerciseInfo> ExerciseDatabase::searchByEquipment(const std::string& input) const{
    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    std::vector<ExerciseInfo> matches;

    for (auto& exercise : _exerciseInfos) {
        std::string lowerEquipment = exercise.getEquipment();
        std::transform(lowerEquipment.begin(), lowerEquipment.end(), lowerEquipment.begin(), ::tolower);

        if (lowerEquipment.find(lowerInput) != std::string::npos) {
            matches.push_back(exercise);
        }
    }

    return matches;
}