/* 
 * File:   AStar.h
 * Author: Albert
 *
 * Created on 19 de noviembre de 2015, 15:52
 */



#ifndef ASTAR_H
#define	ASTAR_H

#include <list>
#include <stdint.h>
#include <SFML/Graphics.hpp>

//#include "Nodo.h"

/*struct Vector2{
    int x,y;
    Vector2(int x = 0, int y = 0)//Constructor, si no se le pasa valores, se inicializa X e Y a 0
        : x(x), y(y) {
    }
    
    bool operator==(const Vector2& v)const
    {
        return ((this->x==v.x) && (this->y==v.y));
    }
    
    void setx(int nx){
        x=nx;
    }
    
    void sety(int ny)
    {
        y=ny;
    }
};*/

class AStar {
public:
    AStar(char** matrix);
    
    std::list<sf::Vector2i> calculatePath(sf::Vector2i start, sf::Vector2i end);
    
    virtual ~AStar();
private:
    
    struct Nodo{
        sf::Vector2i position;
        uint32_t movementCost;
        uint32_t heuristic;
        uint32_t totalCost;
        Nodo* father;
        
        bool operator==(const Nodo& n) const
        {
            return (this->position == n.position);
        }
    };
    
    uint32_t calculaCoste(Nodo* actual, Nodo* f);
    AStar::Nodo* enLista(std::list<Nodo*> &lista,Nodo* n);
    void pathFromList(std::list<Nodo*> &lista, std::list<sf::Vector2i>& p);
    char** matrix;
    int width, height;
    
    
};

#endif	/* ASTAR_H */

