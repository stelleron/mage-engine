#ifndef COLOR_H
    #define COLOR_H
    #include <array>
    namespace Mage {
        // Used to store color data
        struct Color {
            int r;
            int g;
            int b;
            int a;
            Color();
            Color(std::array<int, 4> colarray);
            Color(int r, int g, int b, int a);
            ~Color();
        };
    }
#endif