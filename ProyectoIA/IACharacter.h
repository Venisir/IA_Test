/* 
 * File:   IACharacter.h
 * Author: Guillermo
 *
 * Created on 22 de junio de 2016, 10:24
 */

#ifndef IACHARACTER_H
#define	IACHARACTER_H

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "AStar.h"

class Player;

class IACharacter : public Character{
public:
    IACharacter();
    virtual ~IACharacter();

    void Update();
    
    void setPlayer(Player* p);
    void SetOrigin(sf::Vector2f origin);
    sf::Vector2f GetOrigin() const;
    void SetDestiny(sf::Vector2f destiny);
    sf::Vector2f GetDestiny() const;

private:
    AStar* pathFinding;
    Player* player;
    
    sf::Vector2f origin;
    sf::Vector2f destiny;
    sf::Vector2f target;
    
    bool patrol;
    bool is_going_destiny;
    
};

#endif	/* IACHARACTER_H */
