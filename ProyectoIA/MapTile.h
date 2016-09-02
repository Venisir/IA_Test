/* 
 * File:   MapTile.h
 * Author: Guillermo
 *
 * Created on 13 de junio de 2016, 11:36
 */

#ifndef MAPTILE_H
#define	MAPTILE_H
#include "RenderableDebug.h"
#include <SFML/Graphics.hpp>

class MapTile : public RenderableDebug {
public:
    MapTile(float width , float height);
    virtual ~MapTile();
    
    void setPosition(sf::Vector2f vector);
    void setOutlineColor(sf::Color color);
    void setOutlineThickness(float t);
    
    void resetColour();
private:
    sf::Shape* shape;
    
};

#endif	/* MAPTILE_H */

