//
// Created by stanislavmotesicky on 06/01/2022.
//

#ifndef CLOVECE_CLIENT_H
#define CLOVECE_CLIENT_H


#include <vector>
#include <deque>
#include <string>
#include <netinet/in.h>
#include <raylib.h>
#include "../common/SColor.h"

struct REntity {
    int x;
    int y;
    float angle;
    Texture2D *texture;

    void render() const;
};

class Client {
public:
    explicit Client(const std::string &hostname, int port);

    void start();

    ~Client();

private:

    void loadTextures();

    void unloadTextures();

    int sockFd;
    struct sockaddr_in servAddr;
    struct hostent *server;

    const int WINDOW_WIDTH = 704;
    const int WINDOW_HEIGHT = 704;

    bool waitingForClick;

    SColor color;

    std::vector<REntity> entities;

    std::vector<Image> images;
    std::vector<Texture2D> textures;
};


#endif //CLOVECE_CLIENT_H
