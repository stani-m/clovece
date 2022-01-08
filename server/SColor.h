//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_COLOR_H
#define CLOVECE_COLOR_H



#include <string>

enum class SColor {
    Red, Green, Blue, Yellow, Black, White
};

inline std::string colorString(SColor color) {
    switch (color) {
        case SColor::Red:
            return "Red";
        case SColor::Green:
            return "Green";
        case SColor::Blue:
            return "Blue";
        case SColor::Yellow:
            return "Yellow";
        case SColor::Black:
            return "Black";
        case SColor::White:
            return "White";
    }
    return "";
}

#endif //CLOVECE_COLOR_H
