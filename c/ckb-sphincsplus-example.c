
#ifdef __riscv
#undef CKB_DECLARATION_ONLY
#include "entry.h"
#define CKB_DECLARATION_ONLY
#include "ckb_syscalls.h"
#endif  // __RISCV64__

//
#include <stdio.h>

#include "ckb-sphincsplus.h"

int main() {
  spx_ctx ctx;

  unsigned char block[SPX_N];

  unsigned char addr[SPX_ADDR_BYTES];

  unsigned char pk[SPX_PK_BYTES];
  unsigned char sk[SPX_SK_BYTES];

  unsigned char wots_pk[SPX_WOTS_PK_BYTES];

  unsigned char m[SPX_MLEN];
  unsigned char sm[SPX_BYTES + SPX_MLEN];

  unsigned long long smlen;
  unsigned long long mlen;

  unsigned char fors_sig[SPX_FORS_BYTES];
  unsigned char fors_pk[SPX_FORS_PK_BYTES];
  unsigned char fors_m[SPX_FORS_MSG_BYTES];
  unsigned char mout[SPX_BYTES + SPX_MLEN];

  printf("--thash\n");
  thash(block, block, 1, &ctx, (uint32_t *)addr);

  printf("--crypto_sign_keypair\n");
  // generating keypair
  // crypto_sign_keypair(pk, sk);

  printf("--wots_gen_pkx1\n");
  wots_gen_pkx1(wots_pk, &ctx, (uint32_t *)addr);

  // // signing
  printf("--crypto_sign\n");
  crypto_sign(sm, &smlen, m, SPX_MLEN, sk);
  fors_sign(fors_sig, fors_pk, fors_m, &ctx, (uint32_t *)addr);
  wots_gen_pkx1(wots_pk, &ctx, (uint32_t *)addr);

  // // verify
  crypto_sign_open(mout, &mlen, sm, smlen, pk);

  printf("--end\n");
  return 0;
}
