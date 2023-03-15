#include <parabox.h>

Parabox::Parabox(std::unique_ptr<BaseAgent> agent, int x, int y) :
agent_(std::move(agent)),
keyboard_(),
canvas_(x, y)
{
    std::cout << "start init parabox" << std::endl;
    object_manager_ = agent_->GetObjectManager();
    map_manager_ = agent_->GetMapManager();
    UpdateCanvas();
    std::cout << "finished init parabox" << std::endl;
    canvas_.CanvasPrint();
}

void Parabox::UpdateCanvas()
{
    std::cout << "start update canvas" << std::endl;
    std::vector<uint64_t> object_ids = std::move(object_manager_->GetObjectInMap(map_manager_->GetCurrentMapID()));

    canvas_.InitCanvas(agent_->GetCurrentMapX(), agent_->GetCurrentMapY());

    std::cout << "start set canvas with object num " << object_ids.size() << std::endl;

    for (auto object_id : object_ids)
    {
        Coordinate tmp_coord = object_manager_->GetObjectCoord(object_id);
        // std::cout << "set obj coord (" << tmp_coord.first << ", " << tmp_coord.second << ") with type " << object_manager_->GetObjectType(object_id) << std::endl;
        canvas_.CanvasSet(tmp_coord, object_manager_->GetObjectType(object_id));
    }
}

std::unique_ptr<BaseAgent> Parabox::NewAgentByType(AGENT::AgentType agent_type)
{
    std::cout << "start create agent" << std::endl;
    std::unique_ptr<BaseAgent> tmp_object;
    switch (agent_type)
    {
    case AGENT::BASE:
        tmp_object = std::move(std::make_unique<BaseAgent>());
        break;
    case AGENT::INNER:
        tmp_object = std::move(std::make_unique<InnerMapAgent>());
        break;
    default:
        break;
    }
    return std::move(tmp_object);
}

void Parabox::Start()
{
    std::thread keyboard_capture(&KeyboardControl::ActionCapture, keyboard_);

    KEYBOARD::Action act = KEYBOARD::NOP;
    while (true)
    {
        act = keyboard_.ActionGet();
        switch (act)
        {
        case KEYBOARD::ESC:
            goto exit;
        case KEYBOARD::UP:
        case KEYBOARD::DOWN:
        case KEYBOARD::LEFT:
        case KEYBOARD::RIGHT:
            agent_->OperatorMove((ACTION::Action)(ACTION::UP + (act - KEYBOARD::UP)));
            UpdateCanvas();
            canvas_.CanvasPrint();
            std::cout << "finished one action" << std::endl;
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
