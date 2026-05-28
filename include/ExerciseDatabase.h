#pragma once

#include <vector>
#include <string>
#include "ExerciseInfo.h"

class ExerciseDatabase {
    private:
        std::vector<ExerciseInfo> _exerciseInfos;

    public:
        ExerciseDatabase();
        const std::vector<ExerciseInfo>& getExerciseInfos() const;
        void loadFromFile(const std::string& filename);

        std::vector<ExerciseInfo> searchByName(const std::string& input) const;
        std::vector<ExerciseInfo> searchByPrimaryMuscle(const std::string& input) const;
        std::vector<ExerciseInfo> searchByEquipment(const std::string& input) const;

};