#include "Editor.h"
#include "GameInstance.h"
#include "Observer.h"
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Editor editor;
    FileObserver fileObserver;
    ConsoleObserver consoleObserver;

    GameInstance::getInstance().attach(&fileObserver);
    GameInstance::getInstance().attach(&consoleObserver);
    std::cout << "Добро пожаловать в игру Balagur Fate 3" << std::endl;

    while (true) {
        std::cout << "Выберите команду:" << std::endl;
        std::cout << "Добавить врага: add <type> <name> <x> <y> (type может быть Slaver, Druid, Ork)" << std::endl;
        std::cout << "Сохранить файл: save <filename>" << std::endl;
        std::cout << "Загрузить файл: load <filename>" << std::endl;
        std::cout << "Вывести всех врагов: print" << std::endl;
        std::cout << "Запустить сражение: battle <distance> (distance - расстояние между врагами)" << std::endl;
        std::cout << "Выйти: exit" << std::endl;
        std::cout << "Введите вашу команду: ";


        std::string command;
        std::cin >> command;


        if (command == "add") {
            std::string type, name;
            int x, y;
            std::cin >> type >> name >> x >> y;
            editor.addNPC(type, name, x, y);
        } else if (command == "save") {
            std::string filename;
            std::cin >> filename;
            GameInstance::getInstance().saveNPCs(filename);
        } else if (command == "load") {
            std::string filename;
            std::cin >> filename;
            GameInstance::getInstance().loadNPCs(filename);
        } else if (command == "print") {
            GameInstance::getInstance().printNPCs();
        } else if (command == "battle") {
            int range;
            std::cin >> range;
            GameInstance::getInstance().startBattle(range);
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}