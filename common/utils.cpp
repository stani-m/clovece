//
// Created by stanislavmotesicky on 07/01/2022.
//

#include "utils.h"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

void sendMessage(int sockFd, const std::string &message) {
    ssize_t n = write(sockFd, message.c_str(), message.size());
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

void receiveMessage(int sockFd, char buffer[256]) {
    bzero(buffer,256);
    ssize_t n = read(sockFd, buffer, 255);
    if (n < 0)
    {
        throw std::runtime_error("Error reading from socket");
    }
}

