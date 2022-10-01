#ifndef ARCANA2D_FONT
    #define ARCANA2D_FONT
    #include "geom/Geometry.hpp"
    #include "gfx/Sprite.hpp"

    #define START_CHAR 32
    #define END_CHAR 126
    #define NUM_CHARS END_CHAR - START_CHAR + 1
    
    #define DEFAULT_FONT_SIZE 32

    namespace arcana {
        // Used to create a font object
        struct Font {
            private:
                int fontSize;
            public:
                Rectangle fontRecs[NUM_CHARS];
                Texture fontTex;

                // Constructor
                Font();
                Font(const char* path, int fontsize = DEFAULT_FONT_SIZE);
                Font(unsigned char* data, size_t size, int fontsize = DEFAULT_FONT_SIZE);
                // Destructor 
                ~Font();

                void load(const char* path, int fontsize = DEFAULT_FONT_SIZE);
                void load(unsigned char* data, size_t size, int fontsize = DEFAULT_FONT_SIZE);
                bool isLoaded(); // Check if the font has been loaded
        };
    }
#endif