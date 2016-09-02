/* 
 * File:   Player.h
 * Author: Guillermo
 *
 * Created on 9 de junio de 2016, 11:24
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "AStar.h"
#include "Tactico.h"
#include "IACharacter.h"

class IACharacter;

class Player : public Character {

public:
    Player();
    virtual ~Player();

    void Update();

    void showMatrix();
    void generateSensorMatrix();
    void setIA1(IACharacter* ia);
    void setIA2(IACharacter* ia);

protected:

private:
    IACharacter* ia1;
    IACharacter* ia2;
	
    Tactico* pathFindingT;
    AStar* pathFindingA;
    char** sensorMatrix;
};

#endif	/* PLAYER_H */

