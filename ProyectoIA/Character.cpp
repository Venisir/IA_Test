/* 
 * File:   Character.cpp
 * Author: Guillermo
 * 
 * Created on 9 de junio de 2016, 11:29
 */

#include <cmath>
#include <iostream>

#include "Game.h"
#include "Character.h"
#include "Map.h"
#include "MapTile.h"
#include "VisionZone.h"
#include "Segment.h"
#include "TextValue.h"
#include "AudioZone.h"
#include <vector>
#include <sstream>

Character::Character() : is_sneakSPeed(false), is_travelling(false), normalSpeed(40), sneakSpeed(20), position(0, 0), rotation(1, 1), weightValue(5000), somethingIsOnSight(false),
targetIsMakingNoise(false), name("character"), showMatrixValues(false) {
    speed = normalSpeed;
    Game::Instance()->characterObjects.push_back(this);

    h = Game::Instance()->getMap()->getHeight();
    w = Game::Instance()->getMap()->getWidth();

    segment = new Segment(position, position);
    generateSensorsMatrix();
    /*
    MOSTRAR CUADRICULA
     */
    for (int x = 0; x < 45; x++) {
        std::vector<MapTile*> row;
        for (int y = 0; y < 64; y++) {
            MapTile* tile = new MapTile(16, 16);
            tile->setPosition(sf::Vector2f(y * 16, x * 16));
            tile->setOutlineColor(sf::Color::Black);
            tile->setOutlineThickness(0.5f);
            row.push_back(tile);
        }
        tileWeight.push_back(row);
    }
    /******/
}

void Character::MatrixUpdate() {

    UpdateMatrix(sensorAudioMatrix);
    UpdateMatrix(sensorVisionMatrix);
}

void Character::SetUseTactic(bool useTactic) {
    this->useTactic = useTactic;
}

bool Character::IsUseTactic() const {
    return useTactic;
}

void Character::SetVisionColor(sf::Color visionColor) {
    this->visionColor = visionColor;
}

sf::Color Character::GetVisionColor() const {
    return visionColor;
}

void Character::SetAudioColor(sf::Color audioColor) {
    this->audioColor = audioColor;
}

sf::Color Character::GetAudioColor() const {
    return audioColor;
}

void Character::SetName(std::string name) {
    this->name = name;
}

std::string Character::GetName() const {
    return name;
}

void Character::UpdateMatrix(float** matrix) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (matrix[i][j] > 0) {
                matrix[i][j]-=2;
                if (showMatrixValues) {
                    if (matrix[i][j] > 4500) {
                        if (this->GetName() == "Player") {
                            this->tileWeight[i][j]->setOutlineColor(sf::Color::Blue);
                            this->tileWeight[i][j]->setOutlineThickness(2.0f);
                            //Game::Instance()->getMap()->getTileShape()[i][j]
                        }
                    } else if (matrix[i][j] > 3500) {
                        if (this->GetName() == "Player") {
                            this->tileWeight[i][j]->setOutlineColor(sf::Color::Green);
                            this->tileWeight[i][j]->setOutlineThickness(2.0f);
                        }
                    } else if (matrix[i][j] > 50) {
                        if (this->GetName() == "Player") {
                            this->tileWeight[i][j]->setOutlineColor(sf::Color::White);
                            this->tileWeight[i][j]->setOutlineThickness(2.0f);
                        }

                    } else {
                        if (this->GetName() == "Player") {
                            this->tileWeight[i][j]->setOutlineColor(sf::Color::Black);
                            this->tileWeight[i][j]->setOutlineThickness(0.5f);
                        }

                    }

                }
            }
        }
    }
}

void Character::setSpeedToNormalSpeed() {
    speed = normalSpeed;
}

void Character::setSpeedToSneakSpeed() {
    speed = sneakSpeed;
}

void Character::changeWalkingMode() {

    if (is_sneakSPeed) {
        setSpeedToNormalSpeed();
    } else {
        setSpeedToSneakSpeed();
    }
}

void Character::SetIs_travelling(bool is_travelling) {
    this->is_travelling = is_travelling;
}

bool Character::IsIs_travelling() const {
    return is_travelling;
}

Character::~Character() {
    delete (segment);
    delete (shape);
}

void Character::SetSpeed(float speed) {
    this->speed = speed;
}

float Character::GetSpeed() const {
    return speed;
}

void Character::SetNormalSpeed(float normalSpeed) {
    this->normalSpeed = normalSpeed;
}

float Character::GetNormalSpeed() const {
    return normalSpeed;
}

void Character::SetSneakSpeed(float sneakSpeed) {
    this->sneakSpeed = sneakSpeed;
}

