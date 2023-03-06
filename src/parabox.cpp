#include <parabox.h>

Parabox::Parabox() :
agent_(),
keyboard_(),
canvas_(agent_.GetMapX(), agent_.GetMapY())
{
    std::cout << "start ini parabox" << std::endl;
    object_manager_ = agent_.GetObjectManager();
    UpdateCanvas();
    std::cout << "finished ini parabox" << std::endl;
    canvas_.CanvasPrint();
}

void Parabox::UpdateCanvas()
{
    OBJECT::ObjectType type;
    for (int i = 0; i < canvas_.GetCanvasX(); ++i)
    {
        for (int j = 0; j < canvas_.GetCanvasY(); ++j)
        {
            type = object_manager_->GetObjectType(object_manager_->GetObjectAtCoord({i, j}));
            if (type != OBJECT::OBJ_COUNT)
            {
                // std::cout << "Update " << i << " " << j << std::endl;
                canvas_.CanvasSet(i, j, type);
            }
            else
            {
                std::cerr << "Failed to update canvas : Incomplete Map" << std::endl;
            }
        }
    }
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
            goto exit;
        case ACTION::UP:
        case ACTION::DOWN:
        case ACTION::LEFT:
        case ACTION::RIGHT:
            agent_.OperatorMove(act);
            UpdateCanvas();
            canvas_.CanvasPrint();
            break;
        default:
            break;
        }
    }

exit:
    keyboard_.Stop();
    keyboard_capture.join();
    return;
}
