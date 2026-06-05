#include "utils.h"
#include <optional>
#include <set>
#include <iomanip>
#include <map>

#include "WorkoutLog.h"
#include "ExerciseDatabase.h"
std::optional<ExerciseInfo> searchAndSelectExercise(const ExerciseDatabase& db) {
    while (true) {
        std::string query = getValidString("Search exercise (or 'done' to finish): ");
        if (query == "done") return std::nullopt;

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
            return results[choice - 1];
    }
}

int selectWorkoutFlow(const WorkoutLog& log) {
    log.displayWorkouts();
    int count = static_cast<int>(log.getWorkouts().size());
    int choice = getValidInt("Select workout (0 to cancel): ");
    if (choice < 1 || choice > count) return -1;
    return choice - 1;
}

bool deleteWorkoutFlow(WorkoutLog& log, int index) {
    std::cout << "Delete \"" << log.getWorkout(index).getName() << "\"? (y/n): ";
    std::string confirm = getValidString("");
    if (confirm == "y" || confirm == "Y") {
        log.deleteWorkout(index);
        std::cout << "Workout deleted.\n";
        return true;
    }
    return false;
}

void editWorkoutFlow(WorkoutLog& log, int index, const ExerciseDatabase& db) {
    while (true) {
        Workout& w = log.getWorkout(index);
        std::cout << "\n--- Edit Workout ---\n";
        std::cout << "1. Edit name\n";
        std::cout << "2. Edit date\n";
        std::cout << "3. Edit length\n";
        std::cout << "4. Add exercise\n";
        std::cout << "5. Edit exercise\n";
        std::cout << "6. Delete exercise\n";
        std::cout << "7. Done\n";
        int choice = getValidInt("Choice: ");

        if (choice == 1) {
            w.setName(getValidString("New name: "));
        } else if (choice == 2) {
            w.setDate(getValidString("New date (YYYY-MM-DD): "));
        } else if (choice == 3) {
            w.setLength(getValidDouble("New length (minutes): "));
        } else if (choice == 4) {
            std::optional<ExerciseInfo> info = searchAndSelectExercise(db);
            if (info) {
                int reps = getValidInt("Enter reps: ");
                double weight = getValidDouble("Enter weight: ");
                w.addExercise(Exercise(info->getName(), reps, weight, info->getPrimaryMuscles(), info->getSecondaryMuscles()));
            }
        } else if (choice == 5) {
            const auto& exercises = w.getExercises();
            if (exercises.empty()) { std::cout << "No exercises to edit.\n"; continue; }
            for (int i = 0; i < static_cast<int>(exercises.size()); ++i)
                std::cout << i + 1 << ". " << exercises[i].getName() << "\n";
            int exChoice = getValidInt("Select exercise (0 to cancel): ");
            if (exChoice >= 1 && exChoice <= static_cast<int>(exercises.size())) {
                Exercise& ex = w.getExercise(exChoice - 1);
                ex.setReps(getValidInt("New reps: "));
                ex.setWeight(getValidDouble("New weight: "));
            }
        } else if (choice == 6) {
            const auto& exercises = w.getExercises();
            if (exercises.empty()) { std::cout << "No exercises to delete.\n"; continue; }
            for (int i = 0; i < static_cast<int>(exercises.size()); ++i)
                std::cout << i + 1 << ". " << exercises[i].getName() << "\n";
            int exChoice = getValidInt("Select exercise to delete (0 to cancel): ");
            if (exChoice >= 1 && exChoice <= static_cast<int>(exercises.size()))
                w.deleteExercise(exChoice - 1);
        } else {
            return;
        }
    }
}

void viewSingleWorkoutFlow(WorkoutLog& log, int index, const ExerciseDatabase& db) {
    while (true) {
        Workout& w = log.getWorkout(index);
        w.displayWorkout();

        const auto& exercises = w.getExercises();
        double totalVolume = 0;
        std::map<std::string, double> muscleMap;
        for (const auto& ex : exercises) {
            totalVolume += ex.getReps() * ex.getWeight();
            for (const auto& m : ex.getPrimaryMuscles()) muscleMap[m] += ex.getReps() * ex.getWeight();
        }

        std::cout << "Exercises: " << exercises.size() << "\n";
        std::cout << "Total Volume: " << std::fixed << std::setprecision(1) << totalVolume << " lbs\n";
        if (!muscleMap.empty()) {
            std::cout << "Muscles: ";
            bool first = true;
            for (const auto& m : muscleMap) {
                if (!first) std::cout << ", ";
                std::cout << m.first << " (" << std::fixed << std::setprecision(1) << m.second << " lbs)";
                first = false;
            }
            std::cout << "\n";
        }

        std::cout << "\n1. Edit\n2. Delete\n3. Back\n";
        int choice = getValidInt("Choice: ");
        if (choice == 1) {
            editWorkoutFlow(log, index, db);
        } else if (choice == 2) {
            if (deleteWorkoutFlow(log, index)) {
                return;
            }
        } else {
            return;
        }
    }
}

void viewWorkoutsFlow(WorkoutLog& log, const ExerciseDatabase& db) {
    if (log.getWorkouts().empty()) {
        std::cout << "No workouts logged yet.\n";
        return;
    }
    int index = selectWorkoutFlow(log);
    if (index == -1) return;
    viewSingleWorkoutFlow(log, index, db);
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
        std::optional<ExerciseInfo> info = searchAndSelectExercise(db);
        if (!info) break;

        int reps = getValidInt("Enter reps: ");
        double weight = getValidDouble("Enter weight: ");

        workout.addExercise(Exercise(info->getName(), reps, weight, info->getPrimaryMuscles(), info->getSecondaryMuscles()));
    }

    log.addWorkout(workout);
    std::cout << "Workout added!\n";
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
                viewWorkoutsFlow(workoutLog, exerciseDb);
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
