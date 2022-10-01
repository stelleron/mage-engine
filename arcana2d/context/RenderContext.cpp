#include <glad/glad.h>
#include <cmath>
#include "context/RenderContext.hpp"
#include "geom/Vertex.hpp"
#include "utils/Logger.hpp"

#define MAX_BATCH_SIZE 8000
#define DRAW_OBJECT(type, vnum, obj) do { \
    RenderMode rmode = rBatch.vertexArray.getRenderType(); \
    if (rmode == type && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, vnum) && currentTextureID == defaultTextureID) { \
        rBatch.add(obj); \
    } \
    else { \
        if (rmode != None) { \
            draw(rBatch.vertexArray); \
        } \
        currentTextureID = defaultTextureID; \
        rBatch.vertexArray.reset(type, MAX_BATCH_SIZE); \
        rBatch.vertexPointer = 0; \
        rBatch.add(obj); \
    } \
} while (false); \

namespace arcana {
    // RENDER BATCH IMPL.
    RenderContext::RenderBatch::RenderBatch() {
        vertexPointer = 0;
    }

    RenderContext::RenderBatch::~RenderBatch() {

    }

    void RenderContext::RenderBatch::add(const Point& point) {
        vertexArray.add(point, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const DrawPoint& point) {
        vertexArray.add(point, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const Line& line) {
        vertexArray.add(line, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const DrawLine& line) {
        vertexArray.add(line, vertexPointer);
        vertexPointer += 2;
    }

    void RenderContext::RenderBatch::add(const Triangle& triangle) {
        vertexArray.add(triangle, vertexPointer);
        vertexPointer += 3;
    }

    void RenderContext::RenderBatch::add(const DrawTriangle& triangle) {
        vertexArray.add(triangle, vertexPointer);
        vertexPointer += 3;
    }

    void RenderContext::RenderBatch::add(const Rectangle& rectangle) {
        vertexArray.add(rectangle, vertexPointer);
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(const Quadrilateral& quad) {
        vertexArray.add(quad, vertexPointer);
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(const DrawQuad& quad) {
        vertexArray.add(quad, vertexPointer);
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(Sprite& sprite) {
        Texture* tex = sprite.getTexturePtr();
        // First set the color of all vertices
        vertexArray[vertexPointer].color = sprite.color;
        vertexArray[vertexPointer + 1].color = sprite.color;
        vertexArray[vertexPointer + 2].color = sprite.color;
        vertexArray[vertexPointer + 3].color = sprite.color;
        // Now set the tex coords
        vertexArray[vertexPointer].texCoords = {sprite.targetRect.point.x/tex->width, sprite.targetRect.point.y/tex->height};
        vertexArray[vertexPointer + 1].texCoords = {(sprite.targetRect.point.x + sprite.targetRect.width)/tex->width, sprite.targetRect.point.y/tex->height};
        vertexArray[vertexPointer + 2].texCoords = {sprite.targetRect.point.x/tex->width, (sprite.targetRect.point.y + sprite.targetRect.height)/tex->height};
        vertexArray[vertexPointer + 3].texCoords = {(sprite.targetRect.point.x + sprite.targetRect.width)/tex->width, (sprite.targetRect.point.y + sprite.targetRect.height)/tex->height};
        // And finally positions
        if (sprite.rotation != 0.0f) {
            float radius = sqrt((sprite.targetRect.width * sprite.targetRect.width *  sprite.scale.x *  sprite.scale.x) + (sprite.targetRect.height * sprite.targetRect.height * sprite.scale.y * sprite.scale.y))/2; 
            float topRightAngle = atan( (sprite.targetRect.height * sprite.scale.y) / (sprite.targetRect.width *  sprite.scale.x) ) * 180/M_PI;
            float bottomRightAngle = 180 - topRightAngle;
            float bottomLeftAngle = 180 + topRightAngle;
            float topLeftAngle = 180 + bottomRightAngle;

            vertexArray[vertexPointer].pos = {
                sprite.pos.x + sinf(glm::radians(topLeftAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(topLeftAngle + sprite.rotation)) * radius, 
                sprite.z};
            vertexArray[vertexPointer + 1].pos = {
                sprite.pos.x + sinf(glm::radians(topRightAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(topRightAngle + sprite.rotation)) * radius,  
                sprite.z};
            vertexArray[vertexPointer + 2].pos = {
                sprite.pos.x + sinf(glm::radians(bottomLeftAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(bottomLeftAngle + sprite.rotation)) * radius, 
                sprite.z};
            vertexArray[vertexPointer + 3].pos = {
                sprite.pos.x + sinf(glm::radians(bottomRightAngle + sprite.rotation)) * radius, 
                sprite.pos.y - cosf(glm::radians(bottomRightAngle + sprite.rotation)) * radius,
                sprite.z};
        }
        else {
            vertexArray[vertexPointer].pos = {
                sprite.pos.x - (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y - (sprite.scale.y * sprite.targetRect.height)/2, 
                sprite.z};
            vertexArray[vertexPointer + 1].pos = {
                sprite.pos.x + (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y - (sprite.scale.y * sprite.targetRect.height)/2, 
                sprite.z};
            vertexArray[vertexPointer + 2].pos = {
                sprite.pos.x - (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y + (sprite.scale.y * sprite.targetRect.height)/2, 
                sprite.z};
            vertexArray[vertexPointer + 3].pos = {
                sprite.pos.x + (sprite.scale.x * sprite.targetRect.width)/2, 
                sprite.pos.y + (sprite.scale.y * sprite.targetRect.height)/2, 
                sprite.z};
        }

        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(Texture& tex, Vector2 pos, Vector2 scale, float z, float rotation, Color color, Rectangle targetRect) {
        // First set color
        vertexArray[vertexPointer].color = color;
        vertexArray[vertexPointer + 1].color = color;
        vertexArray[vertexPointer + 2].color = color;
        vertexArray[vertexPointer + 3].color = color;
        // Then set tex coords
        vertexArray[vertexPointer].texCoords = {targetRect.point.x/tex.width, targetRect.point.y/tex.height};
        vertexArray[vertexPointer + 1].texCoords = {(targetRect.point.x + targetRect.width)/tex.width, targetRect.point.y/tex.height};
        vertexArray[vertexPointer + 2].texCoords = {targetRect.point.x/tex.width, (targetRect.point.y + targetRect.height)/tex.height};
        vertexArray[vertexPointer + 3].texCoords = {(targetRect.point.x + targetRect.width)/tex.width, (targetRect.point.y + targetRect.height)/tex.height};
        // Then finally set positions 
        if (rotation != 0.0f) {
            float line_dist = sqrt((targetRect.width * targetRect.width *  scale.x *  scale.x) + (targetRect.height * targetRect.height * scale.y * scale.y));
            vertexArray[vertexPointer].pos = {
                pos.x, 
                pos.y, 
                z
            };
            vertexArray[vertexPointer + 1].pos = {
                pos.x + sinf(glm::radians(90.0 + rotation)) * targetRect.width * scale.x,
                pos.y - cosf(glm::radians(90.0 + rotation)) * targetRect.width * scale.x,
                z
            };
            vertexArray[vertexPointer + 2].pos = {
                pos.x + sinf(glm::radians(180.0 + rotation)) * targetRect.height * scale.y,
                pos.y - cosf(glm::radians(180.0 + rotation)) * targetRect.height * scale.y,
                z
            };
            vertexArray[vertexPointer + 3].pos = {
                pos.x + sinf(glm::radians(135.0 + rotation)) * line_dist,
                pos.y - cosf(glm::radians(135.0 + rotation)) * line_dist,
                z
            };
            
        }
        else {
            vertexArray[vertexPointer].pos = {
                pos.x, 
                pos.y, 
                z};
            vertexArray[vertexPointer + 1].pos = {
                pos.x + (targetRect.width * scale.x), 
                pos.y, 
                z};
            vertexArray[vertexPointer + 2].pos = {
                pos.x, 
                pos.y + (targetRect.height * scale.y), 
                z};
            vertexArray[vertexPointer + 3].pos = {
                pos.x + (targetRect.width * scale.x),  
                pos.y + (targetRect.height * scale.y),  
                z};
        }
        vertexPointer += 4;
    }

    void RenderContext::RenderBatch::add(const Circle& circle) {
        vertexArray.add(circle, vertexPointer);
        vertexPointer += 37; 
    }

    void RenderContext::RenderBatch::add(const DrawCircle& circle) {
        vertexArray.add(circle, vertexPointer);
        vertexPointer += 37;
    }

    // RENDER CONTEXT IMPL.
    RenderContext::RenderContext() {
        
    }

    RenderContext::~RenderContext() {
        glDeleteVertexArrays(1, &defaultVAO);
        glDeleteBuffers(1, &defaultVBO);
        glDeleteTextures(1, &defaultTextureID);
        glDeleteBuffers(1, &defaultEBO);
    } 

    void RenderContext::init() {
        // Create the default texture here
        unsigned char defaultTexture[4] = { 255, 255, 255, 255 }; 
        glGenTextures(1, &defaultTextureID); 
        glBindTexture(GL_TEXTURE_2D, defaultTextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, defaultTexture);
        glGenerateMipmap(GL_TEXTURE_2D);
        glGenVertexArrays(1, &defaultVAO);
        glGenBuffers(1, &defaultVBO);
        glGenBuffers(1, &defaultEBO);
        currentTextureID = defaultTextureID;
    }

    void RenderContext::setVertexAttributes() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)12);
        glEnableVertexAttribArray(1);  
         
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);
        glEnableVertexAttribArray(2);
    }

    void RenderContext::useShader() {
        currShader->setMat4("projection", currCamera->getProjectionMatrix());
        currShader->use();
    }

    void RenderContext::draw(VertexArray& vArray) {
        RenderMode rMode = vArray.getRenderType();
        if (rMode == None) {
            ERROR("Error: Cannot draw a vertex array with type None!");
        }
        else if (rMode == Quads || rMode == Circles) {
            // Bind all vertex objects
            glBindVertexArray(defaultVAO);
            glBindBuffer(GL_ARRAY_BUFFER, defaultVBO); 
            glBufferData(GL_ARRAY_BUFFER, vArray.getArraySize(), vArray.getVertexArray(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, defaultEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, vArray.getIndexArraySize(), vArray.getIndexArray(), GL_STATIC_DRAW);
            setVertexAttributes();
            glBindBuffer(GL_ARRAY_BUFFER, 0);  
            GLenum drawType;
            switch (rMode) {
                case Circles: drawType = GL_TRIANGLES; break;
                case Quads: drawType = GL_TRIANGLES; break;
                default: break;
            }

            useShader();
            glBindTexture(GL_TEXTURE_2D, currentTextureID);
            glBindVertexArray(defaultVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawElements(drawType, vArray.getIndexArraySize()/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }
        else {
            // Bind all vertex objects
            glBindVertexArray(defaultVAO);
            glBindBuffer(GL_ARRAY_BUFFER, defaultVBO); 
            glBufferData(GL_ARRAY_BUFFER, vArray.getArraySize(), vArray.getVertexArray(), GL_STATIC_DRAW);
            setVertexAttributes();
            glBindBuffer(GL_ARRAY_BUFFER, 0);  
            GLenum drawType;
            switch (rMode) {
                case Points: drawType = GL_LINES; break;
                case Lines: drawType = GL_LINES; break;
                case Triangles: drawType = GL_TRIANGLES; break;
                default: break;
            }

            useShader();
            glBindTexture(GL_TEXTURE_2D, currentTextureID);
            glBindVertexArray(defaultVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(drawType, 0, vArray.getNumVertices());
        }
        
    }

    void RenderContext::draw(const Point& point) {
        DRAW_OBJECT(Points, 2, point);
    }

    void RenderContext::draw(const DrawPoint& point) {
        DRAW_OBJECT(Points, 2, point);
    }

    void RenderContext::draw(const Line& line) {
        DRAW_OBJECT(Lines, 2, line);
    }

    void RenderContext::draw(const DrawLine& line) {
        DRAW_OBJECT(Lines, 2, line);
    }

    void RenderContext::draw(const Triangle& triangle) {
        DRAW_OBJECT(Triangles, 3, triangle);
    }

    void RenderContext::draw(const DrawTriangle& triangle) {
        DRAW_OBJECT(Triangles, 3, triangle);
    }

    void RenderContext::draw(const Rectangle& rectangle) {
        DRAW_OBJECT(Quads, 4, rectangle);
    }

    void RenderContext::draw(const Quadrilateral& quad) {
        DRAW_OBJECT(Quads, 4, quad);
    }

    void RenderContext::draw(const DrawQuad& quad) {
        DRAW_OBJECT(Quads, 4, quad);
    }

    void RenderContext::draw(const Circle& circle) {
        DRAW_OBJECT(Circles, 37, circle);
    }

    void RenderContext::draw(const DrawCircle& circle) {
        DRAW_OBJECT(Circles, 37, circle);
    }

    void RenderContext::draw(Sprite& sprite) {
        Texture* tex = sprite.getTexturePtr();
        RenderMode rmode = rBatch.vertexArray.getRenderType(); 
        if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4) && currentTextureID == tex->id) { 
            rBatch.add(sprite); 
        } 
        else { 
            if (rmode != None) { 
                draw(rBatch.vertexArray); 
            } 
            currentTextureID = tex->id; 
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
            rBatch.vertexPointer = 0; 
            rBatch.add(sprite); 
        } 
    }

    void RenderContext::draw(Texture& tex, Vector2 pos, Vector2 scale, float z, float rotation, Color color) {
        draw(tex, Rectangle({0.0, 0.0}, tex.width, tex.height), pos, scale, z, rotation, color);
    } 

    void RenderContext::draw(Texture& tex, Rectangle targetRect, Vector2 pos, Vector2 scale, float z, float rotation, Color color) {
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4) && currentTextureID == tex.id) { 
            rBatch.add(tex, pos, scale, z, rotation, color, targetRect); 
        } 
        else { 
            if (rmode != None) { 
                draw(rBatch.vertexArray); 
            } 
            currentTextureID = tex.id; 
            rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
            rBatch.vertexPointer = 0; 
            rBatch.add(tex, pos, scale, z, rotation, color, targetRect); 
        }
    }

    void RenderContext::print(Font& font, std::string message, Vector2 pos, float z, Color color, int padding) {
        int xOffset = 0;
        for (int x = 0; x < message.length(); x++) {
            RenderMode rmode = rBatch.vertexArray.getRenderType();
            if (rmode == Quads && rBatch.vertexArray.checkSpace(rBatch.vertexPointer, 4) && currentTextureID == font.fontTex.id) { 
                rBatch.add(font.fontTex, {pos.x + xOffset, pos.y}, {1.0, 1.0}, z, 0, color, font.fontRecs[(int)message[x] - START_CHAR]); 
            } 
            else { 
                if (rmode != None) { 
                    draw(rBatch.vertexArray); 
                } 
                currentTextureID = font.fontTex.id; 
                rBatch.vertexArray.reset(Quads, MAX_BATCH_SIZE); 
                rBatch.vertexPointer = 0; 
                rBatch.add(font.fontTex, {pos.x + xOffset, pos.y}, {1.0, 1.0}, z, 0, color, font.fontRecs[(int)message[x] - START_CHAR]);
            }
            xOffset += font.fontRecs[(int)message[x] - START_CHAR].width + padding;
        }
    }

    void RenderContext::drawBatch() {
        // Reset the draw batch
        RenderMode rmode = rBatch.vertexArray.getRenderType();
        if (rmode != None) {
            draw(rBatch.vertexArray);
        }
        rBatch.vertexArray.reset();
        rBatch.vertexPointer = 0;
    }
}

