#include "sessionvisitor.h"
#include <iostream>

#include "../vectordata.h"

SessionVisitor::SessionVisitor() {
}

SessionVisitor::~SessionVisitor() {

}
    
void SessionVisitor::visitVectorData(const VectorData& vectordata) {
    std::cout << "Visited VectorData " << vectordata.GetPath() << std::endl;
}
void SessionVisitor::visitRasterData(const RasterData& rasterdata) {
    std::cout << "Visited RasterData " << std::endl;
} 