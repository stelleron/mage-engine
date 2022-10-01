#ifndef ARCANA2D_CAMERA
    #define ARCANA2D_CAMERA
    // Includes
    #include "utils/Vector.hpp"

    namespace arcana {
        // Used to create a 2D camera
        class Camera { 
            public:
                Vector2 dimensions; // Stores the camera dimensions
                Vector2 offset;
                float zoom; 
                float rotation;

                // Constructor
                Camera();
                // Destructor 
                ~Camera();

                // Get the projection matrix
                Mat4 getProjectionMatrix();
        };
    }
#endif