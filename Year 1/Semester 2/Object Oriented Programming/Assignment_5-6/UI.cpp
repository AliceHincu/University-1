//
// Created by Octavian Custura on 20/03/2020.
//

#include "UI.h"
#include <iostream>
#include <map>
#include <functional>
#define MAX_PARAMETERS 5
UI::UI(Service& service) {
    this->service = service;
}

void UI::runProgramAdministrator() {
    std::map<std::string, std::function<void(UI&, std::string)>> mapOfChoices;
    mapOfChoices["add"] = &UI::addElement;
    mapOfChoices["delete"] = &UI::removeElement;
    mapOfChoices["update"] = &UI::updateElement;
    mapOfChoices["list"] = &UI::listAllElements;
    mapOfChoices["mode"] = &UI::changeMode;
    while(true) {
        std::string stringLine;
        std::getline(std::cin, stringLine);
        std::string command;
        bool isCommand = true;
        std::string parameters;
        for (char stringLineIndex : stringLine) {
            if (isCommand and stringLineIndex != ' ') {
                command += stringLineIndex;
            } else if (isCommand) {
                isCommand = false;
            }else {
                parameters += stringLineIndex;
            }
        }
        if (command == "exit") {
            exit(0);
        }
        auto currentChoice = mapOfChoices.find(command);
        if (currentChoice == mapOfChoices.end()) {
            std::cout << "Invalid command\n";
        }else {
            mapOfChoices[command](*this, parameters);
        }
    }
}

void UI::runProgramFieldAgent() {
    std::map<std::string, std::function<void(UI&, std::string)>> mapOfChoices;
    mapOfChoices["next"] = &UI::nextElement;
    mapOfChoices["save"] = &UI::saveTitle;
    mapOfChoices["list"] = &UI::listProperty;
    mapOfChoices["mylist"] = &UI::myList;
    mapOfChoices["mode"] = &UI::changeMode;
    while(true) {
        std::string stringLine;
        std::getline(std::cin, stringLine);
        std::string command;
        bool isCommand = true;
        std::string parameters;
        for (char stringLineIndex : stringLine) {
            if (isCommand and stringLineIndex != ' ') {
                command += stringLineIndex;
            } else if (isCommand) {
                isCommand = false;
            }else {
                parameters += stringLineIndex;
            }
        }
        if (command == "exit") {
            exit(0);
        }
        auto currentChoice = mapOfChoices.find(command);
        if (currentChoice == mapOfChoices.end()) {
            std::cout << "Invalid command\n";
        }else {
            mapOfChoices[command](*this, parameters);
        }
    }
}

void UI::addElement(const std::string& commandParameters) {
    std::string ArrayOfParameters[MAX_PARAMETERS];
    int currentCommand = 0;
    for (auto commandParametersElement: commandParameters) {
        if (commandParametersElement != ',') {
            ArrayOfParameters[currentCommand] += commandParametersElement;
        }else {
            currentCommand++;
        }
    }
    try {
        service.addFootage(ArrayOfParameters[0], ArrayOfParameters[1], ArrayOfParameters[2], ArrayOfParameters[3], ArrayOfParameters[4]);
    }catch (std::exception& exception) {
        std::cout << "Invalid parameters\n";
    }
}

void UI::removeElement(const std::string &commandParameters) {
    try {
        service.deleteFootage(commandParameters);
    }catch (std::exception& exception){
        std::cout << "Invalid parameters\n";
    }
}

void UI::updateElement(const std::string &commandParameters) {
    std::string ArrayOfParameters[MAX_PARAMETERS];
    int currentCommand = 0;
    for (auto commandParametersElement: commandParameters) {
        if (commandParametersElement != ',') {
            ArrayOfParameters[currentCommand] += commandParametersElement;
        }else {
            currentCommand++;
        }
    }
    try {
        service.updateFootage(ArrayOfParameters[0], ArrayOfParameters[1], ArrayOfParameters[2], ArrayOfParameters[3], ArrayOfParameters[4]);
    }catch (std::exception& exception) {
        std::cout << "Invalid parameters\n";
    }
}

void UI::listAllElements(const std::string &commandParameters) {
    DynamicArray<Footage> arrayOfFootage = service.getAllElements();
    if (arrayOfFootage.getSize() == 0) {
        std::cout << "There are no footage in the list\n";
        return;
    }
    for (int arrayOfFootageIndex = 0; arrayOfFootageIndex < arrayOfFootage.getSize(); ++arrayOfFootageIndex) {
        std::cout << arrayOfFootage.getElement(arrayOfFootageIndex).toString() << "\n";
    }
}

void UI::runProgram() {
    std::string modeLine;
    std::getline(std::cin, modeLine);
    std::string command, mode;
    bool isCommand = true;
    for (auto modeLineIndex: modeLine) {
        if (isCommand and modeLineIndex != ' ') {
            command += modeLineIndex;
        }else if (isCommand) {
            isCommand = false;
        }else if (modeLineIndex != ' ') {
            mode += modeLineIndex;
        }
    }
    if (command != "mode") {
        std::cout << "Invalid command\n";
    }else {
        changeMode(mode);
    }
}

void UI::changeMode(const std::string &commandParameters) {
    if (commandParameters == "A") {
        runProgramAdministrator();
    }else if (commandParameters == "B") {
        runProgramFieldAgent();
    } else {
            std::cout <<"Invalid mode\n";
    }
}

void UI::nextElement(const std::string &commandParameters) {
    Footage currentFootage = service.getCurrent();
    std::cout << currentFootage.toString() << '\n';
}

void UI::saveTitle(const std::string &commandParameters) {
    try {
        service.addToMyList(commandParameters);
    }catch (std::exception&) {
        std::cout << "Invalid title" << '\n';
    }
}

void UI::myList(const std::string &commandParameters) {
    auto myListFootage = service.getMyList();
    for (int myListIndex = 0; myListIndex < myListFootage.getSize(); ++myListIndex) {
        std::cout << myListFootage.getElement(myListIndex).toString() << '\n';
    }
}

void UI::listProperty(const std::string &commandParameters) {
    std::string ArrayOfParameters[MAX_PARAMETERS];
    int currentCommand = 0;
    for (auto commandParametersElement: commandParameters) {
        if (commandParametersElement != ',') {
            ArrayOfParameters[currentCommand] += commandParametersElement;
        }else {
            currentCommand++;
        }
    }
    DynamicArray<Footage> filteredListOfFootage;
    try {
        filteredListOfFootage = service.getFilteredList(ArrayOfParameters[0], ArrayOfParameters[1]);
    }catch (std::exception&) {
        std::cout << "Invalid parameters\n";
    }
    if (filteredListOfFootage.getSize() == 0) {
        std::cout << "There are no elements with given property\n";
    }else {
        for (int filteredListIndex = 0; filteredListIndex < filteredListOfFootage.getSize(); ++filteredListIndex) {
            std::cout << filteredListOfFootage.getElement(filteredListIndex).toString() << '\n';
        }
    }
}


