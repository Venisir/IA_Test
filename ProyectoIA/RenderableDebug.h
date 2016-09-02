/* 
 * File:   RenderableDebug.h
 * Author: Albert
 *
 * Created on 7 de junio de 2016, 13:19
 */

#ifndef RENDERABLEDEBUG_H
#define	RENDERABLEDEBUG_H
#include <SFML/Graphics.hpp>

class RenderableDebug {
public:
    RenderableDebug();
    void Render();
    virtual ~RenderableDebug();
protected:
    sf::Drawable* drawable;
private:

};

#endif	/* RENDERABLEDEBUG_H */

