#include "utils/Logger.hpp"
#include "gfx/VertexArray.hpp"


#define RENDER_TYPE_ASSERT(arg) if (rMode != arg) {ERROR("Error: Vertex buffer is not the correct type!"); return;}
#define BATCH_SPACE_ASSERT(start, value) if (!checkSpace(start, value)) {ERROR("Error: Vertex buffer does not have enough space!"); return;}
#define NUM_SECTORS 36
#define SECTOR_ANGLE 360.0f/(float)NUM_SECTORS
#define CIRCLE_VSIZE NUM_SECTORS + 1
#define NUM_INDICES NUM_SECTORS * 3

namespace arcana {
    // ELEMENT BUFFER IMPL.
    ElementBuffer::ElementBuffer(RenderMode rMode, int size) {
        totalSize = 0;
        int iVal = 0;
        switch (rMode)
        {
            case Quads: 
                // If the mode is Quads, store six times the given size of vertices as indices, and auto generate
                iArray = new unsigned int[size * 6];
                totalSize = sizeof(unsigned int) * size * 6;
                for (int x = 0; x < size; x++) {
                    iArray[x * 6] = iVal;
                    iArray[x * 6 + 1] = iVal + 1;
                    iArray[x * 6 + 2] = iVal + 2;
                    iArray[x * 6 + 3] = iVal + 1;
                    iArray[x * 6 + 4] = iVal + 2;
                    iArray[x * 6 + 5] = iVal + 3;
                    iVal = iVal + 4;
                }
                break;
            case Circles:
                // If the mode is Circles, store 108 times the given size of vertices as indices, and auto generate
                iArray = new unsigned int[size * NUM_INDICES];
                totalSize = sizeof(unsigned int) * size * NUM_INDICES;
                for (int x = 0; x < size; x++) {
                    for (int y = 0; y < NUM_SECTORS; y++) {
                        iArray[(x * NUM_INDICES) + (y * 3)] = iVal;
                        iArray[(x * NUM_INDICES) + (y * 3 + 1)] = iVal + y + 1;
                        if (y != NUM_SECTORS - 1) {
                            iArray[(x * NUM_INDICES) + (y * 3 + 2)] = iVal + y + 2;
                        }
                        else {
                            iArray[(x * NUM_INDICES) + (y * 3 + 2)] = iVal + 1;
                        }                        
                    }
                    iVal += CIRCLE_VSIZE;
                } 
                break;
            default: break;
        }
    }

    ElementBuffer::~ElementBuffer() {
        delete[] iArray;
    }

    size_t ElementBuffer::getSize() {
        return totalSize;
    }
 
    // VERTEX BUFFER IMPL.
    VertexArray::VertexArray() {
        eBuffer = nullptr;
        vArray = nullptr;
        vSize = 0;
        primSize = 0;
        rMode = RenderMode::None;
    }

    VertexArray::VertexArray(RenderMode rMode, int vertexNum) {
        eBuffer = nullptr;
        vArray = nullptr;
        create(rMode, vertexNum);
    }

    VertexArray::~VertexArray() {
        if (eBuffer) {
            delete eBuffer;
        }
        if (vArray)
            delete[] vArray;
    }

    void VertexArray::create(RenderMode rMode, int vertexNum) {
        if (eBuffer) {
            delete eBuffer;
            eBuffer = nullptr;
        }
        if (vArray) {
            delete[] vArray;
            vArray = nullptr;
        }
        if (rMode == RenderMode::None) {
            ERROR("Error: Cannot set the render mode of a vertex array as None!");
            exit(0);
        }

        switch (rMode)
        {
            case Points: primSize = 2; break;
            case Lines: primSize = 2; break;
            case Triangles: primSize = 3; break;
            case Quads: primSize = 4; eBuffer = new ElementBuffer(rMode, vertexNum/primSize); break;
            case Circles: primSize = CIRCLE_VSIZE; eBuffer = new ElementBuffer(rMode, vertexNum/primSize); break;
            default: break;
        }

        // Now allocate memory for the vertices
        vSize = vertexNum;
        vArray = new Vertex[vSize];

        // Save the render mode and set the vertex pointer to 0
        this->rMode = rMode;
    }

    void VertexArray::clear() {
        if (vArray)
            for (int x = 0; x < vSize; x++) {
                vArray[vSize] = Vertex();
            }
    }

    void VertexArray::reset(RenderMode rMode, int vertexNum) {
        create(rMode, vertexNum);
    }

    void VertexArray::reset() {
        if (eBuffer) {
            delete eBuffer;
            eBuffer = nullptr;
        }
        if (vArray) {
            delete[] vArray;
            vArray = nullptr;
        }
        vSize = 0;
        primSize = 0;
        rMode = RenderMode::None;
    }

    bool VertexArray::checkSpace(int startIndex, int numVertices) {
        if (numVertices + startIndex <= vSize) {
            return true;
        }
        else {
            return false;
        }
    }

    size_t VertexArray::getArraySize() {
        return vSize * sizeof(Vertex);
    }

