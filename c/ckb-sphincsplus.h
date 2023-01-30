

#include <stdint.h>

#include "context.h"
#include "params.h"
#include "utils.h"
#include "thash.h"

//
// #include "thash_shake_robust.c"

// //
#include "api.h"
#include "wotsx1.h"
#include "fors.h"

#define SPX_MLEN 32

void wots_gen_pkx1(unsigned char *pk, const spx_ctx *ctx,
                          uint32_t addr[8]) {
  struct leaf_info_x1 leaf;
  unsigned steps[SPX_WOTS_LEN] = {0};
  INITIALIZE_LEAF_INFO_X1(leaf, addr, steps);
  wots_gen_leafx1(pk, ctx, 0, &leaf);
}

