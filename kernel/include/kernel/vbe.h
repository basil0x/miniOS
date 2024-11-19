#pragma once

#include <stdint.h>

#define FRAMEBUFFER_WIDTH    1366    // Framebuffer width (in pixels)
#define FRAMEBUFFER_HEIGHT   768    // Framebuffer height (in pixels)
#define PIXEL_SIZE           4      // 4 bytes per pixel (32-bit color)

// This is a simple representation of an 8x8 bitmap font (for simplicity, it's just a few letters)
extern uint8_t font[128][8];  // Font data for ASCII characters (you need to define or load this)

// Function to draw a pixel on the framebuffer
void draw_pixel(uint32_t x, uint32_t y, uint32_t color, framebuffer_tag_t *fb_tag) {
    uint8_t *framebuffer = (uint8_t *)fb_tag->framebuffer_addr;

    // Calculate the pixel's position in memory (x, y) coordinates
    uint32_t pixel_offset = (y * fb_tag->framebuffer_pitch) + (x * (fb_tag->framebuffer_depth / 8));

    // Set the pixel color (assuming 32-bit depth)
    framebuffer[pixel_offset + 0] = (color & 0xFF);        // Blue
    framebuffer[pixel_offset + 1] = ((color >> 8) & 0xFF); // Green
    framebuffer[pixel_offset + 2] = ((color >> 16) & 0xFF); // Red
    framebuffer[pixel_offset + 3] = ((color >> 24) & 0xFF); // Alpha
}

// Function to render a single character at (x, y) position on the framebuffer
void draw_char(uint32_t x, uint32_t y, char c, framebuffer_tag_t *fb_tag) {
    if (c < 32 || c > 127) return;  // Only printable ASCII characters

    // Get the character bitmap from the font (8x8)
    uint8_t *char_bitmap = font[c];

    // Loop through the 8x8 pixels of the character
    for (uint32_t row = 0; row < 8; row++) {
        for (uint32_t col = 0; col < 8; col++) {
            if (char_bitmap[row] & (1 << (7 - col))) {  // If the pixel is set
                draw_pixel(x + col, y + row, 0xFFFFFF, fb_tag);  // Draw white pixel (you can change the color)
            }
        }
    }
}

// Function to print a string at (x, y) position
void print_string(uint32_t x, uint32_t y, const char *str, framebuffer_tag_t *fb_tag) {
    while (*str) {
        draw_char(x, y, *str++, fb_tag);
        x += 8;  // Move x position for the next character (8px wide)
    }
}
