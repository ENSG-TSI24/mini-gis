#include "geojsonloader.h"


using json = nlohmann::json;

Geojsonloader::Geojsonloader(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier GeoJSON : " + filePath);
    }

    json geojson;
    try {
        file >> geojson;
    } catch (const std::exception& e) {
        throw std::runtime_error("Erreur lors du parsing du fichier GeoJSON : " + std::string(e.what()));
    }

    points.clear();
    if (geojson["type"] != "FeatureCollection") {
        throw std::runtime_error("Le fichier GeoJSON n'est pas de type FeatureCollection.");
    }

    for (const auto& feature : geojson["features"]) {
        if (!feature.contains("geometry")) continue;

        auto geometry = feature["geometry"];
        if (geometry["type"] == "Point" && geometry.contains("coordinates")) {
            const auto& coord = geometry["coordinates"];
            if (coord.size() >= 2) {
                points.emplace_back(coord[0], coord[1]); // (longitude, latitude)
            }

        } else if (geometry["type"] == "LineString" && geometry.contains("coordinates")) {
            std::vector<std::pair<float, float>> line;
            for (const auto& coord : geometry["coordinates"]) {
                if (coord.size() >= 2) {
                    line.emplace_back(coord[0], coord[1]);
                }
            }
            if (!line.empty()) {
                linestrings.push_back(line);
            }

        } else if (geometry["type"] == "Polygon" && geometry.contains("coordinates")) {
            std::vector<std::vector<std::pair<float, float>>> polygon;
            for (const auto& ring : geometry["coordinates"]) {
                std::vector<std::pair<float, float>> ringPoints;
                for (const auto& coord : ring) {
                    if (coord.size() >= 2) {
                        ringPoints.emplace_back(coord[0], coord[1]);
                    }
                }
                if (!ringPoints.empty()) {
                    polygon.push_back(ringPoints);
                }
            }
            if (!polygon.empty()) {
                polygons.push_back(polygon);
            }
        }
    }
}


std::vector<std::pair<float, float>> Geojsonloader::getPoints(){
    return this->points;
}

std::vector<std::vector<std::pair<float, float>>> Geojsonloader::getLinestrings(){
    return this->linestrings;
}

std::vector<std::vector<std::vector<std::pair<float, float>>>> Geojsonloader::getPolygons(){
    return this->polygons;
}