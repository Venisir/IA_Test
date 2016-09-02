/* 
 * File:   Game.cpp
 * Author: Albert
 * 
 * Created on 7 de junio de 2016, 12:44
 */

#include <list>

#include "Game.h"
#include "Renderable.h"
#include "RenderableDebug.h"
#include "UI.h"
#include "Map.h"
#include "DebugTest.h"
#include "Character.h"
#include "Player.h"
#include "IACharacter.h"
#include "DrawableLineShape.h"
#include "Segment.h"
#include "Path.h"
#include "AudioZone.h"
#include "VisionZone.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <AntTweakBar.h>
#include <iostream>

Game* Game::pInstance = 0;

Game::Game() : deltaTime(0), is_DebugMode(false) {
    renderWindow = new sf::RenderWindow(sf::VideoMode(1024, 768), "Prototipo IA", sf::Style::Close);
    renderWindow->setVerticalSyncEnabled(true);
    font = new sf::Font();
    
    if (!font->loadFromFile("arial.ttf"))
    {
        std::cout<<"Problema al cargar la fuente de letra.\n";
    }
}

Game* Game::Instance() {
    if (!pInstance) {
        pInstance = new Game();
    }
    return pInstance;
}

Game::~Game() {
    delete(m);
    delete(renderWindow);
    delete(GUI);
    delete(p);
    delete(ia1);
    delete(ia2);
    delete(font);
    for (std::list<Renderable*>::iterator i = renderableObjects.begin(); i != renderableObjects.end(); i++) {
        Renderable* aux_delete = (*i);
        delete(aux_delete);
    }
    renderableObjects.clear();
    
    for (std::list<RenderableDebug*>::iterator i = renderableDebugObjects.begin(); i != renderableDebugObjects.end(); i++) {
        RenderableDebug* aux_delete = (*i);
        delete(aux_delete);
    }
    renderableDebugObjects.clear();
    
    for (std::list<Character*>::iterator i = characterObjects.begin(); i != characterObjects.end(); i++) {
        Character* aux_delete = (*i);
        delete(aux_delete);
    }
    characterObjects.clear();
    
}

void Game::Init() {
    //TODO ARREGLAR
    m = new Map("mapa.tmx", "mapa.png");
    p = new Player();
    ia1 = new IACharacter();
    ia2 = new IACharacter();
    ia2->SetPosition(sf::Vector2f(440, 248));
    ia1->SetPosition(sf::Vector2f(120,120));
    ia1->SetOrigin(ia1->GetPosition());
    ia1->SetDestiny(sf::Vector2f(264, 248));
    ia2->SetOrigin(ia2->GetPosition());
    ia2->SetDestiny(sf::Vector2f(440, 648));
    p->SetName(("Player"));
    ia1->SetName("IA1");
    ia2->SetName("IA2");
    
    p->setIA1(ia1);
    p->setIA2(ia2);
    ia1->setPlayer(p);
    ia2->setPlayer(p);
    GUI = GUI->Instance();
}

void Game::Run() {
    Init();
    GUI->Init();
    
    while (renderWindow->isOpen()) {
        
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        EventManager();
        
        Update();
        Render();
    }
}

float Game::GetDeltaTime() const {
    return deltaTime;
}

void Game::DebugDraw() {
    
    
    for (std::list<RenderableDebug*>::iterator i = renderableDebugObjects.begin();
            i != renderableDebugObjects.end();
            i++) {
        (*i)->Render();
    }
}

void Game::Draw() {
    for (std::list<Renderable*>::iterator i = renderableObjects.begin();
            i != renderableObjects.end();
            i++) {
        (*i)->Render();
    }
}

void Game::Render() {
    renderWindow->clear();
    Draw();
    if (is_DebugMode) {
        DebugDraw();
    }
    GUI->Draw();
    renderWindow->display();
}

void Game::EventManager() {
    sf::Event event;
    
    mouseKeys[0] = false;
    mouseKeys[1] = false;
    
    while (renderWindow->pollEvent(event)) {
        
        mousePosition = sf::Mouse::getPosition(*renderWindow);
        //Comprobamos si es un evento de la GUI.
        int handled = GUI->EventManager(event);
        
        if (!handled) {
            //Si no lo es, es un evento del juego
            
            if (event.type == sf::Event::Closed) {
                renderWindow->close();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    renderWindow->close();
                }
                if (event.key.code == sf::Keyboard::B) {
                    is_DebugMode = !is_DebugMode;
                }
                if (event.key.code == sf::Keyboard::T) {
                    p->SetUseTactic(true);
                }
                if (event.key.code == sf::Keyboard::S) {
                    p->SetShowMatrixValues(true);
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                mouseKeys[0] = (event.mouseButton.button == sf::Mouse::Left);
                mouseKeys[1] = (event.mouseButton.button == sf::Mouse::Right);
            }
            
        } else {
            break;
        }
    }
}

sf::Vector2i Game::getMousePos() {
    return mousePosition;
}

void Game::setUseTacticButton(){
    p->SetUseTactic(!p->IsUseTactic());
}

void Game::setUseMatrixButton(){
    p->SetShowMatrixValues(!p->IsShowMatrixValues());
}

bool Game::getMouseKey(unsigned int k) {
    if (k < 2)
        return mouseKeys[k];
    return 0;
}

void Game::Update() {
    for (std::list<Character*>::iterator i = characterObjects.begin();
            i != characterObjects.end();
            i++) {
        (*i)->GetAudioSensorZone()->setSize((*i)->GetAudiodistance());
        (*i)->GetVisionSensorZone()->setLength((*i)->GetVisionDistance());
        (*i)->GetVisionSensorZone()->setAngle((*i)->GetVisionAngle());
        if ((*i)->targetIsMakingNoise == false) {
            (*i)->GetAudioSensorZone()->setColor((*i)->GetAudioColor());
        }else {
            (*i)->targetIsMakingNoise = false;
        }
        if ((*i)->somethingIsOnSight == false) {
            (*i)->GetVisionSensorZone()->setColor((*i)->GetVisionColor());
        }else {
            (*i)->somethingIsOnSight = false;
        }
        (*i)->Update();
    }
    GUI->Update();
}

sf::RenderWindow* Game::getWindow() {
    return renderWindow;
}

Map* Game::getMap() {
    return m;
}

void Game::SetFont(sf::Font* font) {
    this->font = font;
}

sf::Font* Game::GetFont() const {
    return font;
}

void Game::setMouseKey(int i, bool b) {
    mouseKeys[i] = b;
}