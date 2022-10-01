#ifndef ARCANA2D_VERTEX
    #define ARCANA2D_VERTEX
    // Includes
    #include "utils/Color.hpp"
    #include "utils/Vector.hpp"

    // Macro defines
    #define VERTEX_SIZE 9

    namespace arcana {
        // Used to create a vertex object
        struct Vertex {
            Vector3 pos;
            Color color;
            Vector2 texCoords;
        
            // Constructor
            Vertex();
            Vertex(Vector2 pos);
            Vertex(Vector2 pos, Color color);
            Vertex(Vector2 pos, Color color, Vector2 texCoords);
            Vertex(Vector3 pos);
            Vertex(Vector3 pos, Color color);
            Vertex(Vector3 pos, Color color, Vector2 texCoords);
        };
    }
#endif