//
// Created by stanislavmotesicky on 07/01/2022.
//

#include "utils.h"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

void sendString(int sockFd, const std::string &message) {
//    printf("Sent string: %s\n", message.c_str());
    sendInt(sockFd, (int) message.size());
    ssize_t n = write(sockFd, message.c_str(), message.size());
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

void sendInt(int sockFd, int number) {
//    printf("Sent int: %d\n", number);
    ssize_t n = write(sockFd, &number, sizeof(int));
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

void sendFloat(int sockFd, float number) {
//    printf("Sent float: %f\n", number);
    ssize_t n = write(sockFd, &number, sizeof(float));
    if (n < 0) {
        throw std::runtime_error("Error writing to socket");
    }
}

std::string receiveString(int sockFd) {
    int size = receiveInt(sockFd);
    char *buffer = new char[size + 1];
    ssize_t n = read(sockFd, buffer, 255);
    if (n < 0) {
        throw std::runtime_error("Error reading from socket");
    }
    buffer[size] = '\0';
    std::string str(buffer);
    delete[] buffer;
    return str;
}

int receiveInt(int sockFd) {
    int i;
    ssize_t n = read(sockFd, &i, sizeof(int));
    if (n < 0) {
        throw std::runtime_error("Error reading from socket");
    }
//    printf("Received int: %d\n", i);
    return i;
}

float receiveFloat(int sockFd) {
    float f;
    ssize_t n = read(sockFd, &f, sizeof(float));
    if (n < 0) {
        throw std::runtime_error("Error reading from socket");
    }
//    printf("Received float: %f\n", f);
    return f;
}

