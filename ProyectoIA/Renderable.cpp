/* 
 * File:   Renderable.cpp
 * Author: Albert
 * 
 * Created on 7 de junio de 2016, 12:43
 */

#include <list>

#include "Renderable.h"

#include "Game.h"

Renderable::Renderable():drawable(0){
    Game::Instance()->renderableObjects.push_back(this);
}

Renderable::~Renderable() {
}

void Renderable::Render() {
    if(drawable){
        Game::Instance()->renderWindow->draw(*drawable);
    }
}
