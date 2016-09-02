/* 
 * File:   Renderable.h
 * Author: Albert
 *
 * Created on 7 de junio de 2016, 12:43
 */

#ifndef RENDERABLE_H
#define	RENDERABLE_H
#include <SFML/Graphics.hpp>

class Renderable {
public:
    Renderable();
    void Render();
    virtual ~Renderable();
protected:
    sf::Drawable* drawable;
private:
    
};

#endif	/* RENDERABLE_H */

