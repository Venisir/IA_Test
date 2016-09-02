/* 
 * File:   VisionZone.h
 * Author: Guillermo
 *
 * Created on 15 de junio de 2016, 15:02
 */

#ifndef VISIONZONE_H
#define	VISIONZONE_H
#include "RenderableDebug.h"
#include <SFML/Graphics.hpp>
#include <list>
class Segment;

class VisionZone : public RenderableDebug {
public:
    VisionZone(float length, float angle);
    virtual ~VisionZone();
    void setLength(float length);
    void setAngle(float angle);
    void setColor(sf::Color c);
    void setPosition(sf::Vector2f position, sf::Vector2f rotation);
    bool isOnSight(sf::Vector2f target, sf::Vector2f center);
    
    std::list<sf::Vector2i> calculateVisionZoneMatrix(int w, int h, sf::Vector2i center);

    sf::Vector2f left;
    sf::Vector2f right;
private:

    sf::CircleShape* circle;

    Segment* leftVision;
    Segment* rightVision;
    float visionD;
    float visionA;
    float pi;
    float fordward;
    float anglePointX;
    float anglePointY;
    
    std::list<sf::Vector2i> coneVision;

    bool areClockwise(sf::Vector2f v1, sf::Vector2f v2);
    bool isInsideSector(sf::Vector2f point, sf::Vector2f center);

};

#endif	/* VISIONZONE_H */
