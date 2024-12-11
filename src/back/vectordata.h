#ifndef VECTORDATA_H
#define VECTORDATA_H

#include "datamanagment.h"
#include "dataextract/datavisitor.h"

class VectorData : public DataManagment {
public:
    VectorData();
    VectorData(const char* path);
    ~VectorData();
    std::vector<std::vector<std::vector<std::pair<float, float>>>> GetPolygons();
    std::vector<std::vector<std::pair<float, float>>> GetLineStrings();
    std::vector<std::pair<float, float>> GetPoints();
    
    void accept(DataVisitor& visitor) override;

protected:
    const char* filePath;
};

#endif // VECTORDATA_H
