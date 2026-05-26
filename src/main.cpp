#include "WorkoutLog.h"
#include "utils.h"

void displayMenu() {
    std::cout << "\n=== Exercise Logger ===\n";
    std::cout << "1. Add Workout\n";
    std::cout << "2. View Workouts\n";
    std::cout << "3. Exit\n";
}

void addWorkoutFlow(WorkoutLog& log) {
    std::string date = getValidString("Enter workout date (YYYY-MM-DD): ");
    std::string exerciseName = getValidString("Enter workout name: ");
    double length = getValidDouble("Enter workout length (minutes): ");
    Workout workout(date, exerciseName, length);

    while (true) {
        std::string name = getValidString("Enter exercise name (or 'done' to finish): ");
        if (name == "done") break;

        int reps = getValidInt("Enter reps: ");
        double weight = getValidDouble("Enter weight: ");

        workout.addExercise(Exercise(name, reps, weight));
    }

    log.addWorkout(workout);
    std::cout << "Workout added!\n";
}

void viewWorkoutsFlow(const WorkoutLog& log) {
    if (log.getWorkouts().empty()) {
        std::cout << "No workouts logged yet.\n";
        return;
    }
    log.displayWorkouts();
}

int main() {
    const std::string filename = "data/workouts.json";
    WorkoutLog workoutLog;
    workoutLog.loadFromFile(filename);

    while (true) {
        displayMenu();
        int choice = getValidInt("Choice: ");

        switch (choice) {
            case 1:
                addWorkoutFlow(workoutLog);
                break;
            case 2:
                viewWorkoutsFlow(workoutLog);
                break;
            case 3:
                workoutLog.saveToFile(filename);
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice, try again.\n";
        }
    }
}
