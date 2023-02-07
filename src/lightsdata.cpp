#include "lightsdata.hpp"

blimp::LightsData::LightsData(DLights directionalLights, PLights pointLights, SLights spotLights) {
    this -> directionalLights = directionalLights;
    this -> pointLights = pointLights;
    this -> spotLights = spotLights;
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

DLights* blimp::LightsData::getDirectionalLights() {
    return &this -> directionalLights;
}

PLights* blimp::LightsData::getPointLights() {
    return &this -> pointLights;
}

SLights* blimp::LightsData::getSpotLights() {
    return &this -> spotLights;
}