#include "Component.h"
#include <iostream>

// === Component base class implementation ===

Component::Component(const std::string& name, ComponentType type, int node1, int node2, double value)
    : name(name), type(type), node1(node1), node2(node2), value(value) {}

std::string Component::getName() const {
    return name;
}

ComponentType Component::getType() const {
    return type;
}

int Component::getNode1() const {
    return node1;
}

int Component::getNode2() const {
    return node2;
}

double Component::getValue() const {
    return value;
}

void Component::print() const {
    std::cout << "Component " << name << ": Type=" << static_cast<int>(type)
              << ", Nodes=(" << node1 << "," << node2 << "), Value=" << value << std::endl;
}

// === Derived component class implementations ===

Resistor::Resistor(const std::string& name, int node1, int node2, double resistance)
    : Component(name, ComponentType::RESISTOR, node1, node2, resistance) {}

Capacitor::Capacitor(const std::string& name, int node1, int node2, double capacitance)
    : Component(name, ComponentType::CAPACITOR, node1, node2, capacitance) {}

Inductor::Inductor(const std::string& name, int node1, int node2, double inductance)
    : Component(name, ComponentType::INDUCTOR, node1, node2, inductance) {}

VoltageSource::VoltageSource(const std::string& name, int node1, int node2, double voltage)
    : Component(name, ComponentType::VOLTAGE_SOURCE, node1, node2, voltage) {}

CurrentSource::CurrentSource(const std::string& name, int node1, int node2, double current)
    : Component(name, ComponentType::CURRENT_SOURCE, node1, node2, current) {}

// === VCVS implementation ===

VCVS::VCVS(const std::string& name, int node1, int node2, int ctrlNode1, int ctrlNode2, double gain)
    : Component(name, ComponentType::VCVS, node1, node2, gain),
      ctrlNode1(ctrlNode1), ctrlNode2(ctrlNode2) {}

int VCVS::getCtrlNode1() const {
    return ctrlNode1;
}

int VCVS::getCtrlNode2() const {
    return ctrlNode2;
}
