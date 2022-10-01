#ifndef ARCANA2D_GEOMETRY
    #define ARCANA2D_GEOMETRY
    // Includes
    #include "utils/Vector.hpp"

    namespace arcana {
        // Used to create a point object
        struct Point {
            Vector2 pos;
            
            // Constructors
            Point();
            Point(Vector2 pos);
        };

        // Used to create a line object
        struct Line {
            Vector2 startPoint;
            Vector2 endPoint;
            
            // Constructors
            Line();
            Line(Vector2 startPoint, Vector2 endPoint);
        };

        // Used to create a triangle
        struct Triangle {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;

            // Constructors
            Triangle();
            Triangle(Vector2 point, int width, int height); // Right angle triangle
            Triangle(Vector2 point1, Vector2 point2, Vector2 point3);
        };

        // Used to create a quadrilateral
        struct Quadrilateral {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;
            Vector2 point4;

            // Constructors
            Quadrilateral();
            Quadrilateral(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4);
        };   

        // Used to create a rectangle
        struct Rectangle {
            Vector2 point;
            int width;
            int height;

            // Constructors
            Rectangle();
            Rectangle(Vector2 point, int size); // Square
            Rectangle(Vector2 point, int width, int height);
        };

        // Used to create a circle
        struct Circle {
            Vector2 center;
            float radius;

            // Constructors
            Circle();
            Circle(Vector2 center, float radius);
        };    
    }
#endif
