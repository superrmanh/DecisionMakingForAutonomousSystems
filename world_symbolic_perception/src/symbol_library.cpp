#include "world_symbolic_perception/symbol_library.hpp"

#include <algorithm>
#include <cmath>

std::vector<std::string> symbol_names = {"on", "leftOf", "rightOf"};

// Helpers and thresholds shared by the predicates below
namespace
{
    // Thresholds for leftOf / rightOf (tune them if needed)
    constexpr double SIDE_BY_SIDE_MIN_Z_OVERLAP = 0.5;  // min vertical overlap, as a fraction of the shorter object's height
    constexpr double LATERAL_THRESHOLD_M = 0.05;        // min distance between the two centres along y

    // A bounding box is usable only if all its values are finite and its size is positive
    // (e.g. ground_plane has inf/nan values, and an object that has not received a bounding box has size 0)
    bool bbox_is_valid(const vision_msgs::msg::BoundingBox3D &bbox)
    {
        const auto &centre = bbox.center.position;
        const auto &size = bbox.size;

        const bool centre_is_finite = std::isfinite(centre.x) && std::isfinite(centre.y) && std::isfinite(centre.z);
        const bool size_is_finite = std::isfinite(size.x) && std::isfinite(size.y) && std::isfinite(size.z);
        const bool size_is_positive = size.x > 0.0 && size.y > 0.0 && size.z > 0.0;

        return centre_is_finite && size_is_finite && size_is_positive;
    }

    // How much the two boxes overlap in height, as a fraction (0 to 1) of the shorter box's height.
    // ~1 for objects standing side by side on the same surface, ~0 when one object is on top of the other.
    double vertical_overlap_ratio(const vision_msgs::msg::BoundingBox3D &bbox1, const vision_msgs::msg::BoundingBox3D &bbox2)
    {
        const double bottom1 = bbox1.center.position.z - bbox1.size.z / 2.0;
        const double top1 = bbox1.center.position.z + bbox1.size.z / 2.0;
        const double bottom2 = bbox2.center.position.z - bbox2.size.z / 2.0;
        const double top2 = bbox2.center.position.z + bbox2.size.z / 2.0;

        const double overlap_m = std::min(top1, top2) - std::max(bottom1, bottom2);
        const double shorter_height_m = std::min(bbox1.size.z, bbox2.size.z);

        return std::max(0.0, overlap_m) / shorter_height_m;
    }
}

