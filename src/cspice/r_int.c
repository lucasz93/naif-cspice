#include "f2c.h"
#include "fprocs.h"

#ifdef KR_headers
double floor();
double r_int(f2c,x) f2c_state_t *f2c; real *x;
#else
#undef abs
#include "math.h"
double r_int(f2c_state_t *f2c, real *x)
#endif
{
return( (*x>0) ? floor(*x) : -floor(- *x) );
}
