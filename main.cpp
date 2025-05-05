#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <memory>

#include "Node.h"

const int W = 1020;
const int H = 800;

const SDL_Color GREY = {200, 200, 200, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color WHITE = {255, 255, 255, 255};

bool running = true;
bool terminalFocused = false;
std::string inputText = "";
std::vector<std::string> logs = {};
int scrollOffset = 0;
Uint32 lastBlink = 0;
bool showCursor = true;

std::vector<std::string> optionLabels = {
    "3D", "Combine", "Constraint", "Deformation", "Favorites",
    "Filter", "Generator", "Group", "Misc", "Move", "Output"
};
std::vector<std::string> headerLabels = {"File", "Edit", "View", "Navigate"};

int selectedHeader = -1;
int selectedOption = -1;

std::vector<std::unique_ptr<Node>> nodes;
NodeType draggingType = NodeType::None;
int mouseX, mouseY;

// Define layout regions
SDL_Rect topRect = { 0, 0, W, H - 100 };  // Main canvas (top)
SDL_Rect bottomRect = { 0, H - 100, W, 100 };  // Node library (bottom)

SDL_Texture* loadImage(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void handle_terminal(const std::string& input) {
    std::cout << "[handle_terminal] Received: " << input << "\n";
}

void handle_options(int index) {
    std::cout << "[handle_options] Clicked: " << optionLabels[index] << "\n";
}

void handle_menu(int index) {
    std::cout << "[handle_menu] Clicked: " << headerLabels[index] << "\n";
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), BLACK);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Node View UI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("C:\\Users\\USER\\CLionProjects\\graph\\Fonts\\Arial.ttf", 16);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
        return 1;
    }

    // Load node images
    SDL_Texture* drawTex = loadImage(renderer, "C:\\Users\\USER\\CLionProjects\\graph\\images\\drawing.png");
    SDL_Texture* compositeTex = loadImage(renderer, "C:\\Users\\USER\\CLionProjects\\graph\\images\\composite.png");
    SDL_Texture* pegTex = loadImage(renderer, "C:\\Users\\USER\\CLionProjects\\graph\\images\\peg.png");

    SDL_StartTextInput();
    SDL_Event e;
    lastBlink = SDL_GetTicks();

    while (running) {///// THE EVENT LOOP
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseY > topRect.h) {
                    // Bottom panel clicked — library node clicked
                    if (mouseX < 100) draggingType = NodeType::Drawing;
                    else if (mouseX < 200) draggingType = NodeType::Peg;
                    else draggingType = NodeType::Composite;
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP && draggingType != NodeType::None) {
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseY < topRect.h) {
                    // Drop into the top canvas
                    switch (draggingType) {
                        case NodeType::Drawing:
                            nodes.emplace_back(std::make_unique<DrawingNode>(mouseX, mouseY));
                        break;
                        case NodeType::Peg:
                            nodes.emplace_back(std::make_unique<PegNode>(mouseX, mouseY));
                        break;
                        case NodeType::Composite:
                            nodes.emplace_back(std::make_unique<CompositeNode>(mouseX, mouseY));
                        break;
                        default: break;
                    }
                }
                draggingType = NodeType::None;
            }


            if (e.type == SDL_MOUSEWHEEL && terminalFocused) {
                scrollOffset += e.wheel.y * 20;
                scrollOffset = std::max(0, scrollOffset);
            }

            if (e.type == SDL_TEXTINPUT && terminalFocused) {
                inputText += e.text.text;
            }

            if (e.type == SDL_KEYDOWN && terminalFocused) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                    inputText.pop_back();
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    logs.push_back(">> " + inputText);
                    handle_terminal(inputText);
                    inputText.clear();
                }
            }
