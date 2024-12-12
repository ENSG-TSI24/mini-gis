#include "src/front/mainwindow.h"
#include <QApplication>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include "src/back/API_WMS.h"

using json = nlohmann::json;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // Créer et afficher la fenêtre principale
    MainWindow w;
    w.show();
    const char* wfsUrl = "WMS:https://data.geopf.fr/wms-r?SERVICE=WMS&VERSION=1.3.0&REQUEST=GetCapabilities";

    const char* layerName = "ADMINEXPRESS-COG.LATEST:chflieu_commune";


    return app.exec();
}
