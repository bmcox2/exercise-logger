#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

#include "nlohmann/json.hpp"

class Exercise {
    private:
        std::string _name;
        int _reps;
        double _weight;

    public:
        Exercise(const std::string& name, int reps, double weight);
        const std::string& getName() const;
        int getReps() const;
        double getWeight() const;

        nlohmann::json toJson() const;
        static Exercise fromJson(const nlohmann::json& j);
};