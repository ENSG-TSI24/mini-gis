#include "sessionvisitor.h"
#include <iostream>
#include <fstream>

#include "../vectordata.h"
#include "../rasterdata.h"

SessionVisitor::SessionVisitor() {
    m_json = std::make_shared<nlohmann::json>();
    std::ifstream infile("../data/session.json");
    if (infile.peek() != std::ifstream::traits_type::eof()) {
        infile >> *m_json;
    }
    infile.close();
}

SessionVisitor::~SessionVisitor() {

}

void SessionVisitor::updateFile() {
    std::ofstream file("../data/session.json");
    file << m_json->dump(4);
    file.close();
}

void SessionVisitor::addToJson(const char* path) {
    m_json->push_back(path);
    updateFile();
}

    
void SessionVisitor::visitVectorData(const VectorData& vectordata) {
    addToJson(vectordata.GetPath());
}
void SessionVisitor::visitRasterData(const RasterData& rasterdata) {
    addToJson(rasterdata.GetPath());
} 