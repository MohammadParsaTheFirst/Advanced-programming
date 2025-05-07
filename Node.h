#pragma once
#include <string>
#include <vector>

enum class NodeType {
    Add,
    Multiply,
    Constant,
    Output,
    Undefined
};

class Node {
public:
    Node(int id, NodeType type, const std::string& name, const std::string& value);

    //int getId() const;
    NodeType getType() const;
    //std::string getName() const;

    void addInput(int nodeId);
    void addOutput(int nodeId);

    std::vector<int>& getInputs();
    std::vector<int>& getOutputs();

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getValue() const { return value; }
    const std::vector<int>& getOutputs() const { return outputs; } // use const here


private:
    int id;
    NodeType type;
    std::string name;
    std::string value;
    std::vector<int> inputs;
    std::vector<int> outputs;
};
