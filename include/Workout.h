#pragma once

#include "Exercise.h"
#include <iomanip>

class Workout {
    private:
        std::string _date;
        std::string _name;
        double _length;
        std::vector<Exercise> _exercises;


    public:
        Workout(const std::string& date, const std::string& name, double length);
        void addExercise(const Exercise& exercise);
        void displayWorkout() const;
        const std::string& getDate() const;
        const std::string& getName() const;
        double getLength() const;
        const std::vector<Exercise>& getExercises() const;

        nlohmann::json toJson() const;
        static Workout fromJson(const nlohmann::json& j);
};