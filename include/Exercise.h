#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

class Exercise {
    private:
        std::string _name;
        int _reps;
        double _weight;
        std::vector<std::string> _primaryMuscles;
        std::vector<std::string> _secondaryMuscles;

    public:
        Exercise(const std::string& name, int reps, double weight, const std::vector<std::string>& primaryMuscles, const std::vector<std::string>& secondaryMuscles);
           
        const std::string& getName() const;
        int getReps() const;
        double getWeight() const;
        const std::vector<std::string>& getPrimaryMuscles() const;
        const std::vector<std::string>& getSecondaryMuscles() const;

        nlohmann::json toJson() const;
        static Exercise fromJson(const nlohmann::json& j);

        void setReps(int reps);
        void setWeight(double weight);
        void setName(const std::string& name);
        void setPrimaryMuscles(const std::vector<std::string>& muscles);
        void setSecondaryMuscles(const std::vector<std::string>& muscles);
};