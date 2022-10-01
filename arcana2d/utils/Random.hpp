
#ifndef ARCANA2D_RANDOM
    #define ARCANA2D_RANDOM
    namespace arcana {
        // Used to generate random numbers
        namespace random {
            // Generate a random float between 0 and 1
            float generate();
            // Generate random numbers
            int generateNum(int min, int max); // Between MIN and MAX
            // Set a seed
            void setSeed(unsigned int seed);
        }
    }
#endif