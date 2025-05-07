#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

// Enum for component types
enum class ComponentType {
    RESISTOR,
    CAPACITOR,
    INDUCTOR,
    VOLTAGE_SOURCE,
    CURRENT_SOURCE,
    VCVS,  // Voltage-Controlled Voltage Source
    CCVS,  // Current-Controlled Voltage Source
    VCCS,  // Voltage-Controlled Current Source
    CCCS   // Current-Controlled Current Source
};

// Base class for all circuit components
class Component {
public:
    Component(const std::string& name, ComponentType type, int node1, int node2, double value);
    virtual ~Component() = default;

    std::string getName() const;
    ComponentType getType() const;
    int getNode1() const;
    int getNode2() const;
    double getValue() const;

    virtual void print() const;

protected:
    std::string name;
    ComponentType type;
    int node1;
    int node2;
    double value;
};

// Derived component classes
class Resistor : public Component {
public:
    Resistor(const std::string& name, int node1, int node2, double resistance);
};

class Capacitor : public Component {
public:
    Capacitor(const std::string& name, int node1, int node2, double capacitance);
};

class Inductor : public Component {
public:
    Inductor(const std::string& name, int node1, int node2, double inductance);
};

class VoltageSource : public Component {
public:
    VoltageSource(const std::string& name, int node1, int node2, double voltage);
};

class CurrentSource : public Component {
public:
    CurrentSource(const std::string& name, int node1, int node2, double current);
};

// Dependent Sources

class VCVS : public Component {
public:
    VCVS(const std::string& name, int node1, int node2, int ctrlNode1, int ctrlNode2, double gain);
    int getCtrlNode1() const;
    int getCtrlNode2() const;

private:
    int ctrlNode1;
    int ctrlNode2;
};

// TODO: Add CCVS, VCCS, CCCS similarly

#endif // COMPONENT_H
