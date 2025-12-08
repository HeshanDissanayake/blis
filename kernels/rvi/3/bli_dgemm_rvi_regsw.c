#include "blis.h"

void bli_dgemm_rvi_regsw2
     (
             dim_t      m,
             dim_t      n,
             dim_t      k,
       const void*      alpha,
       const void*      a,
       const void*      b,
       const void*      beta,
             void*      c, inc_t rs_c, inc_t cs_c,
       const auxinfo_t* data,
       const cntx_t*    cntx
     )
{


      const double* A = (const double*)a;
      const double* B = (const double*)b;
    
	const inc_t rs_a   = bli_cntx_get_blksz_def_dt( BLIS_DOUBLE, BLIS_BBM, cntx ); 
	const inc_t cs_a   = bli_cntx_get_blksz_max_dt( BLIS_DOUBLE, BLIS_MR, cntx ); 

	const inc_t rs_b   = bli_cntx_get_blksz_max_dt( BLIS_DOUBLE, BLIS_NR, cntx ); 
	const inc_t cs_b   = bli_cntx_get_blksz_def_dt( BLIS_DOUBLE, BLIS_BBN, cntx ); 


 printf("in kernle: m=%lu n=%lu k=%lu | alpha=%lf beta=%lf | A=%p B=%p C=%p | rs_a=%ld cs_a=%ld | rs_b=%ld cs_b=%ld |  rs_c=%ld cs_c=%ld | \n",
       (unsigned long)m,
       (unsigned long)n,
       (unsigned long)k,
       *(const double*)alpha,
       a,
       b,
       *(const double*)beta,
       c,
       (long)rs_a,
       (long)cs_a,
       (long)rs_b,
       (long)cs_b,
       (long)rs_c,
       (long)cs_c);

      printf("\n--- A tile (m x k) REAL layout ---\n");
      for (dim_t i = 0; i < m; ++i)
      {
      for (dim_t j = 0; j < k; ++j)
      {
            printf("%8.4lf ", A[i * rs_a + j * cs_a]);
      }
      printf("\n");
      }

      // ---- B tile ----
      printf("\n--- B tile (k x n) REAL layout ---\n");
      for (dim_t i = 0; i < k; ++i)
      {
      for (dim_t j = 0; j < n; ++j)
      {
            printf("%8.4lf ", B[i * rs_b + j * cs_b]);
      }
      printf("\n");
      }


}