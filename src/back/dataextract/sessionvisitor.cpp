#include "sessionvisitor.h"
#include <iostream>

SessionVisitor::SessionVisitor() {
}

SessionVisitor::~SessionVisitor() {

}
    
void SessionVisitor::visitVectorData(const VectorData& vectordata) {
    std::cout << "Visited VectorData " << std::endl;
}
void SessionVisitor::visitRasterData(const RasterData& rasterdata) {
    std::cout << "Visited RasterData " << std::endl;
} 