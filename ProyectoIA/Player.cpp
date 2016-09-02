/* 
 * File:   Player.cpp
 * Author: Guillermo
 * 
 * Created on 9 de junio de 2016, 11:24
 */

#include "Player.h"
#include "IACharacter.h"
#include "Game.h"
#include "Map.h"
#include "AStar.h"
#include "MapTile.h"
#include <iostream>
#include "VisionZone.h"
#include "AudioZone.h"
#include "Tactico.h"

#include <iostream>

Player::Player() : ia1(0), ia2(0) {
    shape = new sf::CircleShape(8);
    shape->setFillColor(sf::Color::Cyan);
    shape->setOutlineColor(sf::Color::Black);
    shape->setOutlineThickness(1.0f);
    SetPosition(sf::Vector2f(24, 24));
    targetPosition = position;
    drawable = shape;
    visionSensorZone->setColor(sf::Color::Cyan);
    
    this->speed = 80.0f;
    
    std::list<infoTactica> l;
    l.push_back(infoTactica(Game::Instance()->getMap()->getMatrixT(), 1));
    l.push_back(infoTactica(sensorAudioMatrix, 20.0f));
    l.push_back(infoTactica(sensorVisionMatrix, 20.0f));
    
    //TODO modificar esta variable para usar A* o tactico
    useTactic = false;
    
    pathFindingT = new Tactico(l, Game::Instance()->getMap()->getWidth(),Game::Instance()->getMap()->getHeight());
    pathFindingA = new AStar(Game::Instance()->getMap()->getMatrix());
    //generateSensorMatrix();
}

Player::~Player() {
    delete (shape);
    
    delete (ia1);
    delete (ia2);
    
    delete pathFindingA;
    delete pathFindingT;
}

void Player::setIA1(IACharacter* ia) {
    ia1 = ia;
}

void Player::setIA2(IACharacter* ia) {
    ia2 = ia;
}

void Player::Update() {
    
    bool view_listen = false;
    
    view_listen=checkAudio(ia1)||view_listen;
    view_listen=checkVision(ia1)||view_listen;
    
    view_listen=checkAudio(ia2)||view_listen;
    view_listen=checkVision(ia2)||view_listen;
    
    setSensorsOrigin(position, rotation);
    Game::Instance()->GetDeltaTime();
    
    //TODO Arreglar cuando recalcula el camino
    
    if (Game::Instance()->getMouseKey(0) || view_listen) {
        sf::Vector2i ini = calculateTargetPositionInMatrix(position); //convierto la posicion de la pantalla a posicion dentro de la matriz
        
        if(Game::Instance()->getMouseKey(0)) 
            endOfPath = calculateTargetPositionInMatrix((sf::Vector2f)Game::Instance()->getMousePos());//convierto la posicion final en la pantalla a posicion dentro de la matriz
        
        if(Game::Instance()->getMap()->getTilemap()[1][endOfPath.y][endOfPath.x]==0)
        {
            if(useTactic){
                if (ini != endOfPath) camino = pathFindingT->calculatePath(ini, endOfPath);
            }
            else if(Game::Instance()->getMouseKey(0)){
                //TODO no funciona con el recalculo del camino
                if (ini != endOfPath) camino = pathFindingA->calculatePath(ini, endOfPath); //obtengo el camino
            }
        }
    }
    showSensorsRangeAndView();
    move();
     
    //std::cout<<pathFindingT->matrix[(int)(position.y/16)][(int)(position.x/16)]<<std::endl;
          
    setSensorsOrigin(position, rotation);
    
    bresenham((int) position.x, (int) position.y, (int) Game::Instance()->getMousePos().x, (int) Game::Instance()->getMousePos().y);
    MatrixUpdate();
}