//////////////// ----------------------------------
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x;
                int my = e.button.y;
                SDL_Point mousePoint = {mx, my};

                SDL_Rect terminal = {W / 2, static_cast<int>(H * 0.75), W / 2, static_cast<int>(H * 0.25)};
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    if (SDL_PointInRect(&mousePoint, &terminal)) {
                        terminalFocused = true;
                    } else {
                        terminalFocused = false;
                    }
                }

                SDL_Rect leftPanel = {0, static_cast<int>(H * 0.75), W / 2, static_cast<int>(H * 0.25)};
                SDL_Rect categoryBox = {0, leftPanel.y, 100, leftPanel.h};
                if (SDL_PointInRect(&mousePoint, &categoryBox)) {
                    int itemHeight = categoryBox.h / optionLabels.size();
                    int clickedIndex = (my - categoryBox.y) / itemHeight;
                    if (clickedIndex >= 0 && clickedIndex < optionLabels.size()) {
                        handle_options(clickedIndex);
                        selectedOption = clickedIndex;
                    }
                }

                SDL_Rect headerBar = {0, 0, W, 30};
                if (SDL_PointInRect(&mousePoint, &headerBar)) {
                    int itemWidth = W / headerLabels.size();
                    int clickedHeader = mx / itemWidth;
                    if (clickedHeader >= 0 && clickedHeader < headerLabels.size()) {
                        handle_menu(clickedHeader);
                        selectedHeader = clickedHeader;
                    }
                } else {
                    selectedHeader = -1;
                }

                if (!SDL_PointInRect(&mousePoint, &terminal)) {
                    terminalFocused = false;
                }
            }
        }

        if (SDL_GetTicks() - lastBlink > 500) {
            showCursor = !showCursor;
            lastBlink = SDL_GetTicks();
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect headerBar = {0, 0, W, 30};
        for (size_t i = 0; i < headerLabels.size(); ++i) {
            SDL_Rect itemRect = {static_cast<int>(i * (W / headerLabels.size())), 0, W / static_cast<int>(headerLabels.size()), 30};
            SDL_SetRenderDrawColor(renderer, (i == selectedHeader) ? 180 : 210, 210, 250, 255);
            SDL_RenderFillRect(renderer, &itemRect);
            renderText(renderer, font, headerLabels[i], itemRect.x + 10, itemRect.y + 7);
        }

        SDL_Rect topRect = {0, 30, W, static_cast<int>(H * 0.75) - 30};
        SDL_SetRenderDrawColor(renderer, GREY.r, GREY.g, GREY.b, GREY.a);
        SDL_RenderFillRect(renderer, &topRect);

        SDL_Rect leftPanel = {0, static_cast<int>(H * 0.75), W / 2, static_cast<int>(H * 0.25)};
        SDL_Rect terminal = {W / 2, static_cast<int>(H * 0.75), W / 2, static_cast<int>(H * 0.25)};
        SDL_Rect categoryBox = {0, leftPanel.y, 100, leftPanel.h};

        for (size_t i = 0; i < optionLabels.size(); ++i) {
            SDL_Rect itemRect = {0, categoryBox.y + static_cast<int>(i) * 20, 100, 20};
            SDL_SetRenderDrawColor(renderer, (i == selectedOption) ? 200 : 230, 200, 250, 255);
            SDL_RenderFillRect(renderer, &itemRect);
            renderText(renderer, font, optionLabels[i], 10, itemRect.y + 5);
        }

        SDL_Rect categoryRest = {categoryBox.w, categoryBox.y, leftPanel.w - categoryBox.w, categoryBox.h};
        SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
        SDL_RenderFillRect(renderer, &categoryRest);

        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderFillRect(renderer, &terminal);

        std::string inputDisplay = ">> " + inputText + (terminalFocused && showCursor ? "|" : "");
        renderText(renderer, font, inputDisplay, terminal.x + 10, terminal.y + 10);

        int logY = terminal.y + 30 - scrollOffset;
        for (int i = static_cast<int>(logs.size()) - 1; i >= 0; --i) {
            if (logY >= terminal.y + 30 && logY <= terminal.y + terminal.h - 20)
                renderText(renderer, font, logs[i], terminal.x + 10, logY);
            logY += 20;
        }


        // Render three node icons in the middle bottom (Draw, Peg, Composite)
        int iconY = H - 90;
        int spacing = 20;
        int iconW = 64, iconH = 64;
        //int totalWidth = 3 * iconW + 2 * spacing;
        int startX = 120; // Start just to the right of category box (x=100) with 20px padding
        SDL_Rect drawRect = {startX, iconY, iconW, iconH};
        SDL_Rect pegRect = {startX + iconW + spacing, iconY, iconW, iconH};
        SDL_Rect compRect = {startX + 2 * (iconW + spacing), iconY, iconW, iconH};

        if (drawTex) {
            SDL_RenderCopy(renderer, drawTex, nullptr, &drawRect);
        } if (pegTex) {
            SDL_RenderCopy(renderer, pegTex, nullptr, &pegRect);
        } if (compositeTex) {
            SDL_RenderCopy(renderer, compositeTex, nullptr, &compRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyTexture(drawTex);
    SDL_DestroyTexture(pegTex);
    SDL_DestroyTexture(compositeTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}