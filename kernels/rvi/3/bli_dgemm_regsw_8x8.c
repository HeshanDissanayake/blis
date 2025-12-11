#include "blis.h"

void bli_dgemm_regsw2_8x8
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
      double*       C = (double*)c;

	const inc_t rs_a   = bli_cntx_get_blksz_def_dt( BLIS_DOUBLE, BLIS_BBM, cntx ); 
	const inc_t cs_a   = bli_cntx_get_blksz_max_dt( BLIS_DOUBLE, BLIS_MR, cntx ); 

	const inc_t rs_b   = bli_cntx_get_blksz_max_dt( BLIS_DOUBLE, BLIS_NR, cntx ); 
	const inc_t cs_b   = bli_cntx_get_blksz_def_dt( BLIS_DOUBLE, BLIS_BBN, cntx ); 


//  printf("in kernle: m=%lu n=%lu k=%lu | alpha=%lf beta=%lf | A=%p B=%p C=%p | rs_a=%ld cs_a=%ld | rs_b=%ld cs_b=%ld |  rs_c=%ld cs_c=%ld | \n",
//        (unsigned long)m,
//        (unsigned long)n,
//        (unsigned long)k,
//        *(const double*)alpha,
//        a,
//        b,
//        *(const double*)beta,
//        c,
//        (long)rs_a,
//        (long)cs_a,
//        (long)rs_b,
//        (long)cs_b,
//        (long)rs_c,
//        (long)cs_c);

      // printf("\n--- A tile (m x k) REAL layout ---\n");
      // for (dim_t i = 0; i < m; ++i)
      // {
      // for (dim_t j = 0; j < k; ++j)
      // {
      //       printf("%8.4lf ", A[i * rs_a + j * cs_a]);
      // }
      // printf("\n");
      // }



      // // ---- B tile ----
      // printf("\n--- B tile (k x n) REAL layout ---\n");
      // for (dim_t i = 0; i < k; ++i)
      // {
      // for (dim_t j = 0; j < n; ++j)
      // {
      //       printf("%8.4lf ", B[i * rs_b + j * cs_b]);
      // }
      // printf("\n");
      // }  

      
      __asm__ volatile ( 
"fmv.d.x  f7, x0\n"
"fmv.d.x  f8, x0\n"
"fmv.d.x  f9, x0\n"
"fmv.d.x  f10, x0\n"
"fmv.d.x  f11, x0\n"
"fmv.d.x  f12, x0\n"
"fmv.d.x  f13, x0\n"
"fmv.d.x  f14, x0\n"
"fmv.d.x  f15, x0\n"
"fmv.d.x  f16, x0\n"
"fmv.d.x  f17, x0\n"
"fmv.d.x  f18, x0\n"
"fmv.d.x  f19, x0\n"
"fmv.d.x  f20, x0\n"
"fmv.d.x  f21, x0\n"
"fmv.d.x  f22, x0\n"

             :
             :
             : 
             );


         for (int ik = 0; ik < k; ik++) {
                double *a = A+ik*cs_a;
                double *b = B+ik*rs_b;

            // printf("A = %6.2f, %6.2f, %6.2f, %6.2f\n", a[0], a[1], a[2], a[3]);
            // printf("B = %6.2f, %6.2f, %6.2f, %6.2f\n\n", b[0], b[1], b[2], b[3]);

 __asm__ volatile ( 
                 

"fld f3, 0(%1)\n"
"fld f4, 8(%1)\n"
"fld f5, 16(%1)\n"
"fld f6, 24(%1)\n"
 
"fld f1, 0(%0)\n"
"fmul.d f2, f1, f3\n"
"fadd.d f7, f2, f7\n"
"fmul.d f2, f1, f4\n"
"fadd.d f8, f2, f8\n"
"fmul.d f2, f1, f5\n"
"fadd.d f9, f2, f9\n"
"fmul.d f2, f1, f6\n"
"fadd.d f10, f2, f10\n"
 
"fld f1, 8(%0)\n"
"fmul.d f2, f1, f3\n"
"fadd.d f11, f2, f11\n"
"fmul.d f2, f1, f4\n"
"fadd.d f12, f2, f12\n"
"fmul.d f2, f1, f5\n"
"fadd.d f13, f2, f13\n"
"fmul.d f2, f1, f6\n"
"fadd.d f14, f2, f14\n"
 
"fld f1, 16(%0)\n"
"fmul.d f2, f1, f3\n"
"fadd.d f15, f2, f15\n"
"fmul.d f2, f1, f4\n"
"fadd.d f16, f2, f16\n"
"fmul.d f2, f1, f5\n"
"fadd.d f17, f2, f17\n"
"fmul.d f2, f1, f6\n"
"fadd.d f18, f2, f18\n"
 
"fld f1, 24(%0)\n"
"fmul.d f2, f1, f3\n"
"fadd.d f19, f2, f19\n"
"fmul.d f2, f1, f4\n"
"fadd.d f20, f2, f20\n"
"fmul.d f2, f1, f5\n"
"fadd.d f21, f2, f21\n"
"fmul.d f2, f1, f6\n"
"fadd.d f22, f2, f22\n"



                    ::"r"(a), "r"(b):);
           
            }


 __asm__ volatile ( 
"fsd f7, 0(%0)\n"
"fsd f8, 8(%0)\n"
"fsd f9, 16(%0)\n"
"fsd f10, 24(%0)\n"
"fsd f11, 0(%1)\n"
"fsd f12, 8(%1)\n"
"fsd f13, 16(%1)\n"
"fsd f14, 24(%1)\n"
"fsd f15, 0(%2)\n"
"fsd f16, 8(%2)\n"
"fsd f17, 16(%2)\n"
"fsd f18, 24(%2)\n"
"fsd f19, 0(%3)\n"
"fsd f20, 8(%3)\n"
"fsd f21, 16(%3)\n"
"fsd f22, 24(%3)\n"

             :
             :"r"(C),"r"(C+rs_c), "r"(C+rs_c*2), "r"(C+rs_c*3) 
             : 
             );

    
      // for(int kk =0; kk < k; kk++){
      //       for (dim_t i=0; i<m; i++){
      //             for(dim_t j=0; j<n; j++){
      //                   C[i*rs_c + j*cs_c] += A[i*rs_a + kk*cs_a] * B[kk*rs_b + j*cs_b];
      //                   // printf("C[%d,%d] A:%8.4lf B:%8.4lf \n",i,j ,A[i*rs_a + kk*cs_a] , B[kk*rs_b + j*cs_b]);
      //             }
      //       }
      // }


      
}