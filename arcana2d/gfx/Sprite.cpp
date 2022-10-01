#include "gfx/Sprite.hpp"
#include "res/Filesystem.hpp"
#include <glad/glad.h>
#include "utils/Logger.hpp"

namespace arcana {
    SpriteData::SpriteData() {
        scale = {1.0f, 1.0f};
        rotation = 0.0f;
        z = 0.0f;
        color = Color::RGB(255, 255, 255);
    }

    Texture::Texture() {
        id = 0;
    }
    Texture::~Texture() {
        if (id) {
            glDeleteTextures(1, &id);
        }
    }
    Texture::Texture(const char* path) {
        load(path);
    }
    Texture::Texture(unsigned char* data, size_t size) {
        load(data, size);
    }
    Texture::Texture(const Image& image) {
        load(image);
    }
    void Texture::load(const char* path) {
        Image image(path);
        load(image);
    }
    void Texture::load(unsigned char* data, size_t size) {
        Image image(data, size);
        load(image);
    }
    void Texture::load(const Image& image) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        // Default texture params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
        // Default color swizzling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
        switch (image.format)
        {
            case GRAYSCALE:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image.width, image.height, 0, GL_RED, GL_UNSIGNED_BYTE, image.data); 
                break;
            case GRAY_ALPHA: 
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_GREEN);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, image.width, image.height, 0, GL_RG, GL_UNSIGNED_BYTE, image.data); 
                break;       
            case RGB: 
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data); 
                break;
            case RGBA: 
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data); 
                break;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        width = image.width;
        height = image.height;
    }

    Sprite::Sprite() {

    }

    Sprite::Sprite(const char* path) {
        load(path);
    }

    Sprite::Sprite(unsigned char* data, size_t size) {
        load(data, size);
    }

    Sprite::Sprite(const Image& image) {
        load(image);
    }

    Sprite::~Sprite() {

    }

    void Sprite::load(const char* path) {
        tex.load(path);
        pos = {tex.width/2, tex.height/2};
        targetRect.point = {0.0f, 0.0f};
        targetRect.width = tex.width;
        targetRect.height = tex.height;
    }

    void Sprite::load(unsigned char* data, size_t size) {
        tex.load(data, size);
        pos = {tex.width/2, tex.height/2};
        targetRect.point = {0.0f, 0.0f};
        targetRect.width = tex.width;
        targetRect.height = tex.height;
    }

    void Sprite::load(const Image& image) {
        tex.load(image);
        pos = {tex.width/2, tex.height/2};
        targetRect.point = {0.0f, 0.0f};
        targetRect.width = tex.width;
        targetRect.height = tex.height;
    }
}