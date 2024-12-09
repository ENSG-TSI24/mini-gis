#include "renderer2d.h"

Renderer2D::Renderer2D(Renderer& renderer) : parent(renderer) {}

Renderer2D::~Renderer2D() {}

void Renderer2D::paintGl2D() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    renderRasters();
    renderLayers2d();
}

void Renderer2D::renderLayers2d() {
    for (int i = lst_layers2d.size() - 1; i >= 0; --i) {
        auto& layer = lst_layers2d[i];
        if (layer.isVisible) {
            layer.renderPolygons();
            layer.renderLinestrings();
            layer.renderPoints();
        }
    }
}

void Renderer2D::renderRasters() {
    int i = 0;
    for (auto& raster: lst_layersraster){
        std::cout<<"------------ Layer : "<<i<< " ------------"<<std::endl;
        raster.renderRasters();
        ++i;
    }
}

void Renderer2D::reset2D(){
    if(lst_layers2d.size()!=0 ){
        lst_layers2d.clear();
        parent.controller->getCamera().resetCamera();
        parent.update();
    }
}
