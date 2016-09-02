/* 
 * File:   TextValue.cpp
 * Author: Guillermo
 * 
 * Created on 11 de julio de 2016, 12:48
 */

#include "TextValue.h"
#include "Game.h"

TextValue::TextValue() : x(0), y(0) {
    value = new sf::Text();
    value->setFont(*Game::Instance()->GetFont());
    value->setOrigin(0,0);
    value->setScale(1.0f,1.0f);
    value->setCharacterSize(8);
    value->setColor(sf::Color::Red);
    value->setPosition( 100.0f, 100.0f );
    value->setString("");
    drawable = value;
}

TextValue::~TextValue() {
    delete(value);
}

sf::Text* TextValue::GetValue() const {
    return value;
}

