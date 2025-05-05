#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

enum class NodeType { None, Drawing, Peg, Composite };

class Node {
public:
    Node(int x, int y, std::string label) : x(x), y(y), label(std::move(label)), dragging(false) {}
    virtual ~Node() = default;

    virtual void render(SDL_Renderer* renderer, TTF_Font* font);
    virtual bool canConnectTo(Node* other, bool fromTop) = 0;
    virtual SDL_Color getColor() const = 0;

    // Get port positions for rendering connections
    SDL_Point getTopPort() const { return { x + 50, y }; }
    SDL_Point getBottomPort(int index) const { return { x + 50, y + 50 }; }

    int x, y;
    std::string label;
    bool dragging;
};

class DrawingNode : public Node {
public:
    DrawingNode(int x, int y) : Node(x, y, "Drawing") {}
    bool canConnectTo(Node* other, bool fromTop) override;
    SDL_Color getColor() const override { return { 0, 0, 255, 255 }; } // Blue
};

class PegNode : public Node {
public:
    PegNode(int x, int y) : Node(x, y, "Peg") {}
    bool canConnectTo(Node* other, bool fromTop) override;
    SDL_Color getColor() const override { return { 0, 255, 0, 255 }; } // Green
};

class CompositeNode : public Node {
public:
    CompositeNode(int x, int y) : Node(x, y, "Composite") {}
    bool canConnectTo(Node* other, bool fromTop) override;
    SDL_Color getColor() const override { return { 0, 0, 139, 255 }; } // Dark Blue
};

// Structure to represent a wire between nodes
struct Wire {
    Node* fromNode;
    Node* toNode;
    std::vector<SDL_Point> waypoints; // Waypoints for the wire
};

#ifndef NODE_H
#define NODE_H
#endif //NODE_H