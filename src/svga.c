/* Copyright (c) 2020 M.A.X. Port Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "svga.h"

#include "wrappers.h"

static SDL_Window *sdlWindow;
static SDL_Renderer *sdlRenderer;
static SDL_Surface *sdlWindowSurface;
static SDL_Surface *sdlPaletteSurface;
static SDL_Texture *sdlTexture;

SDL_Surface *svga_get_screen(void) { return sdlPaletteSurface; }

int init_vesa_mode(int mode, int width, int height, int half) {
    Uint32 flags;

    flags = 0;
    // flags |= SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;

    if ((sdlWindow = SDL_CreateWindow("M.A.X.: Mechanized Assault & Exploration", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, width, height, flags)) == NULL) {
        SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
    }
    if ((sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        SDL_Log("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdlRenderer, width, height);

    sdlWindowSurface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    sdlPaletteSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_INDEX8);
    sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    scr_blit = &vesa_screen_blit;

    scr_size.lrx = width - 1;
    scr_size.lry = height - 1;
    scr_size.ulx = 0;
    scr_size.uly = 0;

    if (0 != SDL_RenderClear(sdlRenderer)) {
        SDL_Log("SDL_RenderClear failed: %s\n", SDL_GetError());
    }
    /** \todo handle return code */
    SDL_RenderPresent(sdlRenderer);

    if (sdlWindowSurface && sdlTexture && sdlPaletteSurface) {
        return 0;
    } else {
        return -1;
    }
}

void get_start_mode(void) {}

void reset_mode(void) {}

void vesa_screen_blit(unsigned char *srcBuf, unsigned int srcW, unsigned int srcH, unsigned int subX, unsigned int subY,
                      unsigned int subW, unsigned int subH, unsigned int dstX, unsigned int dstY) {
    SDL_assert(sdlPaletteSurface && sdlPaletteSurface->format &&
               sdlPaletteSurface->format->BytesPerPixel == sizeof(unsigned char));

    {
        unsigned char *target_pixels =
            &((unsigned char *)sdlPaletteSurface->pixels)[dstX + sdlPaletteSurface->w * dstY];
        unsigned char *source_pixels = &srcBuf[subX + srcW * subY];

        for (int h = 0; h < subH; ++h) {
            memcpy(target_pixels, source_pixels, subW);
            source_pixels += srcW;
            target_pixels += sdlPaletteSurface->w;
        }
    }

    {
        void *pixels;
        int pitch;

        /* Blit 8-bit palette surface onto the window surface that's closer to the texture's format */
        if (SDL_BlitSurface(sdlPaletteSurface, NULL, sdlWindowSurface, NULL) != 0) {
            SDL_Log("SDL_BlitSurface failed: %s\n", SDL_GetError());
        }

        /* Modify the texture's pixels */
        if (SDL_LockTexture(sdlTexture, NULL, &pixels, &pitch) == 0) {
            if (SDL_ConvertPixels(sdlWindowSurface->w, sdlWindowSurface->h, sdlWindowSurface->format->format,
                                  sdlWindowSurface->pixels, sdlWindowSurface->pitch, SDL_PIXELFORMAT_RGBA8888, pixels,
                                  pitch) != 0) {
                SDL_Log("SDL_ConvertPixels failed: %s\n", SDL_GetError());
            }
            SDL_UnlockTexture(sdlTexture);
        }

        /* Make the modified texture visible by rendering it */
        if (SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL) != 0) {
            SDL_Log("SDL_RenderCopy failed: %s\n", SDL_GetError());
        }
        SDL_RenderPresent(sdlRenderer);
    }
}