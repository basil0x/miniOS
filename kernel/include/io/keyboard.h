#pragma once

#include <stdint.h>

/* TODO: Alternative key types (ex. numpad ENTER) seem to get e0 sent before them */

uint8_t kb_stat; /* Flags are set in IRQ1 */
uint8_t kb_scancode; /* Scancode is updated in IRQ1 */

#define IS_RELEASED        (kb_scancode & 0x80)
#define IS_PRESSED      (~(kb_scancode & 0x80))

#define STAT_SUPER              (kb_stat & 0x01)
#define STAT_LCTRL              (kb_stat & 0x02)
#define STAT_RCTRL              (kb_stat & 0x04)
#define STAT_LSHIFT             (kb_stat & 0x08)

#define STAT_RSHIFT             (kb_stat & 0x10)
#define STAT_LALT               (kb_stat & 0x20)
#define STAT_RALT               (kb_stat & 0x40)
#define STAT_CAPS               (kb_stat & 0x80)

/* #define IS_KEY_ALPHANUM       () */

/* General macros */

#define IS_SPACE      (0x39 == (kb_scancode & 0x7f))
#define IS_ENTER      (0x1c == (kb_scancode & 0x7f))
#define IS_TAB        (0x0f == (kb_scancode & 0x7f))
#define IS_CAPS       (0x3a == (kb_scancode & 0x7f))
#define IS_BACK       (0x0e == (kb_scancode & 0x7f))  /* Backspace */

#define IS_SUPER      (0x5b == (kb_scancode & 0x7f))  /* Commonly called Meta or Windows key */
#define IS_LCTRL      (0x1d == (kb_scancode & 0x7f))
#define IS_RCTRL      (0x1d == (kb_scancode & 0x7f))
#define IS_LSHIFT     (0x2a == (kb_scancode & 0x7f))

#define IS_RSHIFT     (0x2a == (kb_scancode & 0x7f))
#define IS_LALT       (0x38 == (kb_scancode & 0x7f))
#define IS_RALT       (0x38 == (kb_scancode & 0x7f))
#define IS_CAPS       (0x3a == (kb_scancode & 0x7f))

/* Functions */
void kb_init(void)
{
    kb_stat = 0;
    kb_scancode = 0;

    /* Setup IRQ gate here in future */
}

unsigned char kbdmix[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '+', /*'´' */0, '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '<',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '-',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,  '<',
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdse_shift[128] =
{
    0,  27, '!', '\"', '#', 0 /* shift+4 */, '%', '&', '/', '(',	/* 9 */
  ')', '=', '?', '`', '\b',	/* Backspace */
  '\t',			/* Tab */

 'Q', 'W', 'E', 'R',   /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'A', '\n', /* Enter key */
    0,          /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'O', /* 39 */
 '\'', '>',   0,        /* Left shift */
 '*', 'Z', 'X', 'C', 'V', 'B', 'N',            /* 49 */
  'M', ';', ':', '_',   0,              /* Right shift */

  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   '>',
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdse_alt[128] =
{
    0,  27, 0 /*alt+1*/, '@', 0, '$', 0, 0, '{', '[',	/* 9 */
  ']', '}', '\\', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,  '|',
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
