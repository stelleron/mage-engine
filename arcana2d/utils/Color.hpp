#ifndef ARCANA2D_COLOR
    #define ARCANA2D_COLOR
    
    // Macros
    #define FLOAT_REP(color) (float)color/255
    #define COLOR_TO_FLOAT(color) FLOAT_REP(color.r), FLOAT_REP(color.g), FLOAT_REP(color.b), FLOAT_REP(color.a)

    namespace arcana {
        // Used to create a color object
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

            // Constructor options
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b);
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

            // Static constructors
            static Color RGB(unsigned char r, unsigned char g, unsigned char b);
            static Color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
            static Color HSV(float h, float s, float v);
            static Color HSVA(float h, float s, float v, unsigned char a);
            static Color NormalRGB(float r_normal, float g_normal, float b_normal);
            static Color NormalRGBA(float r_normal, float g_normal, float b_normal, float a_normal);
            static Color HexRGB(int hexValue);
            static Color HexRGBA(int hexValue);
        };
    }
#endif