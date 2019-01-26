#include "sat_collision_detection.hpp"
#include <numeric>
#include <iostream>

bool SatCollisionDetection::detect_collision(const std::vector<sf::Vector2f> &convexPolygonA, const std::vector<sf::Vector2f> &convexPolygonB)
{
    std::cout << "1" << std::endl;
    for (int i = 0; i < convexPolygonA.size(); ++i) {
        std::cout << "2" << std::endl;
        sf::Vector2f vertex = convexPolygonA[i];
        std::cout << "2.1" << std::endl;
        sf::Vector2f nextVertex = convexPolygonA[(i + 1) % convexPolygonA.size()];
        std::cout << "2.2" << std::endl;
        sf::Vector2f edge = nextVertex - vertex;
        std::cout << "2.3" << std::endl;
        sf::Vector2f axis;
        axis.x = -edge.y;
        axis.y = edge.x;
        std::cout << "2.4" << std::endl;
        float polygonAMax = -std::numeric_limits<float>::infinity();
        float polygonAMin = std::numeric_limits<float>::infinity();
        float polygonBMax = -std::numeric_limits<float>::infinity();
        float polygonBMin = std::numeric_limits<float>::infinity();
        std::cout << "3" << std::endl;
        for (const auto& vertex : convexPolygonA) {
            std::vector<float> axisVec{axis.x, axis.y};
            std::vector<float> vertexVec{ vertex.x, vertex.y };
            auto proj = std::inner_product(std::begin(axisVec), std::end(axisVec), std::begin(vertexVec), 0.0);
            if (proj < polygonAMin) polygonAMin = proj;
            if (proj > polygonAMax) polygonAMax = proj;
        }
        std::cout << "4" << std::endl;
        for (const auto& vertex : convexPolygonB) {
            std::vector<float> axisVec{ axis.x, axis.y };
            std::vector<float> vertexVec{ vertex.x, vertex.y };
            auto proj = std::inner_product(std::begin(axisVec), std::end(axisVec), std::begin(vertexVec), 0.0);
            if (proj < polygonBMin) polygonBMin = proj;
            if (proj > polygonBMax) polygonBMax = proj;
        }
        std::cout << "5" << std::endl;
        if (polygonAMax < polygonBMin || polygonAMin > polygonBMax)
        {
            return false;
        }
            
    }
    return true;
}