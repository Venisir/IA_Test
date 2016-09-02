/* 
 * File:   MapTile.cpp
 * Author: Guillermo
 * 
 * Created on 13 de junio de 2016, 11:36
 */

#include "MapTile.h"

MapTile::MapTile(float width = 16, float height = 16) {
    shape = new sf::RectangleShape(sf::Vector2f(width, height));
    drawable = shape;
}

MapTile::~MapTile() {
}

void MapTile::setOutlineColor(sf::Color color) {
    shape->setOutlineColor(color);
    shape->setOutlineThickness(0.5f);
    shape->setFillColor(sf::Color::Transparent);
}

void MapTile::setPosition(sf::Vector2f vector) {
    shape->setPosition(vector);
}

void MapTile::resetColour() {
    shape->setOutlineColor(sf::Color::Yellow);
}

void MapTile::setOutlineThickness(float t) {
    shape->setOutlineThickness(t);
}





