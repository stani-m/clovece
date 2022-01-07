//
// Created by stanislavmotesicky on 06/01/2022.
//

#include <stdexcept>
#include <netdb.h>
#include "Client.h"
#include <unistd.h>

Client::Client(const std::string &hostname, int port, SDL_Renderer *renderer) : renderer(renderer) {
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

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        throw std::runtime_error("Error creating socket");
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        throw std::runtime_error("Error connecting to socket");
    }

    bzero(buffer,256);
    ssize_t n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        throw std::runtime_error("Error reading from socket");
    }

    printf("You are playing as %s!\n", buffer);
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


//    bool endGame = false;
//    while (!endGame) {
//
//    }


}

Client::~Client() {
    close(sockfd);
}
