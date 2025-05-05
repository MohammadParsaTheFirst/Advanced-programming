#include "Node.h"

void Node::render(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect rect = { x, y, 100, 50 };
    SDL_Color color = getColor();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Render top port
    SDL_Rect topPort = { x + 50 - 5, y - 5, 10, 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &topPort);

    // Render bottom port (single for simplicity)
    SDL_Rect bottomPort = { x + 50 - 5, y + 50 - 5, 10, 10 };
    SDL_RenderFillRect(renderer, &bottomPort);

    SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), {0, 0, 0});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = { x + 10, y + 10, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool DrawingNode::canConnectTo(Node* other, bool fromTop) {
    if (fromTop) {
        // Top port can connect to any node (only one top port)
        return true;
    } else {
        // Bottom ports can connect to any node, no limit
        return true;
    }
}

bool PegNode::canConnectTo(Node* other, bool fromTop) {
    if (fromTop) {
        // Top port can only connect to another Peg node
        return dynamic_cast<PegNode*>(other) != nullptr;
    } else {
        // Bottom ports can connect to any node except Composite
        return dynamic_cast<CompositeNode*>(other) == nullptr;
    }
}

bool CompositeNode::canConnectTo(Node* other, bool fromTop) {
    // Top and bottom ports can connect to any node except Peg
    return dynamic_cast<PegNode*>(other) == nullptr;
}
