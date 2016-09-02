/* 
 * File:   AudioRaodius.cpp
 * Author: Guillermo
 * 
 * Created on 15 de junio de 2016, 14:41
 */

#include "AudioZone.h"

AudioZone::AudioZone(float r) {
    circle = new sf::CircleShape(r);
    circle->setOrigin(r,r);
    circle->setOutlineThickness(1.5f);
    circle->setFillColor(sf::Color::Transparent);
    drawable = circle;
}

AudioZone::~AudioZone() {
    delete(circle);
}

void AudioZone::setColor(sf::Color c) {
    circle->setOutlineColor(c);
}

void AudioZone::setSize(float r) {
    circle->setRadius(r);
    circle->setOrigin(r,r);
}

void AudioZone::setPosition(sf::Vector2f position) {
    circle->setPosition(position);
}




