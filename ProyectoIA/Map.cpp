/* 
 * File:   Map.cpp
 * Author: Albert
 * 
 * Created on 7 de junio de 2016, 12:28
 */

#include "Map.h"
#include "MapTile.h"
#include "tinyxml2.h"
#include <iostream>
#include "Globales.h"
#include <float.h>

Map::Map(const char* path, std::string s) {
    texture = new sf::Texture();
    texture->loadFromFile(s);

    shape = new sf::RectangleShape(sf::Vector2f(1024, 720));
    shape->setTexture(texture);
    
    drawable = shape;
    
    /*
     MOSTRAR CUADRICULA
     */
    for (int x = 0; x < 64; x++) {
        std::vector<MapTile*> row;
        for (int y = 0; y < 45; y++) {
            MapTile* tile = new MapTile(16, 16);
            tile->setPosition(sf::Vector2f(x * 16, y * 16));
            tile->setOutlineColor(sf::Color::Black);
            row.push_back(tile);
        }
        tileShape.push_back(row);
    }
    /******/

    /*prueba carga tiled*/
    width = 0;
    height = 0;
    imageHeight = 0;
    imageWidth = 0;
    tileHeight = 0;
    tileWidth = 0;
    numLayers = 0;

    //Cargamos el XML y creamos la ventana
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    tinyxml2::XMLElement* map = doc.FirstChildElement("map");

    //obtenemos los tamanyos de mapa y tiles
    map->QueryIntAttribute("width", &width);
    map->QueryIntAttribute("height", &height);
    map->QueryIntAttribute("tilewidth", &tileWidth);
    map->QueryIntAttribute("tileheight", &tileHeight);


    //Imagen del tileset
    tinyxml2::XMLElement* img = map->FirstChildElement("tileset")->FirstChildElement("image");
    const char *filename = img->Attribute("source");
    img->QueryIntAttribute("height", &imageHeight);
    img->QueryIntAttribute("width", &imageWidth);

    //Cuantas capas tiene mi XML
    tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
    while (layer) {
        numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    tinyxml2::XMLElement* data;

    //Reservando memoria para la variable tilemap, que contendra los gid de las capas
    tilemap = new int**[numLayers];

    for (int i = 0; i < numLayers; i++) {
        tilemap[i] = new int*[height];
    }

    for (int i = 0; i < numLayers; i++) {
        for (int j = 0; j < height; j++) {
            tilemap[i][j] = new int[width];
        }
    }

    //Reservando memoria para los sprite
    tilemapSprite = new sf::Sprite***[numLayers];
    for (int i = 0; i < numLayers; i++) {
        tilemapSprite[i] = new sf::Sprite **[height];
    }

    for (int i = 0; i < numLayers; i++) {
        for (int j = 0; j < height; j++) {
            tilemapSprite[i][j] = new sf::Sprite*[width];
            for (int k = 0; k < width; k++) {
                tilemapSprite[i][j][k] = new sf::Sprite();
            }
        }
    }

    //layer apunta a la primera capa
    layer = map->FirstChildElement("layer");

    //Bucle que recorre todas las capas 1 a 1
    for (int i = 0; i < numLayers; i++) {
        //Hacemos que data apunte al primer tile de la capa actual
        data = layer->FirstChildElement("data")->FirstChildElement("tile");

        //Obtenemos todos los tiles de la capa actual
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < width; k++) {
                //Obtenemos el gid del tile (id del spite) y lo ponemos en la matriz 3D tilemap que almacena todos 
                data->QueryIntAttribute("gid", &tilemap[i][j][k]);
                //Siguiente tile
                data = data->NextSiblingElement("tile");
            }
        }
        layer = layer->NextSiblingElement("layer");
    }

    generaCharMatrix();
    generaFloatMatrix();
    /*fin prueba tiled*/
}

void Map::generaCharMatrix() {

    char c;

    //reserva de memoria para la matriz de char
    matrix = new char*[height];

    for (int i = 0; i < height; i++) {
        matrix[i] = new char[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            c = 0;

            //actual
            if (tilemap[1][i][j] != 0) {
                c = NONE;
            } else {
                c = c | TRANS;


                //arriba
                if (i > 0) {
                    if (tilemap[1][i - 1][j] == 0) {
                        c = c | UP;
                    }
                }

                //abajo
                if (i < height - 1) {
                    if (tilemap[1][i + 1][j] == 0) {
                        c = c | DOWN;
                    }
                }

                //izquierda
                if (j > 0) {
                    if (tilemap[1][i][j - 1] == 0) {
                        c = c | LEFT;
                    }
                }

                //derecha
                if (j < width - 1) {
                    if (tilemap[1][i][j + 1] == 0) {
                        c = c | RIGHT;
                    }
                }

                //arriba-izquierda
                if (i > 0 && j > 0) {
                    if (tilemap[1][i - 1][j - 1] == 0) {
                        c = c | UPLEFT;
                    }
                }

                //arriba-derecha
                if (i > 0 && j < width - 1) {
                    if (tilemap[1][i - 1][j + 1] == 0) {
                        c = c | UPRIGHT;
                    }
                }

                //abajo-izquierda
                if (i < height - 1 && j > 0) {
                    if (tilemap[1][i + 1][j - 1] == 0) {
                        c = c | DOWNLEFT;
                    }
                }

                //abajo-derecha
                if (i < height - 1 && j < width - 1) {
                    if (tilemap[1][i + 1][j - 1] == 0) {
                        c = c | DOWNRIGHT;
                    }
                }
            }
            //asignamos a la matriz el valor que corresponde
            matrix[i][j] = c;
        }
    }
    //std::cout << (matrix[1][1] & RIGHT) << std::endl;
}

char** Map::getMatrix() {
    return matrix;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

int*** Map::getTilemap() const {
    return tilemap;
}

std::vector<std::vector<MapTile*> > Map::getTileShape() const {
    return tileShape;
}

void Map::resetDebugTileMap() {
    for (int x = 0; x < tileShape.size(); x++) {
        for (int y = 0; y < tileShape.at(x).size(); y++) {
            tileShape.at(x).at(y)->setOutlineColor(sf::Color::Black);
        } 
    }
}

Map::~Map() {
    delete texture;
    delete shape;
    for (int x = 0; x < tileShape.size(); x++) {
        for (int y = 0; y < tileShape.at(x).size(); y++) {
            delete(tileShape.at(x).at(y));
        } 
    }
    tileShape.clear();
}

void Map::generaFloatMatrix() {
    matrixT = new float*[height];

    for (int i = 0; i < height; i++) {
        matrixT[i] = new float[width];
        for( int j = 0; j<width;j++){
            if(tilemap[1][i][j]==0){
                matrixT[i][j] = 0;
            }
            else{
                matrixT[i][j] = FLT_MAX;
            }
            std::cout<<((matrixT[i][j]>0)?1:0)<<", ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    
}

float** Map::getMatrixT() {
    return matrixT;
}
