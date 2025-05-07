#include "NodeManager.h"
#include <iostream>
#include <sstream>

NodeType parseNodeType(const std::string& str) {
    if (str == "add") return NodeType::Add;
    if (str == "multiply") return NodeType::Multiply;
    if (str == "constant") return NodeType::Constant;
    if (str == "output") return NodeType::Output;
    return NodeType::Undefined;
}
//git push -u origin project
int main() {
    NodeManager manager;
    std::string input;

    std::cout << "Simple Node CLI. Type 'help' for commands.\n";

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "create") {
            std::string typeStr, name, value;
            iss >> typeStr >> name >> value;
            if (typeStr.empty() || name.empty() || value.empty()) {
                std::cout << "Usage: create [type] [name]\n";
                continue;
            }
            NodeType type = parseNodeType(typeStr);
            if (type == NodeType::Undefined) {
                std::cout << "Invalid type. Use add, multiply, constant, output.\n";
                continue;
            }
            manager.createNode(type, name, value);

        } else if (command == "delete") {
            int id;
            iss >> id;
            if (!iss) {
                std::cout << "Usage: delete [id]\n";
                continue;
            }
            manager.deleteNode(id);

        } else if (command == "list") {
            manager.listNodes();

        } else if (command == "help") {
            std::cout << "Commands:\n"
                      << "  create [type] [name]   - Create a node\n"
                      << "  delete [id]            - Delete a node\n"
                      << "  list                   - List all nodes\n"
                      << "  exit                   - Exit the program\n";

        } else if (command == "connect") {
            int from, to;
            iss >> from >> to;
            if (!iss) {
                std::cout << "Usage: connect [fromId] [toId]\n";
                continue;
            }
            manager.createConnection(from, to);

        } else if (command == "disconnect") {
            int from, to;
            iss >> from >> to;
            if (!iss) {
                std::cout << "Usage: disconnect [fromId] [toId]\n";
                continue;
            }
            manager.deleteConnection(from, to);

        } else if (command == "wires") {
            manager.listConnections();
        } else if (command == "exit") {
            break;

        } else {
            std::cout << "Unknown command. Type 'help' for list.\n";
        }
    }

    return 0;
}
