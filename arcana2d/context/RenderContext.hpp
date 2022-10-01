#ifndef ARCANA2D_RENDER_CONTEXT
    #define ARCANA2D_RENDER_CONTEXT

    #include <string>
    #include "camera/Camera.hpp"
    #include "gfx/Shader.hpp"
    #include "gfx/Sprite.hpp"
    #include "gfx/VertexArray.hpp"
    #include "res/Font.hpp"


    namespace arcana {
        // Creates the render context
        class RenderContext {
            // Creates an internal render batch
            struct RenderBatch {
                VertexArray vertexArray;
                int vertexPointer;

                RenderBatch();
                ~RenderBatch();

                // Used to add objects to the render batch
                void add(const Point& point);
                void add(const DrawPoint& point);

                void add(const Line& line);
                void add(const DrawLine& line);

                void add(const Triangle& triangle);
                void add(const DrawTriangle& triangle);

                void add(const Rectangle& rectangle);
                void add(const Quadrilateral& quad);
                void add(const DrawQuad& quad);

                void add(const Circle& circle);
                void add(const DrawCircle& circle);

                void add(Sprite& sprite);
                void add(Texture& tex, Vector2 pos, Vector2 scale, float z, float rotation, Color color, Rectangle targetRect);
            };

            private:
                Shader* currShader;
                Camera* currCamera;
                RenderBatch rBatch;

                unsigned int defaultVBO;
                unsigned int defaultVAO;
                unsigned int defaultEBO;
                unsigned int defaultTextureID;
                unsigned int currentTextureID;

                void setVertexAttributes();
                void useShader();
                void drawBatchAndReset();
            public:
                // Constructor
                RenderContext();
                // Destructor
                ~RenderContext();
                void init();
                void setCurrentCamera(Camera& camera) {currCamera = &camera;}
                void setCurrentShader(Shader& shader) {currShader = &shader;}

                // Draw functions
                void draw(VertexArray& vArray);

                // Used to add objects to the render batch
                void draw(const Point& point);
                void draw(const DrawPoint& point);

                void draw(const Line& line);
                void draw(const DrawLine& line);

                void draw(const Triangle& triangle);
                void draw(const DrawTriangle& triangle);

                void draw(const Rectangle& rectangle);
                void draw(const Quadrilateral& quad);
                void draw(const DrawQuad& quad);

                void draw(const Circle& circle);
                void draw(const DrawCircle& circle);

                // Used to render textures and sprites
                void draw(Sprite& sprite);

                void draw(Texture& tex, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float z = 0.0, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));
                void draw(Texture& tex, Rectangle targetRect, Vector2 pos = {0.0, 0.0}, Vector2 scale = {1.0, 1.0}, float z = 0.0, float rotation = 0.0, Color color = Color::RGB(255, 255, 255));

                // Used to render text
                void print(Font& font, std::string message, Vector2 pos = {0.0, 0.0}, float z = 0, Color color = Color::RGB(255, 255, 255), int padding = 4);

                void drawBatch();
        };
    }

#endif