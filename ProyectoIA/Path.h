/* 
 * File:   Path.h
 * Author: Albert
 *
 * Created on 15 de junio de 2016, 12:25
 */

#ifndef PATH_H
#define	PATH_H

#include <list>
#include "Segment.h"
#include "RenderableDebug.h"


class Path: public RenderableDebug {
public:
    Path();
    virtual ~Path();
    
    void addPoint(sf::Vector2f p);
    void addSegment(Segment* s);
    
    void setColor(sf::Color c);
    
private:
    sf::VertexArray* vertices;
    sf::Color color;
};

#endif	/* PATH_H */

