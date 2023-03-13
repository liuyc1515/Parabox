#include <iostream>
#include <parabox.h>
#include <manager/map_manager.h>
#include <canvas/canvas.h>
#include <utils/types.h>

int main()
{
    Canvas::InitColors();
    std::unique_ptr<BaseAgent> agent = Parabox::NewAgentByType(AGENT::INNER);
    int x = agent->GetCurrentMapX();
    int y = agent->GetCurrentMapY();
    Parabox game(std::move(agent), x, y);
    game.Start();
    return 0;
}
