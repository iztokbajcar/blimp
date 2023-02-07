#ifndef _blimp_LIGHTS_DATA
#define _blimp_LIGHTS_DATA

#include <vector>
#include "directionallight.hpp"
#include "pointlight.hpp"
#include "spotlight.hpp"

typedef std::vector<blimp::DirectionalLight*> DLights;
typedef std::vector<blimp::PointLight*> PLights;
typedef std::vector<blimp::SpotLight*> SLights;

namespace blimp {
    
    class LightsData {
        public: 
            LightsData(DLights directionalLights, PLights pointLights, SLights spotLights);
            int countDirectionalLights();
            int countPointLights();
            int countSpotLights();
            DLights* getDirectionalLights();
            PLights* getPointLights();
            SLights* getSpotLights();
        private:
            DLights directionalLights;
            PLights pointLights;
            SLights spotLights;
    };

}

#endif