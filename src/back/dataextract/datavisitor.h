#ifndef DATAVISITOR_H
#define DATAVISITOR_H


class VectorData;

class DataVisitor {
public:
    virtual void visitVectorData(const VectorData& vectordata) = 0;
};

#endif
