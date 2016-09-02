/* 
 * File:   Map.h
 * Author: Albert
 *
 * Created on 7 de junio de 2016, 12:28
 */

#ifndef MAP_H
#define	MAP_H

#include "Renderable.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

class MapTile;

class Map: public Renderable {
public:
    Map(const char* path,std::string s);
    
    virtual ~Map();
    char** getMatrix();
    float** getMatrixT();
    int getWidth() const;
    int getHeight() const;
    int*** getTilemap() const;
    std::vector<std::vector<MapTile*> > getTileShape() const;
    void resetDebugTileMap();
private:
    sf::Texture* texture;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    int imageWidth;
    int imageHeight;
    int numLayers;
    
    int *** tilemap;
    sf::Sprite **** tilemapSprite;
    char ** matrix;
    float ** matrixT;
    
    std::vector<std::vector<MapTile*> > tileShape;
    
    void generaCharMatrix();
    void generaFloatMatrix();
    
    sf::Shape* shape;
    
};

#endif	/* MAP_H */

