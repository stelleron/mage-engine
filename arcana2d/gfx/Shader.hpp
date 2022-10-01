#ifndef ARCANA2D_SHADER
    #define ARCANA2D_SHADER

    #include "utils/Vector.hpp"

    namespace arcana {
        // Used to create a shader class 
        class Shader {
            private:
                bool is_init;
                unsigned int id;
            public:
                // Different shader constructors 
                Shader();
                Shader(int exclude1, int exclude2);
                Shader(const char* vSource, int exclude);
                Shader(int exclude, const char* fSource);
                Shader(const char* vSource, const char* fSource);
                
                // Load the shader
                void load(int exclude1, int exclude2);
                void load(const char* vSource, const char* fSource);

                // Uniform setting functions
                void setBool(const char* name, bool value);  
                void setInt(const char* name, int value);   
                void setFloat(const char* name, float value);
                void setVec2(const char* name, Vector2 vec);
                void setVec3(const char* name, Vector3 vec);
                void setVec4(const char* name, Vector4 vec);
                void setMat4(const char* name, Mat4 matrix);

                // Use the shader
                void use();

                // Getters
                inline const unsigned int getID() {return id;}
                inline const bool getInit() {return is_init;}

                // Setters
                void deInit() { is_init = false;}

                // Copy assignment operator
                Shader& operator=(Shader& shader) {
                    if (is_init) {glDeleteProgram(id);} 
                    id = shader.getID();
                    shader.deInit();
                    is_init = true;
                    return *this;
                }

                // Destructor
                ~Shader();
        };
    }
#endif