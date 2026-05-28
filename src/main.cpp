#include "WorkoutLog.h"
#include "ExerciseDatabase.h"
#include "utils.h"

std::string searchAndSelectExercise(const ExerciseDatabase& db) {
    while (true) {
        std::string query = getValidString("Search exercise (or 'done' to finish): ");
        if (query == "done") return "done";

        std::vector<ExerciseInfo> results = db.searchByName(query);
        if (results.empty()) {
            std::cout << "No matches found.\n";
            continue;
        }

        int resultCount = std::min((int)results.size(), 50);
        for (int i = 0; i < resultCount; ++i)
            std::cout << i + 1 << ". " << results[i].getName() << "\n";

        int choice = getValidInt("Pick a number (0 to search again): ");
        if (choice >= 1 && choice <= resultCount)
            return results[choice - 1].getName();
    }
}

void displayMenu() {
    std::cout << "\n=== Exercise Logger ===\n";
    std::cout << "1. Add Workout\n";
    std::cout << "2. View Workouts\n";
    std::cout << "3. Exit\n";
}

void addWorkoutFlow(WorkoutLog& log, const ExerciseDatabase& db) {
    std::string date = getValidString("Enter workout date (YYYY-MM-DD): ");
    std::string exerciseName = getValidString("Enter workout name: ");
    double length = getValidDouble("Enter workout length (minutes): ");
    Workout workout(date, exerciseName, length);

    while (true) {
        std::string name = searchAndSelectExercise(db);
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

    ExerciseDatabase exerciseDb;
    exerciseDb.loadFromFile("data/exercises.json");

    while (true) {
        displayMenu();
        int choice = getValidInt("Choice: ");

        switch (choice) {
            case 1:
                addWorkoutFlow(workoutLog, exerciseDb);
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
