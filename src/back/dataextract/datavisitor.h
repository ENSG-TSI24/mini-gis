#ifndef DATAVISITOR_H
#define DATAVISITOR_H


class VectorData;
class RasterData;

class DataVisitor {
public:
    virtual void visitVectorData(const VectorData& vectordata) = 0;
    virtual void visitRasterData(const RasterData& rasterdata) = 0;
};

#endif
