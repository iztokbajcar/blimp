#ifndef _blimp_COLOR
#define _blimp_COLOR

namespace blimp {

    class Color {
        public:
            Color(float r, float g, float b);
            Color(float r, float g, float b, float a);
            Color(const float rgb[3]);
            static Color fromRGB(float r, float g, float b);
            float getR();
            float getG();
            float getB();
            float getA();

            // CSS3 basic colors
            static const float BLACK[3];   
            static const float SILVER[3];  
            static const float GRAY[3];    
            static const float WHITE[3];   
            static const float MAROON[3];  
            static const float RED[3];     
            static const float PURPLE[3];  
            static const float FUCHSIA[3]; 
            static const float GREEN[3];   
            static const float LIME[3];    
            static const float OLIVE[3];   
            static const float YELLOW[3];  
            static const float NAVY[3];    
            static const float BLUE[3];    
            static const float TEAL[3];    
            static const float AQUA[3];    

        private:
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            float alpha = 1.0f;
    };

}

#endif