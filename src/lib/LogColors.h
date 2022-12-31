#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 

namespace LogColors{
    enum Color{
        NORMAL,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };
    template<typename... Args>
    void print(Color color, Args... strings){
        std::string colorString = "\x1B[0m"; // Default is NORMAL
        switch (color)
        {
        case NORMAL:
            colorString = "\x1B[0m";
            break;
        case BLUE:
            colorString = "\x1B[34m";
            break;
        case RED:
            colorString = "\x1B[31m";
            break;
        case GREEN:
            colorString = "\x1B[32m";
            break;
        case YELLOW:
            colorString = "\x1B[33m";
            break;
        case MAGENTA:
            colorString = "\x1B[35m";
            break;
        case CYAN:
            colorString = "\x1B[36m";
            break;
        case WHITE:
            colorString = "\x1B[37m";
            break;
        }
        std::cout << colorString;
        (std::cout << ... << strings) << std::endl;
        std::cout << "\x1B[0m"; // Logs NORMAL at the end to reset
    }

    void red(std::string s){
        print(RED, s);
    }
};
