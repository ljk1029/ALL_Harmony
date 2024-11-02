/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_MD5_H
# define HEADER_MD5_H


# ifdef  __cplusplus
extern "C" {
# endif
/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * ! MD5_LONG has to be at least 32 bits wide.                     !
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
#define MD5_BLOCK_SIZE 64
#define MD5_DIGEST_SIZE 16

typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[MD5_BLOCK_SIZE];
} MD5_CTX;

void md5_init(MD5_CTX *ctx);
void md5_update(MD5_CTX *ctx, const unsigned char *data, size_t len);
void md5_final(MD5_CTX *ctx, unsigned char *digest);
void md5_transform(uint32_t state[4], const unsigned char block[MD5_BLOCK_SIZE]);
# ifdef  __cplusplus
}
# endif
# endif

