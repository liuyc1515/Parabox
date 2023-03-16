#pragma once

#include <thread>
#include <mutex>

#include <keyboard/keyboard_control.h>
#include <agents/base_agent.h>
#include <agents/inner_map_agent.h>
#include <agents/recursion_agent.h>
#include <canvas/canvas.h>
#include <manager/object_manager.h>
#include <manager/map_manager.h>
#include <utils/types.h>

class Parabox
{
private:
    KeyboardControl keyboard_;
    Canvas canvas_;
    std::unique_ptr<BaseAgent> agent_;
    std::shared_ptr<const ObjectManager> object_manager_;
    std::shared_ptr<const MapManager> map_manager_;
    void UpdateCanvas();
public:
    Parabox(std::unique_ptr<BaseAgent> agent, int x, int y);
    void Start();
    static std::unique_ptr<BaseAgent> NewAgentByType(AGENT::AgentType agent_type);
};
