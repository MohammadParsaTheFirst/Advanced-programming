#include "NodeManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <bits/locale_facets_nonio.h>

std::string const empty = "";

NodeManager::NodeManager() : nextId(1) {}

int NodeManager::createNode(NodeType type, const std::string& name, const std::string& value) {
    int id = nextId++;
    //std::string default_value = "0"; // Provide a default value
    nodes.emplace(id, Node(id, type, name, value));
    std::cout << "Node created with ID: " << id << "\n";
    return id;
}

bool NodeManager::deleteNode(int id) {
    auto it = nodes.find(id);
    if (it != nodes.end()) {
        nodes.erase(it);
        std::cout << "Node " << id << " deleted.\n";
        return true;
    } else {
        std::cout << "Node " << id << " not found.\n";
        return false;
    }
}

void NodeManager::listNodes() const {
    if (nodes.empty()) {
        std::cout << "No nodes available.\n";
        return;
    }

    for (const auto& [id, node] : nodes) {
        std::cout << "ID: " << id << ", Name: " << node.getName() << ", Type: ";
        switch (node.getType()) {
            case NodeType::Add: std::cout << "Add"; break;
            case NodeType::Multiply: std::cout << "Multiply"; break;
            case NodeType::Constant: std::cout << "Constant"; break;
            case NodeType::Output: std::cout << "Output"; break;
            default: std::cout << "Undefined"; break;
        }
        std::cout << "\n";
    }
}

Node* NodeManager::getNode(int id) {
    auto it = nodes.find(id);
    return (it != nodes.end()) ? &it->second : nullptr;
}

bool NodeManager::createConnection(int fromId, int toId) {
    Node* from = getNode(fromId);
    Node* to = getNode(toId);
    if (!from || !to) {
        std::cout << "Invalid node IDs.\n";
        return false;
    }

    // Prevent duplicate connections
    for (const auto& conn : connections) {
        if (conn.fromNodeId == fromId && conn.toNodeId == toId) {
            std::cout << "Connection already exists.\n";
            return false;
        }
    }

    from->addOutput(toId);
    to->addInput(fromId);
    connections.emplace_back(fromId, toId);
    std::cout << "Connection created: " << fromId << " -> " << toId << "\n";
    return true;
}

bool NodeManager::deleteConnection(int fromId, int toId) {
    auto it = std::remove_if(connections.begin(), connections.end(),
        [=](const Connection& conn) {
            return conn.fromNodeId == fromId && conn.toNodeId == toId;
        });

    if (it == connections.end()) {
        std::cout << "Connection not found.\n";
        return false;
    }

    connections.erase(it, connections.end());

    // Remove from input/output lists
    if (Node* from = getNode(fromId)) {
        auto& outs = from->getOutputs();
        outs.erase(std::remove(outs.begin(), outs.end(), toId), outs.end());
    }
    if (Node* to = getNode(toId)) {
        auto& ins = to->getInputs();
        ins.erase(std::remove(ins.begin(), ins.end(), fromId), ins.end());
    }

    std::cout << "Connection deleted: " << fromId << " -> " << toId << "\n";
    return true;
}

void NodeManager::listConnections() const {
    if (connections.empty()) {
        std::cout << "No connections.\n";
        return;
    }

    for (const auto& conn : connections) {
        std::cout << conn.fromNodeId << " -> " << conn.toNodeId << "\n";
    }
}

bool NodeManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "# Nodes\n";
    for (const auto& [id, node] : nodes) {
        file << node.getId() << " " << node.getName() << " " << node.getValue() << "\n";
    }

    file << "# Connections\n";
    for (const auto& conn : connections) {
        file << conn.fromNodeId << " " << conn.toNodeId << "\n";
    }

    return true;
}

bool NodeManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    nodes.clear();
    connections.clear();

    std::string line;
    bool readingNodes = false, readingConnections = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') {
            if (line.find("Nodes") != std::string::npos) {
                readingNodes = true;
                readingConnections = false;
            } else if (line.find("Connections") != std::string::npos) {
                readingNodes = false;
                readingConnections = true;
            }
            continue;
        }

        std::istringstream iss(line);
        if (readingNodes) {
            int id;
            std::string name;
            std::string value;
            iss >> id >> name >> value;
            NodeType type = NodeType::Constant; // Default type when loading
            nodes.emplace(id, Node(id, type, name, value));
        } else if (readingConnections) {
            int fromId, toId;
            iss >> fromId >> toId;
            createConnection(fromId, toId);
        }
    }

    return true;
}

void NodeManager::addNode(const std::string& name, int id) {
    NodeType type = NodeType::Constant; // Default type when adding
    std::string value = "0"; // Default value
    nodes.emplace(id, Node(id, type, name, value));
}

void NodeManager::addConnection(int fromId, int toId) {
    Node* from = getNode(fromId);
    Node* to = getNode(toId);
    if (from && to) {
        from->addOutput(toId);
        to->addInput(fromId);
        connections.emplace_back(fromId, toId);
    }
}







