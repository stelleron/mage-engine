#include "geom/DrawGeometry.hpp"

namespace arcana { 
    DrawPoint::DrawPoint(const Point& point, const Color& color) {
        this->pos = point.pos;
        this->color = color;
        this->z = 0.0f;
    }

    DrawPoint::DrawPoint(const Point& point, const Color& color, const float z) {
        this->pos = point.pos;
        this->color = color;
        this->z = z;
    }

    DrawLine::DrawLine(const Line& line, const Color& color) {
        this->startPoint = line.startPoint;
        this->endPoint = line.endPoint;
        this->color = color;
        this->z = 0.0f;
    }

    DrawLine::DrawLine(const Line& line, const Color& color, const float z) {
        this->startPoint = line.startPoint;
        this->endPoint = line.endPoint;
        this->color = color;
        this->z = z;
    }

    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
        this->z = 0.0f;
    }

    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color, float z) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
        this->z = z;
    }

    DrawQuad::DrawQuad(const Quadrilateral& quad, const Color& color) {
        this->point1 = quad.point1;
        this->point2 = quad.point2;
        this->point3 = quad.point3;
        this->point4 = quad.point4;
        this->color = color;
        this->z = 0.0f;
    }

    DrawQuad::DrawQuad(const Quadrilateral& quad, const Color& color, const float z) {
        this->point1 = quad.point1;
        this->point2 = quad.point2;
        this->point3 = quad.point3;
        this->point4 = quad.point4;
        this->color = color;
        this->z = z;
    }

    DrawQuad::DrawQuad(const Rectangle& rect, const Color& color) {
        this->point1 = rect.point;
        this->point2 = Vector2(rect.point.x, rect.point.y + rect.height);
        this->point3 = Vector2(rect.point.x + rect.width, rect.point.y);
        this->point4 = Vector2(rect.point.x + rect.width, rect.point.y + rect.height);
        this->color = color;
        this->z = 0.0f;
    }

    DrawQuad::DrawQuad(const Rectangle& rect, const Color& color, const float z) {
        this->point1 = rect.point;
        this->point2 = Vector2(rect.point.x, rect.point.y + rect.height);
        this->point3 = Vector2(rect.point.x + rect.width, rect.point.y);
        this->point4 = Vector2(rect.point.x + rect.width, rect.point.y + rect.height);
        this->color = color;
        this->z = z;
    }

    DrawCircle::DrawCircle(const Circle& circle, const Color& color) {
        this->center = circle.center;
        this->radius = circle.radius;
        this->color = color;
        this->z = 0.0f;
    }

    DrawCircle::DrawCircle(const Circle& circle, const Color& color, const float z) {
        this->center = circle.center;
        this->radius = circle.radius;
        this->color = color;
        this->z = z;
    }
    
    namespace drawable {
        DrawPoint make(const Point point, const Color color) {
            return DrawPoint(point, color);
        }

        DrawPoint make(const Point point, const Color color, const float z) {
            return DrawPoint(point, color, z);
        }

        DrawLine make(const Line line, const Color color) {
            return DrawLine(line, color);
        }

        DrawLine make(const Line line, const Color color, const float z) {
            return DrawLine(line, color, z);
        }

        DrawTriangle make(const Triangle triangle, const Color color) {
            return DrawTriangle(triangle, color);
        }  
        DrawTriangle make(const Triangle triangle, const Color color, const float z) {
            return DrawTriangle(triangle, color, z);
        }   

        DrawQuad make(const Quadrilateral quad, const Color color) {
            return DrawQuad(quad, color);
        }

        DrawQuad make(const Quadrilateral quad, const Color color, const float z) {
            return DrawQuad(quad, color, z);
        }

        DrawQuad make(const Rectangle rect, const Color color) {
            return DrawQuad(rect, color);
        }

        DrawQuad make(const Rectangle rect, const Color color, const float z) {
            return DrawQuad(rect, color, z);
        }

        DrawCircle make(const Circle circle, const Color color) {
            return DrawCircle(circle, color);
        }

        DrawCircle make(const Circle circle, const Color color, const float z) {
            return DrawCircle(circle, color, z);
        }
    }
}