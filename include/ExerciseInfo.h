#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

class ExerciseInfo {
    private:
        std::string _name;
        std::vector<std::string> _primaryMuscles;
        std::vector<std::string> _secondaryMuscles;
        std::string _equipment;

    public: 
        ExerciseInfo(const std::string& name, const std::vector<std::string>& primaryMuscles, const std::vector<std::string>& secondaryMuscles, const std::string& equipment);
        const std::string& getName() const;
        const std::vector<std::string>& getPrimaryMuscles() const;
        const std::vector<std::string>& getSecondaryMuscles() const;
        const std::string& getEquipment() const;

        static ExerciseInfo fromJson(const nlohmann::json& j);
};