float Character::GetSneakSpeed() const {
    return sneakSpeed;
}

void Character::SetPosition(sf::Vector2f position) {
    this->position = position;

    shape->setPosition(position - sf::Vector2f(shape->getGlobalBounds().width, shape->getGlobalBounds().height)*0.5f);
}

sf::Vector2f Character::GetPosition() const {
    return position;
}

void Character::SetRotation(sf::Vector2f rotation) {
    this->rotation = rotation;
}

sf::Vector2f Character::GetRotation() const {
    return rotation;
}

void Character::SetIs_sneakSPeed(bool is_sneakSPeed) {
    this->is_sneakSPeed = is_sneakSPeed;
}

bool Character::IsIs_sneakSPeed() const {
    return is_sneakSPeed;
}

void Character::lookAt(sf::Vector2f target) {
    sf::Vector2f dif = target - position;
    float distance = std::sqrt(dif.x * dif.x + dif.y * dif.y);
    rotation = dif / distance;
}

void Character::move() {
    sf::Vector2f dif = targetPosition - position;
    float dist = (dif.x * dif.x + dif.y * dif.y);
    if (dist > 25) {
        lookAt(targetPosition);
        SetPosition(position + (rotation * Game::Instance()->GetDeltaTime()) * speed);
    } else {
        if (camino.size() > 1) {
            //clearPath(camino.front());
            camino.pop_front();
            
            targetPosition = (sf::Vector2f)(camino.front()*16) + sf::Vector2f(8, 8);
            showPath(camino.front());
        }
        else{
            camino.pop_front();
        }
    }
}

void Character::showPath(sf::Vector2i tile) {
    if (camino.size() > 0) {
        std::vector<std::vector < MapTile*> > shapeMatrix = Game::Instance()->getMap()->getTileShape();

        for (std::list<sf::Vector2i>::iterator i = camino.begin(); i != camino.end(); i++) {
            shapeMatrix.at((*i).x).at((*i).y)->setOutlineColor(sf::Color::Black);
        }
        shapeMatrix.at(tile.x).at(tile.y)->setOutlineColor(sf::Color::White);
    }
}

void Character::clearPath(sf::Vector2i tile) {
    std::vector<std::vector < MapTile*> > shapeMatrix = Game::Instance()->getMap()->getTileShape();
    shapeMatrix.at(tile.x).at(tile.y)->setOutlineColor(sf::Color::Black);
}

void Character::showSensorsRangeAndView() {
    Game::Instance()->getMap()->resetDebugTileMap();
}

bool Character::targetIsOnDistance(sf::Vector2f target, float radius) {
    sf::Vector2f dif = target - position;
    float distance = std::sqrt(dif.x * dif.x + dif.y * dif.y);
    if (distance <= radius) {
        return true;
    } else {
        return false;
    }
}

bool Character::targetIsOnSight(sf::Vector2f target) {

    if (bresenham(position.x, position.y, target.x, target.y)) {
        return true;
    } else {
        return false;
    }
}

bool Character::bresenham(int x1, int y1, int x2, int y2) {

    //Algoritmo de bresenham. (Raycast)
    //Se le pasa por parametro los puntos inicial y final
    //Traza una línea desde el primer punto hasta el final. 
    //Devuelve TRUE si consigue dibujarla "directamente", 
    //y FALSE si encuentra un obstáculo en el camino (colisión)

    int x0 = x1;
    int y0 = y1;

    int delta_x(x2 - x1);
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    if (delta_x >= delta_y) {
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2) {
            if (isCollisionPoint(x1, y1)) {
                segment->setVertices(position, sf::Vector2f(x1, y1));
                return false;
            }

            if ((error >= 0) && (error || (ix > 0))) {
                error -= delta_x;
                y1 += iy;
            }
            error += delta_y;
            x1 += ix;
        }
    } else {
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2) {
            if (isCollisionPoint(x1, y1)) {
                segment->setVertices(position, sf::Vector2f(x1, y1));
                return false;
            }

            if ((error >= 0) && (error || (iy > 0))) {
                error -= delta_y;
                x1 += ix;
            }
            error += delta_x;
            y1 += iy;
        }
    }
    segment->setVertices(sf::Vector2f(x0, y0), sf::Vector2f(x1, y1));
    return true;
}

bool Character::isCollisionPoint(int x, int y) {

    if (Game::Instance()->getMap()->getMatrix()[y / 16][x / 16] == 0) {
        return true;
    } else {
        return false;
    }
}

