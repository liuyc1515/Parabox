#include <agents/base_agent.h>

BaseAgent::BaseAgent() : objects_(std::make_shared<std::map<uint64_t, std::shared_ptr<const BaseObject>>>())
{
    std::cout << "start init base agent" << std::endl;
    std::shared_ptr<BaseObject> tmp_object(NULL);
    object_manager_ = std::make_shared<ObjectManager>();
    map_manager_ = std::make_shared<MapManager>();
    for (int i = 0; i < map_manager_->GetMapX(); ++i)
    {
        for (int j = 0; j < map_manager_->GetMapY(); ++j)
        {
            tmp_object = NewObjectByType(map_manager_->GetObjectType({i, j}));
            object_manager_->SetObjectInfo(tmp_object->GetID(), {{i, j}, tmp_object->GetType()});
            objects_->insert({tmp_object->GetID(), tmp_object});
            if (tmp_object->GetType() == OBJECT::PLAYER)
            {
                operator_ = std::move(tmp_object);
            }
        }
    }
}

BaseAgent::~BaseAgent()
{
    
}

inline std::shared_ptr<BaseObject> BaseAgent::NewObjectByType(OBJECT::ObjectType type) const
{
    std::shared_ptr<BaseObject> tmp_object(NULL);
    switch (type)
    {
    case OBJECT::BLOCK:
        tmp_object = std::make_shared<BlockObject>(object_manager_, objects_);
        break;
    case OBJECT::VOID:
        tmp_object = std::make_shared<VoidObject>(object_manager_, objects_);
        break;
    case OBJECT::PLAYER:
        tmp_object = std::make_shared<PlayerObject>(object_manager_, objects_);
        break;
    case OBJECT::WALL:
        tmp_object = std::make_shared<WallObject>(object_manager_, objects_);
        break;
    default:
        break;
    }
    return std::move(tmp_object);
}

void BaseAgent::UpdateObjects(const std::map<uint64_t, ACTION::Action> &changes)
{
    std::shared_ptr<const BaseObject> tmp_object(NULL);
    std::map<uint64_t, ObjectInfo> new_map;
    for (int i = 0; i < GetMapX(); ++i)
    {
        for (int j = 0; j < GetMapY(); ++j)
        {
            tmp_object = objects_->at(object_manager_->GetObjectAtCoord({i, j}));
            if (tmp_object.get() != NULL)
            {
                if (changes.find(tmp_object->GetID()) != changes.end())
                {
                    if (tmp_object->GetType() != OBJECT::VOID)
                    {
                        new_map.insert({tmp_object->GetID(), {map_manager_->CalcCoordByAction({i, j}, changes.at(tmp_object->GetID())), tmp_object->GetType()}});
                    }
                    else
                    {
                        new_map.insert({tmp_object->GetID(), {object_manager_->GetObjectCoord(operator_->GetID()), tmp_object->GetType()}});
                    }
                }
                else
                {
                    new_map.insert({tmp_object->GetID(), {{i, j}, tmp_object->GetType()}});
                }
            }
            else
            {
                std::cerr << "Failed to update object : Incomplete Map" << std::endl;
            }
        }
    }

    object_manager_->SetWholeMap(new_map);
}

std::shared_ptr<const ObjectManager> BaseAgent::GetObjectManager() const
{
    return object_manager_;
}

void BaseAgent::OperatorMove(ACTION::Action act)
{
    std::map<uint64_t, ACTION::Action> changes;
    changes = operator_->Move(act);
    UpdateObjects(changes);
}

int BaseAgent::GetMapX() const
{
    return map_manager_->GetMapX();
}

int BaseAgent::GetMapY() const
{
    return map_manager_->GetMapY();
}
