#ifndef RASTERDATA_H
#define RASTERDATA_H

#include "datamanagment.h"
#include <QImage>
#include "dataextract/datavisitor.h"

class RasterData : public DataManagment{
public:
    RasterData();
    RasterData(const char* path);
    ~RasterData();

    std::pair<double, double> GetGeoCoordinates(int pixelX, int pixelY);
    std::vector<std::pair<double, double>> GetGeoCoordinatesForPixels(const std::vector<std::pair<int, int>>& pixelCoordinates);
    QImage *GetImage();
    void accept(DataVisitor& visitor) override;
    int GetWidth() const;
    int GetHeight() const;

protected:
    int width;
    int height;
    QImage* image;

};

#endif // RASTERDATA_H
