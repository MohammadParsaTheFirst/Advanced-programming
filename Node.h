#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

enum class NodeType { None, Drawing, Peg, Composite };

class Node {
public:
    Node(int x, int y, std::string label) : x(x), y(y), label(std::move(label)), dragging(false) {}
    virtual ~Node() = default;

    virtual void render(SDL_Renderer* renderer, TTF_Font* font);
    virtual bool canConnectTo(Node* other, bool fromTop) = 0;

    int x, y;
    std::string label;
    bool dragging;
};

class DrawingNode : public Node {
public:
    DrawingNode(int x, int y) : Node(x, y, "Drawing") {}
    bool canConnectTo(Node* other, bool fromTop) override;
};

class PegNode : public Node {
public:
    PegNode(int x, int y) : Node(x, y, "Peg") {}
    bool canConnectTo(Node* other, bool fromTop) override;
};

class CompositeNode : public Node {
public:
    CompositeNode(int x, int y) : Node(x, y, "Composite") {}
    bool canConnectTo(Node* other, bool fromTop) override;
};


#ifndef NODE_H
#define NODE_H

#endif //NODE_H
