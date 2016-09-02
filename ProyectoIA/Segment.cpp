/* 
 * File:   Segment.cpp
 * Author: Albert
 * 
 * Created on 15 de junio de 2016, 11:43
 */

#include "Segment.h"

#include <iostream>
#include <list>

Segment::Segment():color(sf::Color::White) {
    
    vertices = new sf::VertexArray();
    vertices->setPrimitiveType(sf::Lines);
    drawable=vertices;
    
}

Segment::Segment(sf::Vector2f a, sf::Vector2f b):color(sf::Color::White) {
    vertices = new sf::VertexArray();
    vertices->setPrimitiveType(sf::Lines);
    setVertices(a,b);
    drawable=vertices;
}

void Segment::setColor(sf::Color c) {
    if(vertices->getVertexCount()!=0){
        (*vertices)[0].color=c;
        (*vertices)[1].color=c;
    }
    color=c;
}

Segment::~Segment() {
    delete vertices;
}

void Segment::setVertices(sf::Vector2f a, sf::Vector2f b) {
    
    vertices->clear();
    
    vertices->append(sf::Vertex(a,color));
    vertices->append(sf::Vertex(b,color));
}

std::list<sf::Vector2f> Segment::getVertices() {
    std::list<sf::Vector2f> l;
    if(vertices->getVertexCount()!=0){
        l.push_back((*vertices)[0].position);
        l.push_back((*vertices)[1].position);
    }
    return l;
}
