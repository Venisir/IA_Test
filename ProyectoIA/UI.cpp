/* 
 * File:   UI.cpp
 * Author: Albert
 * 
 * Created on 7 de junio de 2016, 12:42
 */

#include <list>

#include "UI.h"
#include "Game.h"
#include "Character.h"
#include <iostream>

void TW_CALL buttonTactico(void *clientData){
    std::cout << "Táctico" << std::endl;
    Game::Instance()->setUseTacticButton();
}

void TW_CALL buttonMatrix(void *clientData){
    std::cout << "Activando matrices" << std::endl;
    Game::Instance()->setUseMatrixButton();
}

UI* UI::pInstance=0;

UI::UI() {
    
}

UI* UI::Instance() {
    if(!pInstance){
        pInstance = new UI();
    }
    return pInstance;
}

UI::~UI() {
    
}

void UI::Init() {
    
    boolTactico = false;
    boolTacticoAux = false;
    
    boolMatriz = false;
    boolMatrizAux = false;
    
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(1024, 768);
    
    int aux = 0;
    
    std::list<Character*>::const_iterator iterator;
    for (iterator = Game::Instance()->characterObjects.begin(); iterator != Game::Instance()->characterObjects.end(); ++iterator) {
        switch(aux){
            case 0:{
                // Tweak bar Player
                layoutPlayer = TwNewBar("Player");
                
                TwDefine(" Player refresh=0.25 alpha=200 ");
                
                int layoutPlayerpos[2] = {0, 400};
                TwSetParam(layoutPlayer, NULL, "position", TW_PARAM_INT32, 2, &layoutPlayerpos);
                
                TwAddVarRW(layoutPlayer, "Speed", TW_TYPE_FLOAT, &((*iterator)->speed), " min=0.0 max=400.0 step=0.1 ");
                
                TwAddVarRW(layoutPlayer, "NormalSpeed", TW_TYPE_FLOAT, &((*iterator)->normalSpeed), " min=0.0 max=1000 step=0.1 ");
                
                TwAddVarRW(layoutPlayer, "Position X", TW_TYPE_FLOAT, &((*iterator)->position.x), " min=0.0 max=1000.0 step=0.1 ");
                TwAddVarRW(layoutPlayer, "Position Y", TW_TYPE_FLOAT, &((*iterator)->position.y), " min=0.0 max=1000.0 step=0.1 ");
                
                TwAddVarRW(layoutPlayer, "Rotation X", TW_TYPE_FLOAT, &((*iterator)->rotation.x), " step=0.1 ");
                TwAddVarRW(layoutPlayer, "Rotation Y", TW_TYPE_FLOAT, &((*iterator)->rotation.y), " step=0.1 ");
                
                TwAddSeparator(layoutPlayer, NULL, NULL);
                
                TwAddVarRW(layoutPlayer, "Rango de Audio", TW_TYPE_FLOAT, (*iterator)->getAudioDistanceDir(), " step=0.1 ");
                TwAddVarRW(layoutPlayer, "Rango de Visión", TW_TYPE_FLOAT, (*iterator)->getVisionDistanceDir(), " step=0.1 ");
                TwAddVarRW(layoutPlayer, "Angulo de Visión", TW_TYPE_FLOAT, (*iterator)->getVisionAngleDir(), " step=0.1 ");
                
                TwAddSeparator(layoutPlayer, NULL, NULL);
                
                TwAddVarRW(layoutPlayer, "Debug mode", TW_TYPE_BOOLCPP, &(Game::Instance()->is_DebugMode), " ");
                TwAddVarRW(layoutPlayer, "Tactico", TW_TYPE_BOOLCPP, &(boolTactico), " ");
                TwAddVarRW(layoutPlayer, "Mostrar pesos", TW_TYPE_BOOLCPP, &(boolMatriz), " ");
                TwAddVarRW(layoutPlayer, "Modo sigilo", TW_TYPE_BOOLCPP, &((*iterator)->is_sneakSPeed), " ");
                
                TwAddSeparator(layoutPlayer, NULL, NULL);
                
                TwAddVarRW(layoutPlayer, "Escucha algo", TW_TYPE_BOOLCPP, &((*iterator)->targetIsMakingNoise), " ");
                TwAddVarRW(layoutPlayer, "Ve algo", TW_TYPE_BOOLCPP, &((*iterator)->somethingIsOnSight), " ");
                
                /*
                TwAddButton(layoutPlayer, "Tactico", buttonTactico, this, " ");
                TwAddButton(layoutPlayer, "Ver matriz", buttonMatrix, this, " ");
                */
                
                break;
            }
            case 1:{
                
                // Tweak bar IA
                layoutIA1 = TwNewBar("IA1");
                
                TwDefine(" IA1 refresh=0.25 alpha=200 ");
                
                int layoutIA1pos[2] = {825, 0};
                TwSetParam(layoutIA1, NULL, "position", TW_PARAM_INT32, 2, &layoutIA1pos);
                
                TwAddVarRW(layoutIA1, "Speed", TW_TYPE_FLOAT, &((*iterator)->speed), " min=0.0 max=400.0 step=0.1 ");
                
                TwAddVarRW(layoutIA1, "NormalSpeed", TW_TYPE_FLOAT, &((*iterator)->normalSpeed), " min=0.0 max=1000 step=0.1 ");
                
                TwAddVarRW(layoutIA1, "Position X", TW_TYPE_FLOAT, &((*iterator)->position.x), " min=0.0 max=1000.0 step=0.1 ");
                TwAddVarRW(layoutIA1, "Position Y", TW_TYPE_FLOAT, &((*iterator)->position.y), " min=0.0 max=1000.0 step=0.1 ");
                
                TwAddVarRW(layoutIA1, "Rotation X", TW_TYPE_FLOAT, &((*iterator)->rotation.x), " step=0.1 ");
                TwAddVarRW(layoutIA1, "Rotation Y", TW_TYPE_FLOAT, &((*iterator)->rotation.y), " step=0.1 ");
                
                TwAddSeparator(layoutIA1, NULL, NULL);
                
                TwAddVarRW(layoutIA1, "Escucha algo", TW_TYPE_BOOLCPP, &((*iterator)->targetIsMakingNoise), " ");
                TwAddVarRW(layoutIA1, "Ve algo", TW_TYPE_BOOLCPP, &((*iterator)->somethingIsOnSight), " ");
                break;
            }
            case 2:{
                // Tweak bar IA
                layoutIA2 = TwNewBar("IA2");
                
                TwDefine(" IA2 refresh=0.25 alpha=200 ");
                
                int layoutIA2pos[2] = {825, 400};
                TwSetParam(layoutIA2, NULL, "position", TW_PARAM_INT32, 2, &layoutIA2pos);
                
                TwAddVarRW(layoutIA2, "Speed", TW_TYPE_FLOAT, &((*iterator)->speed), " min=0.0 max=400.0 step=0.1 ");
                
                TwAddVarRW(layoutIA2, "NormalSpeed", TW_TYPE_FLOAT, &((*iterator)->normalSpeed), " min=0.0 max=1000 step=0.1 ");
                
                TwAddVarRW(layoutIA2, "Position X", TW_TYPE_FLOAT, &((*iterator)->position.x), " min=0.0 max=1000.0 step=0.1 ");
                TwAddVarRW(layoutIA2, "Position Y", TW_TYPE_FLOAT, &((*iterator)->position.y), " min=0.0 max=1000.0 step=0.1 ");
                
                TwAddVarRW(layoutIA2, "Rotation X", TW_TYPE_FLOAT, &((*iterator)->rotation.x), " step=0.1 ");
                TwAddVarRW(layoutIA2, "Rotation Y", TW_TYPE_FLOAT, &((*iterator)->rotation.y), " step=0.1 ");
                
                TwAddSeparator(layoutIA2, NULL, NULL);
                
                TwAddVarRW(layoutIA2, "Escucha algo", TW_TYPE_BOOLCPP, &((*iterator)->targetIsMakingNoise), " ");
                TwAddVarRW(layoutIA2, "Ve algo", TW_TYPE_BOOLCPP, &((*iterator)->somethingIsOnSight), " ");
                break;
            }
        }
        aux++;
    }
}

int UI::EventManager(sf::Event event) {
    //TODO
    return TwEventSFML(&event, 2, 1); // Assume SFML version 1.6 here
}

void UI::Update() {
    
//    std::cout << Game::Instance()->characterObjects.front()->GetName() << " " << Game::Instance()->characterObjects.front()->targetIsMakingNoise << std::endl;
    if(boolTactico != boolTacticoAux){
        boolTacticoAux = boolTactico;
        std::cout << "Táctico" << std::endl;
        Game::Instance()->setUseTacticButton();
    }
    
    if(boolMatriz != boolMatrizAux){
        boolMatrizAux = boolMatriz;
        std::cout << "Matriz" << std::endl;
        Game::Instance()->setUseMatrixButton();
    }
    /*
     TwRefreshBar(layoutIA1);
     TwRefreshBar(layoutIA2);
     TwRefreshBar(layoutPlayer);
     */
    
}

void UI::Draw() {
    TwDraw();
}

void UI::End(){
    
}