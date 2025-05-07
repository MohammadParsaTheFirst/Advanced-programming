#include <iostream>

#include "CommandInterface.h"


int main() {
    CommandInterface cmdInterface;
    std::string command;

    std::cout << "Simple Circuit Simulator (type 'help' for commands, 'exit' to quit)\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        cmdInterface.processCommand(command);
    }

    return 0;
}
