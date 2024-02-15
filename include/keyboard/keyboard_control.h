#pragma once

#include <stdio.h>
#include <utils/types.h>

#include <iostream>
#include <mutex>
#include <queue>

#if defined(__APPLE__) || defined(__linux__)
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>

#elif defined(_WIN64)
#include <conio.h>

#endif

const int KEY_W = 119;
const int KEY_A = 97;
const int KEY_S = 115;
const int KEY_D = 100;

const int KEY_ESC = 27;

class KeyboardControl {
	private:
		static std::queue<KEYBOARD::Action> buffer_;
		static std::mutex queue_mtx_;
		bool stop_;
		int GetChar();

	public:
		KeyboardControl();
		void ActionCapture();
		void Stop();
		KEYBOARD::Action ActionGet();
};
