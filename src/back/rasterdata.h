#ifndef RASTERDATA_H
#define RASTERDATA_H

#include <QImage>
#include "datamanagment.h"
#include "dataextract/datavisitor.h"


class RasterData : public DataManagment{
public:
    RasterData();
    RasterData(const char* path);
    ~RasterData();

    std::pair<double, double> GetGeoCoordinates(int pixelX, int pixelY);
    std::vector<std::pair<double, double>> GetGeoCoordinatesForPixels(const std::vector<std::pair<int, int>>& pixelCoordinates);
    QImage *GetImage();
    int GetWidth() const;
    int GetHeight() const;
    void accept(DataVisitor& visitor) override;

protected:
    int width;
    int height;
    QImage* image;

};

#endif // RASTERDATA_H
