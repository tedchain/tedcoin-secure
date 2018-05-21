#ifndef MD5_H
#define MD5_H


#include "md5global.h"

namespace md5
{
	/* MD5 context. */
	typedef struct {
		UINT4 state[4];                                   /* state (ABCD) */
		UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];                         /* input buffer */
	} MD5_CTX;

	static void MD5Init(MD5_CTX * context);
	static void MD5Update( MD5_CTX *context, const unsigned char *input, unsigned int inputLen );
	static void MD5Final ( unsigned char digest[16], MD5_CTX *context );
	static void hmac_md5(const unsigned char* text, int text_len, const unsigned char* key, int key_len, unsigned char *digest);

	
	inline bool md5( unsigned char *input, int ilen, unsigned char output[16] )
	{
		MD5_CTX ctx;

		MD5Init( &ctx );
		MD5Update( &ctx, input, ilen );
		MD5Final( output, &ctx);

		memset( &ctx, 0, sizeof( MD5_CTX) );
		return true;
	}


}

#include "md5_l.inl"

#endif
