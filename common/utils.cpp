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

void receiveMessage(int sockFd, void *buffer, size_t nBytes) {
    ssize_t n = read(sockFd, buffer, nBytes);
    if (n < 0)
    {
        throw std::runtime_error("Error reading from socket");
    }
}

