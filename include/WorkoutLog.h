#pragma once

#include "Workout.h"

class WorkoutLog {
    private:
        std::vector<Workout> _workouts;

    public:
        void addWorkout(const Workout& workout);
        void displayWorkouts() const;
        const std::vector<Workout>& getWorkouts() const;

        void saveToFile(const std::string& filename) const;
        void loadFromFile(const std::string& filename);

        void deleteWorkout(int index);
        Workout& getWorkout(int index);
};