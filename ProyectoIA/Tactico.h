/* 
 * File:   Tactico.h
 * Author: Ricky
 *
 * Created on 21 de junio de 2016, 18:47
 */

#ifndef TACTICO_H
#define	TACTICO_H

#include "SFML/Graphics.hpp"
#include <list>


struct infoTactica
{
    infoTactica(float** m, float p):mat(m),peso(p){};
    float** mat;
    float peso;
};


class Tactico {
public:
    Tactico();
    Tactico(std::list<infoTactica> info, int w, int h);
    std::list<sf::Vector2i> calculatePath(sf::Vector2i start, sf::Vector2i end);
    virtual ~Tactico();
    float** matrix;
   
private:
    struct NodoT{
        sf::Vector2i position;
        float movementCost;
        uint32_t heuristic;
        float totalCost;
        NodoT* father;
        
        bool operator==(const NodoT& n) const
        {
            return (this->position == n.position);
        }
    };
    
    uint32_t calculaCoste(NodoT* actual, NodoT* f);
    Tactico::NodoT* enLista(std::list<NodoT*> &lista,NodoT* n);
    void pathFromList(std::list<NodoT*> &lista, std::list<sf::Vector2i>& p);
    
    std::list<infoTactica> tacticas;
    
    void calculatePrivateMatrix();
    
    int width,height;
};

#endif	/* TACTICO_H */

