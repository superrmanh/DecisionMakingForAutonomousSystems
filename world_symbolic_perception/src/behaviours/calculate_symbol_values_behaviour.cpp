#include "world_symbolic_perception/behaviours/calculate_symbol_values_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

CalculateSymbolValuesBehaviour::CalculateSymbolValuesBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: SyncActionNode(name, conf), node(params.nh)
{}

PortsList CalculateSymbolValuesBehaviour::providedPorts()
{
    return { InputPort<std::vector<world_symbolic_perception::msg::Object>>("visible_objects"),
             OutputPort<std::vector<robot_swiss_knife_msgs::msg::Fluent>>("scene_symbols") };
}

NodeStatus CalculateSymbolValuesBehaviour::tick()
{
    std::vector<world_symbolic_perception::msg::Object> visible_objects;
    this->getInput("visible_objects", visible_objects);

    std::vector<robot_swiss_knife_msgs::msg::Fluent> scene_symbols;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Calculate the predicate values for all pairs of visible objects, and add all predicates that hold to scene_symbols
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Notes:
    // For every ordered pair (obj1, obj2) of different visible objects, we evaluate every predicate of the symbol library.
    // ordered pairs mean that both pred(X, Y) and pred(Y, X) are checked.
    // each predicate that holds is stored as a Fluent in the format of the expected knowledge base state, e.g.
    //   on(beer, table)  ->  on -- [ (Object, beer) ] -- table
    // i.e. name = predicate name, one parameter ("Object", obj1), value = obj2.

    // Predicates from the symbol library, with the name each one gets in the knowledge base
    using Predicate = bool (*)(world_symbolic_perception::msg::Object, world_symbolic_perception::msg::Object, rclcpp::Node::SharedPtr);
    // small dictionary for predicates
    const std::vector<std::pair<std::string, Predicate>> predicates = {
        {"on", &SymbolLibrary::on},
        {"leftOf", &SymbolLibrary::leftOf},
        {"rightOf", &SymbolLibrary::rightOf}
    };

    // const rclcpp::Logger logger = this->node->get_logger();
    // RCLCPP_INFO(logger, "[calculate_symbol_values] Evaluating predicates for %zu visible objects", visible_objects.size());

    for (const auto &obj1 : visible_objects)
    {
        for (const auto &obj2 : visible_objects)
        {
            const bool same_object = obj1.name == obj2.name;
            if (same_object)
            {
                continue;  // an object is never related to itself
            }

            for (const auto &[predicate_name, predicate] : predicates)
            {
                const bool holds = predicate(obj1, obj2, this->node);
                if (holds)
                {
                    robot_swiss_knife_msgs::msg::KnowledgeItem object_param;
                    object_param.name = "Object";
                    object_param.value = obj1.name;

                    robot_swiss_knife_msgs::msg::Fluent fluent;
                    fluent.name = predicate_name;
                    fluent.params.push_back(object_param);
                    fluent.value = obj2.name;

                    scene_symbols.push_back(fluent);

                    // RCLCPP_INFO(logger, "[calculate_symbol_values] %s(%s, %s) holds -> added to scene_symbols",
                                // predicate_name.c_str(), obj1.name.c_str(), obj2.name.c_str());
                }
            }
        }
    }

    // RCLCPP_INFO(logger, "[calculate_symbol_values] %zu predicates hold in the current scene", scene_symbols.size());

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (scene_symbols.size() == 0)
    {
        return NodeStatus::FAILURE;
    }

    this->setOutput("scene_symbols", scene_symbols);
    return NodeStatus::SUCCESS;
}

CreateRosNodePlugin(CalculateSymbolValuesBehaviour, "CalculateSymbolValuesBehaviour");
