/* 
 * File:   Character.h
 * Author: Guillermo
 *
 * Created on 9 de junio de 2016, 11:29
 */

#ifndef CHARACTER_H
#define	CHARACTER_H
#include <SFML/Graphics.hpp>
#include "Renderable.h"
#include "Sensors.h"
#include "TextValue.h"
#include <list>

class Segment;
class TextValue;
class MapTile;

class Character : public Renderable, public Sensors {
public:
    Character();
    virtual ~Character();
    void SetSpeed(float speed);
    float GetSpeed() const;
    void SetNormalSpeed(float normalSpeed);
    float GetNormalSpeed() const;
    void SetSneakSpeed(float sneakSpeed);
    float GetSneakSpeed() const;
    void SetPosition(sf::Vector2f positon);
    sf::Vector2f GetPosition() const;
    void SetRotation(sf::Vector2f rotation);
    sf::Vector2f GetRotation() const;
    void SetIs_sneakSPeed(bool is_sneakSPeed);
    bool IsIs_sneakSPeed() const;
    void setSpeedToSneakSpeed();
    void setSpeedToNormalSpeed();
    
    void changeWalkingMode();

    void lookAt(sf::Vector2f target);

    virtual void Update() = 0;
    void SetIs_travelling(bool is_travelling);
    bool IsIs_travelling() const;

    void move();

    void showPath(sf::Vector2i tile);
    void clearPath(sf::Vector2i tile);
    void showSensorsRangeAndView();

    bool targetIsOnDistance(sf::Vector2f target, float radius);
    bool targetIsOnSight(sf::Vector2f target);

    bool bresenham(int x0, int y0, int x1, int y1);
    bool isCollisionPoint(int x, int y);

    bool checkVision(Character*);
    bool checkAudio(Character*);

    sf::Vector2i calculateTargetPositionInMatrix(sf::Vector2f position);

    void MatrixUpdate();
    void SetUseTactic(bool useTactic);
    bool IsUseTactic() const;
    void SetVisionColor(sf::Color visionColor);
    sf::Color GetVisionColor() const;
    void SetAudioColor(sf::Color audioColor);
    sf::Color GetAudioColor() const;
    void SetName(std::string name);
    std::string GetName() const;

    sf::Vector2f position;
    float speed;
    float normalSpeed;
    float sneakSpeed;
    sf::Vector2f rotation;
    bool is_sneakSPeed;
    bool is_travelling;
    
    bool somethingIsOnSight;
    bool targetIsMakingNoise;
    
    bool showMatrixValues;
    
    std::string name;

    sf::Vector2f targetPosition;
    
    sf::Vector2i endOfPath;
    
    std::list<sf::Vector2i> camino;

    sf::Shape* shape;

    Segment* segment;

    float** sensorAudioMatrix;
    float** sensorVisionMatrix;

    void SetShowMatrixValues(bool showMatrixValues);
    bool IsShowMatrixValues() const;

protected:
    
    bool useTactic;
    
private:
    void generateSensorsMatrix();
    void generateMatrix(float** matrix);
    void UpdateMatrix(float** matrix);
    void changeAudioMatrixWeight(sf::Vector2i SoundOriginPosition);
    void changeVisionMatrixWeight(sf::Vector2i TargetOriginPosition);
    void checkAndModifyMatrixTile(int xPos, int yPos, int value);
    void ShowValues(int x, int y, float value);

    int h;
    int w;
    int weightValue;
    sf::Color visionColor = sf::Color::Yellow;
    sf::Color audioColor = sf::Color::Magenta;
    std::vector<std::vector<MapTile*> > tileWeight;
};

#endif	/* CHARACTER_H */