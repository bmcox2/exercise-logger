#include "utils.h"

int getValidInt(const std::string& prompt) {
    std::cout << prompt;
    int input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, try again: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

double getValidDouble(const std::string& prompt) {
    std::cout << prompt;
    double input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, try again: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

std::string getValidString(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    while (input.empty()) {
        std::cout << "Invalid input, try again: ";
        std::getline(std::cin, input);
    }
    return input;
}