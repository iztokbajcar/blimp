#ifndef _blimp_COLOR
#define _blimp_COLOR

/** @file color.hpp */

namespace blimp {

    //! Represents a RGBA color.
    class Color {
        public:
            /** The default constructor.
             * Creates a fully opaque black color
            */
            Color();

            /** Creates a color with the given RGB values.
             * Alpha will be set to `1.0`, making the color fully opaque.
             * @param r The red component
             * @param g The green component
             * @param b The blue component
            */ 
            Color(float r, float g, float b);

            /** Creates a color with the given RGBA values.
             * @param r The red component
             * @param g The green component
             * @param b The blue component
             * @param a The alpha component
            */
            Color(float r, float g, float b, float a);

            /** Create a color from an RGB float array.
             * Alpha will be set to `1.0`, making the color fully opaque.
             * @param rgb Array of R, G and B values, respectively
            */
            Color(const float rgb[3]);

            /** Returns the color's red component. 
             * @return The red component
            */
            float getR();

            /** Returns the color's green component. 
             * @return The green component
            */
            float getG();

            /** Returns the color's blue component. 
             * @return The blue component
            */
            float getB();

            /** Returns the color's alpha component. 
             * @return The alpha component
            */
            float getA();

            // CSS3 basic colors
            static const float BLACK[3];  /**< The `black` color (`0.0`, `0.0`, `0.0`). */
            static const float SILVER[3];  /**< The `silver` color (`0.75`, `0.75`, `0.75`). */
            static const float GRAY[3];  /**< The `gray` color (`0.5`, `0.5`, `0.5`). */
            static const float WHITE[3];  /**< The `white` color (`1.0`, `1.0`, `1.0`). */
            static const float MAROON[3];  /**< The `maroon` color (`0.5`, `0.0`, `0.0`). */  
            static const float RED[3];  /**< The `red` color (`1.0`, `0.0`, `0.0`). */
            static const float PURPLE[3];  /**< The `purple` color (`0.5`, `0.0`, `0.5`). */  
            static const float FUCHSIA[3];  /**< The `fuchsia` color (`1.0`, `0.0`, `1.0`). */ 
            static const float GREEN[3];  /**< The `green` color (`0.0`, `0.5`, `0.0`). */   
            static const float LIME[3];  /**< The `lime` color (`0.0`, `1.0`, `0.0`). */    
            static const float OLIVE[3];  /**< The `olive` color (`0.5`, `0.5`, `0.0`). */   
            static const float YELLOW[3];  /**< The `yellow` color (`1.0`, `1.0`, `0.0`). */  
            static const float NAVY[3];  /**< The `navy` color (`0.0`, `0.0`, `0.5`). */    
            static const float BLUE[3];  /**< The `blue` color (`0.0`, `0.0`, `1.0`). */    
            static const float TEAL[3];  /**< The `teal` color (`0.0`, `0.5`, `0.5`). */    
            static const float AQUA[3];  /**< The `aqua` color (`0.0`, `1.0`, `1.0`). */    

        private:
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            float alpha = 1.0f;
    };

}

#endif