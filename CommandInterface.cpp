#include "CommandInterface.h"
#include "Circuit.h"
#include "Component.h"
#include "MatrixAnalyzer.h"

#include <sstream>
#include <iterator>
#include <iostream>
#include <stdexcept>

CommandInterface::CommandInterface()
    : currentCircuit(std::make_shared<Circuit>()) {}

double CommandInterface::parseSpiceValue(const std::string& valueStr) {
    static std::unordered_map<char, double> units = {
        {'T', 1e12}, {'G', 1e9}, {'M', 1e6}, {'K', 1e3}, {'k', 1e3},
        {'m', 1e-3}, {'U', 1e-6}, {'u', 1e-6}, {'N', 1e-9}, {'n', 1e-9},
        {'P', 1e-12}, {'p', 1e-12}, {'F', 1e-15}, {'f', 1e-15}
    };

    if (valueStr.empty()) return 0.0;

    char lastChar = valueStr.back();
    if (isalpha(lastChar)) {
        double num = stod(valueStr.substr(0, valueStr.size()-1));
        auto it = units.find(toupper(lastChar));
        if (it != units.end()) {
            return num * it->second;
        }
    }
    return stod(valueStr);
}

int parseNodeName(const std::string& nodeName) {
    // Handle ground node
    if (nodeName == "GND" || nodeName == "0") {
        return 0;
    }

    // Handle SPICE-style nodes (Nxxx)
    if (nodeName[0] == 'N' || nodeName[0] == 'n') {
        try {
            return std::stoi(nodeName.substr(1));
        } catch (...) {
            throw std::runtime_error("Invalid node format: " + nodeName);
        }
    }

    // Handle pure numeric nodes
    try {
        return std::stoi(nodeName);
    } catch (...) {
        throw std::runtime_error("Invalid node format: " + nodeName);
    }
}

void CommandInterface::handleSpiceComponent(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4) {
        throw std::runtime_error("Invalid SPICE component syntax");
    }

    char typeChar = toupper(tokens[0][0]);
    std::string name = tokens[0];
    int node1 = parseNodeName(tokens[1]);  // Convert to integer
    int node2 = parseNodeName(tokens[2]);
    double value = parseSpiceValue(tokens[3]);

    switch(typeChar) {
        case 'R': {
            auto r = std::make_shared<Resistor>(name, node1, node2, value);
            currentCircuit->addComponent(r);
            std::cout << "Added resistor " << name << '\n';
            break;
        }
        case 'C': {
            auto c = std::make_shared<Capacitor>(name, node1, node2, value);
            currentCircuit->addComponent(c);
            std::cout << "Added capacitor " << name << '\n';
            break;
        }
        case 'L': {
            auto l = std::make_shared<Inductor>(name, node1, node2, value);
            currentCircuit->addComponent(l);
            std::cout << "Added inductor " << name << '\n';
            break;
        }
        case 'V': {
            auto v = std::make_shared<VoltageSource>(name, node1, node2, value);
            currentCircuit->addComponent(v);
            std::cout << "Added voltage source " << name << '\n';
            break;
        }
        case 'I': {
            auto i = std::make_shared<CurrentSource>(name, node1, node2, value);
            currentCircuit->addComponent(i);
            std::cout << "Added current source " << name << '\n';
            break;
        }
        default:
            throw std::runtime_error("Unknown SPICE component type: " + std::string(1, typeChar));
    }
}

void CommandInterface::processCommand(const std::string& command) {
    auto tokens = splitCommand(command);
    if (tokens.empty()) return;

    const std::string& cmd = tokens[0];

    // Check for SPICE-style component definition
    if (tokens.size() >= 4 && (cmd[0] == 'R' || cmd[0] == 'C' || cmd[0] == 'L' ||
                               cmd[0] == 'V' || cmd[0] == 'I')) {
        handleSpiceComponent(tokens);
        return;
                               }

    try {
        const std::string& cmd = tokens[0];
        if (cmd == "add") handleAdd(tokens);
        else if (cmd == "list") handleList(tokens);
        else if (cmd == "nodes") currentCircuit->listNodes();
        else if (cmd == "analyze") analyze();
        else if (cmd == "help") printHelp();
        else std::cout << "ERROR: Unknown command\n";
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n';
    }
}

