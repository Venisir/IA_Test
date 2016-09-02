/* 
 * File:   UI.h
 * Author: Albert
 *
 * Created on 7 de junio de 2016, 12:42
 */

#ifndef UI_H
#define	UI_H

#include <SFML/Graphics.hpp>
#include <AntTweakBar.h>

#include <list>

class UI {
public:
    friend class Game;
    static UI* Instance();
private:
    UI();
    static UI* pInstance;
    virtual ~UI();
    void Init();
    int EventManager(sf::Event event);
    void Update();
    void Draw();
    void End();
    
    TwBar *layoutIA1;
    TwBar *layoutIA2;
    TwBar *layoutPlayer;
    
    bool boolTactico;
    bool boolTacticoAux;
    
    bool boolMatriz;
    bool boolMatrizAux;
};

#endif	/* UI_H */

