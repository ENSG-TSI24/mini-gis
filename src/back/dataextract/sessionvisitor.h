#ifndef SESSIONVISITOR_H
#define SESSIONVISITOR_H

#include <nlohmann/json.hpp>
#include "datavisitor.h"
#include "../vectordata.h"

class VectorData;

class SessionVisitor : public DataVisitor {
public:
    SessionVisitor();
    ~SessionVisitor();
    void visitVectorData(const VectorData& vectordata) override;
private:

};
#endif