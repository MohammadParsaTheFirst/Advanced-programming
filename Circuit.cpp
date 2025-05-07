// Circuit.cpp
#include "Circuit.h"
#include <iostream>
#include <stdexcept>

Circuit::Circuit() {
    nodes.insert(0); // Ground node always exists
}

void Circuit::addComponent(std::shared_ptr<Component> component) {
    // Check for duplicate names
    if (componentMap.find(component->getName()) != componentMap.end()) {
        throw std::runtime_error("ERROR: Component " + component->getName() + " already exists");
    }

    // Validate nodes
    if (component->getNode1() < 0 || component->getNode2() < 0) {
        throw std::runtime_error("ERROR: Node numbers must be non-negative");
    }

    // Add to appropriate lists
    components.push_back(component);
    componentMap[component->getName()] = component;
    nodes.insert(component->getNode1());
    nodes.insert(component->getNode2());

    // Add to type-specific lists
    switch (component->getType()) {
        case ComponentType::RESISTOR:
            resistors.push_back(std::dynamic_pointer_cast<Resistor>(component));
            break;
        case ComponentType::CAPACITOR:
            capacitors.push_back(std::dynamic_pointer_cast<Capacitor>(component));
            break;
        case ComponentType::INDUCTOR:
            inductors.push_back(std::dynamic_pointer_cast<Inductor>(component));
            break;
        case ComponentType::VOLTAGE_SOURCE:
            voltageSources.push_back(std::dynamic_pointer_cast<VoltageSource>(component));
            break;
        case ComponentType::CURRENT_SOURCE:
            currentSources.push_back(std::dynamic_pointer_cast<CurrentSource>(component));
            break;
        case ComponentType::VCVS:
            vcvss.push_back(std::dynamic_pointer_cast<VCVS>(component));
            break;
        default:
            break;
    }
}

bool Circuit::hasGround() const {
    return nodes.find(0) != nodes.end();
}

const std::set<int>& Circuit::getNodes() const {
    return nodes;
}

const std::vector<std::shared_ptr<Resistor>>& Circuit::getResistors() const {
    return resistors;
}

const std::vector<std::shared_ptr<Capacitor>>& Circuit::getCapacitors() const {
    return capacitors;
}

const std::vector<std::shared_ptr<Inductor>>& Circuit::getInductors() const {
    return inductors;
}

const std::vector<std::shared_ptr<VoltageSource>>& Circuit::getVoltageSources() const {
    return voltageSources;
}

const std::vector<std::shared_ptr<CurrentSource>>& Circuit::getCurrentSources() const {
    return currentSources;
}

const std::vector<std::shared_ptr<VCVS>>& Circuit::getVCVSs() const {
    return vcvss;
}

void Circuit::listComponents() const {
    std::cout << "All Components:" << std::endl;
    for (const auto& comp : components) {
        comp->print();
    }
}

void Circuit::listResistors() const {
    std::cout << "Resistors:" << std::endl;
    for (const auto& r : resistors) {
        r->print();
    }
}

void Circuit::listCapacitors() const {
    std::cout << "Capacitors:" << std::endl;
    for (const auto& c : capacitors) {
        c->print();
    }
}

void Circuit::listInductors() const {
    std::cout << "Inductors:" << std::endl;
    for (const auto& l : inductors) {
        l->print();
    }
}

void Circuit::listVoltageSources() const {
    std::cout << "Voltage Sources:" << std::endl;
    for (const auto& vs : voltageSources) {
        vs->print();
    }
}

void Circuit::listCurrentSources() const {
    std::cout << "Current Sources:" << std::endl;
    for (const auto& cs : currentSources) {
        cs->print();
    }
}

void Circuit::listNodes() const {
    std::cout << "Circuit Nodes:";
    for (int node : nodes) {
        std::cout << " " << node;
    }
    std::cout << std::endl;
}

void Circuit::validateCircuit() const {
    if (!hasGround()) {
        throw std::runtime_error("ERROR: No ground node detected");
    }

    // Check for disconnected components
    std::set<int> connectedNodes;
    for (const auto& comp : components) {
        connectedNodes.insert(comp->getNode1());
        connectedNodes.insert(comp->getNode2());
    }

    if (connectedNodes.size() != nodes.size()) {
        throw std::runtime_error("ERROR: Circuit has disconnected components");
    }
}

bool Circuit::nodeExists(int node) const {
    return nodes.find(node) != nodes.end();
}