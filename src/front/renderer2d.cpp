#include "renderer2d.h"
#include "src/back/vectordata.h"
#include "src/back/rasterdata.h"
#include <iostream>

Renderer2D::Renderer2D(){
    session = Session();
    auto layers2d_json = session.getLayers();
    for (auto& layer_info : layers2d_json) {
        const std::string& layer_type = layer_info.second;
        const std::string& layer_path = layer_info.first;
        const char* layer_path_cstr = layer_path.c_str();
        if (layer_type == "vector") {
            VectorData geo(layer_path_cstr);
            std::shared_ptr<Layer2d> vector = std::make_unique<Layer2d>(geo);
            vector->calculateBoundingBox();
            vector->setName(layer_path);
            lst_layers2d.push_back(vector);
        } else if (layer_type == "raster") {
            RasterData geo(layer_path_cstr);
            std::shared_ptr<LayerRaster> raster = std::make_unique<LayerRaster>(geo);
            raster->calculateBoundingBox();
            raster->setName(layer_path);
            lst_layers2d.push_back(raster);
        } 
    }

}

Renderer2D::~Renderer2D() {}

void Renderer2D::paintGl2D() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    renderLayers2d();
}

void Renderer2D::renderLayers2d() {
    for (int i = lst_layers2d.size() - 1; i >= 0; --i) {
        auto& layer = lst_layers2d[i];
        if (layer->getIsVisible()) {
            layer->render();
        }
    }
}

void Renderer2D::reset2D(){
    if(lst_layers2d.size()!=0 ){
        lst_layers2d.clear();
    }
}


void Renderer2D::highlightGeometry(const std::string& layerName, int rowIndex) {
    for (auto& layer : lst_layers2d) {
        if (layer->getName() == layerName) {
            // Highlight the geometry in the specified layer
            layer->highlightGeometry(rowIndex);
            return; // Stop once the target layer is found
        }
    }
}

