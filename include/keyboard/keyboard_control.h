#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <stdio.h>

#if defined(__APPLE__) || defined(__linux__)
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>

#elif defined(_WIN64)
#include <conio.h>

#endif

const int KEY_W = 119;
const int KEY_A = 97;
const int KEY_S = 115;
const int KEY_D = 100;

const int KEY_ESC = 27;

namespace ACTION
{
    enum Action
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        DISAPPEAR,
        ESC,
        NOP
    };
}

class KeyboardControl
{
private:
    static std::queue<ACTION::Action> buffer_;
    static std::mutex queue_mtx_;
    int GetChar();
public:
    KeyboardControl();
    void ActionCapture();
    ACTION::Action ActionGet();
};
