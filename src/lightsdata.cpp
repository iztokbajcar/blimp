#include "lightsdata.hpp"

blimp::LightsData::LightsData(ALights ambientLights, DLights directionalLights, PLights pointLights, SLights spotLights) {
    this -> ambientLights = ambientLights;
    this -> directionalLights = directionalLights;
    this -> pointLights = pointLights;
    this -> spotLights = spotLights;
}

int blimp::LightsData::countAmbientLights() {
    return this -> ambientLights.size();
}

int blimp::LightsData::countDirectionalLights() {
    return this -> directionalLights.size();
}

int blimp::LightsData::countPointLights() {
    return this -> pointLights.size();
}

int blimp::LightsData::countSpotLights() {
    return this -> spotLights.size();
}

ALights* blimp::LightsData::getAmbientLights() {
    return &this -> ambientLights;
}

DLights* blimp::LightsData::getDirectionalLights() {
    return &this -> directionalLights;
}

PLights* blimp::LightsData::getPointLights() {
    return &this -> pointLights;
}

SLights* blimp::LightsData::getSpotLights() {
    return &this -> spotLights;
}