#include <stdio.h>
#include "emmintrin.h"

/*
#define PRINTA(x) {                           \
    int i; \
    printf("\n");                          \
    for(i=0; i<16; ++i)                    \
        printf(#x"[%2d] = %d\n", i, x[i]); \
    }
*/

void printarr(const char *v, const char *txt){
    int i;
    printf("\n");
    for(i=0; i<16; ++i)
        printf("%s[%2d] = %x\n", txt, i, v[i]);
}

void main() {
    int i;
    __m128i v1, v2;
    char a1[16], a2[16];
    int test = 0x12345678;
    char *ptr = (char *)&test;
    // packing data
    v1 = _mm_set_epi16(0, 1, 2, 3, 4, 5, 6, 7);
    v2 = _mm_set_epi32(0xfedc, 0xba98, 0x7654, 0x3210);
    
    // load data
    _mm_storeu_si128((__m128i*)a1, v1);
    _mm_storeu_si128((__m128i*)a2, v2);

    for(i=0; i<4; ++i)
        printf("%d = %x\n", i, (char)ptr[i]);

}
