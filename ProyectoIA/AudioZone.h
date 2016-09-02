/* 
 * File:   AudioRaodius.h
 * Author: Guillermo
 *
 * Created on 15 de junio de 2016, 14:41
 */

#ifndef AUDIOZONE_H
#define	AUDIOZONE_H
#include "RenderableDebug.h"
#include <SFML/Graphics.hpp>

class AudioZone : public RenderableDebug {
public:
    AudioZone(float r);
    virtual ~AudioZone();
    void setSize(float r);
    void setColor(sf::Color c);
    void setPosition(sf::Vector2f position);
private:
    sf::CircleShape* circle;

};

#endif	/* AUDIOZONE_H */
