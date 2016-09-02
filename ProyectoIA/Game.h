/* 
 * File:   Game.h
 * Author: Albert
 *
 * Created on 7 de junio de 2016, 12:44
 */

#ifndef GAME_H
#define	GAME_H

#include <SFML/Graphics.hpp>
#include <list>
#include "DrawableLineShape.h"
#include "IACharacter.h"

class Renderable;
class RenderableDebug;
class UI;
class Character;
class Map;
class Player;
class IACharacter;

class Game {
public:
    friend class Renderable;
    friend class RenderableDebug;
    friend class UI;
    friend class Character;
    friend class Player;

    static Game* Instance();
    void Run();

    float GetDeltaTime() const;
    
    sf::Vector2i getMousePos();
    bool getMouseKey(unsigned int);
    void setMouseKey(int i,bool b);
    Map* getMap();
    void SetFont(sf::Font* font);
    sf::Font* GetFont() const;
    
    void setUseTacticButton();
    void setUseMatrixButton();
    
private:
    
    static Game* pInstance;
    
    Game();
    virtual ~Game();
    
    sf::RenderWindow* getWindow();
    
    void Render();
    
    void Draw();
    void DebugDraw();
    
    void EventManager();
    
    void Init();
    
    void Update();
    
    sf::RenderWindow* renderWindow;
    
    UI* GUI;
    
    std::list<Renderable*> renderableObjects;
    std::list<RenderableDebug*> renderableDebugObjects;
    
    std::list<Character*> characterObjects;
    
    sf::Clock clock;
    float deltaTime;
    
    sf::Vector2i mousePosition;
    
    bool mouseKeys[2];
    bool is_DebugMode;
    Map *m;
    Player *p;
    IACharacter* ia1;
    IACharacter* ia2;
    sf::Font* font;
    
};

#endif	/* GAME_H */

