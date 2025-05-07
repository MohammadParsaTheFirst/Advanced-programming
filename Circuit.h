// Circuit.h
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Component.h"
#include <vector>
#include <memory>
#include <set>
#include <unordered_map>

class Circuit {
public:
    Circuit();

    void addComponent(std::shared_ptr<Component> component);

    bool hasGround() const;
    const std::set<int>& getNodes() const;

    const std::vector<std::shared_ptr<Resistor>>& getResistors() const;
    const std::vector<std::shared_ptr<Capacitor>>& getCapacitors() const;
    const std::vector<std::shared_ptr<Inductor>>& getInductors() const;
    const std::vector<std::shared_ptr<VoltageSource>>& getVoltageSources() const;
    const std::vector<std::shared_ptr<CurrentSource>>& getCurrentSources() const;
    const std::vector<std::shared_ptr<VCVS>>& getVCVSs() const;

    void listComponents() const;
    void listResistors() const;
    void listCapacitors() const;
    void listInductors() const;
    void listVoltageSources() const;
    void listCurrentSources() const;
    void listNodes() const;

    void validateCircuit() const;
    bool nodeExists(int node) const;

private:
    std::vector<std::shared_ptr<Component>> components;
    std::unordered_map<std::string, std::shared_ptr<Component>> componentMap;
    std::vector<std::shared_ptr<Resistor>> resistors;
    std::vector<std::shared_ptr<Capacitor>> capacitors;
    std::vector<std::shared_ptr<Inductor>> inductors;
    std::vector<std::shared_ptr<VoltageSource>> voltageSources;
    std::vector<std::shared_ptr<CurrentSource>> currentSources;
    std::vector<std::shared_ptr<VCVS>> vcvss;
    std::set<int> nodes;
};

#endif // CIRCUIT_H