/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Generic binary BCH encoding/decoding library
 *
 * Copyright © 2011 Parrot S.A.
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 *
 * Description:
 *
 * This library provides runtime configurable encoding/decoding of binary
 * Bose-Chaudhuri-Hocquenghem (BCH) codes.
*/
#ifndef _BCH_H
#define _BCH_H

#include <stdbool.h>
#include <stdint.h>

#define __bswap_32( value ) \
         ( ( ( (value) & 0x000000ffUL ) << 24 ) |                        \
           ( ( (value) & 0x0000ff00UL ) <<  8 ) |                        \
           ( ( (value) & 0x00ff0000UL ) >>  8 ) |                        \
           ( ( (value) & 0xff000000UL ) >> 24 ) )

extern uint32_t my_htobe32(uint32_t value);

#define kmalloc(size, flags) malloc(size)
#define kfree free
#define GFP_KERNEL 1
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define WARN_ON(...) 0
#define cpu_to_be32 my_htobe32
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef uint8_t  u8;
typedef uint32_t u32;

/**
 * struct bch_control - BCH control structure
 * @m:          Galois field order
 * @n:          maximum codeword size in bits (= 2^m-1)
 * @t:          error correction capability in bits
 * @ecc_bits:   ecc exact size in bits, i.e. generator polynomial degree (<=m*t)
 * @ecc_bytes:  ecc max size (m*t bits) in bytes
 * @a_pow_tab:  Galois field GF(2^m) exponentiation lookup table
 * @a_log_tab:  Galois field GF(2^m) log lookup table
 * @mod8_tab:   remainder generator polynomial lookup tables
 * @ecc_buf:    ecc parity words buffer
 * @ecc_buf2:   ecc parity words buffer
 * @xi_tab:     GF(2^m) base for solving degree 2 polynomial roots
 * @syn:        syndrome buffer
 * @cache:      log-based polynomial representation buffer
 * @elp:        error locator polynomial
 * @poly_2t:    temporary polynomials of degree 2t
 * @swap_bits:  swap bits within data and syndrome bytes
 */
struct bch_control {
	unsigned int    m;
	unsigned int    n;
	unsigned int    t;
	unsigned int    ecc_bits;
	unsigned int    ecc_bytes;
/* private: */
	uint16_t       *a_pow_tab;
	uint16_t       *a_log_tab;
	uint32_t       *mod8_tab;
	uint32_t       *ecc_buf;
	uint32_t       *ecc_buf2;
	unsigned int   *xi_tab;
	unsigned int   *syn;
	int            *cache;
	struct gf_poly *elp;
	struct gf_poly *poly_2t[4];
	bool		swap_bits;
};

struct bch_control *bch_init(int m, int t, unsigned int prim_poly,
			     bool swap_bits);

void bch_free(struct bch_control *bch);

void bch_encode(struct bch_control *bch, const uint8_t *data,
		unsigned int len, uint8_t *ecc);

int bch_decode(struct bch_control *bch, const uint8_t *data, unsigned int len,
	       const uint8_t *recv_ecc, const uint8_t *calc_ecc,
	       const unsigned int *syn, unsigned int *errloc);


static int fls(int x)
{
    int r = 32;

    if (!x)
        return 0;
    if (!(x & 0xffff0000u)) {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u)) {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u)) {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u)) {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u)) {
        x <<= 1;
        r -= 1;
    }
    return r;
}


#endif /* _BCH_H */
