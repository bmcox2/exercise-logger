CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -I include -I .
TARGET = logger
OBJS = src/main.o src/Workout.o src/Exercise.o src/WorkoutLog.o src/utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: src/main.cpp Workout.h include/Exercise.h include/WorkoutLog.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp

Workout.o: src/Workout.cpp include/Workout.h
	$(CXX) $(CXXFLAGS) -c src/Workout.cpp

Exercise.o: src/Exercise.cpp include/Exercise.h
	$(CXX) $(CXXFLAGS) -c src/Exercise.cpp

WorkoutLog.o: src/WorkoutLog.cpp include/WorkoutLog.h
	$(CXX) $(CXXFLAGS) -c src/WorkoutLog.cpp

utils.o: src/utils.cpp include/utils.h
	$(CXX) $(CXXFLAGS) -c src/utils.h

clean:
	rm -f *.o *.exe $(TARGET)