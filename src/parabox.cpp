#include <parabox.h>

Parabox::Parabox(int canvas_x, int canvas_y, int op_x, int op_y): agent_(canvas_x, canvas_y, op_x, op_y)
{

}

void Parabox::Start()
{
    std::thread keyboard_capture(&KeyboardControl::ActionCapture, keyboard_);

    ACTION::Action act = ACTION::NOP;
    while (true)
    {
        act = keyboard_.ActionGet();
        switch (act)
        {
        case ACTION::ESC:
            return;
        case ACTION::UP:
        case ACTION::DOWN:
        case ACTION::LEFT:
        case ACTION::RIGHT:
            agent_.OperatorMove(act);
            break;
        default:
            break;
        }
    }

    keyboard_capture.join();
    return;
}
