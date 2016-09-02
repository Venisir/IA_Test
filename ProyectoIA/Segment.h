/* 
 * File:   Segment.h
 * Author: Albert
 *
 * Created on 15 de junio de 2016, 11:43
 */

#ifndef SEGMENT_H
#define	SEGMENT_H

#include <list>

#include "RenderableDebug.h"



class Segment:public RenderableDebug {
public:
    Segment();
    
    Segment(sf::Vector2f a, sf::Vector2f b);
    virtual ~Segment();
    
    std::list<sf::Vector2f> getVertices();
    void setVertices(sf::Vector2f a, sf::Vector2f b);
    void setColor(sf::Color c);
    

private:
    sf::VertexArray* vertices;
    sf::Color color;
};

#endif	/* SEGMENT_H */

