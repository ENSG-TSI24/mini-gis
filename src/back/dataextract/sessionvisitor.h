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
private:

};
#endif