#include <stdio.h>
#include "emmintrin.h"
#include "tmmintrin.h"


/*
#define PRINTA(x) {                           \
    int i; \
    printf("\n");                          \
    for(i=0; i<16; ++i)                    \
        printf(#x"[%2d] = %d\n", i, x[i]); \
    }
*/

void printarr(const unsigned char *v, const char *txt){
    int i;
    printf("\n");
    for(i=0; i<16; ++i)
        printf("%s[%2d] = %x\n", txt, i, v[i]);
}

void main() {
    int i;
    __m128i v1, v2, vs;
    char a1[16], a2[16];

    // packing data
    for(i=0; i<16; ++i)
        a1[i] = i;
    v1 = _mm_loadu_si128((__m128i*)a1);

    // shffule data
    vs = _mm_set_epi8(0x0e, 0xff, 0xff, 0xff, 
                      0x0c, 0x0b, 0x05, 0xff, 
                      0x0a, 0x08, 0x0f, 0xf1, 
                      0x03, 0x02, 0xff, 0x01);
    v2 = _mm_shuffle_epi8(v1, vs);

    // load data
    _mm_storeu_si128((__m128i*)a1, v1);
    _mm_storeu_si128((__m128i*)a2, v2);

    printarr(a1, "a1");
    printarr(a2, "a2");

}
