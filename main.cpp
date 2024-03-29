#include <canvas/canvas.h>
#include <manager/map_manager.h>
#include <parabox.h>
#include <utils/types.h>

#include <iostream>

int main() {
	Canvas::InitColors();
	std::unique_ptr<BaseAgent> agent = Parabox::NewAgentByType(AGENT::RECURSION);
	int x = agent->GetCurrentMapX();
	int y = agent->GetCurrentMapY();
	Parabox game(std::move(agent), x, y);
	game.Start();
	return 0;
}
