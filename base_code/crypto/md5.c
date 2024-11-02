#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef unsigned int UINT4;
void md5_encode(unsigned char *output, const uint32_t *input, size_t len);
void md5_decode(uint32_t *output, const unsigned char *input, size_t len);

#define MD5_BLOCK_SIZE 64
#define MD5_DIGEST_SIZE 16

typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[MD5_BLOCK_SIZE];
} MD5_CTX;

static unsigned char padding[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const unsigned int T[] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
    0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
    0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
    0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
    0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
    0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
    0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 
};

const unsigned int s[] = { 
    7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
    5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
    4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
    6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

/*
* F, G, H and I are basic MD5 functions.
*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/*
* ROTATE_LEFT rotates x left n bits.
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/*
* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4. Rotation is
* separate from addition to prevent recomputation.
*/
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }



void md5_init(MD5_CTX *ctx) {
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;

    ctx->count[0] = 0;
    ctx->count[1] = 0;
}

void md5_update(MD5_CTX *ctx, const unsigned char *data, size_t len) {
    uint32_t i, index, partLen;

    index = (ctx->count[0] >> 3) & 0x3F;

    ctx->count[0] += len << 3;
    if (ctx->count[0] < (len << 3))
        ctx->count[1]++;
    ctx->count[1] += len >> 29;

    partLen = 64 - index;

    if (len >= partLen) {
        memcpy(&ctx->buffer[index], data, partLen);
        md5_transform(ctx->state, ctx->buffer);

        for (i = partLen; i + 63 < len; i += 64) {
            md5_transform(ctx->state, &data[i]);
        }

        index = 0;
    } else {
        i = 0;
    }

    memcpy(&ctx->buffer[index], &data[i], len - i);
}

void md5_final(MD5_CTX *ctx, unsigned char *digest) {
    unsigned char bits[8];
    uint32_t index, padLen;

    md5_encode(bits, ctx->count, 8);

    index = (ctx->count[0] >> 3) & 0x3F;
    padLen = (index < 56) ? (56 - index) : (120 - index);

    md5_update(ctx, padding, padLen);
    md5_update(ctx, bits, 8);

    md5_encode(digest, ctx->state, MD5_DIGEST_SIZE);
}

