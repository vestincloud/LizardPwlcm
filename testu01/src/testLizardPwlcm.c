#include "LizardPwlcm.h"

static inline void thisrng_seed(uint64_t seed) { LizardPwlcm_seed(seed); }


static inline uint64_t thisrng() { return LizardPwlcm(); }

const char *name = "LizardPwlcm";

#include "main.h"
