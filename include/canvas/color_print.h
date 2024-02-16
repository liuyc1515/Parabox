#pragma once

#include <stdio.h>

#include <iostream>
#include <string>

inline void RedPrint(char ch) {
	printf("\033[;31m %c \033[0m", ch);
}

inline void GreenPrint(char ch) {
	printf("\033[;32m %c \033[0m", ch);
}

inline void BluePrint(char ch) {
	printf("\033[;34m %c \033[0m", ch);
}

inline void YellowPrint(char ch) {
	printf("\033[;33m %c \033[0m", ch);
}

inline void PurplePrint(char ch) {
	printf("\033[;35m %c \033[0m", ch);
}

inline void DarkGreenPrint(char ch) {
	printf("\033[;36m %c \033[0m", ch);
}

inline void BlackPrint(char ch) {
	printf("\033[;30m %c \033[0m", ch);
}

inline void WhitePrint(char ch) {
	printf("\033[;37m %c \033[0m", ch);
}

inline void UnderlinePrint(char ch) {
	printf("\033[4;37m %c \033[0m", ch);
}
