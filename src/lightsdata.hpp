#ifndef _blimp_LIGHTS_DATA
#define _blimp_LIGHTS_DATA

#include <vector>
#include "ambientlight.hpp"
#include "directionallight.hpp"
#include "pointlight.hpp"
#include "spotlight.hpp"

typedef std::vector<blimp::AmbientLight*> ALights;
typedef std::vector<blimp::DirectionalLight*> DLights;
typedef std::vector<blimp::PointLight*> PLights;
typedef std::vector<blimp::SpotLight*> SLights;

namespace blimp {
    
    class LightsData {
        public: 
            LightsData(ALights ambientLights, DLights directionalLights, PLights pointLights, SLights spotLights);
            int countAmbientLights();
            int countDirectionalLights();
            int countPointLights();
            int countSpotLights();
            ALights* getAmbientLights();
            DLights* getDirectionalLights();
            PLights* getPointLights();
            SLights* getSpotLights();
        private:
            ALights ambientLights;
            DLights directionalLights;
            PLights pointLights;
            SLights spotLights;
    };

}

#endif