void md5_transform(uint32_t state[4], const unsigned char block[MD5_BLOCK_SIZE]) {
    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t x[16];

    md5_decode(x, block, MD5_BLOCK_SIZE);

    // Round 1
    FF(a, b, c, d, x[0],  7,  0xD76AA478);
    FF(d, a, b, c, x[1],  12, 0xE8C7B756);
    FF(c, d, a, b, x[2],  17, 0x242070DB);
    FF(b, c, d, a, x[3],  22, 0xC1BDCEEE);
    FF(a, b, c, d, x[4],  7,  0xF57C0FAF);
    FF(d, a, b, c, x[5],  12, 0x4787C62A);
    FF(c, d, a, b, x[6],  17, 0xA8304613);
    FF(b, c, d, a, x[7],  22, 0xFD469501);
    FF(a, b, c, d, x[8],  7,  0x698098D8);
    FF(d, a, b, c, x[9],  12, 0x8B44F7AF);
    FF(c, d, a, b, x[10], 17, 0xFFFF5BB1);
    FF(b, c, d, a, x[11], 22, 0x895CD7BE);
    FF(a, b, c, d, x[12], 7,  0x6B901122);
    FF(d, a, b, c, x[13], 12, 0xFD987193);
    FF(c, d, a, b, x[14], 17, 0xA679438E);
    FF(b, c, d, a, x[15], 22, 0x49B40821);

    // Round 2
    GG(a, b, c, d, x[1],  5, 0xF61E2562);
    GG(d, a, b, c, x[6],  9, 0xC040B340);
    GG(c, d, a, b, x[11], 14, 0x265E5A51);
    GG(b, c, d, a, x[0],  20, 0xE9B6C7AA);
    GG(a, b, c, d, x[5],  5, 0xD62F105D);
    GG(d, a, b, c, x[10], 9, 0x02441453);
    GG(c, d, a, b, x[15], 14, 0xD8A1E681);
    GG(b, c, d, a, x[4],  20, 0xE7D3FBC8);
    GG(a, b, c, d, x[9],  5, 0x21E1CDE6);
    GG(d, a, b, c, x[14], 9, 0xC33707D6);
    GG(c, d, a, b, x[3],  14, 0xF4D50D87);
    GG(b, c, d, a, x[8],  20, 0x455A14ED);
    GG(a, b, c, d, x[13], 5, 0xA9E3E905);
    GG(d, a, b, c, x[2],  9, 0xFCEFA3F8);
    GG(c, d, a, b, x[7],  14, 0x676F02D9);
    GG(b, c, d, a, x[12], 20, 0x8D2A4C8A);

    // Round 3
    HH(a, b, c, d, x[5],  4,  0xFFFA3942);
    HH(d, a, b, c, x[8],  11, 0x8771F681);
    HH(c, d, a, b, x[11], 16, 0x6D9D6122);
    HH(b, c, d, a, x[14], 23, 0xFDE5380C);
    HH(a, b, c, d, x[1],  4,  0xA4BEEA44);
    HH(d, a, b, c, x[4],  11, 0x4BDECFA9);
    HH(c, d, a, b, x[7],  16, 0xF6BB4B60);
    HH(b, c, d, a, x[10], 23, 0xBEBFBC70);
    HH(a, b, c, d, x[13], 4,  0x289B7EC6);
    HH(d, a, b, c, x[0],  11, 0xEAA127FA);
    HH(c, d, a, b, x[3],  16, 0xD4EF3085);
    HH(b, c, d, a, x[6],  23, 0x04881D05);
    HH(a, b, c, d, x[9],  4,  0xD9D4D039);
    HH(d, a, b, c, x[12], 11, 0xE6DB99E5);
    HH(c, d, a, b, x[15], 16, 0x1FA27CF8);
    HH(b, c, d, a, x[2],  23, 0xC4AC5665);

    // Round 4
    II(a, b, c, d, x[0],  6,  0xF4292244);
    II(d, a, b, c, x[7],  10, 0x432AFF97);
    II(c, d, a, b, x[14], 15, 0xAB9423A7);
    II(b, c, d, a, x[5],  21, 0xFC93A039);
    II(a, b, c, d, x[12], 6,  0x655B59C3);
    II(d, a, b, c, x[3],  10, 0x8F0CCC92);
    II(c, d, a, b, x[10], 15, 0xFFEFF47D);
    II(b, c, d, a, x[1],  21, 0x85845DD1);
    II(a, b, c, d, x[8],  6,  0x6FA87E4F);
    II(d, a, b, c, x[15], 10, 0xFE2CE6E0);
    II(c, d, a, b, x[6],  15, 0xA3014314);
    II(b, c, d, a, x[13], 21, 0x4E0811A1);
    II(a, b, c, d, x[4],  6,  0xF7537E82);
    II(d, a, b, c, x[11], 10, 0xBD3AF235);
    II(c, d, a, b, x[2],  15, 0x2AD7D2BB);
    II(b, c, d, a, x[9],  21, 0xEB86D391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void md5_encode(unsigned char *output, const uint32_t *input, size_t len) {
    size_t i, j;

    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
    }
}

void md5_decode(uint32_t *output, const unsigned char *input, size_t len) {
    size_t i, j;

    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[i] = input[j] |
                    (input[j + 1] << 8) |
                    (input[j + 2] << 16) |
                    (input[j + 3] << 24);
    }
}



int main() {
    MD5_CTX ctx;
    unsigned char digest[MD5_DIGEST_SIZE];
    char message[256];
    printf("Plain Text: ");
    scanf("%s", message);

    md5_init(&ctx);
    md5_update(&ctx, (unsigned char *)message, strlen(message));
    md5_final(&ctx, digest);

    printf("\n");
    printf("MD5 Digest: ");
    for (int i = 0; i < MD5_DIGEST_SIZE; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}
