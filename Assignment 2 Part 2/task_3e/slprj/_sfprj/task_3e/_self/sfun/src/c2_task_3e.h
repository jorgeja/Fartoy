#ifndef __c2_task_3e_h__
#define __c2_task_3e_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_task_3eInstanceStruct
#define typedef_SFc2_task_3eInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_task_3e;
  real_T (*c2_x_hat)[4];
  real_T *c2_u;
  real_T (*c2_y)[3];
  real_T (*c2_P)[16];
  real_T (*c2_x_hat_dot)[4];
  real_T (*c2_P_dot)[16];
  real_T (*c2_A)[16];
  real_T (*c2_B)[4];
  real_T (*c2_C)[12];
  real_T (*c2_E)[16];
  real_T (*c2_Q)[16];
  real_T (*c2_R_inv)[9];
} SFc2_task_3eInstanceStruct;

#endif                                 /*typedef_SFc2_task_3eInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_task_3e_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_task_3e_get_check_sum(mxArray *plhs[]);
extern void c2_task_3e_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
