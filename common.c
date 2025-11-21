#include "common.h"

void putchar(char ch);


void *memset(void *buf, char c, size_t n) {
    uint8_t *d = (uint8_t *) buf;
    while (n--)
        *d++ = c;
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t *) dst;
    const uint8_t *s = (const uint8_t *) src;
    while (n--)
        *d++ = *s++;
    return dst;
}

char *strcpy(char *dst, const char *src) {
    char *d = dst;
    while (*src)
        *d++ = *src++;
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
    }

    return *(unsigned char *) s1 - *(unsigned char *)s2;
}

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while(*fmt) {
        if (*fmt == '%') {
            fmt++; // Skip '%'
            switch (*fmt) { //Read the next character
                case '\0': // '%' at the end of the format string
                    putchar('%');
                    goto end;
                case '%': // Print '%'
                    putchar('%');
                    break;
                case 's': {
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }

                    break;
                }
                case 'd': { // Print an integer in decimal
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;

                    if (value < 0) {
                        putchar('-');
                        magnitude = -magnitude;
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9)
                        divisor *= 10;

                    while (divisor > 0) {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }

                    break;
                }

                case 'x': { // Print an integer in hexadecimal.
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = (sizeof(unsigned) * 2) - 1; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0x0f;
                        putchar("0123456789abcdef"[nibble]);
                    }

                    break;
                }

                case 'p': { // Print a pointer (address)
                    void *ptr = va_arg(vargs, void *);
                    unsigned long address = (unsigned long)ptr; // Cast pointer to unsigned long
                    putchar('0');
                    putchar('x'); // Prefix for hexadecimal addresses
                    for (int i = (sizeof(void *) * 2) - 1; i >= 0; i--) {
                        unsigned nibble = (address >> (i * 4)) & 0x0f; // Extract each nibble
                        putchar("0123456789abcdef"[nibble]); // Print nibble as hex
                    }
                    break;
                }
            };
        } else {
            putchar(*fmt);
        }

        fmt++;
    }

end:
    va_end(vargs);
}