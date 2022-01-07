//
// Created by stanislavmotesicky on 07/01/2022.
//

#ifndef CLOVECE_UTILS_H
#define CLOVECE_UTILS_H

#include <string>

void sendMessage(int sockFd, const std::string &message);

void receiveMessage(int sockFd, void *buffer, size_t nBytes);

#endif //CLOVECE_UTILS_H
