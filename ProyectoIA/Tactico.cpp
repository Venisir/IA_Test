/* 
 * File:   Tactico.cpp
 * Author: Ricky
 * 
 * Created on 21 de junio de 2016, 18:47
 */

//#include <list>
#include <float.h>

#include <iostream>

#include "Tactico.h"

Tactico::Tactico(std::list<infoTactica> info, int w, int h): tacticas(info), width(w), height(h) {
    matrix = new float*[height];
    for(int i = 0;i<height;i++){
        matrix[i] = new float[width];
    }
}

void Tactico::calculatePrivateMatrix() {
    float suma=0;
    std::list<infoTactica>::iterator it;
    
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            suma=0;
            for(it=tacticas.begin();it!=tacticas.end();it++)
            {
                suma+=(*it).mat[i][j]*(*it).peso;
            }
            
            matrix[i][j]=suma;
        }
    } 
}


Tactico::~Tactico() {
}

uint32_t Tactico::calculaCoste(NodoT* actual,NodoT* f) {
    sf::Vector2i act=actual->position;
    sf::Vector2i fin=f->position;
    uint32_t dX=(act.x>fin.x)? //Compruebo cual es mayor
        (act.x-fin.x): //Si actual es mayor
        (fin.x-act.x); //Si final es mayor
    
    uint32_t dY=(act.y>fin.y)?
        (act.y-fin.y):
        (fin.y-act.y);
    
    return dX+dY;
    //return std::abs(actual->position.x-final->position.x)+ std::abs(actual->position.y-final->position.y);
}

Tactico::NodoT* Tactico::enLista(std::list<NodoT*>& lista, NodoT* n) {
    std::list<NodoT*>::iterator iter;
    
    for(iter=lista.begin();iter!=lista.end();iter++)
    {
        if((*(*iter))== (*n))
        {
            return (*iter);
        }
    }
    
    return 0;
}


