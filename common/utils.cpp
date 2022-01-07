//
// Created by stanislavmotesicky on 07/01/2022.
//

#include "utils.h"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

void sendString(int sockFd, const std::string &message) {
    ssize_t n = write(sockFd, message.c_str(), message.size());
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

void sendInt(int sockFd, int number) {
    ssize_t n = write(sockFd, &number, sizeof(int));
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

void sendFloat(int sockFd, float number) {
    ssize_t n = write(sockFd, &number, sizeof(float));
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

std::string receiveString(int sockFd) {
    char buffer[256];
    bzero(buffer,256);
    ssize_t n = read(sockFd, buffer, 255);
    if (n < 0)
    {
        throw std::runtime_error("Error reading from socket");
    }
    return {buffer};
}

int receiveInt(int sockFd) {
    int i;
    ssize_t n = read(sockFd, &i, sizeof(int));
    if (n < 0)
    {
        throw std::runtime_error("Error reading from socket");
    }
    return i;
}

float receiveFloat(int sockFd) {
    float f;
    ssize_t n = read(sockFd, &f, sizeof(float));
    if (n < 0)
    {
        throw std::runtime_error("Error reading from socket");
    }
    return f;
}

