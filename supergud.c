#include "supergud.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

/**
   encode sha256 hash to unicode
 */
char * supergud_encode(char * shabuff)
{
    char * str = (char *) malloc(SHA256_DIGEST_LENGTH+1);
    str[SHA256_DIGEST_LENGTH] = 0;
    int idx = 0;
    while(idx < SHA256_DIGEST_LENGTH) {
	str[idx] = (shabuff[idx] & (uint8_t) 0xdf | (uint8_t) 0xc1);
	idx ++;
	str[idx] = (shabuff[idx] & (uint8_t) 0xbf | (uint8_t) 0x82);
	idx++;
    }
    return str;
}

// IT'S OVER 9000!!
#define SUPERGUD_ROUNDS 90000

const char * supergud_hash(const char * str, const char * salt)
{
    int secure_trip = 0;
    char * idx = strchr(str, '#');
    if ( idx == NULL ) { return str; } // bail if not tripcode
    if ( ! *(idx+1) ) { return str; } // bail if empty tripcode
    if ( strchr(idx, '#') ) { secure_trip = 1; } // check for secure tripcode

    size_t triplen = strlen(idx);
    size_t saltlen = strlen(salt);
    char shabuff[SHA256_DIGEST_LENGTH];
    bzero(&shabuff, SHA256_DIGEST_LENGTH);

    size_t rounds = SUPERGUD_ROUNDS * triplen;
    do {
	SHA256_CTX sha;
	SHA256_Init(&sha);
	SHA256_Update(&sha, &shabuff, SHA256_DIGEST_LENGTH);
	SHA256_Update(&sha, idx, triplen);
	if (secure_trip) {
	    SHA256_Update(&sha, salt, saltlen);
	}
	SHA256_Final(shabuff, &sha);
    } while(--rounds);
    return supergud_encode(&shabuff);
}

