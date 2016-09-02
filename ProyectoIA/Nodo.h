/* 
 * File:   Nodo.h
 * Author: Ricky
 *
 * Created on 12 de noviembre de 2015, 10:48
 */



#ifndef NODO_H
#define	NODO_H

#include <math.h>

class Nodo {
public:
    Nodo();
    Nodo(Nodo* p,Nodo* f,int posx,int posy,int costg);
    Nodo(const Nodo& orig);
    int calculaCoste();
    int getX();
    int getY();
    int getEstado();
    int getF();
    int getG();
    void setEstado(int i);
    void setX(int xx);
    void setY(int yy);
    virtual ~Nodo();
    bool operator==(const Nodo& n) const;
    
      
private:
    Nodo* padre;
    Nodo* final;//detino final del A* , se pone aqui para calcular la heuristica intermanente
    int g;//coste g 
    int f;//coste total
    int estado; //1=abierto | 0=cerrado
    int x,y;//posicion del nodo
};

#endif	/* NODO_H */

