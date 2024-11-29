#include "Observer.h"
#include <fstream>
#include <iostream>

void FileObserver::update(const std::string &event) {
    std::ofstream logFile("log.txt", std::ios::app);
    logFile << event << std::endl;
    logFile.close();
}

void ConsoleObserver::update(const std::string &event) {
    std::cout << event << std::endl;
}