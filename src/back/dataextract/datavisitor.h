#ifndef DATAVISITOR_H
#define DATAVISITOR_H

#include "../vectordata.h"

class VectorData;

class DataVisitor {
public:
    virtual void visitVectorData(const VectorData& vectordata) = 0;
};

#endif
