#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" 

#include "utils/Vector.hpp"
#include "res/Image.hpp"
#include "res/Font.hpp"
#include "res/Filesystem.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    struct GlyphData {
        int charValue;
        int xOffset;
        int yOffset;
        int advance;
        Image image;
    };

    Font::Font() {

    }

    Font::Font(const char* path, int fontsize) {
        load(path, fontsize);
    }

    Font::Font(unsigned char* data, size_t size, int fontsize) {
        load(data, size, fontsize);
    }

    Font::~Font() {

    }

    void Font::load(const char* path, int fontsize) {
        size_t fsize;
        // Load file

        // Load file data
        unsigned char* data = filesystem::loadFileData(path, fsize);
        std::string extension = filesystem::getFileExtension(path);
        if (extension == "otf" || extension == "ttf")
            load(data, fsize, fontsize);
        else 
            LOG("Font: Font type not supported!");
        delete[] data;
    }

    void Font::load(unsigned char* data, size_t size, int fontsize) {
        GlyphData* glyphs = new GlyphData[NUM_CHARS];
        this->fontSize = fontsize;
        int xCharDim = 0, yCharDim = 0, xOffset = 0, yOffset = 0, imgArea = 0;

        // Load the font
        stbtt_fontinfo ftData = {0};
        if (!stbtt_InitFont(&ftData, data, 0)) {
            LOG("Font: Could not process the font data!");
            return;
        }

        // Now create the font atlas
        // First fetch font data
        float scale = stbtt_ScaleForPixelHeight(&ftData, fontSize);
        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&ftData, &ascent, &descent, &lineGap);

        // Now get the data for each glyph
        for (int i = START_CHAR; i <= END_CHAR; i++) {
            int index = i - START_CHAR;
            // Loading the glyph data
            glyphs[index].image.format = GRAYSCALE;
            stbtt_GetCodepointHMetrics(&ftData, i, &glyphs[index].advance, NULL);
            glyphs[index].advance = (int)((float)glyphs[index].advance*scale);

            if (i != 32) {
                glyphs[index].image.data = 
                stbtt_GetCodepointBitmap(&ftData, scale, scale, i, 
                                        &glyphs[index].image.width, 
                                        &glyphs[index].image.height, 
                                        &glyphs[index].xOffset, 
                                        &glyphs[index].yOffset);
            }
            else {
                glyphs[index].image.data = new unsigned char[fontSize * glyphs[index].advance];
                memset(glyphs[index].image.data, 0, glyphs[index].advance * fontSize);
                glyphs[index].image.width = glyphs[index].advance;
                glyphs[index].image.height = fontSize;
            }
            imgArea += glyphs[index].image.width * glyphs[index].image.height;
        }
        
        // Now generate an atlas
        // First calculate an image size
        float guessSize = sqrtf(imgArea)*1.4f;
        int imageSize = (int)powf(2, ceilf(logf((float)guessSize)/logf(2)));
        
        // Set the font atlas
        Image fontAtlas;
        fontAtlas.data = new unsigned char[imageSize * imageSize];
        memset(fontAtlas.data, 0, imageSize * imageSize);
        fontAtlas.width = imageSize;
        fontAtlas.height = imageSize;
        fontAtlas.format = GRAYSCALE;

        // Now copy the data for each glyph
        int dataPtrX = 0, dataPtrY = 0;
        for (int i = 0; i < NUM_CHARS; i++) {
            for (int y = 0; y < glyphs[i].image.height; y++)
            {
                for (int x = 0; x < glyphs[i].image.width; x++)
                {
                    fontAtlas.data[(y + dataPtrY) * fontAtlas.width + (x + dataPtrX)] = 
                            glyphs[i].image.data[y * glyphs[i].image.width + x];
                }
            }
            // Set the rectangles
            fontRecs[i].point = {dataPtrX, dataPtrY};
            fontRecs[i].width = glyphs[i].image.width;
            fontRecs[i].height = glyphs[i].image.height;

            dataPtrX += glyphs[i].image.width;

            if (dataPtrX + glyphs[i].image.width >= fontAtlas.width) {
                dataPtrX = 0;
                dataPtrY += fontSize;
            }
        }

        // Convert GRAYSCALE to GRAY_ALPHA
        unsigned char *dataGrayAlpha = new unsigned char[fontAtlas.width * fontAtlas.height * 2]; 

        for (int i = 0, k = 0; i < fontAtlas.width*fontAtlas.height; i++, k += 2)
        {
            dataGrayAlpha[k] = 255;
            dataGrayAlpha[k + 1] = fontAtlas.data[i];
        }

        delete[] fontAtlas.data;
        fontAtlas.data = dataGrayAlpha;
        fontAtlas.format = GRAY_ALPHA;

        // And finally convert it to a texture
        fontTex.load(fontAtlas);

        // Also delete glyphs
        delete[] glyphs;
    }
}