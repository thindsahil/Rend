typedef struct FRAMEBITMAP {
    BITMAPINFO BitmapInfo;
    void* pixels;
} FRAMEBITMAP;

typedef struct PIXEL32 {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
} PIXEL32;


static void SetPixel(int x, int y, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    PIXEL32* coord = (PIXEL32*) frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * y) + x;
    memcpy_s(coord, sizeof(PIXEL32), &color, sizeof(PIXEL32));

}

static void FillRect(int x, int y, int w, int h, FRAMEBITMAP& frameBuffer, PIXEL32& color) {
    for (int j = y; j < y+h; j++) {
        for (int i = x; i < x+w; i++) {
            PIXEL32* coord = (PIXEL32*)frameBuffer.pixels + (frameBuffer.BitmapInfo.bmiHeader.biWidth * j) + i;
            memcpy_s(coord, sizeof(PIXEL32), &color, sizeof(PIXEL32));
            //SetPixel(i, j, frameBuffer, color); 
        }
    }
}