// #include "NodeManager.h"
//
// #include <fstream>
// #include <sstream>
// #include <algorithm>
// #include <iostream>
// #include <bits/locale_facets_nonio.h>
// std::string const empty = "";
// NodeManager::NodeManager() : nextId(1) {}
//
// int NodeManager::createNode(NodeType type, const std::string& name, const std::string& value); {
//     int id = nextId++;
//     nodes.emplace(id, Node(id, type, name, value));
//     std::cout << "Node created with ID: " << id << "\n";
//     return id;
// }
//
// bool NodeManager::deleteNode(int id) {
//     auto it = nodes.find(id);
//     if (it != nodes.end()) {
//         nodes.erase(it);
//         std::cout << "Node " << id << " deleted.\n";
//         return true;
//     } else {
//         std::cout << "Node " << id << " not found.\n";
//         return false;
//     }
// }
//
// void NodeManager::listNodes() const {
//     if (nodes.empty()) {
//         std::cout << "No nodes available.\n";
//         return;
//     }
//
//     for (const auto& [id, node] : nodes) {
//         std::cout << "ID: " << id << ", Name: " << node.getName() << ", Type: ";
//         switch (node.getType()) {
//             case NodeType::Add: std::cout << "Add"; break;
//             case NodeType::Multiply: std::cout << "Multiply"; break;
//             case NodeType::Constant: std::cout << "Constant"; break;
//             case NodeType::Output: std::cout << "Output"; break;
//             default: std::cout << "Undefined"; break;
//         }
//         std::cout << "\n";
//     }
// }
//
// Node* NodeManager::getNode(int id) {
//     auto it = nodes.find(id);
//     return (it != nodes.end()) ? &it->second : nullptr;
// }
//
// bool NodeManager::createConnection(int fromId, int toId) {
//     Node* from = getNode(fromId);
//     Node* to = getNode(toId);
//     if (!from || !to) {
//         std::cout << "Invalid node IDs.\n";
//         return false;
//     }
//
//     // Prevent duplicate connections
//     for (const auto& conn : connections) {
//         if (conn.fromNodeId == fromId && conn.toNodeId == toId) {
//             std::cout << "Connection already exists.\n";
//             return false;
//         }
//     }
//
//     from->addOutput(toId);
//     to->addInput(fromId);
//     connections.emplace_back(fromId, toId);
//     std::cout << "Connection created: " << fromId << " -> " << toId << "\n";
//     return true;
// }
//
// bool NodeManager::deleteConnection(int fromId, int toId) {
//     auto it = std::remove_if(connections.begin(), connections.end(),
//         [=](const Connection& conn) {
//             return conn.fromNodeId == fromId && conn.toNodeId == toId;
//         });
//
//     if (it == connections.end()) {
//         std::cout << "Connection not found.\n";
//         return false;
//     }
//
//     connections.erase(it, connections.end());
//
//     // Remove from input/output lists
//     if (Node* from = getNode(fromId)) {
//         auto& outs = from->getOutputs();
//         from->getOutputs().erase(std::remove(outs.begin(), outs.end(), toId), outs.end());
//     }
//     if (Node* to = getNode(toId)) {
//         auto& ins = to->getInputs();
//         to->getInputs().erase(std::remove(ins.begin(), ins.end(), fromId), ins.end());
//     }
//
//     std::cout << "Connection deleted: " << fromId << " -> " << toId << "\n";
//     return true;
// }
//
// void NodeManager::listConnections() const {
//     if (connections.empty()) {
//         std::cout << "No connections.\n";
//         return;
//     }
//
//     for (const auto& conn : connections) {
//         std::cout << conn.fromNodeId << " -> " << conn.toNodeId << "\n";
//     }
// }
//
//
// bool NodeManager::saveToFile(const std::string& filename) const {
//     std::ofstream file(filename);
//     if (!file.is_open()) return false;
//
//     file << "# Nodes\n";
//     for (const auto& [id, node] : nodes) {
//         file << node.getId() << " " << node.getName() << " " << node.getValue() << "\n";
//         for (int outId : node.getOutputs()) {
//             file << node.getId() << " " << outId << "\n";
//         }
//     }
//
//
//     file << "# Connections\n";
//     for (const auto& [id, node] : nodes) {
//         for (int outId : node.getOutputs()) {
//             file << node.getId() << " " << outId << "\n";
//         }
//     }
//
//     return true;
// }
//
// bool NodeManager::loadFromFile(const std::string& filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) return false;
//
//     nodes.clear(); // clear existing nodes
//
//     std::string line;
//     bool readingNodes = false, readingConnections = false;
//
//     while (std::getline(file, line)) {
//         if (line.empty()) continue;
//         if (line[0] == '#') {
//             if (line.find("Nodes") != std::string::npos) {
//                 readingNodes = true;
//                 readingConnections = false;
//             } else if (line.find("Connections") != std::string::npos) {
//                 readingNodes = false;
//                 readingConnections = true;
//             }
//             continue;
//         }
//
//         std::istringstream iss(line);
//         if (readingNodes) {
//             int id;
//             std::string name;
//             float value;
//             iss >> id >> name >> value;
//             this->addNode(name, id);  // allow specifying ID
//             nodes[id].getValue() = value;
//         } else if (readingConnections) {
//             int fromId, toId;
//             iss >> fromId >> toId;
//             this->addConnection(fromId, toId);
//         }
//     }
//
//     return true;
// }
//
// void NodeManager::addNode(const std::string& name, int id, NodeType type, std::string& value) {
//     nodes[id] = Node(id, type, name, value);
// }
//
// void NodeManager::addConnection(int fromId, int toId) {
//     nodes[fromId].addOutput(toId);
//     connections.emplace_back(fromId, toId);
// }
