/*
 * Copyright 2017 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright 2015-2016 Cryptography Research, Inc.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 *
 * Originally written by Mike Hamburg
 */

#ifndef __DECAF_ED448_H__
# define __DECAF_ED448_H__ 1

# include "point_448.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Number of bytes in an EdDSA public key. */
# define DECAF_EDDSA_448_PUBLIC_BYTES 57

/* Number of bytes in an EdDSA private key. */
# define DECAF_EDDSA_448_PRIVATE_BYTES DECAF_EDDSA_448_PUBLIC_BYTES

/* Number of bytes in an EdDSA private key. */
# define DECAF_EDDSA_448_SIGNATURE_BYTES (DECAF_EDDSA_448_PUBLIC_BYTES + \
                                          DECAF_EDDSA_448_PRIVATE_BYTES)

/* Does EdDSA support non-contextual signatures? */
# define DECAF_EDDSA_448_SUPPORTS_CONTEXTLESS_SIGS 0

/* EdDSA encoding ratio. */
# define DECAF_448_EDDSA_ENCODE_RATIO 4

/* EdDSA decoding ratio. */
# define DECAF_448_EDDSA_DECODE_RATIO (4 / 4)

/*
 * EdDSA key generation.  This function uses a different (non-Decaf) encoding.
 *
 * pubkey (out): The public key.
 * privkey (in): The private key.
 */
decaf_error_t decaf_ed448_derive_public_key(
                        uint8_t pubkey [DECAF_EDDSA_448_PUBLIC_BYTES],
                        const uint8_t privkey [DECAF_EDDSA_448_PRIVATE_BYTES]);

/*
 * EdDSA signing.
 *
 * signature (out): The signature.
 * privkey (in): The private key.
 * pubkey (in):  The public key.
 * message (in):  The message to sign.
 * message_len (in):  The length of the message.
 * prehashed (in):  Nonzero if the message is actually the hash of something
 *                  you want to sign.
 * context (in):  A "context" for this signature of up to 255 bytes.
 * context_len (in):  Length of the context.
 *
 * For Ed25519, it is unsafe to use the same key for both prehashed and
 * non-prehashed messages, at least without some very careful protocol-level
 * disambiguation.  For Ed448 it is safe.  The C++ wrapper is designed to make
 * it harder to screw this up, but this C code gives you no seat belt.
 */
decaf_error_t decaf_ed448_sign(
                        uint8_t signature[DECAF_EDDSA_448_SIGNATURE_BYTES],
                        const uint8_t privkey[DECAF_EDDSA_448_PRIVATE_BYTES],
                        const uint8_t pubkey[DECAF_EDDSA_448_PUBLIC_BYTES],
                        const uint8_t *message, size_t message_len,
                        uint8_t prehashed, const uint8_t *context,
                        size_t context_len)
                        __attribute__ ((nonnull(1, 2, 3)));

/*
 * EdDSA signing with prehash.
 *
 * signature (out): The signature.
 * privkey (in): The private key.
 * pubkey (in): The public key.
 * hash (in): The hash of the message.  This object will not be modified by the
 *            call.
 * context (in): A "context" for this signature of up to 255 bytes.  Must be the
 *               same as what was used for the prehash.
 * context_len (in): Length of the context.
 *
 * For Ed25519, it is unsafe to use the same key for both prehashed and
 * non-prehashed messages, at least without some very careful protocol-level
 * disambiguation.  For Ed448 it is safe.  The C++ wrapper is designed to make
 * it harder to screw this up, but this C code gives you no seat belt.
 */
decaf_error_t decaf_ed448_sign_prehash(
                        uint8_t signature[DECAF_EDDSA_448_SIGNATURE_BYTES],
                        const uint8_t privkey[DECAF_EDDSA_448_PRIVATE_BYTES],
                        const uint8_t pubkey[DECAF_EDDSA_448_PUBLIC_BYTES],
                        const uint8_t hash[64],
                        const uint8_t *context,
                        size_t context_len)
                        __attribute__ ((nonnull(1, 2, 3, 4)));

/*
 * EdDSA signature verification.
 *
 * Uses the standard (i.e. less-strict) verification formula.
 *
 * signature (in): The signature.
 * pubkey (in): The public key.
 * message (in): The message to verify.
 * message_len (in): The length of the message.
 * prehashed (in): Nonzero if the message is actually the hash of something you
 *                 want to verify.
 * context (in): A "context" for this signature of up to 255 bytes.
 * context_len (in): Length of the context.
 *
 * For Ed25519, it is unsafe to use the same key for both prehashed and
 * non-prehashed messages, at least without some very careful protocol-level
 * disambiguation.  For Ed448 it is safe.  The C++ wrapper is designed to make
 * it harder to screw this up, but this C code gives you no seat belt.
 */
