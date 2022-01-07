//
// Created by stanislavmotesicky on 06/01/2022.
//

#include <stdexcept>
#include <netdb.h>
#include "Client.h"
#include "../common/utils.h"
#include "../common/messages.h"
#include <unistd.h>

Client::Client(const std::string &hostname, int port, SDL_Renderer *renderer) : renderer(renderer), isActive(false) {
    textures.emplace_back(loadTexture("assets/RedPiece.bmp"));
    textures.emplace_back(loadTexture("assets/BluePiece.bmp"));
    textures.emplace_back(loadTexture("assets/GreenPiece.bmp"));
    textures.emplace_back(loadTexture("assets/YellowPiece.bmp"));
    textures.emplace_back(loadTexture("assets/RedTile.bmp"));
    textures.emplace_back(loadTexture("assets/BlueTile.bmp"));
    textures.emplace_back(loadTexture("assets/GreenTile.bmp"));
    textures.emplace_back(loadTexture("assets/YellowTile.bmp"));
    textures.emplace_back(loadTexture("assets/WhiteTile.bmp"));
    textures.emplace_back(loadTexture("assets/RedDot.bmp"));
    textures.emplace_back(loadTexture("assets/BlueDot.bmp"));
    textures.emplace_back(loadTexture("assets/GreenDot.bmp"));
    textures.emplace_back(loadTexture("assets/YellowDot.bmp"));
    textures.emplace_back(loadTexture("assets/WhiteArrow.bmp"));
    textures.emplace_back(loadTexture("assets/Dice1.bmp"));
    textures.emplace_back(loadTexture("assets/Dice2.bmp"));
    textures.emplace_back(loadTexture("assets/Dice3.bmp"));
    textures.emplace_back(loadTexture("assets/Dice4.bmp"));
    textures.emplace_back(loadTexture("assets/Dice5.bmp"));
    textures.emplace_back(loadTexture("assets/Dice6.bmp"));

    server = gethostbyname(hostname.c_str());
    if (server == nullptr)
    {
        throw std::runtime_error("Error, no such host");
    }

    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&servAddr.sin_addr.s_addr,
            server->h_length
    );
    servAddr.sin_port = htons(port);

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        throw std::runtime_error("Error creating socket");
    }

    if(connect(sockFd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        throw std::runtime_error("Error connecting to socket");
    }
}

SDL_Texture *Client::loadTexture(const std::string &path) {
    SDL_Surface *piece_surface = SDL_LoadBMP(path.c_str());
    if (piece_surface == nullptr) {
        throw std::runtime_error("Loading textures failed!");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, piece_surface);
    SDL_FreeSurface(piece_surface);
    if (texture == nullptr) {
        throw std::runtime_error("Something failed!");
    }
    return texture;
}

void Client::render(int x, int y, float angle, int textureIndex) {
    SDL_Rect rectangle;
    rectangle.x = x * 64;
    rectangle.y = y * 64;
    rectangle.h = 64;
    rectangle.w = 64;

    SDL_RenderCopyEx(renderer, textures[textureIndex], nullptr, &rectangle, angle, nullptr, SDL_FLIP_NONE);
}

void Client::start() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while (true) {
        if (!isActive) {
            std::string message = receiveString(sockFd);
            if (message == TURN_START) {
                bool quit = pollEvents();
                if (quit) {
                    sendString(sockFd, QUIT);
                } else {
                    isActive = true;
                    sendString(sockFd, CONTINUE);
                }
            } else if (message == QUIT) {
                break;
            } else if (message == ACTIVATE) {
                isActive = true;
            } else if (message == START_REDRAW) {
                SDL_RenderClear(renderer);
                while (true) {
                    message = receiveString(sockFd);
                    if (message == END_REDRAW) {
                        SDL_RenderPresent(renderer);
                        break;
                    } else if (message == TEXTURE) {
                        SDL_Rect rectangle;
                        rectangle.w = 64;
                        rectangle.h = 64;
                        rectangle.x = receiveInt(sockFd) * 64;
                        rectangle.y = receiveInt(sockFd) * 64;
                        float angle = receiveFloat(sockFd);
                        int index = receiveInt(sockFd);

                        SDL_RenderCopyEx(renderer, textures[index], nullptr, &rectangle, angle, nullptr, SDL_FLIP_NONE);
                    }
                }
            } else if (message == PRINT_MESSAGE) {
                printf("%s\n", receiveString(sockFd).c_str());
            }
        } else {
            SDL_Event event;
            if (SDL_WaitEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    sendString(sockFd, QUIT);
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    sendString(sockFd, MOUSE_CLICK);
                    sendInt(sockFd, event.button.x / 64);
                    sendInt(sockFd, event.button.y / 64);
                    if (receiveString(sockFd) == DEACTIVATE) {
                        isActive = false;
                    }
                }
            }
        }
    }
}

bool Client::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

Client::~Client() {
    close(sockFd);
}
