#include "sat_collision_detection.hpp"
#include <numeric>

bool SatCollisionDetection::detect_collision(const std::vector<sf::Vector2f> &convexPolygonA, const std::vector<sf::Vector2f> &convexPolygonB)
{
    for (int i = 0; i < convexPolygonA.size(); ++i) {
        sf::Vector2f vertex = convexPolygonA[i];
        sf::Vector2f nextVertex = convexPolygonA[(i + 1) % convexPolygonA.size()];
        sf::Vector2f edge = nextVertex - vertex;
        sf::Vector2f axis;
        axis.x = -edge.y;
        axis.y = edge.x;
        float polygonAMax = -std::numeric_limits<float>::infinity();
        float polygonAMin = std::numeric_limits<float>::infinity();
        float polygonBMax = -std::numeric_limits<float>::infinity();
        float polygonBMin = std::numeric_limits<float>::infinity();
        for (const auto& vertex : convexPolygonA) {
            std::vector<float> axisVec{axis.x, axis.y};
            std::vector<float> vertexVec{ vertex.x, vertex.y };
            auto proj = std::inner_product(std::begin(axisVec), std::end(axisVec), std::begin(vertexVec), 0.0);
            if (proj < polygonAMin) polygonAMin = proj;
            if (proj > polygonAMax) polygonAMax = proj;
        }
        for (const auto& vertex : convexPolygonB) {
            std::vector<float> axisVec{ axis.x, axis.y };
            std::vector<float> vertexVec{ vertex.x, vertex.y };
            auto proj = std::inner_product(std::begin(axisVec), std::end(axisVec), std::begin(vertexVec), 0.0);
            if (proj < polygonBMin) polygonBMin = proj;
            if (proj > polygonBMax) polygonBMax = proj;
        }
        if (polygonAMax < polygonBMin || polygonAMin > polygonBMax)
        {
            return false;
        }
            
    }
    return true;
}