std::vector<std::string> CommandInterface::splitCommand(const std::string& input) {
    std::istringstream iss(input);
    return {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
}
// here to change
// void CommandInterface::handleAdd(const std::vector<std::string>& tokens) {
//     if (tokens.size() < 2) throw std::runtime_error("Invalid add command syntax");
//     const auto& type = tokens[1];
//     if (type == "Resistor" || type == "R") addResistor(tokens);
//     else if (type == "Capacitor" || type == "C") addCapacitor(tokens);
//     else if (type == "Inductor" || type == "L") addInductor(tokens);
//     else if (type == "VoltageSource" || type == "V") addVoltageSource(tokens);
//     else if (type == "CurrentSource" || type == "I") addCurrentSource(tokens);
//     else throw std::runtime_error("Unknown component type: " + type);
// }
void CommandInterface::handleAdd(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        throw std::runtime_error("Invalid add command syntax");
    }
    const auto& type = tokens[1];
    // Support both full names and single-letter codes
    if (type == "Resistor" || type == "R") addResistor(tokens);
    else if (type == "Capacitor" || type == "C") addCapacitor(tokens);
    else if (type == "Inductor" || type == "L") addInductor(tokens);
    else if (type == "VoltageSource" || type == "V") addVoltageSource(tokens);
    else if (type == "CurrentSource" || type == "I") addCurrentSource(tokens);
    else {
        // Try to interpret as SPICE-style even after 'add'
        std::vector<std::string> spiceTokens(tokens.begin() + 1, tokens.end());
        handleSpiceComponent(spiceTokens);
    }
}

void CommandInterface::addResistor(const std::vector<std::string>& tokens) {
    if (tokens.size() != 6)
        throw std::runtime_error("Usage: add Resistor <name> <node1> <node2> <value>");
    auto r = std::make_shared<Resistor>(tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]));
    currentCircuit->addComponent(r);
    std::cout << "Added resistor " << tokens[2] << '\n';
}

void CommandInterface::addCapacitor(const std::vector<std::string>& tokens) {
    if (tokens.size() != 6)
        throw std::runtime_error("Usage: add Capacitor <name> <node1> <node2> <value>");
    auto c = std::make_shared<Capacitor>(tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]));
    currentCircuit->addComponent(c);
    std::cout << "Added capacitor " << tokens[2] << '\n';
}

void CommandInterface::addInductor(const std::vector<std::string>& tokens) {
    if (tokens.size() != 6)
        throw std::runtime_error("Usage: add Inductor <name> <node1> <node2> <value>");
    auto l = std::make_shared<Inductor>(tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]));
    currentCircuit->addComponent(l);
    std::cout << "Added inductor " << tokens[2] << '\n';
}

void CommandInterface::addVoltageSource(const std::vector<std::string>& tokens) {
    if (tokens.size() != 6)
        throw std::runtime_error("Usage: add VoltageSource <name> <node1> <node2> <value>");
    auto v = std::make_shared<VoltageSource>(tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]));
    currentCircuit->addComponent(v);
    std::cout << "Added voltage source " << tokens[2] << '\n';
}

void CommandInterface::addCurrentSource(const std::vector<std::string>& tokens) {
    if (tokens.size() != 6)
        throw std::runtime_error("Usage: add CurrentSource <name> <node1> <node2> <value>");
    auto i = std::make_shared<CurrentSource>(tokens[2], std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]));
    currentCircuit->addComponent(i);
    std::cout << "Added current source " << tokens[2] << '\n';
}

void CommandInterface::handleList(const std::vector<std::string>& tokens) {
    if (tokens.size() == 1) {
        currentCircuit->listComponents();
    } else if (tokens.size() == 2) {
        const auto& type = tokens[1];
        if (type == "Resistors" || type == "R") currentCircuit->listResistors();
        else if (type == "Capacitors" || type == "C") currentCircuit->listCapacitors();
        else if (type == "Inductors" || type == "L") currentCircuit->listInductors();
        else if (type == "VoltageSources" || type == "V") currentCircuit->listVoltageSources();
        else if (type == "CurrentSources" || type == "I") currentCircuit->listCurrentSources();
        else throw std::runtime_error("Unknown component type for listing");
    } else {
        throw std::runtime_error("Invalid list command syntax");
    }
}

void CommandInterface::analyze() {
    if (!currentCircuit->hasGround())
        throw std::runtime_error("No ground node detected in the circuit");

    MatrixAnalyzer analyzer(*currentCircuit);
    analyzer.buildDCMatrix();
    analyzer.solveDC();
    analyzer.printSolution();
}

void CommandInterface::printHelp() {
    std::cout << "Available commands:\n"
              << "  add <component> <name> <node1> <node2> <value>\n"
              << "  list [type]       - List components or by type\n"
              << "  nodes             - List all nodes\n"
              << "  analyze           - Perform DC analysis\n"
              << "  help              - Show help message\n";
}
