#include "Node.h"

Node::Node(int id, NodeType type, const std::string& name, const std::string& value)
    : id(id), type(type), name(name), value(value) {}

// int Node::getId() const {
//     return id;
// }

NodeType Node::getType() const {
    return type;
}

// std::string Node::getName() const {
//     return name;
// }

void Node::addInput(int nodeId) {
    inputs.push_back(nodeId);
}

void Node::addOutput(int nodeId) {
    outputs.push_back(nodeId);
}

std::vector<int>& Node::getInputs() {
    return inputs;
}

std::vector<int>& Node::getOutputs()  {
    return outputs;
}

