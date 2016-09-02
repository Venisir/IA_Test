/* 
 * File:   IACharacter.cpp
 * Author: Guillermo
 * 
 * Created on 22 de junio de 2016, 10:24
 */

#include "IACharacter.h"
#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "AStar.h"
#include <iostream>
#include "VisionZone.h"
#include "AudioZone.h"

#include <cmath>
#include <iostream>

IACharacter::IACharacter() : player(0),patrol(1), is_going_destiny(0) {
    shape = new sf::CircleShape(8);
    shape->setFillColor(sf::Color::Red);
    shape->setOutlineColor(sf::Color::Black);
    shape->setOutlineThickness(1.0f);

    audioSensorZone->setColor(sf::Color::Magenta);

    drawable = shape;
    pathFinding = new AStar(Game::Instance()->getMap()->getMatrix());
}

IACharacter::~IACharacter() {
    delete (shape);
    delete pathFinding;
    delete(player);
}

void IACharacter::setPlayer(Player* p) {
    player = p;
}

void IACharacter::SetOrigin(sf::Vector2f origin) {
    this->origin = origin;
}

sf::Vector2f IACharacter::GetOrigin() const {
    return origin;
}

void IACharacter::SetDestiny(sf::Vector2f destiny) {
    this->destiny = destiny;
}

sf::Vector2f IACharacter::GetDestiny() const {
    return destiny;
}

void IACharacter::Update() {
    setSensorsOrigin(position, rotation);
   
    //bool test=0;
    
    bool listen = checkAudio(player);
    bool view = checkVision(player);
    
    
    patrol = !listen&&!view;
    
    if (patrol) {
        if(camino.size()==0){
            if (is_going_destiny){
                sf::Vector2i ini = calculateTargetPositionInMatrix(position);
                sf::Vector2i end = calculateTargetPositionInMatrix(origin);
                camino = pathFinding->calculatePath(ini, end);
                is_going_destiny=false;
            }
            else{
                sf::Vector2i ini = calculateTargetPositionInMatrix(position);
                sf::Vector2i end = calculateTargetPositionInMatrix(destiny);
                camino = pathFinding->calculatePath(ini, end);
                is_going_destiny=true;
            }
            targetPosition = (sf::Vector2f)(camino.front()*16) + sf::Vector2f(8, 8);
        }
    }
    else{
        if(listen && !view ){
            sf::Vector2i ini = calculateTargetPositionInMatrix(position);
            sf::Vector2i end = calculateTargetPositionInMatrix(player->position);
            if(ini!=end) camino = pathFinding->calculatePath(ini, end);
        }
        if(view){
            camino.clear();
            targetPosition = player->position;
        }
    }
    move();
}

