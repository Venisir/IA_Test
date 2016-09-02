/* 
 * File:   Sensors.h
 * Author: Guillermo
 *
 * Created on 9 de junio de 2016, 11:17
 */

#ifndef SENSORS_H
#define	SENSORS_H
#include <SFML/Graphics.hpp>
class AudioZone;
class VisionZone;

class Sensors {
public:
    Sensors();
    virtual ~Sensors();
    void SetAudiodistance(float audiodistance);
    float GetAudiodistance() const;
    void SetVisionDistance(float visionDistance);
    float GetVisionDistance() const;
    void SetVisionAngle(float visionAngle);
    float GetVisionAngle() const;
    void setSensorsOrigin(sf::Vector2f position, sf::Vector2f rotation);
    void changeAudioZoneColor(sf::Color color);
    AudioZone* GetAudioSensorZone() const;
    VisionZone* GetVisionSensorZone() const;
    
    float* getAudioDistanceDir();
    float* getVisionDistanceDir();
    float* getVisionAngleDir();

protected:
    float audiodistance;
    float visionDistance;
    float visionAngle;
    AudioZone* audioSensorZone;
    VisionZone* visionSensorZone;    

};

#endif	/* SENSORS_H */

