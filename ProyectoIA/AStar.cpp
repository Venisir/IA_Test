#include "AStar.h"
#include <cmath>
#include <iostream>
#include "Globales.h"


AStar::AStar(char **matrix){
    this->matrix=matrix;
}

AStar::~AStar() {
    
}

uint32_t AStar::calculaCoste(Nodo* actual,Nodo* f) {
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

AStar::Nodo* AStar::enLista(std::list<Nodo*> &lista, Nodo* n) {
    std::list<Nodo*>::iterator iter;
    
    for(iter=lista.begin();iter!=lista.end();iter++)
    {
        if((*(*iter))== (*n))
        {
            return (*iter);
        }
    }
    
    return 0;
}

void AStar::pathFromList(std::list<Nodo*> &lista, std::list<sf::Vector2i>& p) {
    std::list<Nodo*>::iterator iter;
    Nodo* aux=(lista.back());
    //std::cout << "entra4" << std::endl;
    p.push_front(aux->position);//guardo en la lista con push_front para que al final quede ordenada ya que recorremos la lista de nodos a la inversa
    
    for(iter=lista.end()--;iter!=lista.begin();iter--)//se recorre la lista a la inversa empezando por el penultimo
    {
        //std::cout << "entra5" << std::endl;
        if((*(aux->father)) == (*(*iter)))//si el nodo actual es padre del anterior
        {
            aux=(*iter);//guardo el actual para las futuras comparaciones
            p.push_front(aux->position);//guardo en la lista
        } 
        
    }
    p.push_front(lista.front()->position);
}



std::list<sf::Vector2i> AStar::calculatePath(sf::Vector2i start, sf::Vector2i end) {
    
    std::list<Nodo*> listaNodosAbierta;
    std::list<Nodo*> listaNodosCerrada;
    std::list<Nodo*> adyacentes;
    std::list<sf::Vector2i> path;//vector de posiciones del camino
    Nodo *inicio, *f, *actual, *adyacente;//nodos 
    std::list<Nodo*>::iterator iter,iterAux;
    uint32_t menorCoste,costeHV,costeD;
    Nodo* enAbierta;
    Nodo* enCerrada;//punteros a Nodo auxiliares para la modificacion de nodos en alguna de las dos listas
    //std::cout << "entra" << std::endl;
    if(start==end){
        path.push_back(end);
        return path;
    }
    /*creacion de los nodos iniciales*/
    inicio=new Nodo();
    f=new Nodo();
    inicio->position=start;
    f->position=end;
    
    /*asignacion de valores de los costes de cada nodo*/
    inicio->movementCost=0;
    inicio->heuristic=calculaCoste(inicio,f);
    inicio->totalCost=inicio->movementCost+inicio->heuristic;
    
    costeHV=10;//coste de moverse en horizontal/vertical
    costeD=14;//coste de moverse en diagonal
    /*1- Primeramente se pone el nodo de inicio en la lista abierta*/
    listaNodosAbierta.push_back(inicio);
    actual=inicio;
    /*2- Mientras la lista abierta no este vacia*/
    while(!listaNodosAbierta.empty()){
        
        for(iter=adyacentes.begin();iter!=adyacentes.end();iter=adyacentes.begin()){
            delete *iter;
            adyacentes.pop_front();
        }
        menorCoste=-1;//Al ser sin signo, ponerlo a -1 equivale al maximo valor
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
            if((matrix[actual->position.y][actual->position.x]&RIGHT)!=0)
            {   
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x+1;
                adyacente->position.y=actual->position.y;
                adyacente->movementCost=actual->movementCost+costeHV;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente izquierda*/
            if((matrix[actual->position.y][actual->position.x]&LEFT)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x-1;
                adyacente->position.y=actual->position.y;
                adyacente->movementCost=actual->movementCost+costeHV;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente arriba*/
            if((matrix[actual->position.y][actual->position.x]&UP)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x;
                adyacente->position.y=actual->position.y-1;
                adyacente->movementCost=actual->movementCost+costeHV;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente abajo*/
            if((matrix[actual->position.y][actual->position.x]&DOWN)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x;
                adyacente->position.y=actual->position.y+1;
                adyacente->movementCost=actual->movementCost+costeHV;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);
            }
            
            /*Adyacente Arriba-Derecha*/
            if((matrix[actual->position.y][actual->position.x]&UPRIGHT)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x+1;
                adyacente->position.y=actual->position.y-1;
                adyacente->movementCost=actual->movementCost+costeD;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                
            }
            
            /*Adyacente Arriba-Izquierda*/
            if((matrix[actual->position.y][actual->position.x]&UPLEFT)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x-1;
                adyacente->position.y=actual->position.y-1;
                adyacente->movementCost=actual->movementCost+costeD;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                                
            }
            
            /*Adyacente Abajo-Derecha*/
            if((matrix[actual->position.y][actual->position.x]&DOWNRIGHT)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x+1;
                adyacente->position.y=actual->position.y+1;
                adyacente->movementCost=actual->movementCost+costeD;
                adyacente->heuristic=calculaCoste(adyacente,f);
                adyacente->totalCost=adyacente->movementCost+adyacente->heuristic;
                adyacentes.push_back(adyacente);                                                
            }
            
            /*Adyacente Abajo-Izquierda*/
            if((matrix[actual->position.y][actual->position.x]&DOWNLEFT)!=0)
            {
                adyacente=new Nodo();
                adyacente->father=actual;
                adyacente->position.x=actual->position.x-1;
                adyacente->position.y=actual->position.y+1;
                adyacente->movementCost=actual->movementCost+costeD;
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
                    std::list<Nodo*>::iterator itemp=iter;
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