decaf_error_t decaf_ed448_verify(const uint8_t
                                 signature[DECAF_EDDSA_448_SIGNATURE_BYTES],
                                 const uint8_t
                                 pubkey[DECAF_EDDSA_448_PUBLIC_BYTES],
                                 const uint8_t *message, size_t message_len,
                                 uint8_t prehashed, const uint8_t *context,
                                 uint8_t context_len)
                                 __attribute__ ((nonnull(1, 2)));

/*
 * EdDSA signature verification.
 *
 * Uses the standard (i.e. less-strict) verification formula.
 *
 * signature (in): The signature.
 * pubkey (in): The public key.
 * hash (in): The hash of the message.  This object will not be modified by the
 *            call.
 * context (in): A "context" for this signature of up to 255 bytes.  Must be the
 *               same as what was used for the prehash.
 * context_len (in): Length of the context.
 *
 * For Ed25519, it is unsafe to use the same key for both prehashed and
 * non-prehashed messages, at least without some very careful protocol-level
 * disambiguation.  For Ed448 it is safe.  The C++ wrapper is designed to make
 * it harder to screw this up, but this C code gives you no seat belt.
 */
decaf_error_t decaf_ed448_verify_prehash(
                    const uint8_t signature[DECAF_EDDSA_448_SIGNATURE_BYTES],
                    const uint8_t pubkey[DECAF_EDDSA_448_PUBLIC_BYTES],
                    const uint8_t hash[64],
                    const uint8_t *context,
                    uint8_t context_len)
                    __attribute__ ((nonnull(1, 2)));

/*
 * EdDSA point encoding.  Used internally, exposed externally.
 * Multiplies by DECAF_448_EDDSA_ENCODE_RATIO first.
 *
 * The multiplication is required because the EdDSA encoding represents
 * the cofactor information, but the Decaf encoding ignores it (which
 * is the whole point).  So if you decode from EdDSA and re-encode to
 * EdDSA, the cofactor info must get cleared, because the intermediate
 * representation doesn't track it.
 *
 * The way libdecaf handles this is to multiply by
 * DECAF_448_EDDSA_DECODE_RATIO when decoding, and by
 * DECAF_448_EDDSA_ENCODE_RATIO when encoding.  The product of these
 * ratios is always exactly the cofactor 4, so the cofactor
 * ends up cleared one way or another.  But exactly how that shakes
 * out depends on the base points specified in RFC 8032.
 *
 * The upshot is that if you pass the Decaf/Ristretto base point to
 * this function, you will get DECAF_448_EDDSA_ENCODE_RATIO times the
 * EdDSA base point.
 *
 * enc (out): The encoded point.
 * p (in): The point.
 */
void curve448_point_mul_by_ratio_and_encode_like_eddsa(
                                    uint8_t enc [DECAF_EDDSA_448_PUBLIC_BYTES],
                                    const curve448_point_t p);

/*
 * EdDSA point decoding.  Multiplies by DECAF_448_EDDSA_DECODE_RATIO, and
 * ignores cofactor information.
 *
 * See notes on curve448_point_mul_by_ratio_and_encode_like_eddsa
 *
 * enc (out): The encoded point.
 * p (in): The point.
 */
decaf_error_t curve448_point_decode_like_eddsa_and_mul_by_ratio(
                            curve448_point_t p,
                            const uint8_t enc[DECAF_EDDSA_448_PUBLIC_BYTES]);

/*
 * EdDSA to ECDH public key conversion
 * Deserialize the point to get y on Edwards curve,
 * Convert it to u coordinate on Montgomery curve.
 *
 * This function does not check that the public key being converted is a valid
 * EdDSA public key (FUTURE?)
 *
 * x (out): The ECDH public key as in RFC7748(point on Montgomery curve)
 * ed (in): The EdDSA public key(point on Edwards curve)
 */
void decaf_ed448_convert_public_key_to_x448(
                                uint8_t x[DECAF_X448_PUBLIC_BYTES],
                                const uint8_t ed[DECAF_EDDSA_448_PUBLIC_BYTES]);

/*
 * EdDSA to ECDH private key conversion
 * Using the appropriate hash function, hash the EdDSA private key
 * and keep only the lower bytes to get the ECDH private key
 *
 * x (out): The ECDH private key as in RFC7748
 * ed (in): The EdDSA private key
 */
decaf_error_t decaf_ed448_convert_private_key_to_x448(
                            uint8_t x[DECAF_X448_PRIVATE_BYTES],
                            const uint8_t ed[DECAF_EDDSA_448_PRIVATE_BYTES]);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif                          /* __DECAF_ED448_H__ */
