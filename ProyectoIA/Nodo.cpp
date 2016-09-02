/* 
 * File:   Nodo.cpp
 * Author: Ricky
 * 
 * Created on 12 de noviembre de 2015, 10:48
 */

#include <stddef.h>
#include <stdlib.h>

#include "Nodo.h"

Nodo::Nodo() {
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::Nodo(Nodo* p, Nodo* end, int posx, int posy, int costg)
{
    padre=p;
    final=end;
    x=posx;
    y=posy;
    g=costg;
    if(final!=NULL)
    {
        f=g+calculaCoste()/*funcion de calcular coste (MANHATAN)*/;//
    }
    estado=-1; //no esta en ninguna lista
}

int Nodo::calculaCoste()
{
    return abs(x-final->getX())+abs(y-final->getY());
}

int Nodo::getX()
{
   return x; 
}

int Nodo::getY()
{
    return y;
}

int Nodo::getEstado()
{
    return estado;
}

void Nodo::setEstado(int i)
{
    estado=i;
}
int Nodo::getF()
{
    return f;
}
bool Nodo::operator ==(const Nodo& n)const 
{
   return ((this->x==n.x) && (this->y==n.y));    
}

int Nodo::getG()
{
    return g;
}

Nodo::~Nodo() 
{
    delete padre;
    delete final;
}

