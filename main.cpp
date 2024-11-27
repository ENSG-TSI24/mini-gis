#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <curl/curl.h>
#include <gdal/cpl_atomic_ops.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "tinyxml2.h"
#include "src/wmtsdata.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <gdal_priv.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace tinyxml2;

// Callback to store response data from CURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //appel liste flux WMTS
    CallWMTSLayer();
    //appel download WMTS Tuile
    DownloadWMTSTile();
*/
    QApplication app(argc, argv);

      // Initialiser GDAL
      GDALAllRegister();

      // Instancier un objet WMTSData
      wmtsdata wmts;

      // Ouvrir le flux WMTS
      const char* wmtsUrl = "WMTS:https://data.geopf.fr/wmts?SERVICE=WMTS&VERSION=1.0.0&REQUEST=GetCapabilities";
      wmts.open(wmtsUrl);

      // Lister les couches disponibles
      std::cout << "Liste des couches disponibles :" << std::endl;
      wmts.getLayers();

      // Configuration de la vue initiale
      const char* layerName = "ORTHOIMAGERY.ORTHOPHOTOS"; // Exemple de couche
      int zoomLevel = 6;                                 // Niveau de zoom
      int centerRow = 22;                                // Ligne centrale
      int centerCol = 32;                                // Colonne centrale
      int gridSize = 3;                                  // Taille de la grille
      // Charger les tuiles autour de la position centrale
      std::vector<std::string> tilePaths = wmts.loadTileGrid(layerName, zoomLevel, centerRow, centerCol, gridSize);

      // Créer une scène Qt pour afficher les tuiles
      QGraphicsScene scene;

      // Ajouter chaque tuile à la scène
      int tileSize = 256; // Taille typique des tuiles WMTS
      int halfGrid = gridSize / 2;

      for (int i = 0; i < tilePaths.size(); ++i) {
          QPixmap pixmap(QString::fromStdString(tilePaths[i]));
          if (!pixmap.isNull()) {
              // Calculer la position de la tuile dans la scène
              int row = i / gridSize - halfGrid;
              int col = i % gridSize - halfGrid;

              scene.addPixmap(pixmap)->setPos(col * tileSize, row * tileSize);
          } else {
              std::cerr << "Erreur lors du chargement de la tuile : " << tilePaths[i] << std::endl;
          }
      }

      // Créer une vue pour afficher la scène
      QGraphicsView view(&scene);
      view.setWindowTitle("Affichage dynamique du flux WMTS");
      view.setRenderHint(QPainter::Antialiasing);
      view.setRenderHint(QPainter::SmoothPixmapTransform);
      view.show();

      // Fermer le flux WMTS
      wmts.close();

      // Exécuter l'application Qt
      return app.exec();


}










