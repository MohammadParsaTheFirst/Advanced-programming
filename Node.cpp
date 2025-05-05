#include "Node.h"

void Node::render(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect rect = { x, y, 100, 50 };
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), {0, 0, 0});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = { x + 10, y + 10, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// For now, allow any connection
bool DrawingNode::canConnectTo(Node* other, bool fromTop) { return true; }
bool PegNode::canConnectTo(Node* other, bool fromTop) { return true; }
bool CompositeNode::canConnectTo(Node* other, bool fromTop) { return true; }