/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/

#include "PL/platform_image.h"
#include "PL/platform_filesystem.h"

/*	Ritual's FTX Format	*/

typedef struct FTXHeader {
    PLuint32 width;
    PLuint32 height;
    PLuint32 alpha;
} FTXHeader;

PLresult _plLoadFTXImage(FILE *fin, PLImage *out) {
    plFunctionStart();

    FTXHeader header;
    memset(&header, 0, sizeof(FTXHeader));
    header.width = (PLuint)plGetLittleLong(fin);
    header.height = (PLuint)plGetLittleLong(fin);
    header.alpha = (PLuint)plGetLittleLong(fin);

    memset(out, 0, sizeof(PLImage));
    out->size = (PLuint)(header.width * header.height * 4);
    out->data = new PLbyte*[1];
    out->data[0] = new PLbyte[out->size];

    if (fread(out->data[0], sizeof(uint8_t), out->size, fin) != out->size) {
        return PL_RESULT_FILEREAD;
    }

    out->format = PL_IMAGEFORMAT_RGBA8;
    out->colour_format = PL_COLOURFORMAT_RGBA;
    out->width = (PLuint)header.width;
    out->height = (PLuint)header.height;
    return PL_RESULT_SUCCESS;
}