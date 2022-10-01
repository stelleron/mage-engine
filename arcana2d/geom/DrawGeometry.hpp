#ifndef ARCANA2D_DRAW_GEOMETRY
    #define ARCANA2D_DRAW_GEOMETRY
    // Includes
    #include "utils/Color.hpp"
    #include "geom/Geometry.hpp"

    namespace arcana {
        struct DrawPoint : public Point {
            Color color;
            float z;
            DrawPoint(const Point& point, const Color& color);
            DrawPoint(const Point& point, const Color& color, const float z);
        };

        struct DrawLine : public Line {
            Color color;
            float z;
            DrawLine(const Line& line, const Color& color);
            DrawLine(const Line& line, const Color& color, const float z);
        };

        // Used to create a drawable
        struct DrawTriangle : public Triangle {
            Color color;
            float z;
            DrawTriangle(const Triangle& triangle, const Color& color);
            DrawTriangle(const Triangle& triangle, const Color& color, const float z);
        };

        struct DrawQuad : public Quadrilateral {
            Color color;
            float z;
            DrawQuad(const Rectangle& rect, const Color& color);
            DrawQuad(const Rectangle& rect, const Color& color, const float z);
            DrawQuad(const Quadrilateral& quad, const Color& color);
            DrawQuad(const Quadrilateral& quad, const Color& color, const float z);
        };

        struct DrawCircle : public Circle {
            Color color;
            float z;
            DrawCircle(const Circle& circle, const Color& color);
            DrawCircle(const Circle& circle, const Color& color, const float z);
        };

        // Used to make drawable objects
        namespace drawable
        {
            DrawPoint make(const Point point, const Color color);
            DrawPoint make(const Point point, const Color color, const float z);
            DrawLine make(const Line line, const Color color);
            DrawLine make(const Line line, const Color color, const float z);
            DrawTriangle make(const Triangle triangle, const Color color);
            DrawTriangle make(const Triangle triangle, const Color color, const float z);
            DrawQuad make(const Quadrilateral quad, const Color color);
            DrawQuad make(const Quadrilateral quad, const Color color, const float z);
            DrawQuad make(const Rectangle rect, const Color color);
            DrawQuad make(const Rectangle rect, const Color color, const float z);
            DrawCircle make(const Circle circle, const Color color);
            DrawCircle make(const Circle circle, const Color color, const float z);
        }
    }
#endif