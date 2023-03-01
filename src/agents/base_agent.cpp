#include <agents/base_agent.h>

BaseAgent::BaseAgent(int canvas_x, int canvas_y, int op_x, int op_y): canvas_(canvas_x, canvas_y), x_(canvas_x), y_(canvas_y)
{
    map_ = new BaseStaticMap(canvas_x, canvas_y, {op_x, op_y});
    UpdateCanvas();
    canvas_.CanvasPrint();
}

BaseAgent::~BaseAgent()
{
    delete map_;
    map_ = NULL;
}

void BaseAgent::UpdateCanvas()
{
    const BaseObject *tmp_obj = NULL;
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            tmp_obj = map_->GetObject({i, j});
            if (tmp_obj != NULL)
            {
                // std::cout << "Update " << i << " " << j << std::endl;
                canvas_.CanvasSet(i, j, tmp_obj->GetType());
            }
            else
            {
                std::cerr << "Failed to update canvas : Incomplete Map" << std::endl;
            }
        }
    }
}

void BaseAgent::OperatorMove(ACTION::Action act)
{
    // std::cout << "operate move " << act << std::endl;
    map_->Operate(act);
    UpdateCanvas();
    canvas_.CanvasPrint();
}
