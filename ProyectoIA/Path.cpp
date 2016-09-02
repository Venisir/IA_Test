/* 
 * File:   Path.cpp
 * Author: Albert
 * 
 * Created on 15 de junio de 2016, 12:25
 */

#include "Path.h"
#include <SFML/Graphics/PrimitiveType.hpp>

Path::Path():color(sf::Color::White) {
    vertices = new sf::VertexArray();
    vertices->setPrimitiveType(sf::Lines);
    drawable=vertices;
}

Path::~Path() {
    delete vertices;
}

void Path::addSegment(Segment* s) {
    std::list<sf::Vector2f> l=s->getVertices();
    addPoint(l.front());
    addPoint(l.back());
}

void Path::addPoint(sf::Vector2f p) {
    vertices->append(sf::Vertex(p,color));
}

void Path::setColor(sf::Color c) {
    for(int i=0;i<vertices->getVertexCount();i++){
        (*vertices)[i].color=c;
    }
    color=c;
}