bool Character::checkAudio(Character* c) {
    sf::Vector2f target = c->position;
    if ((targetIsOnDistance(target, audiodistance)) && !c->IsIs_sneakSPeed()) {
        targetIsMakingNoise = true;
        sf::Vector2i targetPosition = calculateTargetPositionInMatrix(target);
        changeAudioMatrixWeight(targetPosition);
        audioSensorZone->setColor(sf::Color::Red);
        return true;
    }
    return false;
}

bool Character::checkVision(Character* c) {
    sf::Vector2f target = c->position;
    if (targetIsOnDistance(target, visionDistance)) {
        if (GetVisionSensorZone()->isOnSight(target, this->position)) {
            if (targetIsOnSight(target)) {
                somethingIsOnSight = true;
                visionSensorZone->setColor(sf::Color::Red);
                return true;
            }
        }
    }
    return false;
}

void Character::generateSensorsMatrix() {

    //reserva de memoria para la matriz de char
    sensorAudioMatrix = new float*[h];
    sensorVisionMatrix = new float*[h];
    generateMatrix(sensorAudioMatrix);
    generateMatrix(sensorVisionMatrix);
}

void Character::generateMatrix(float** matrix) {
    for (int i = 0; i < h; i++) {
        matrix[i] = new float[w];
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            matrix[i][j] = 0;
        }
    }
}

sf::Vector2i Character::calculateTargetPositionInMatrix(sf::Vector2f position) {
    sf::Vector2i pos = sf::Vector2i(position.x / 16, position.y / 16);
    return pos;
}

void Character::changeAudioMatrixWeight(sf::Vector2i SoundOriginPosition) {
    int x = SoundOriginPosition.x;
    int y = SoundOriginPosition.y;

    for (int i = y - 5; i <= y + 5; i++) {
        for (int j = x - 5; j <= x + 5; j++) {
            if ((i >= 0 && i < Game::Instance()->getMap()->getHeight()) && (j >= 0 && j < Game::Instance()->getMap()->getWidth())) {
                
                    checkAndModifyMatrixTile(i, j, weightValue);
            }
        }
    }

    /*checkAndModifyMatrixTile(x, y, weightValue);
    checkAndModifyMatrixTile(x, y + 1, weightValue);
    checkAndModifyMatrixTile(x, y - 1, weightValue);

    checkAndModifyMatrixTile(x + 1, y, weightValue);
    checkAndModifyMatrixTile(x - 1, y, weightValue);

    checkAndModifyMatrixTile(x + 1, y + 1, weightValue);
    checkAndModifyMatrixTile(x - 1, y + 1, weightValue);
    checkAndModifyMatrixTile(x - 1, y - 1, weightValue);
    checkAndModifyMatrixTile(x + 1, y - 1, weightValue);*/
}

void Character::changeVisionMatrixWeight(sf::Vector2i TargetOriginPosition) {
    int x = TargetOriginPosition.x;
    int y = TargetOriginPosition.y;

    for (int i = y - 5; i <= y + 5; i++) {
        for (int j = x - 5; j <= x + 5; j++) {
            if ((i >= 0 && i < Game::Instance()->getMap()->getHeight()) && (j >= 0 && j < Game::Instance()->getMap()->getWidth())) {
                
                    checkAndModifyMatrixTile(i, j, weightValue);
            }
        }
    }

    /*checkAndModifyMatrixTile(x, y, weightValue);
    checkAndModifyMatrixTile(x, y + 1, weightValue);
    checkAndModifyMatrixTile(x, y - 1, weightValue);

    checkAndModifyMatrixTile(x + 1, y, weightValue);
    checkAndModifyMatrixTile(x - 1, y, weightValue);

    checkAndModifyMatrixTile(x + 1, y + 1, weightValue);
    checkAndModifyMatrixTile(x - 1, y + 1, weightValue);
    checkAndModifyMatrixTile(x - 1, y - 1, weightValue);
    checkAndModifyMatrixTile(x + 1, y - 1, weightValue);*/

    std::list<sf::Vector2i> VisionTiles = GetVisionSensorZone()->calculateVisionZoneMatrix(w, h, calculateTargetPositionInMatrix(position));

    for (std::list<sf::Vector2i>::iterator i = VisionTiles.begin(); i != VisionTiles.end(); i++) {
        checkAndModifyMatrixTile((*i).x, (*i).y, weightValue + 250);
    }
}

void Character::checkAndModifyMatrixTile(int xPos, int yPos, int value) {
    sensorAudioMatrix[xPos][yPos] = value;
}

void Character::SetShowMatrixValues(bool showMatrixValues) {
    this->showMatrixValues = showMatrixValues;
}

bool Character::IsShowMatrixValues() const {
    return showMatrixValues;
}
