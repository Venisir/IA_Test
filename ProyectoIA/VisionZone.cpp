/* 
 * File:   VisionZone.cpp
 * Author: Guillermo
 * 
 * Created on 15 de junio de 2016, 15:02
 */

#include "VisionZone.h"
#include "Segment.h"
#include <math.h> 
#include <iostream>

VisionZone::VisionZone(float length, float angle) {
    leftVision = new Segment(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
    rightVision = new Segment(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
    leftVision->setColor(sf::Color::Green);
    rightVision->setColor(sf::Color::Green);
    visionD = length;
    pi = 3.141592654f;
    visionA = angle * pi / 180;

    circle = new sf::CircleShape(length);
    circle->setOrigin(length, length);
    circle->setOutlineThickness(2.0f);
    circle->setFillColor(sf::Color::Transparent);
    drawable = circle;
}

VisionZone::~VisionZone() {
    delete(leftVision);
    delete(rightVision);
    delete(circle);
}

void VisionZone::setColor(sf::Color c) {
    circle->setOutlineColor(c);
}

void VisionZone::setLength(float l) {
    visionD = l;
    circle->setRadius(l);
    circle->setOrigin(l,l);
}

void VisionZone::setAngle(float angle) {
    visionA = angle * pi / 180;
}

void VisionZone::setPosition(sf::Vector2f position, sf::Vector2f rotation) {
    circle->setPosition(position);
    fordward = atan2(rotation.y, rotation.x);
    left.x = position.x + visionD * cos(fordward + visionA);
    left.y = position.y + visionD * sin(fordward + visionA);
    right.x = position.x + visionD * cos(fordward - visionA);
    right.y = position.y + visionD * sin(fordward - visionA);
    leftVision->setVertices(position, left);
    rightVision->setVertices(position, right);
    //    leftVision->setColor(sf::Color::Green);
    //    rightVision->setColor(sf::Color::Green);
}

bool VisionZone::isOnSight(sf::Vector2f target, sf::Vector2f center) {
    //std::cout << "¿esta dentro de la zona? > " << isInsideSector(target, center) << std::endl;
    return isInsideSector(target, center);
}

bool VisionZone::areClockwise(sf::Vector2f v1, sf::Vector2f v2) {
    
    if (-v1.x * v2.y + v1.y * v2.x > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool VisionZone::isInsideSector(sf::Vector2f point, sf::Vector2f center) {
    sf::Vector2f actualPoint;
    sf::Vector2f v1;
    sf::Vector2f v2;
    actualPoint.x = point.x - center.x;
    actualPoint.y = point.y - center.y;
    v1.x = right.x - center.x;
    v1.y = right.y - center.y;
    v2.x = left.x - center.x;
    v2.y = left.y - center.y;
    if (!areClockwise(v1, actualPoint) && areClockwise(v2, actualPoint)) {
        return true;
    }
    else {
        return false;
    }
}

std::list<sf::Vector2i> VisionZone::calculateVisionZoneMatrix(int w, int h, sf::Vector2i center) {
    std::list<sf::Vector2i> checkZone;
    for (int x = center.x; x < w; x++) {
        for (int y = center.y; y < h; y++) {
            checkZone.push_back(sf::Vector2i(x, y));
        }
    }
    for (int x = center.x; x > 0; x--) {
        for (int y = center.y; y > 0; y--) {
            checkZone.push_back(sf::Vector2i(x, y));
        }
    }
    std::list<sf::Vector2i> targetDirectionTiles;
    for (std::list<sf::Vector2i>::iterator i = checkZone.begin(); i != checkZone.end(); i++) {
        if (isOnSight(sf::Vector2f((*i).x, (*i).y), (sf::Vector2f)center)) {
            targetDirectionTiles.push_back((*i));
        }
    }
    return targetDirectionTiles;
}