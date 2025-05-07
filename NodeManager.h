#pragma once
#include "Node.h"
#include "Connection.h"
#include <unordered_map>
#include <vector>

class NodeManager {
public:
    NodeManager();

    int createNode(NodeType type, const std::string& name, const std::string& value);
    bool deleteNode(int id);
    void listNodes() const;

    bool createConnection(int fromId, int toId);
    bool deleteConnection(int fromId, int toId);
    void listConnections() const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    void addNode(const std::string& name, int id); // for file loading
    void addConnection(int fromId, int toId);

    Node* getNode(int id);

private:
    int nextId;
    std::vector<Connection> connections;
    std::unordered_map<int, Node> nodes;
};

