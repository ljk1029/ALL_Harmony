#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aes.h"

// cbc测试
void test_aes_cbc() {
    const unsigned char key[] = "0123456789abcdef";
    unsigned char iv[]        = "abcdef0123456789";
    unsigned char ciphertext[32] = {0};
    unsigned char decrypted_plaintext[32] ={0};
    AES_KEY aes_key, aes_key2;
    AES_set_encrypt_key(key, 128, &aes_key);

    char message[256] = {0};
    printf("Plain Text: ");
    scanf("%s", message);

    // 加密
    AES_cbc_encrypt(message, ciphertext, strlen(message), &aes_key, iv, AES_ENCRYPT);

    printf("\naes_cbc AES_ENCRYPT: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        printf("%.2x", ciphertext[i]);
    }

    // 解密
    AES_set_decrypt_key(key, 128, &aes_key2);
    memcpy(iv, "abcdef0123456789", strlen("abcdef0123456789"));
    printf("\nlen:%ld\n",strlen(ciphertext));
    AES_cbc_encrypt(ciphertext, decrypted_plaintext, strlen(ciphertext), &aes_key2, iv, AES_DECRYPT);
    printf("aes_cbc AES_DECRYPT: %s\n", decrypted_plaintext);
}

// ecb加密测试
void test_aes_ecb() {
    const unsigned char key[] = "0123456789abcdef";
    unsigned char ciphertext[32] = {0};
    unsigned char decrypted_plaintext[32] ={0};
    AES_KEY aes_key, aes_key2;
    AES_set_encrypt_key(key, 128, &aes_key);
   
    char message[256]={0};
    printf("Plain Text: ");
    scanf("%s", message);

    // 加密
    AES_ecb_encrypt(message, ciphertext, &aes_key, AES_ENCRYPT);

    printf("\naes_ebc AES_ENCRYPT: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        printf("%.2x", ciphertext[i]);
    }

    // 解密
    AES_set_decrypt_key(key, 128, &aes_key2);
    printf("\nlen:%ld\n",strlen(ciphertext));
    AES_ecb_encrypt(ciphertext, decrypted_plaintext, &aes_key2, AES_DECRYPT);
    printf("aes_ebc AES_DECRYPT: %s\n", decrypted_plaintext);
}

// cfb加密测试
void test_aes_cfb() {
    const unsigned char key[] = "0123456789abcdef";
    unsigned char iv[]  = "abcdef0123456789";
    unsigned char ciphertext[32] = {0};
    unsigned char decrypted_plaintext[32] ={0};
    int num = 0;
    AES_KEY aes_key, aes_key2;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_set_decrypt_key(key, 128, &aes_key2);
    
    char message[256] = {0};
    printf("Plain Text: ");
    scanf("%s", message);

    // 加密
    AES_cfb128_encrypt(message, ciphertext, strlen(message), &aes_key, iv, &num, AES_ENCRYPT);
    //AES_cfb1_encrypt(message, ciphertext, strlen(message), &aes_key, iv, &num, AES_ENCRYPT);
    //AES_cfb8_encrypt(message, ciphertext, strlen(message), &aes_key, iv, NULL, AES_ENCRYPT);

    printf("\naes_cfb AES_ENCRYPT: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        printf("%.2x", ciphertext[i]);
    }

    // 解密
    memcpy(iv, "abcdef0123456789", strlen("abcdef0123456789"));
    printf("\nlen:%ld\n",strlen(ciphertext));
    num =0;
    AES_cfb128_encrypt(ciphertext, decrypted_plaintext, strlen(ciphertext), &aes_key, iv, &num, AES_DECRYPT);
    //AES_cfb1_encrypt(ciphertext, decrypted_plaintext, strlen(ciphertext), &aes_key, iv, &num, AES_DECRYPT); //运行不成功
    //AES_cfb8_encrypt(ciphertext, decrypted_plaintext, strlen(ciphertext), &aes_key, iv, NULL, AES_DECRYPT);
    printf("aes_cfb AES_DECRYPT: %s\n", decrypted_plaintext);
}

// ofb加密测试
void test_aes_ofb() {
    const unsigned char key[] = "0123456789abcdef";
    unsigned char iv[]  = "abcdef0123456789";
    unsigned char ciphertext[32] = {0};
    unsigned char decrypted_plaintext[32] ={0};
    int num = 0;
    AES_KEY aes_key, aes_key2;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_set_decrypt_key(key, 128, &aes_key2);
    
    char message[256] = {0};
    printf("Plain Text: ");
    scanf("%s", message);

    // 加密
    AES_ofb128_encrypt(message, ciphertext, strlen(message), &aes_key, iv, &num);

    printf("\naes_ofb AES_ENCRYPT: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        printf("%.2x", ciphertext[i]);
    }
    
    // 解密
    memcpy(iv, "abcdef0123456789", strlen("abcdef0123456789"));
    printf("\n%ld\n",strlen(ciphertext));
    num =0;
    AES_ofb128_encrypt(ciphertext, decrypted_plaintext, strlen(ciphertext), &aes_key, iv, &num);
    printf("aes_ofb AES_DECRYPT: %s\n", decrypted_plaintext);
}


int main() {
    test_aes_cbc();
    test_aes_ecb();
    test_aes_cfb();
    test_aes_ofb();
    return 0;
}