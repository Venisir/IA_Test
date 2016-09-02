/* 
 * File:   DebugTest.cpp
 * Author: Albert
 * 
 * Created on 7 de junio de 2016, 13:23
 */

#include "DebugTest.h"

DebugTest::DebugTest() {
    shape = new sf::RectangleShape(sf::Vector2f(16,16));
    shape->setFillColor(sf::Color::Blue);
    
    drawable = shape;
    
}

DebugTest::~DebugTest() {
    
    delete (shape);
}

