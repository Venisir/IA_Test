/* 
 * File:   Sensors.cpp
 * Author: Guillermo
 * 
 * Created on 9 de junio de 2016, 11:17
 */

#include "Sensors.h"
#include "VisionZone.h"
#include "AudioZone.h"
Sensors::Sensors() : audiodistance(100), visionAngle(30), visionDistance(200) {
    audioSensorZone = new AudioZone(audiodistance);
    audioSensorZone->setColor(sf::Color::White);
    visionSensorZone = new VisionZone(visionDistance, visionAngle);
    visionSensorZone->setColor(sf::Color::Yellow);
}

Sensors::~Sensors() {
    delete(audioSensorZone);
    delete(visionSensorZone);
}

void Sensors::SetAudiodistance(float audiodistance) {
    this->audiodistance = audiodistance;
}

float Sensors::GetAudiodistance() const {
    return audiodistance;
}

void Sensors::SetVisionDistance(float visionDistance) {
    this->visionDistance = visionDistance;
}

float Sensors::GetVisionDistance() const {
    return visionDistance;
}

void Sensors::SetVisionAngle(float visionAngle) {
    this->visionAngle = visionAngle;
}

float Sensors::GetVisionAngle() const {
    return visionAngle;
}

void Sensors::setSensorsOrigin(sf::Vector2f position, sf::Vector2f rotation) {
    audioSensorZone->setPosition(position);
    visionSensorZone->setPosition(position, rotation);
}

void Sensors::changeAudioZoneColor(sf::Color color) {
    audioSensorZone->setColor(color);
}

AudioZone* Sensors::GetAudioSensorZone() const {
    return audioSensorZone;
}

VisionZone* Sensors::GetVisionSensorZone() const {
    return visionSensorZone;
}

float* Sensors::getAudioDistanceDir() {
    return (&audiodistance);
}

float* Sensors::getVisionDistanceDir() {
    return (&visionDistance);
}

float* Sensors::getVisionAngleDir() {
    return (&visionAngle);
}
