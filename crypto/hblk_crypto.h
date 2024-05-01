#ifndef HBLK_CRYPTO_H
#define HBLK_CRYPTO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/pem.h>
#include <errno.h>
#include <sys/stat.h>



# define EC_CURVE   NID_secp256k1

/* EC_KEY public key octet string length (using 256-bit curve) */
# define EC_PUB_LEN 65

/* Maximum signature octet string length (using 256-bit curve) */
# define SIG_MAX_LEN    72

# define PRI_FILENAME   "key.pem"
# define PUB_FILENAME   "key_pub.pem"



/**
 * struct sig_s - EC Signature structure
 *
 * @sig: Signature buffer;
 *       the whole space may not be used
 * @len: Actual signature size;
 *       can't exceed SIG_MAX_LEN, therefore stored on a byte
 */

typedef struct sig_s
{
	uint8_t     sig[SIG_MAX_LEN];
	uint8_t     len;
} sig_t;



/* sha256.c */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH]);

/* ec_create.c */
EC_KEY *ec_create(void);

/* ec_to_pub.c */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);

/* ec_from_pub.c */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);

/* ec_save.c */
int ec_save(EC_KEY *key, char const *folder);

/* ec_load.c */
EC_KEY *ec_load(char const *folder);

/* ec_sign.c */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
		 size_t msglen, sig_t *sig);

/* ec_verify.c */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
	      size_t msglen, sig_t const *sig);



#endif /* HBLK_CRYPTO_H */
