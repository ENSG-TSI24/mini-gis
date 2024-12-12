#include "sessionvisitor.h"
#include <iostream>

SessionVisitor::SessionVisitor() {
}

SessionVisitor::~SessionVisitor() {

}
    
void SessionVisitor::visitVectorData(const VectorData& vectordata) {
    std::cout << "Visited VectorData" << vectordata.GetPath() << std::endl;
}