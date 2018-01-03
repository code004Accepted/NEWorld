#pragma once
#include "Definitions.h"

extern int BLOCKTEXTURE_SIZE, BLOCKTEXTURE_UNITSIZE, filter;
const short BITMAP_ID = 0x4D42;

namespace Textures{

#pragma pack(push)
#pragma pack(1)
    struct TEXTURE_RGB {
        unsigned int sizeX;
        unsigned int sizeY;
        std::unique_ptr<uint8_t[]> buffer;
    };

    struct TEXTURE_RGBA {
        unsigned int sizeX;
        unsigned int sizeY;
        std::unique_ptr<uint8_t[]> buffer;
    };

    struct BITMAPINFOHEADER {
        int biSize = 40, biWidth, biHeight;
        short biPlanes = 1, biBitCount = 24;
        int biCompression = 0, biSizeImage, biXPelsPerMeter = 0, biYPelsPerMeter = 0, biClrUsed = 0, biClrImportant = 0;
    };

    struct BITMAPFILEHEADER {
        short bfType = BITMAP_ID;
        int bfSize;
        short bfReserved1 = 0, bfReserved2 = 0;
        int bfOffBits = 54;
    };
#pragma pack(pop)

    enum BlockTextureID {
        ROCK, GRASS_TOP, GRASS_SIDE, DIRT, STONE, PLANK, WOOD_TOP, WOOD_SIDE, BEDROCK, LEAF,
        GLASS, WATER, LAVA, GLOWSTONE, SAND, CEMENT, ICE, COAL, IRON, TNT, UNKNOWN
    };
    const int NULLBLOCK = 63;

    void Init();
    uint8_t getTextureIndex(Block blockname, uint8_t side);
    double getTexcoordX(item item, uint8_t side);
    double getTexcoordY(item item, uint8_t side);
    void LoadRGBImage(TEXTURE_RGB& tex, const std::string& Filename);
    void LoadRGBAImage(TEXTURE_RGBA& tex, const std::string& Filename, const std::string& MkFilename);

    TextureID LoadRGBTexture(const std::string& Filename);
    TextureID LoadFontTexture(const std::string& Filename);
    TextureID LoadRGBATexture(const std::string& Filename, const std::string& MkFilename);
    TextureID LoadBlock3DTexture(const std::string& Filename, const std::string& MkFilename);

    void SaveRGBImage(const std::string& filename, TEXTURE_RGB& image);

    void Build2DMipmaps(GLenum format, int w, int h, int level, const uint8_t* src);

}
