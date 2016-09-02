/* 
 * File:   RenderableDebug.cpp
 * Author: Albert
 * 
 * Created on 7 de junio de 2016, 13:19
 */

#include "RenderableDebug.h"

#include <list>

#include "Game.h"

#include "Segment.h"

RenderableDebug::RenderableDebug():drawable(0){
    Game::Instance()->renderableDebugObjects.push_back(this);
}

RenderableDebug::~RenderableDebug() {
}

void RenderableDebug::Render() {
    if(drawable){
        Game::Instance()->renderWindow->draw(*drawable);
    }
}
