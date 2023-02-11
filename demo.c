/*

MIT No Attribution

Copyright (c) 2019-2023 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

SPDX-License-Identifier: MIT-0

*/

#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "hagl_hal.h"
#include "hagl.h"
#include "rgb565.h"
#include "fps.h"
#include "aps.h"
#include "font6x9.h"
#include "backend.h"
#include "blit.h"
#include "bitmap.h"

hagl_backend_t *backend;
static fps_instance_t fps;
static aps_instance_t pps;

uint32_t flush_callback(uint32_t interval, void *param)
{
    hagl_flush(backend);
    return interval;
}

uint32_t pps_callback(uint32_t interval, void *param)
{
    printf("Primitives per second: %f\n", *(float *)param);
    return interval;
}

color_t get_random_color()
{
    return hagl_color(backend, rand() % 0xff, rand() % 0xff, rand() % 0xff);
}

void polygon_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();
    int16_t vertices[10] = {x0, y0, x1, y1, x2, y2, x3, y3, x4, y4};

    hagl_draw_polygon(backend, 5, vertices, color);
}

void fill_polygon_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();
    int16_t vertices[10] = {x0, y0, x1, y1, x2, y2, x3, y3, x4, y4};

    hagl_fill_polygon(backend, 5, vertices, color);
}

void circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t color = get_random_color();

    hagl_draw_circle(backend, x0, y0, r, color);
}

void fill_circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t color = get_random_color();

    hagl_fill_circle(backend, x0, y0, r, color);
}

void line_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();

    hagl_draw_line(backend, x0, y0, x1, y1, color);
}

void rectangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();

    hagl_draw_rectangle(backend, x0, y0, x1, y1, color);
}

void fill_rectangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();

    hagl_fill_rectangle(backend, x0, y0, x1, y1, color);
}

void put_character_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    // uint16_t color = get_random_color();
    uint16_t color1 = get_random_color();
    uint16_t color2 = get_random_color();
    wchar_t ascii = rand() % 127;

    // hagl_put_char(backend, ascii, x0, y0, color, font6x9);
    hagl_char_style_t style = {
        .font = font6x9,
        .mode = HAGL_CHAR_MODE_OPAQUE,
        .background_color = color1,
        .foreground_color = color2,
        .scale_x_numerator = 1 + (rand() % 4),
        .scale_x_denominator = 1,
        .scale_y_numerator = 1 + (rand() % 4),
        .scale_y_denominator = 1,
    };
    hagl_put_char_styled(backend, ascii, x0, y0, &style);
}

void put_text_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    // uint16_t color = get_random_color();
    uint16_t color1 = get_random_color();
    uint16_t color2 = get_random_color();

    // hagl_put_text(backend, L"YO! MTV raps.", x0, y0, color, font6x9);
    hagl_char_style_t style = {
        .font = font6x9,
        .mode = HAGL_CHAR_MODE_TRANSPARENT,
        .background_color = color1,
        .foreground_color = color2,
        .scale_x_numerator = 1 + (rand() % 4),
        .scale_x_denominator = 1,
        .scale_y_numerator = 1 + (rand() % 4),
        .scale_y_denominator = 1,
    };
    hagl_put_text_styled(backend, L"YO! MTV raps.", x0, y0, &style);
}

void put_pixel_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();

    hagl_put_pixel(backend, x0, y0, color);
}

void triangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();

    hagl_draw_triangle(backend, x0, y0, x1, y1, x2, y2, color);
}

void fill_triangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t color = get_random_color();

    hagl_fill_triangle(backend, x0, y0, x1, y1, x2, y2, color);
}

void blit_demo()
{
    static uint8_t buffer[1024];
    static hagl_bitmap_t bitmap;
    color_t color = get_random_color();
    int zoom = 1 + rand() % 4;
    bitmap.buffer = buffer;
    hagl_get_glyph(backend, (wchar_t)('A' + rand() % 26), color, &bitmap, font6x9);
    // printf(
    //     "color=%06x width=%d, height=%d, depth=%d, pitch=%d, buffer=%p, size=%d\n", 
    //     color, bitmap.width, bitmap.height, bitmap.depth, bitmap.pitch, bitmap.buffer, bitmap.size
    // );
    // hagl_put_char(backend, 'X', rand() % backend->width, rand() % backend->height, color, font6x9);
    // hagl_blit_xy_transparent(backend, rand() % backend->width, rand() % backend->height, &bitmap, 0);
    hagl_blit_xywh_transparent(backend, rand() % backend->width, rand() % backend->height, 6 * zoom, 9 * zoom, &bitmap, 0);
    // hagl_blit_xywh      (backend, rand() % backend->width, rand() % backend->height, 48, 72, &bitmap);
}

void rgb_demo()
{
    uint16_t red = rgb565(255, 0, 0);
    uint16_t green = rgb565(0, 255, 0);
    uint16_t blue = rgb565(0, 0, 255);
    int16_t x0 = 0;
    int16_t x1 = backend->width / 3;
    int16_t x2 = 2 * x1;

    hagl_fill_rectangle(backend, x0, 0, x1 - 1, backend->height, red);
    hagl_fill_rectangle(backend, x1, 0, x2 - 1, backend->height, green);
    hagl_fill_rectangle(backend, x2, 0, backend->width, backend->height, blue);
}

int main()
{
    backend = hagl_init();
    // pod_set_clip_window(0, 30, 319, 210);
    srand(time(0));

    uint32_t flush_delay = 1000 / 30; /* 30 fps */
    uint32_t pps_delay = 2000;        /* 0.5 fps */
    uint16_t current_demo = 0;
    float current_pps = 0.0; /* primitives per second */

    SDL_TimerID pps_id;
    SDL_TimerID flush_id;

    flush_id = SDL_AddTimer(flush_delay, flush_callback, NULL);
    pps_id = SDL_AddTimer(pps_delay, pps_callback, &pps.current);

    bool quit = false;
    SDL_Event event;

    // void (*demo[1])();
    // demo[0] = blit_demo;

    void (*demo[14])();
    demo[0] = rgb_demo;
    demo[1] = put_character_demo;
    demo[2] = put_pixel_demo;
    demo[3] = fill_triangle_demo;
    demo[4] = triangle_demo;
    demo[5] = fill_rectangle_demo;
    demo[6] = rectangle_demo;
    demo[7] = line_demo;
    demo[8] = circle_demo;
    demo[9] = fill_circle_demo;
    demo[10] = polygon_demo;
    demo[11] = fill_polygon_demo;
    demo[12] = put_text_demo;
    demo[13] = blit_demo;

    printf("\n");
    printf("Press any key to change demo.\n");
    printf("Press ESC to quit.\n\n");

    aps_init(&pps);

    while (!quit)
    {
        // hagl_flush(backend);
        (*demo[current_demo])();
        aps_update(&pps, 1);
        // SDL_Delay(100);
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (SDLK_ESCAPE == event.key.keysym.sym)
                {
                    quit = true;
                }
                else
                {
                    aps_reset(&pps);
                    hagl_clear(backend);
                    current_demo = (current_demo + 1) % 14;
                }
            }
        }
    }

    SDL_RemoveTimer(flush_id);
    SDL_RemoveTimer(pps_id);
    hagl_close(backend);
    return 0;
}