    Vertex* VertexArray::getVertexArray() {
        return vArray;
    }

    void VertexArray::add(const Point& point, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Points);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 2);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(point.pos);
        vArray[startIndex + 1] = Vertex(Vector2(point.pos.x + 1, point.pos.y + 1));
    }

    void VertexArray::add(const DrawPoint& point, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Points);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 2);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(Vector3(point.pos.x, point.pos.y, point.z), point.color);
        vArray[startIndex + 1] = Vertex(Vector3(point.pos.x + 1, point.pos.y + 1, point.z), point.color);
    }

    void VertexArray::add(const Line& line, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Lines);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 2);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(line.startPoint);
        vArray[startIndex + 1] = Vertex(line.endPoint);
    }

    void VertexArray::add(const DrawLine& line, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Lines);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 2);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(Vector3(line.startPoint.x, line.startPoint.y, line.z), line.color);
        vArray[startIndex + 1] = Vertex(Vector3(line.endPoint.x, line.endPoint.y, line.z), line.color);
    }

    void VertexArray::add(const Triangle& triangle, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 3);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(triangle.point1);
        vArray[startIndex + 1] = Vertex(triangle.point2);
        vArray[startIndex + 2] = Vertex(triangle.point3);
    }

    void VertexArray::add(const DrawTriangle& triangle, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Triangles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 3);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(Vector3(triangle.point1.x, triangle.point1.y, triangle.z), triangle.color);
        vArray[startIndex + 1] = Vertex(Vector3(triangle.point2.x, triangle.point2.y, triangle.z), triangle.color);
        vArray[startIndex + 2] = Vertex(Vector3(triangle.point3.x, triangle.point3.y, triangle.z), triangle.color);
    }

    void VertexArray::add(const Rectangle& rectangle, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Quads);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 4);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(Vector2(rectangle.point.x, rectangle.point.y));
        vArray[startIndex + 1] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y));
        vArray[startIndex + 2] = Vertex(Vector2(rectangle.point.x, rectangle.point.y + rectangle.height));
        vArray[startIndex + 3] = Vertex(Vector2(rectangle.point.x + rectangle.width, rectangle.point.y + rectangle.height));
    }

    void VertexArray::add(const Quadrilateral& quad, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Quads);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 4);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(quad.point1);
        vArray[startIndex + 1] = Vertex(quad.point2);
        vArray[startIndex + 2] = Vertex(quad.point3);
        vArray[startIndex + 3] = Vertex(quad.point4);
    }

    void VertexArray::add(const DrawQuad& quad, int startIndex) {
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Quads);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 4);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(Vector3(quad.point1, quad.z), quad.color);
        vArray[startIndex + 1] = Vertex(Vector3(quad.point2, quad.z), quad.color);
        vArray[startIndex + 2] = Vertex(Vector3(quad.point3, quad.z), quad.color);
        vArray[startIndex + 3] = Vertex(Vector3(quad.point4, quad.z), quad.color);
    }

    void VertexArray::add(const Circle& circle, int startIndex) {
        // TODO
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Circles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, CIRCLE_VSIZE);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(circle.center);
        for (int x = 0; x < NUM_SECTORS; x++) {
            vArray[startIndex + x + 1] = Vertex(Vector2(
                circle.center.x + sinf(glm::radians(SECTOR_ANGLE * x)) * circle.radius, 
                circle.center.y - cosf(glm::radians(SECTOR_ANGLE * x)) * circle.radius
            ));
        }
    }

    void VertexArray::add(const DrawCircle& circle, int startIndex) {
        // TODO
        // First make sure that object has a compatiable type
        RENDER_TYPE_ASSERT(RenderMode::Circles);

        // Then ensure that there is enough space for the primitive
        BATCH_SPACE_ASSERT(startIndex, 37);

        // Now time to add all of the vertices to the vertex array
        vArray[startIndex] = Vertex(circle.center);
        for (int x = 0; x < NUM_SECTORS; x++) {
            vArray[startIndex + x + 1] = Vertex(
            Vector3(
                circle.center.x + sinf(glm::radians(SECTOR_ANGLE * x)) * circle.radius, 
                circle.center.y - cosf(glm::radians(SECTOR_ANGLE * x)) * circle.radius,
                circle.z
            ),
            circle.color
            );
        }
    }

    unsigned int* VertexArray::getIndexArray() {
        if (eBuffer)
            return eBuffer->iArray;
        else 
            ERROR("Error: Nothing in the index array!");
            return nullptr;
    }

    size_t VertexArray::getIndexArraySize() {
        if (eBuffer)
            return eBuffer->getSize();
        else 
            ERROR("Error: Nothing in the index array!");
            return 0;
    }

    Vertex& VertexArray::operator[](int index) {
        if (index >= vSize) {
            ERROR("Error: Index out of range!");
            exit(0);
        }
        return vArray[index];
    }

    Vertex VertexArray::operator[](int index) const {
        if (index >= vSize) {
            ERROR("Error: Index out of range!");
            exit(0);
        }
        return vArray[index];
    }
}