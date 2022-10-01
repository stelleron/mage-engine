#ifndef ARCANA2D_SPRITE
    #define ARCANA2D_SPRITE
    
    #include "utils/Color.hpp"
    #include "geom/Geometry.hpp"
    #include "res/Image.hpp"

    namespace arcana {
        // Used to store the data for a sprite
        struct SpriteData {
            Vector2 pos;
            Vector2 scale;
            Rectangle targetRect;
            Color color;
            float rotation;
            float z;
            SpriteData();
        };

        // Used to create a texture 
        struct Texture {
            unsigned int id;
            int width;
            int height;

            // Constructors
            Texture();
            Texture(const char* path);
            Texture(unsigned char* data, size_t size);
            Texture(const Image& image);
            // Desturctors
            ~Texture();
            
            // Loading functions
            void load(const char* path);
            void load(unsigned char* data, size_t size);
            void load(const Image& image);
        };


        // Used to create a sprite
        class Sprite : public SpriteData {
            private:
                Texture tex;
            public:
                // Constructors
                Sprite();
                Sprite(const char* path);
                Sprite(unsigned char* data, size_t size);
                Sprite(const Image& image);
                // Destructors
                ~Sprite();

                // Loading functions
                void load(const char* path);
                void load(unsigned char* data, size_t size);
                void load(const Image& image);

                // Get the texture pointer
                inline Texture* getTexturePtr() {return &tex;}
        };
    }
#endif