#include <stdint.h>

#include "aesb.h"

#if defined(__cplusplus)
extern "C"
{
#endif

d_4(uint32_t, t_dec(f,n), sb_data, u0, u1, u2, u3);

void aesb_pseudo_round(const uint8_t *in, uint8_t *out, uint8_t *expandedKey)
{   
	uint32_t b0[4], b1[4];
	const uint32_t  *kp = (uint32_t *) expandedKey;
	state_in(b0, in);
	
	round(fwd_rnd,  b1, b0, kp);
	round(fwd_rnd,  b0, b1, kp + 1 * N_COLS);
	round(fwd_rnd,  b1, b0, kp + 2 * N_COLS);
	round(fwd_rnd,  b0, b1, kp + 3 * N_COLS);
	round(fwd_rnd,  b1, b0, kp + 4 * N_COLS);
	round(fwd_rnd,  b0, b1, kp + 5 * N_COLS);
	round(fwd_rnd,  b1, b0, kp + 6 * N_COLS);
	round(fwd_rnd,  b0, b1, kp + 7 * N_COLS);
	round(fwd_rnd,  b1, b0, kp + 8 * N_COLS);
	round(fwd_rnd,  b0, b1, kp + 9 * N_COLS);

	state_out(out, b0);
}


#if defined(__cplusplus)
}
#endif
