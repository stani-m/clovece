//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_COLOR_H
#define CLOVECE_COLOR_H



#include <string>

enum class Color {
    Red, Green, Blue, Yellow, Black, White
};

inline std::string colorString(Color color) {
    switch (color) {
        case Color::Red:
            return "Red";
        case Color::Green:
            return "Green";
        case Color::Blue:
            return "Blue";
        case Color::Yellow:
            return "Yellow";
        case Color::Black:
            return "Black";
        case Color::White:
            return "White";
    }
    return "";
}

#endif //CLOVECE_COLOR_H
