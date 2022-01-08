//
// Created by stanislavmotesicky on 06/01/2022.
//

#include <stdexcept>
#include <netdb.h>
#include "Client.h"
#include "../common/utils.h"
#include "../common/messages.h"
#include <unistd.h>
#include <cstring>

Client::Client(const std::string &hostname, int port) : waitingForClick(false) {
    images.emplace_back(LoadImage("assets/RedPiece.png"));
    images.emplace_back(LoadImage("assets/BluePiece.png"));
    images.emplace_back(LoadImage("assets/GreenPiece.png"));
    images.emplace_back(LoadImage("assets/YellowPiece.png"));
    images.emplace_back(LoadImage("assets/RedTile.png"));
    images.emplace_back(LoadImage("assets/BlueTile.png"));
    images.emplace_back(LoadImage("assets/GreenTile.png"));
    images.emplace_back(LoadImage("assets/YellowTile.png"));
    images.emplace_back(LoadImage("assets/WhiteTile.png"));
    images.emplace_back(LoadImage("assets/RedDot.png"));
    images.emplace_back(LoadImage("assets/BlueDot.png"));
    images.emplace_back(LoadImage("assets/GreenDot.png"));
    images.emplace_back(LoadImage("assets/YellowDot.png"));
    images.emplace_back(LoadImage("assets/WhiteArrow.png"));
    images.emplace_back(LoadImage("assets/Dice1.png"));
    images.emplace_back(LoadImage("assets/Dice2.png"));
    images.emplace_back(LoadImage("assets/Dice3.png"));
    images.emplace_back(LoadImage("assets/Dice4.png"));
    images.emplace_back(LoadImage("assets/Dice5.png"));
    images.emplace_back(LoadImage("assets/Dice6.png"));

    server = gethostbyname(hostname.c_str());
    if (server == nullptr) {
        throw std::runtime_error("Error, no such host");
    }

    bzero((char *) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &servAddr.sin_addr.s_addr,
            server->h_length
    );
    servAddr.sin_port = htons(port);

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        throw std::runtime_error("Error creating socket");
    }

    if (connect(sockFd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        throw std::runtime_error("Error connecting to socket");
    }

    color = (SColor) receiveInt(sockFd);
    printf("You are playing as %s!\n", colorString(color).c_str());
}

void Client::start() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, ("Človeče " + dotColor(color)).c_str());
    SetTargetFPS(60);

    loadTextures();

    while (!WindowShouldClose()) {
        if (!waitingForClick) {
            std::string message = receiveString(sockFd);
            if (message == QUIT) {
                unloadTextures();
                CloseWindow();
                return;
            } else if (message == START_REDRAW) {
                entities.clear();
                while (receiveString(sockFd) == TEXTURE) {
                    REntity entity = {receiveInt(sockFd),
                                      receiveInt(sockFd),
                                      receiveFloat(sockFd),
                                      &textures[receiveInt(sockFd)]};
                    entities.emplace_back(entity);
                }
            } else if (message == PRINT_MESSAGE) {
                printf("%s\n", receiveString(sockFd).c_str());
            } else if (message == GET_CLICK) {
                waitingForClick = true;
            }
        } else {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                sendString(sockFd, MOUSE_CLICK);
                sendInt(sockFd, GetMouseX() / 64);
                sendInt(sockFd, GetMouseY() / 64);
                waitingForClick = false;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (const auto &entity: entities) {
            entity.render();
        }
        EndDrawing();
    }

    unloadTextures();
    CloseWindow();

    if (waitingForClick) {
        sendString(sockFd, QUIT);
    }
    while (true) {
        std::string message = receiveString(sockFd);
        if (message == QUIT) {
            return;
        } else if (message == GET_CLICK) {
            sendString(sockFd, QUIT);
        } else if (message == PRINT_MESSAGE) {
            printf("%s\n", receiveString(sockFd).c_str());
        } else if (message == START_REDRAW) {
            while (receiveString(sockFd) == TEXTURE) {
                receiveInt(sockFd);
                receiveInt(sockFd);
                receiveFloat(sockFd);
                receiveInt(sockFd);
            }
        }
    }
}

Client::~Client() {
    close(sockFd);
}

void Client::loadTextures() {
    for (const auto &image: images) {
        textures.emplace_back(LoadTextureFromImage(image));
        UnloadImage(image);
    }
    images.clear();
}

void Client::unloadTextures() {
    for (const auto &texture: textures) {
        UnloadTexture(texture);
    }
    textures.clear();
}

void REntity::render() const {
    Rectangle src = {0.0f, 0.0f, 16.0f, 16.0f};
    Rectangle dst = {(float) x * 64.0f + 32.0f, (float) y * 64.0f + 32.0f, 64.0f, 64.0f};
    Vector2 origin = {dst.width / 2.0f, dst.height / 2.0f};
    DrawTexturePro(*texture, src, dst, origin, angle, WHITE);
}
