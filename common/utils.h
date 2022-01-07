//
// Created by stanislavmotesicky on 07/01/2022.
//

#ifndef CLOVECE_UTILS_H
#define CLOVECE_UTILS_H

#include <string>

void sendString(int sockFd, const std::string &message);
void sendInt(int sockFd, int number);
void sendFloat(int sockFd, float number);

std::string receiveString(int sockFd);
int receiveInt(int sockFd);
float receiveFloat(int sockFd);

#endif //CLOVECE_UTILS_H
