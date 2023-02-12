#ifndef _blimp_LIGHTS_DATA
#define _blimp_LIGHTS_DATA

#include <vector>
#include "ambientlight.hpp"
#include "directionallight.hpp"
#include "pointlight.hpp"
#include "spotlight.hpp"

/** @file lightsdata.hpp */

/** A vector of AmbientLight objects. */
typedef std::vector<blimp::AmbientLight*> ALights;

/** A vector of DirectionalLight objects. */
typedef std::vector<blimp::DirectionalLight*> DLights;

/** A vector of PointLight objects. */
typedef std::vector<blimp::PointLight*> PLights;

/** A vector of SpotLight objects. */
typedef std::vector<blimp::SpotLight*> SLights;

namespace blimp {
    
    //! A data structure, used to store all the lights in the scene.
    /**
     * It is used internally by Window to determine all the lights that should be used to illuminate the scene.
     */
    class LightsData {
        public:
            /** Creates a new LightsData object from the given light vectors. 
             * @param ambientLights A vector of AmbientLight objects
             * @param directionalLights A vector of DirectionalLight objects
             * @param pointLights A vector of PointLight objects
             * @param spotLights A vector of SpotLight objects
            */
            LightsData(ALights ambientLights, DLights directionalLights, PLights pointLights, SLights spotLights);

            /** Returns the number of ambient lights.
             * @return The number of AmbientLight objects contained
            */
            int countAmbientLights();
            
            /** Returns the number of directional lights.
             * @return The number of DirectionalLight objects contained
            */
            int countDirectionalLights();

            /** Returns the number of point lights.
             * @return The number of PointLight objects contained
            */
            int countPointLights();

            /** Returns the number of spot lights.
             * @return The number of SpotLight objects contained
            */
            int countSpotLights();

            /** Returns all ambient lights.
             * @return A pointer to the vector of AmbientLight objects
            */
            ALights* getAmbientLights();

            /** Returns all directional lights.
             * @return A pointer to the vector of DirectionalLight objects
            */
            DLights* getDirectionalLights();

            /** Returns all point lights.
             * @return A pointer to the vector of PointLight objects
            */
            PLights* getPointLights();

            /** Returns all spot lights.
             * @return A pointer to the vector of SpotLight objects
            */
            SLights* getSpotLights();
        private:
            ALights ambientLights;
            DLights directionalLights;
            PLights pointLights;
            SLights spotLights;
    };

}

#endif