#ifndef SESSIONVISITOR_H
#define SESSIONVISITOR_H

#include <nlohmann/json.hpp>
#include "datavisitor.h"

class VectorData;
class RasterData;


class SessionVisitor : public DataVisitor {
public:
    SessionVisitor();
    ~SessionVisitor();
    void visitVectorData(const VectorData& vectordata) override;
    void visitRasterData(const RasterData& rasterdata) override;
    void addToJson(const char* path);
    void updateFile();
private:
    std::shared_ptr<nlohmann::json> m_json;

};
#endif