std::list<sf::Vector2i> Tactico::calculatePath(sf::Vector2i start, sf::Vector2i end) {
    calculatePrivateMatrix();
    std::list<NodoT*> listaNodosAbierta;
    std::list<NodoT*> listaNodosCerrada;
    std::list<NodoT*> adyacentes;
    std::list<sf::Vector2i> path;//vector de posiciones del camino
    NodoT *inicio, *f, *actual, *adyacente;//nodos 
    std::list<NodoT*>::iterator iter,iterAux;
    float menorCoste,costeHV,costeD;
    NodoT* enAbierta;
    NodoT* enCerrada;//punteros a Nodo auxiliares para la modificacion de nodos en alguna de las dos listas
    //std::cout << "entra" << std::endl;
    /*creacion de los nodos iniciales*/
    inicio=new NodoT();
    f=new NodoT();
    inicio->position=start;
    f->position=end;
    
    /*asignacion de valores de los costes de cada nodo*/
    inicio->movementCost=0;
    inicio->heuristic=calculaCoste(inicio,f);
    inicio->totalCost=inicio->movementCost+inicio->heuristic;
    
    costeHV=1;//coste de moverse en horizontal/vertical
    costeD=1.4;//coste de moverse en diagonal
    /*1- Primeramente se pone el nodo de inicio en la lista abierta*/
    listaNodosAbierta.push_back(inicio);
    actual=inicio;
    /*2- Mientras la lista abierta no este vacia*/
    while(!listaNodosAbierta.empty()){
        
        for(iter=adyacentes.begin();iter!=adyacentes.end();iter=adyacentes.begin()){
            delete *iter;
            adyacentes.pop_front();
        }
        menorCoste=FLT_MAX;//Al ser sin signo, ponerlo a -1 equivale al maximo valor
        /*3- obtenemos el nodo con menor coste de la lista abierta*/ 
        for(iter=listaNodosAbierta.begin();iter!=listaNodosAbierta.end();iter++){
            if((*iter)->totalCost < menorCoste){
                iterAux=iter;//iterador auxiliar que nos ayudara a borrar el elemento correspondiente a la hora de moverlo a la lista cerrada
                menorCoste=actual->totalCost;//actualizo el costemenor
            }
        }
        
        actual=(*iterAux);//guardo el nodo
        listaNodosCerrada.push_back(actual);
        listaNodosAbierta.erase(iterAux);
        if((*actual)==(*f)){//si se ha llegado a la posicion/nodo final
            pathFromList(listaNodosCerrada,path);
            delete inicio;
            delete f;
            return path;
        }
        else{
            /*4- Como no se ha llegado al final de la lista, el nodo actual debe expanderse (sacar sus adyacentes)*/            
            
            /*en las siguientes comprobaciones el <9 y el >0 son para comprobar que no se salga de la matriz*/
            
            /*Adyacente Derecha*/
            if((actual->position.x+1)<width)
            {   
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x+1;
                adyacente->position.y=actual->position.y;
                adyacente->movementCost=actual->movementCost+costeHV+matrix[actual->position.y][actual->position.x+1];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente izquierda*/
            if((actual->position.x-1)>=0)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x-1;
                adyacente->position.y=actual->position.y;
                adyacente->movementCost=actual->movementCost+costeHV+matrix[actual->position.y][actual->position.x-1];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente arriba*/
            if((actual->position.y-1)>=0)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x;
                adyacente->position.y=actual->position.y-1;
                adyacente->movementCost=actual->movementCost+costeHV+matrix[actual->position.y-1][actual->position.x];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente abajo*/
            if((actual->position.y+1)<height)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x;
                adyacente->position.y=actual->position.y+1;
                adyacente->movementCost=actual->movementCost+costeHV+matrix[actual->position.y+1][actual->position.x];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente Arriba-Derecha*/
            if((actual->position.y-1)>=0 && (actual->position.x+1)<width)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x+1;
                adyacente->position.y=actual->position.y-1;
                adyacente->movementCost=actual->movementCost+costeD+matrix[actual->position.y-1][actual->position.x+1];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                
            }
            
            /*Adyacente Arriba-Izquierda*/
            if((actual->position.y-1)>=0 && (actual->position.x-1)>=0)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x-1;
                adyacente->position.y=actual->position.y-1;
                adyacente->movementCost=actual->movementCost+costeD+matrix[actual->position.y-1][actual->position.x-1];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                                
            }
            
            /*Adyacente Abajo-Derecha*/
            if((actual->position.y+1)<height && (actual->position.x+1)<width)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x+1;
                adyacente->position.y=actual->position.y+1;
                adyacente->movementCost=actual->movementCost+costeD+matrix[actual->position.y+1][actual->position.x+1];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                                                
            }
            
            /*Adyacente Abajo-Izquierda*/
            if((actual->position.y+1)<height && (actual->position.x-1)>=0)
            {
                adyacente=new NodoT();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x-1;
                adyacente->position.y=actual->position.y+1;
                adyacente->movementCost=actual->movementCost+costeD+matrix[actual->position.y+1][actual->position.x-1];
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                                                                
            }
            
            
            /*5- Comprobamos para cada adyacente si se encuentran en las respectivas listas (abierta o cerrada)*/
            for(iter=adyacentes.begin();iter!=adyacentes.end();iter++)
            {
                /*compruebo y guardo el resultado de la busqueda del nodo en cuestion en ambas listas*/
                enAbierta=enLista(listaNodosAbierta,(*iter));
                enCerrada=enLista(listaNodosCerrada,(*iter));
                
                
                
                if(enAbierta==0 && enCerrada==0)//si no esta en ninguna de las dos listas
                {
                    std::list<NodoT*>::iterator itemp=iter;
                    listaNodosAbierta.push_back((*iter));
                    iter--;
                    adyacentes.erase(itemp);
                    
                }
                else if(enAbierta!=0)//si el adyacente se encuentra en la lista abierta
                {
                    if((*iter)->totalCost < enAbierta->totalCost)//si el adyacente pertinete tiene mejor coste, se actualiza el Nodo correspondiente de la lista
                    {
                        enAbierta->father=(*iter)->father;
                        enAbierta->heuristic=(*iter)->heuristic;
                        enAbierta->movementCost=(*iter)->movementCost;
                        enAbierta->position=(*iter)->position;
                        enAbierta->totalCost=(*iter)->totalCost;
                    }
                }
                else if(enCerrada!=0)//si el adyacente se encuentra en la lista cerrada
                {
                    if((*iter)->totalCost < enCerrada->totalCost)//si el adyacente pertinete tiene mejor coste, se actualiza el Nodo correspondiente de la lista
                    {
                        enCerrada->father=(*iter)->father;
                        enCerrada->heuristic=(*iter)->heuristic;
                        enCerrada->movementCost=(*iter)->movementCost;
                        enCerrada->position=(*iter)->position;
                        enCerrada->totalCost=(*iter)->totalCost;
                    }
                }   
            }
        }
    }
}

void Tactico::pathFromList(std::list<NodoT*>& lista, std::list<sf::Vector2i>& p) {
    
    NodoT* aux=(lista.back());
    
    while(aux->father!=NULL){
        p.push_front(aux->position);
        aux=aux->father;
    }
}
