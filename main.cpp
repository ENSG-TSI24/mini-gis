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

int CallWMTSLayer(){
    // BOUT DE CODE QUI PERMET DE LISTER LE NOM DES COUCHES WMTS IGN



        CURL* curl = curl_easy_init();
        if (!curl) {
            cerr << "Failed to initialize CURL" << endl;
            return 1;
        }

        // URL for GetCapabilities request
        string url = "https://data.geopf.fr/wmts?SERVICE=WMTS&VERSION=1.0.0&REQUEST=GetCapabilities";
        string response; // To store the server's response

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "CURL error: " << curl_easy_strerror(res) << endl;
            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);

        // Parse the XML response with TinyXML2
        // On descend dans l'arborescence du XML ( capabilities > content > layer > balise ows:identifier
        XMLDocument doc;
        if (doc.Parse(response.c_str()) != XML_SUCCESS) {
            cerr << "Failed to parse XML" << endl;
            return 1;
        }

        // Find all <ows:Identifier> elements under <Layer>
        XMLElement* capabilities = doc.FirstChildElement("Capabilities");
        if (!capabilities) {
            cerr << "Capabilities tag not found in the XML" << endl;
            return 1;
        }

        XMLElement* contents = capabilities->FirstChildElement("Contents");
        if (!contents) {
            cerr << "Contents tag not found in the XML" << endl;
            return 1;
        }

        XMLElement* layer = contents->FirstChildElement("Layer");
        while (layer) {
            XMLElement* identifier = layer->FirstChildElement("ows:Identifier");
            if (identifier && identifier->GetText()) {
                cout << identifier->GetText() << endl;
            }
            layer = layer->NextSiblingElement("Layer");
        }

        return 0;
    }

// BOUT DE CODE QUI PERMET DE TELECHARGER UNE TUILE WMTS
int DownloadWMTSTile(){
    CURL *curl = curl_easy_init();
    if(curl) {
        // WMTS Tile URL
        const char *url_test_tile = "https://data.geopf.fr/wmts?SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=ADMINEXPRESS-COG.LATEST&STYLE=normal&FORMAT=image/png&TILEMATRIXSET=PM_6_16&TILEMATRIX=6&TILEROW=22&TILECOL=33";

        // Open a file to save the downloaded tile
        FILE *file = fopen("/home/formation/Documents/opengl/testsflux/tile.png", "wb");
        if (!file) {
            fprintf(stderr, "Could not open file for writing\n");
            return 1;
        }

        // Set CURL options
        curl_easy_setopt(curl, CURLOPT_URL, url_test_tile);  // Set the URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);  // Set the write callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);  // Pass the file pointer to the callback

        // Perform the request and check for errors
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        fclose(file);
        curl_easy_cleanup(curl);
    }

    return 0;
}


QPixmap loadTileAsPixmap(wmtsdata& wmts, const char* layerName, int zoom, int row, int col) {
    std::string outputFile = "tile_" + std::to_string(zoom) + "_" +
                             std::to_string(row) + "_" + std::to_string(col) + ".png";

    // Télécharger la tuile avec WMTSData
    wmts.downloadTile(layerName, outputFile.c_str(), zoom, row, col);

    // Charger l'image en tant que QPixmap
    return QPixmap(QString::fromStdString(outputFile));
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
      int centerRow = 23;                                // Ligne centrale
      int centerCol = 32;                                // Colonne centrale
      int gridSize = 5;                                  // Taille de la grille (5x5 tuiles)

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










