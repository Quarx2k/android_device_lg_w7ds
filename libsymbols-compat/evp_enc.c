/* crypto/evp/evp_enc.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <openssl/mem.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
#ifdef OPENSSL_FIPS
#include <openssl/fips.h>
#endif

#ifdef OPENSSL_FIPS
#define M_do_cipher(ctx, out, in, inl) FIPS_cipher(ctx, out, in, inl)
#else
#define M_do_cipher(ctx, out, in, inl) ctx->cipher->do_cipher(ctx, out, in, inl)
#endif

#define EVP_R_INPUT_NOT_INITIALIZED 111
#define EVP_CIPH_RAND_KEY 0x200


int EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX *ctx, int type, int arg, void *ptr)
{
	int ret;
	if(!ctx->cipher) {
		//EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_NO_CIPHER_SET);
		return 0;
	}

	if(!ctx->cipher->ctrl) {
		//EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_CTRL_NOT_IMPLEMENTED);
		return 0;
	}

	ret = ctx->cipher->ctrl(ctx, type, arg, ptr);
	if(ret == -1) {
		//EVPerr(EVP_F_EVP_CIPHER_CTX_CTRL, EVP_R_CTRL_OPERATION_NOT_IMPLEMENTED);
		return 0;
	}
	return ret;
}

int EVP_CIPHER_CTX_rand_key(EVP_CIPHER_CTX *ctx, unsigned char *key)
	{
	if (ctx->cipher->flags & EVP_CIPH_RAND_KEY)
		return EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_RAND_KEY, 0, key);
	if (RAND_bytes(key, ctx->key_len) <= 0)
		return 0;
	return 1;
	}

int EVP_CIPHER_CTX_copy(EVP_CIPHER_CTX *out, const EVP_CIPHER_CTX *in)
	{
	if ((in == NULL) || (in->cipher == NULL))
		{
		//EVPerr(EVP_F_EVP_CIPHER_CTX_COPY,EVP_R_INPUT_NOT_INITIALIZED);
		return 0;
		}
#ifndef OPENSSL_NO_ENGINE
	/* Make sure it's safe to copy a cipher context using an ENGINE */
	if (in->engine && !ENGINE_init(in->engine))
		{
		//EVPerr(EVP_F_EVP_CIPHER_CTX_COPY,ERR_R_ENGINE_LIB);
		return 0;
		}
#endif

	EVP_CIPHER_CTX_cleanup(out);
	memcpy(out,in,sizeof *out);

	if (in->cipher_data && in->cipher->ctx_size)
		{
		out->cipher_data=OPENSSL_malloc(in->cipher->ctx_size);
		if (!out->cipher_data)
			{
			//EVPerr(EVP_F_EVP_CIPHER_CTX_COPY,ERR_R_MALLOC_FAILURE);
			return 0;
			}
		memcpy(out->cipher_data,in->cipher_data,in->cipher->ctx_size);
		}

	if (in->cipher->flags & EVP_CIPH_CUSTOM_COPY)
		return in->cipher->ctrl((EVP_CIPHER_CTX *)in, EVP_CTRL_COPY, 0, out);
	return 1;
	}
