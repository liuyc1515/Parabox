#include <keyboard/keyboard_control.h>

std::queue<ACTION::Action> KeyboardControl::buffer_ = std::queue<ACTION::Action>();
std::mutex KeyboardControl::queue_mtx_;

KeyboardControl::KeyboardControl()
{
    
}

void KeyboardControl::ActionCapture()
{
    int key;
    while (true)
    {
        key = GetChar();
        queue_mtx_.lock();
        switch (key)
        {
        case KEY_W:
            buffer_.push(ACTION::UP);
            break;
        case KEY_S:
            buffer_.push(ACTION::DOWN);
            break;
        case KEY_A:
            buffer_.push(ACTION::LEFT);
            break;
        case KEY_D:
            buffer_.push(ACTION::RIGHT);
            break;
        case KEY_ESC:
            buffer_ = std::queue<ACTION::Action>();
            buffer_.push(ACTION::ESC);
            return;
        }
        queue_mtx_.unlock();
    }
}

ACTION::Action KeyboardControl::ActionGet()
{
    queue_mtx_.lock();
    if (buffer_.empty())
    {
        queue_mtx_.unlock();
        return ACTION::NOP;
    }
    ACTION::Action act = buffer_.front();
    buffer_.pop();
    queue_mtx_.unlock();
    return act;
}

#if defined(__APPLE__) || defined(__linux__)
int KeyboardControl::GetChar()
{
    struct termios tm, tm_old;
    int fd = 0;

    if (tcgetattr(fd, &tm) < 0)
    {
        return -1;
    }

    tm_old = tm;
    tm.c_lflag &= ~(ECHO | ICANON);

    if (tcsetattr(fd, TCSANOW, &tm) < 0)
    {
        return -1;
    }

    int ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
    {
        return -1;
    }

    return ch;
}

#elif defined(_WIN64)
int KeyboardControl::GetChar()
{
    int ch;

    ch = 0;
    if (_kbhit())
    {
        ch = _getch();
    }

    return ch;
}

#endif