bool SymbolLibrary::on(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Implement the on predicate
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //  Notes:
    // on(obj1, obj2) holds when obj1 rests on top of obj2:
    // 1. the bottom of obj1 is almost at the same height as the top of obj2, and
    // 2. the centre of obj1 lies within the horizontal footprint of obj2.
    // The bounding boxes are world-frame axis-aligned boxes (centre + full size), so no rotation is needed.

    // Thresholds 
    constexpr double Z_CONTACT_TOLERANCE_M = 0.05;  // max gap or penetration between obj1's bottom and obj2's top, 5 cm just in case 
    constexpr double XY_MARGIN_M = 0.03; // extra margin around obj2's footprint, 3cm

    // const rclcpp::Logger logger = rclcpp::get_logger("symbol_library");

    // Objects without a usable bounding box (e.g. ground_plane has inf/nan values) can never be on anything
    const bool any_bbox_invalid = !bbox_is_valid(obj1.bbox) || !bbox_is_valid(obj2.bbox);
    if (any_bbox_invalid)
    {
        // RCLCPP_INFO(logger, "[on] on(%s, %s): skipped, invalid bounding box", obj1.name.c_str(), obj2.name.c_str());
        return false;
    }

    const auto &c1 = obj1.bbox.center.position;
    const auto &s1 = obj1.bbox.size;
    const auto &c2 = obj2.bbox.center.position;
    const auto &s2 = obj2.bbox.size;

    // 1. Vertical contact: bottom of obj1 vs. top of obj2
    const double obj1_bottom = c1.z - s1.z / 2.0;
    const double obj2_top = c2.z + s2.z / 2.0;
    const double z_gap = obj1_bottom - obj2_top;  // ~0 when obj1 rests on obj2
    const bool vertical_contact = std::abs(z_gap) <= Z_CONTACT_TOLERANCE_M;

    // 2. Horizontal support: centre of obj1 inside the footprint of obj2
    const bool inside_x = std::abs(c1.x - c2.x) <= s2.x / 2.0 + XY_MARGIN_M;
    const bool inside_y = std::abs(c1.y - c2.y) <= s2.y / 2.0 + XY_MARGIN_M;

    const bool result = vertical_contact && inside_x && inside_y;

    // RCLCPP_INFO(logger, "[on] on(%s, %s): z_gap=%.3f m (tol %.3f), centre inside footprint x=%s y=%s -> %s",
                // obj1.name.c_str(), obj2.name.c_str(), z_gap, Z_CONTACT_TOLERANCE_M,
                // inside_x ? "yes" : "no", inside_y ? "yes" : "no", result ? "TRUE" : "false");

    return result;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool SymbolLibrary::leftOf(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Implement the leftOf predicate
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Notes:
    // leftOf(obj1, obj2) holds when obj1 stands beside obj2, further to the left:
    //   1. obj1 and obj2 are side by side (they overlap in height, so neither is on top of the other), and
    //   2. the centre of obj1 is more than LATERAL_THRESHOLD_M to the left of the centre of obj2.
    // "Left" is defined in the world frame: by ROS convention +x points forward and +y points to the left,
    // so obj1 is left of obj2 when its centre has a larger y.

    // const rclcpp::Logger logger = rclcpp::get_logger("symbol_library");

    const bool any_bbox_invalid = !bbox_is_valid(obj1.bbox) || !bbox_is_valid(obj2.bbox);
    if (any_bbox_invalid)
    {
        // RCLCPP_INFO(logger, "[leftOf] leftOf(%s, %s): skipped, invalid bounding box", obj1.name.c_str(), obj2.name.c_str());
        return false;
    }

    // 1. Side by side
    const double z_overlap = vertical_overlap_ratio(obj1.bbox, obj2.bbox);
    const bool side_by_side = z_overlap >= SIDE_BY_SIDE_MIN_Z_OVERLAP;

    // 2. obj1 further to the left (+y) than obj2
    const double dy = obj1.bbox.center.position.y - obj2.bbox.center.position.y;
    const bool further_left = dy > LATERAL_THRESHOLD_M;

    const bool result = side_by_side && further_left;

    // RCLCPP_INFO(logger, "[leftOf] leftOf(%s, %s): z_overlap=%.2f (min %.2f), dy=%.3f m (must be > %.3f) -> %s",
                // obj1.name.c_str(), obj2.name.c_str(), z_overlap, SIDE_BY_SIDE_MIN_Z_OVERLAP,
                // dy, LATERAL_THRESHOLD_M, result ? "TRUE" : "false");

    return result;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool SymbolLibrary::rightOf(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr)
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Implement the rightOf predicate
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // rightOf(obj1, obj2) is the mirror of leftOf: obj1 stands beside obj2, further to the right:
    //   1. obj1 and obj2 are side by side (they overlap in height, so neither is on top of the other), and
    //   2. the centre of obj1 is more than LATERAL_THRESHOLD_M to the right of the centre of obj2.
    // "Right" is defined in the world frame (-y), so obj1 is right of obj2 when its centre has a smaller y.

    // const rclcpp::Logger logger = rclcpp::get_logger("symbol_library");

    const bool any_bbox_invalid = !bbox_is_valid(obj1.bbox) || !bbox_is_valid(obj2.bbox);
    if (any_bbox_invalid)
    {
        // RCLCPP_INFO(logger, "[rightOf] rightOf(%s, %s): skipped, invalid bounding box", obj1.name.c_str(), obj2.name.c_str());
        return false;
    }

    // 1. Side by side
    const double z_overlap = vertical_overlap_ratio(obj1.bbox, obj2.bbox);
    const bool side_by_side = z_overlap >= SIDE_BY_SIDE_MIN_Z_OVERLAP;

    // 2. obj1 further to the right (-y) than obj2
    const double dy = obj1.bbox.center.position.y - obj2.bbox.center.position.y;
    const bool further_right = dy < -LATERAL_THRESHOLD_M;

    const bool result = side_by_side && further_right;

    // RCLCPP_INFO(logger, "[rightOf] rightOf(%s, %s): z_overlap=%.2f (min %.2f), dy=%.3f m (must be < -%.3f) -> %s",
                // obj1.name.c_str(), obj2.name.c_str(), z_overlap, SIDE_BY_SIDE_MIN_Z_OVERLAP,
                // dy, LATERAL_THRESHOLD_M, result ? "TRUE" : "false");

    return result;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
