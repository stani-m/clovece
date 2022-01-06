//
// Created by stanislavmotesicky on 06/01/2022.
//

#ifndef CLOVECE_CLIENT_H
#define CLOVECE_CLIENT_H


#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <netinet/in.h>

class Client {
public:
    explicit Client(SDL_Renderer *renderer);

    void start(const std::string &hostname, int port);

    void render(int x, int y, float angle, int textureIndex);

private:
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];

    SDL_Texture *loadTexture(const std::string &path);

    SDL_Renderer *renderer;

    std::vector<SDL_Texture *> textures;
};


#endif //CLOVECE_CLIENT_H
