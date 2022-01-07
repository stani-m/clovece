//
// Created by stanislavmotesicky on 06/01/2022.
//

#ifndef CLOVECE_CLIENT_H
#define CLOVECE_CLIENT_H


#ifdef linux
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <vector>
#include <deque>
#include <string>
#include <netinet/in.h>

class Client {
public:
    explicit Client(const std::string &hostname, int port, SDL_Renderer *renderer);

    void start();

    void render(int x, int y, float angle, int textureIndex);

    virtual ~Client();

private:
    int sockFd;
    struct sockaddr_in servAddr;
    struct hostent* server;

    bool isActive;

    SDL_Texture *loadTexture(const std::string &path);

    SDL_Renderer *renderer;

    std::vector<SDL_Texture *> textures;

    static bool pollEvents();
};


#endif //CLOVECE_CLIENT_H
