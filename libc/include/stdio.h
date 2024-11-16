#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

// BUG : When called after if statement without {}
#define scprintf(a, ...) {terminal_setcolor(0x0a); printf(a, __VA_ARGS__); terminal_setcolor(0x07);}
#define eprintf(a, ...) {terminal_setcolor(0x0c); printf(a, __VA_ARGS__); terminal_setcolor(0x07);}


#ifdef __cplusplus
}
#endif

#endif
