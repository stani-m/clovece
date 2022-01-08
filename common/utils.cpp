//
// Created by stanislavmotesicky on 07/01/2022.
//

#include "utils.h"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

void sendString(int sockFd, const std::string &message) {
    sendInt(sockFd, (int) message.size());
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
    int size = receiveInt(sockFd);
    std::string str(size, '\0');
    ssize_t n = read(sockFd, str.data(), size);
    if (n < 0) {
        throw std::runtime_error("Error reading from socket");
    }
    return str;
}

int receiveInt(int sockFd) {
    int i;
    ssize_t n = read(sockFd, &i, sizeof(int));
    if (n < 0) {
        throw std::runtime_error("Error reading from socket");
    }
    return i;
}

float receiveFloat(int sockFd) {
    float f;
    ssize_t n = read(sockFd, &f, sizeof(float));
    if (n < 0) {
        throw std::runtime_error("Error reading from socket");
    }
    return f;
}

