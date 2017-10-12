/* Include files */

#include <stddef.h>
#include "blas.h"
#include "task_3e_sfun.h"
#include "c2_task_3e.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "task_3e_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[15] = { "K", "nargin", "nargout",
  "x_hat", "u", "y", "P", "A", "B", "C", "E", "Q", "R_inv", "x_hat_dot", "P_dot"
};

/* Function Declarations */
static void initialize_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void initialize_params_c2_task_3e(SFc2_task_3eInstanceStruct
  *chartInstance);
static void enable_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void disable_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_task_3e(SFc2_task_3eInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_task_3e(SFc2_task_3eInstanceStruct
  *chartInstance);
static void set_sim_state_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void sf_gateway_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void mdl_start_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_chartstep_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void initSimStructsc2_task_3e(SFc2_task_3eInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance, const
  mxArray *c2_b_P_dot, const char_T *c2_identifier, real_T c2_b_y[16]);
static void c2_b_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[16]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_x_hat_dot, const char_T *c2_identifier, real_T c2_b_y[4]);
static void c2_d_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[4]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_f_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[12]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_b_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_b_u);
static void c2_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_threshold(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_c_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_d_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_e_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_f_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static void c2_g_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_g_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_h_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_task_3e, const char_T *c2_identifier);
static uint8_T c2_i_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_task_3eInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_task_3eInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_task_3e = 0U;
}

static void initialize_params_c2_task_3e(SFc2_task_3eInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_task_3e(SFc2_task_3eInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_task_3e(SFc2_task_3eInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i0;
  real_T c2_b_u[16];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i1;
  real_T c2_c_u[4];
  const mxArray *c2_d_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createcellmatrix(3, 1), false);
  for (c2_i0 = 0; c2_i0 < 16; c2_i0++) {
    c2_b_u[c2_i0] = (*chartInstance->c2_P_dot)[c2_i0];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  sf_mex_setcell(c2_b_y, 0, c2_c_y);
  for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
    c2_c_u[c2_i1] = (*chartInstance->c2_x_hat_dot)[c2_i1];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_setcell(c2_b_y, 1, c2_d_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_task_3e;
  c2_d_u = c2_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_b_y, 2, c2_e_y);
  sf_mex_assign(&c2_st, c2_b_y, false);
  return c2_st;
}

static void set_sim_state_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_b_u;
  real_T c2_dv0[16];
  int32_T c2_i2;
  real_T c2_dv1[4];
  int32_T c2_i3;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_b_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 0)),
                      "P_dot", c2_dv0);
  for (c2_i2 = 0; c2_i2 < 16; c2_i2++) {
    (*chartInstance->c2_P_dot)[c2_i2] = c2_dv0[c2_i2];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 1)),
                        "x_hat_dot", c2_dv1);
  for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
    (*chartInstance->c2_x_hat_dot)[c2_i3] = c2_dv1[c2_i3];
  }

  chartInstance->c2_is_active_c2_task_3e = c2_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_b_u, 2)), "is_active_c2_task_3e");
  sf_mex_destroy(&c2_b_u);
  c2_update_debugger_state_c2_task_3e(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_x_hat)[c2_i4], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_u, 1U);
  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_y)[c2_i5], 2U);
  }

  for (c2_i6 = 0; c2_i6 < 16; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_P)[c2_i6], 3U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_task_3e(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_task_3eMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i7 = 0; c2_i7 < 4; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_x_hat_dot)[c2_i7], 4U);
  }

  for (c2_i8 = 0; c2_i8 < 16; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_P_dot)[c2_i8], 5U);
  }

  for (c2_i9 = 0; c2_i9 < 16; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_A)[c2_i9], 6U);
  }

  for (c2_i10 = 0; c2_i10 < 4; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_B)[c2_i10], 7U);
  }

  for (c2_i11 = 0; c2_i11 < 12; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_C)[c2_i11], 8U);
  }

  for (c2_i12 = 0; c2_i12 < 16; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_E)[c2_i12], 9U);
  }

  for (c2_i13 = 0; c2_i13 < 16; c2_i13++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Q)[c2_i13], 10U);
  }

  for (c2_i14 = 0; c2_i14 < 9; c2_i14++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_R_inv)[c2_i14], 11U);
  }
}

static void mdl_start_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  int32_T c2_i15;
  real_T c2_b_x_hat[4];
  real_T c2_b_u;
  int32_T c2_i16;
  real_T c2_b_y[3];
  int32_T c2_i17;
  real_T c2_b_P[16];
  int32_T c2_i18;
  real_T c2_b_A[16];
  int32_T c2_i19;
  real_T c2_b_B[4];
  int32_T c2_i20;
  real_T c2_b_C[12];
  int32_T c2_i21;
  real_T c2_b_E[16];
  int32_T c2_i22;
  real_T c2_b_Q[16];
  int32_T c2_i23;
  real_T c2_b_R_inv[9];
  uint32_T c2_debug_family_var_map[15];
  real_T c2_K[12];
  real_T c2_nargin = 10.0;
  real_T c2_nargout = 2.0;
  real_T c2_b_x_hat_dot[4];
  real_T c2_b_P_dot[16];
  int32_T c2_i24;
  real_T c2_a[16];
  int32_T c2_i25;
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  real_T c2_b[12];
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_i31;
  real_T c2_c_y[12];
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  real_T c2_b_b[9];
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  int32_T c2_i40;
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  int32_T c2_i48;
  real_T c2_c_b[4];
  int32_T c2_i49;
  real_T c2_d_y[4];
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T c2_b_a[4];
  real_T c2_d_b;
  int32_T c2_i53;
  int32_T c2_i54;
  real_T c2_c_a[12];
  int32_T c2_i55;
  int32_T c2_i56;
  real_T c2_e_y[3];
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  int32_T c2_i66;
  real_T c2_e_b[16];
  int32_T c2_i67;
  int32_T c2_i68;
  int32_T c2_i69;
  real_T c2_f_y[16];
  int32_T c2_i70;
  int32_T c2_i71;
  int32_T c2_i72;
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  real_T c2_g_y[16];
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  int32_T c2_i85;
  int32_T c2_i86;
  real_T c2_h_y[16];
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  int32_T c2_i95;
  real_T c2_i_y[16];
  int32_T c2_i96;
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  int32_T c2_i100;
  int32_T c2_i101;
  int32_T c2_i102;
  int32_T c2_i103;
  int32_T c2_i104;
  int32_T c2_i105;
  int32_T c2_i106;
  int32_T c2_i107;
  int32_T c2_i108;
  int32_T c2_i109;
  int32_T c2_i110;
  int32_T c2_i111;
  int32_T c2_i112;
  int32_T c2_i113;
  int32_T c2_i114;
  int32_T c2_i115;
  int32_T c2_i116;
  int32_T c2_i117;
  int32_T c2_i118;
  int32_T c2_i119;
  int32_T c2_i120;
  int32_T c2_i121;
  int32_T c2_i122;
  int32_T c2_i123;
  int32_T c2_i124;
  int32_T c2_i125;
  int32_T c2_i126;
  int32_T c2_i127;
  int32_T c2_i128;
  int32_T c2_i129;
  int32_T c2_i130;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_u;
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_b_x_hat[c2_i15] = (*chartInstance->c2_x_hat)[c2_i15];
  }

  c2_b_u = c2_hoistedGlobal;
  for (c2_i16 = 0; c2_i16 < 3; c2_i16++) {
    c2_b_y[c2_i16] = (*chartInstance->c2_y)[c2_i16];
  }

  for (c2_i17 = 0; c2_i17 < 16; c2_i17++) {
    c2_b_P[c2_i17] = (*chartInstance->c2_P)[c2_i17];
  }

  for (c2_i18 = 0; c2_i18 < 16; c2_i18++) {
    c2_b_A[c2_i18] = (*chartInstance->c2_A)[c2_i18];
  }

  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    c2_b_B[c2_i19] = (*chartInstance->c2_B)[c2_i19];
  }

  for (c2_i20 = 0; c2_i20 < 12; c2_i20++) {
    c2_b_C[c2_i20] = (*chartInstance->c2_C)[c2_i20];
  }

  for (c2_i21 = 0; c2_i21 < 16; c2_i21++) {
    c2_b_E[c2_i21] = (*chartInstance->c2_E)[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 16; c2_i22++) {
    c2_b_Q[c2_i22] = (*chartInstance->c2_Q)[c2_i22];
  }

  for (c2_i23 = 0; c2_i23 < 9; c2_i23++) {
    c2_b_R_inv[c2_i23] = (*chartInstance->c2_R_inv)[c2_i23];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 15U, 15U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_K, 0U, c2_g_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 1U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 2U, c2_f_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_x_hat, 3U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_u, 4U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_y, 5U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_P, 6U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_A, 7U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_B, 8U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_C, 9U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_E, 10U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_Q, 11U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_R_inv, 12U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_x_hat_dot, 13U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_P_dot, 14U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  for (c2_i24 = 0; c2_i24 < 16; c2_i24++) {
    c2_a[c2_i24] = c2_b_P[c2_i24];
  }

  c2_i25 = 0;
  for (c2_i26 = 0; c2_i26 < 3; c2_i26++) {
    c2_i27 = 0;
    for (c2_i28 = 0; c2_i28 < 4; c2_i28++) {
      c2_b[c2_i28 + c2_i25] = c2_b_C[c2_i27 + c2_i26];
      c2_i27 += 3;
    }

    c2_i25 += 4;
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i29 = 0; c2_i29 < 4; c2_i29++) {
    c2_i30 = 0;
    for (c2_i31 = 0; c2_i31 < 3; c2_i31++) {
      c2_c_y[c2_i30 + c2_i29] = 0.0;
      c2_i32 = 0;
      for (c2_i33 = 0; c2_i33 < 4; c2_i33++) {
        c2_c_y[c2_i30 + c2_i29] += c2_a[c2_i32 + c2_i29] * c2_b[c2_i33 + c2_i30];
        c2_i32 += 4;
      }

      c2_i30 += 4;
    }
  }

  for (c2_i34 = 0; c2_i34 < 9; c2_i34++) {
    c2_b_b[c2_i34] = c2_b_R_inv[c2_i34];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  for (c2_i35 = 0; c2_i35 < 12; c2_i35++) {
    c2_K[c2_i35] = 0.0;
  }

  for (c2_i36 = 0; c2_i36 < 12; c2_i36++) {
    c2_K[c2_i36] = 0.0;
  }

  for (c2_i37 = 0; c2_i37 < 12; c2_i37++) {
    c2_b[c2_i37] = c2_K[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 12; c2_i38++) {
    c2_K[c2_i38] = c2_b[c2_i38];
  }

  c2_threshold(chartInstance);
  for (c2_i39 = 0; c2_i39 < 12; c2_i39++) {
    c2_b[c2_i39] = c2_K[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 12; c2_i40++) {
    c2_K[c2_i40] = c2_b[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 4; c2_i41++) {
    c2_i42 = 0;
    c2_i43 = 0;
    for (c2_i44 = 0; c2_i44 < 3; c2_i44++) {
      c2_K[c2_i42 + c2_i41] = 0.0;
      c2_i45 = 0;
      for (c2_i46 = 0; c2_i46 < 3; c2_i46++) {
        c2_K[c2_i42 + c2_i41] += c2_c_y[c2_i45 + c2_i41] * c2_b_b[c2_i46 +
          c2_i43];
        c2_i45 += 4;
      }

      c2_i42 += 4;
      c2_i43 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  for (c2_i47 = 0; c2_i47 < 16; c2_i47++) {
    c2_a[c2_i47] = c2_b_A[c2_i47];
  }

  for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
    c2_c_b[c2_i48] = c2_b_x_hat[c2_i48];
  }

  c2_c_eml_scalar_eg(chartInstance);
  c2_c_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i49 = 0; c2_i49 < 4; c2_i49++) {
    c2_d_y[c2_i49] = 0.0;
    c2_i50 = 0;
    for (c2_i51 = 0; c2_i51 < 4; c2_i51++) {
      c2_d_y[c2_i49] += c2_a[c2_i50 + c2_i49] * c2_c_b[c2_i51];
      c2_i50 += 4;
    }
  }

  for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
    c2_b_a[c2_i52] = c2_b_B[c2_i52];
  }

  c2_d_b = c2_b_u;
  for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
    c2_b_a[c2_i53] *= c2_d_b;
  }

  for (c2_i54 = 0; c2_i54 < 12; c2_i54++) {
    c2_c_a[c2_i54] = c2_b_C[c2_i54];
  }

  for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
    c2_c_b[c2_i55] = c2_b_x_hat[c2_i55];
  }

  c2_d_eml_scalar_eg(chartInstance);
  c2_d_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i56 = 0; c2_i56 < 3; c2_i56++) {
    c2_e_y[c2_i56] = 0.0;
    c2_i57 = 0;
    for (c2_i58 = 0; c2_i58 < 4; c2_i58++) {
      c2_e_y[c2_i56] += c2_c_a[c2_i57 + c2_i56] * c2_c_b[c2_i58];
      c2_i57 += 3;
    }
  }

  for (c2_i59 = 0; c2_i59 < 12; c2_i59++) {
    c2_b[c2_i59] = c2_K[c2_i59];
  }

  for (c2_i60 = 0; c2_i60 < 3; c2_i60++) {
    c2_e_y[c2_i60] = c2_b_y[c2_i60] - c2_e_y[c2_i60];
  }

  c2_e_eml_scalar_eg(chartInstance);
  c2_e_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i61 = 0; c2_i61 < 4; c2_i61++) {
    c2_c_b[c2_i61] = 0.0;
    c2_i62 = 0;
    for (c2_i63 = 0; c2_i63 < 3; c2_i63++) {
      c2_c_b[c2_i61] += c2_b[c2_i62 + c2_i61] * c2_e_y[c2_i63];
      c2_i62 += 4;
    }
  }

  for (c2_i64 = 0; c2_i64 < 4; c2_i64++) {
    c2_b_x_hat_dot[c2_i64] = (c2_d_y[c2_i64] + c2_b_a[c2_i64]) + c2_c_b[c2_i64];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  for (c2_i65 = 0; c2_i65 < 16; c2_i65++) {
    c2_a[c2_i65] = c2_b_A[c2_i65];
  }

  for (c2_i66 = 0; c2_i66 < 16; c2_i66++) {
    c2_e_b[c2_i66] = c2_b_P[c2_i66];
  }

  c2_f_eml_scalar_eg(chartInstance);
  c2_f_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i67 = 0; c2_i67 < 4; c2_i67++) {
    c2_i68 = 0;
    for (c2_i69 = 0; c2_i69 < 4; c2_i69++) {
      c2_f_y[c2_i68 + c2_i67] = 0.0;
      c2_i70 = 0;
      for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
        c2_f_y[c2_i68 + c2_i67] += c2_a[c2_i70 + c2_i67] * c2_e_b[c2_i71 +
          c2_i68];
        c2_i70 += 4;
      }

      c2_i68 += 4;
    }
  }

  for (c2_i72 = 0; c2_i72 < 16; c2_i72++) {
    c2_a[c2_i72] = c2_b_P[c2_i72];
  }

  c2_i73 = 0;
  for (c2_i74 = 0; c2_i74 < 4; c2_i74++) {
    c2_i75 = 0;
    for (c2_i76 = 0; c2_i76 < 4; c2_i76++) {
      c2_e_b[c2_i76 + c2_i73] = c2_b_A[c2_i75 + c2_i74];
      c2_i75 += 4;
    }

    c2_i73 += 4;
  }

  c2_f_eml_scalar_eg(chartInstance);
  c2_f_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i77 = 0; c2_i77 < 4; c2_i77++) {
    c2_i78 = 0;
    for (c2_i79 = 0; c2_i79 < 4; c2_i79++) {
      c2_g_y[c2_i78 + c2_i77] = 0.0;
      c2_i80 = 0;
      for (c2_i81 = 0; c2_i81 < 4; c2_i81++) {
        c2_g_y[c2_i78 + c2_i77] += c2_a[c2_i80 + c2_i77] * c2_e_b[c2_i81 +
          c2_i78];
        c2_i80 += 4;
      }

      c2_i78 += 4;
    }
  }

  for (c2_i82 = 0; c2_i82 < 16; c2_i82++) {
    c2_a[c2_i82] = c2_b_E[c2_i82];
  }

  for (c2_i83 = 0; c2_i83 < 16; c2_i83++) {
    c2_e_b[c2_i83] = c2_b_Q[c2_i83];
  }

  c2_f_eml_scalar_eg(chartInstance);
  c2_f_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i84 = 0; c2_i84 < 4; c2_i84++) {
    c2_i85 = 0;
    for (c2_i86 = 0; c2_i86 < 4; c2_i86++) {
      c2_h_y[c2_i85 + c2_i84] = 0.0;
      c2_i87 = 0;
      for (c2_i88 = 0; c2_i88 < 4; c2_i88++) {
        c2_h_y[c2_i85 + c2_i84] += c2_a[c2_i87 + c2_i84] * c2_e_b[c2_i88 +
          c2_i85];
        c2_i87 += 4;
      }

      c2_i85 += 4;
    }
  }

  c2_i89 = 0;
  for (c2_i90 = 0; c2_i90 < 4; c2_i90++) {
    c2_i91 = 0;
    for (c2_i92 = 0; c2_i92 < 4; c2_i92++) {
      c2_e_b[c2_i92 + c2_i89] = c2_b_E[c2_i91 + c2_i90];
      c2_i91 += 4;
    }

    c2_i89 += 4;
  }

  c2_f_eml_scalar_eg(chartInstance);
  c2_f_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i93 = 0; c2_i93 < 4; c2_i93++) {
    c2_i94 = 0;
    for (c2_i95 = 0; c2_i95 < 4; c2_i95++) {
      c2_i_y[c2_i94 + c2_i93] = 0.0;
      c2_i96 = 0;
      for (c2_i97 = 0; c2_i97 < 4; c2_i97++) {
        c2_i_y[c2_i94 + c2_i93] += c2_h_y[c2_i96 + c2_i93] * c2_e_b[c2_i97 +
          c2_i94];
        c2_i96 += 4;
      }

      c2_i94 += 4;
    }
  }

  for (c2_i98 = 0; c2_i98 < 16; c2_i98++) {
    c2_a[c2_i98] = c2_b_P[c2_i98];
  }

  c2_i99 = 0;
  for (c2_i100 = 0; c2_i100 < 3; c2_i100++) {
    c2_i101 = 0;
    for (c2_i102 = 0; c2_i102 < 4; c2_i102++) {
      c2_b[c2_i102 + c2_i99] = c2_b_C[c2_i101 + c2_i100];
      c2_i101 += 3;
    }

    c2_i99 += 4;
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i103 = 0; c2_i103 < 4; c2_i103++) {
    c2_i104 = 0;
    for (c2_i105 = 0; c2_i105 < 3; c2_i105++) {
      c2_c_y[c2_i104 + c2_i103] = 0.0;
      c2_i106 = 0;
      for (c2_i107 = 0; c2_i107 < 4; c2_i107++) {
        c2_c_y[c2_i104 + c2_i103] += c2_a[c2_i106 + c2_i103] * c2_b[c2_i107 +
          c2_i104];
        c2_i106 += 4;
      }

      c2_i104 += 4;
    }
  }

  for (c2_i108 = 0; c2_i108 < 9; c2_i108++) {
    c2_b_b[c2_i108] = c2_b_R_inv[c2_i108];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i109 = 0; c2_i109 < 4; c2_i109++) {
    c2_i110 = 0;
    c2_i111 = 0;
    for (c2_i112 = 0; c2_i112 < 3; c2_i112++) {
      c2_b[c2_i110 + c2_i109] = 0.0;
      c2_i113 = 0;
      for (c2_i114 = 0; c2_i114 < 3; c2_i114++) {
        c2_b[c2_i110 + c2_i109] += c2_c_y[c2_i113 + c2_i109] * c2_b_b[c2_i114 +
          c2_i111];
        c2_i113 += 4;
      }

      c2_i110 += 4;
      c2_i111 += 3;
    }
  }

  for (c2_i115 = 0; c2_i115 < 12; c2_i115++) {
    c2_c_a[c2_i115] = c2_b_C[c2_i115];
  }

  c2_g_eml_scalar_eg(chartInstance);
  c2_g_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i116 = 0; c2_i116 < 4; c2_i116++) {
    c2_i117 = 0;
    c2_i118 = 0;
    for (c2_i119 = 0; c2_i119 < 4; c2_i119++) {
      c2_h_y[c2_i117 + c2_i116] = 0.0;
      c2_i120 = 0;
      for (c2_i121 = 0; c2_i121 < 3; c2_i121++) {
        c2_h_y[c2_i117 + c2_i116] += c2_b[c2_i120 + c2_i116] * c2_c_a[c2_i121 +
          c2_i118];
        c2_i120 += 4;
      }

      c2_i117 += 4;
      c2_i118 += 3;
    }
  }

  for (c2_i122 = 0; c2_i122 < 16; c2_i122++) {
    c2_e_b[c2_i122] = c2_b_P[c2_i122];
  }

  c2_f_eml_scalar_eg(chartInstance);
  c2_f_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i123 = 0; c2_i123 < 4; c2_i123++) {
    c2_i124 = 0;
    for (c2_i125 = 0; c2_i125 < 4; c2_i125++) {
      c2_a[c2_i124 + c2_i123] = 0.0;
      c2_i126 = 0;
      for (c2_i127 = 0; c2_i127 < 4; c2_i127++) {
        c2_a[c2_i124 + c2_i123] += c2_h_y[c2_i126 + c2_i123] * c2_e_b[c2_i127 +
          c2_i124];
        c2_i126 += 4;
      }

      c2_i124 += 4;
    }
  }

  for (c2_i128 = 0; c2_i128 < 16; c2_i128++) {
    c2_b_P_dot[c2_i128] = ((c2_f_y[c2_i128] + c2_g_y[c2_i128]) + c2_i_y[c2_i128])
      - c2_a[c2_i128];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i129 = 0; c2_i129 < 4; c2_i129++) {
    (*chartInstance->c2_x_hat_dot)[c2_i129] = c2_b_x_hat_dot[c2_i129];
  }

  for (c2_i130 = 0; c2_i130 < 16; c2_i130++) {
    (*chartInstance->c2_P_dot)[c2_i130] = c2_b_P_dot[c2_i130];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_task_3e(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i131;
  int32_T c2_i132;
  int32_T c2_i133;
  real_T c2_b_inData[16];
  int32_T c2_i134;
  int32_T c2_i135;
  int32_T c2_i136;
  real_T c2_b_u[16];
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i131 = 0;
  for (c2_i132 = 0; c2_i132 < 4; c2_i132++) {
    for (c2_i133 = 0; c2_i133 < 4; c2_i133++) {
      c2_b_inData[c2_i133 + c2_i131] = (*(real_T (*)[16])c2_inData)[c2_i133 +
        c2_i131];
    }

    c2_i131 += 4;
  }

  c2_i134 = 0;
  for (c2_i135 = 0; c2_i135 < 4; c2_i135++) {
    for (c2_i136 = 0; c2_i136 < 4; c2_i136++) {
      c2_b_u[c2_i136 + c2_i134] = c2_b_inData[c2_i136 + c2_i134];
    }

    c2_i134 += 4;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance, const
  mxArray *c2_b_P_dot, const char_T *c2_identifier, real_T c2_b_y[16])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P_dot), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_b_P_dot);
}

static void c2_b_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[16])
{
  real_T c2_dv2[16];
  int32_T c2_i137;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv2, 1, 0, 0U, 1, 0U, 2, 4,
                4);
  for (c2_i137 = 0; c2_i137 < 16; c2_i137++) {
    c2_b_y[c2_i137] = c2_dv2[c2_i137];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_P_dot;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[16];
  int32_T c2_i138;
  int32_T c2_i139;
  int32_T c2_i140;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_b_P_dot = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P_dot), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_b_P_dot);
  c2_i138 = 0;
  for (c2_i139 = 0; c2_i139 < 4; c2_i139++) {
    for (c2_i140 = 0; c2_i140 < 4; c2_i140++) {
      (*(real_T (*)[16])c2_outData)[c2_i140 + c2_i138] = c2_b_y[c2_i140 +
        c2_i138];
    }

    c2_i138 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i141;
  real_T c2_b_inData[4];
  int32_T c2_i142;
  real_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i141 = 0; c2_i141 < 4; c2_i141++) {
    c2_b_inData[c2_i141] = (*(real_T (*)[4])c2_inData)[c2_i141];
  }

  for (c2_i142 = 0; c2_i142 < 4; c2_i142++) {
    c2_b_u[c2_i142] = c2_b_inData[c2_i142];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_x_hat_dot, const char_T *c2_identifier, real_T c2_b_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat_dot), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_b_x_hat_dot);
}

static void c2_d_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[4])
{
  real_T c2_dv3[4];
  int32_T c2_i143;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv3, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i143 = 0; c2_i143 < 4; c2_i143++) {
    c2_b_y[c2_i143] = c2_dv3[c2_i143];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_x_hat_dot;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[4];
  int32_T c2_i144;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_b_x_hat_dot = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat_dot), &c2_thisId,
                        c2_b_y);
  sf_mex_destroy(&c2_b_x_hat_dot);
  for (c2_i144 = 0; c2_i144 < 4; c2_i144++) {
    (*(real_T (*)[4])c2_outData)[c2_i144] = c2_b_y[c2_i144];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i145;
  int32_T c2_i146;
  int32_T c2_i147;
  real_T c2_b_inData[9];
  int32_T c2_i148;
  int32_T c2_i149;
  int32_T c2_i150;
  real_T c2_b_u[9];
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i145 = 0;
  for (c2_i146 = 0; c2_i146 < 3; c2_i146++) {
    for (c2_i147 = 0; c2_i147 < 3; c2_i147++) {
      c2_b_inData[c2_i147 + c2_i145] = (*(real_T (*)[9])c2_inData)[c2_i147 +
        c2_i145];
    }

    c2_i145 += 3;
  }

  c2_i148 = 0;
  for (c2_i149 = 0; c2_i149 < 3; c2_i149++) {
    for (c2_i150 = 0; c2_i150 < 3; c2_i150++) {
      c2_b_u[c2_i150 + c2_i148] = c2_b_inData[c2_i150 + c2_i148];
    }

    c2_i148 += 3;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i151;
  int32_T c2_i152;
  int32_T c2_i153;
  real_T c2_b_inData[12];
  int32_T c2_i154;
  int32_T c2_i155;
  int32_T c2_i156;
  real_T c2_b_u[12];
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i151 = 0;
  for (c2_i152 = 0; c2_i152 < 4; c2_i152++) {
    for (c2_i153 = 0; c2_i153 < 3; c2_i153++) {
      c2_b_inData[c2_i153 + c2_i151] = (*(real_T (*)[12])c2_inData)[c2_i153 +
        c2_i151];
    }

    c2_i151 += 3;
  }

  c2_i154 = 0;
  for (c2_i155 = 0; c2_i155 < 4; c2_i155++) {
    for (c2_i156 = 0; c2_i156 < 3; c2_i156++) {
      c2_b_u[c2_i156 + c2_i154] = c2_b_inData[c2_i156 + c2_i154];
    }

    c2_i154 += 3;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 3, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i157;
  real_T c2_b_inData[3];
  int32_T c2_i158;
  real_T c2_b_u[3];
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i157 = 0; c2_i157 < 3; c2_i157++) {
    c2_b_inData[c2_i157] = (*(real_T (*)[3])c2_inData)[c2_i157];
  }

  for (c2_i158 = 0; c2_i158 < 3; c2_i158++) {
    c2_b_u[c2_i158] = c2_b_inData[c2_i158];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(real_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_b_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_b_y = c2_d0;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout),
    &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i159;
  int32_T c2_i160;
  int32_T c2_i161;
  real_T c2_b_inData[12];
  int32_T c2_i162;
  int32_T c2_i163;
  int32_T c2_i164;
  real_T c2_b_u[12];
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i159 = 0;
  for (c2_i160 = 0; c2_i160 < 3; c2_i160++) {
    for (c2_i161 = 0; c2_i161 < 4; c2_i161++) {
      c2_b_inData[c2_i161 + c2_i159] = (*(real_T (*)[12])c2_inData)[c2_i161 +
        c2_i159];
    }

    c2_i159 += 4;
  }

  c2_i162 = 0;
  for (c2_i163 = 0; c2_i163 < 3; c2_i163++) {
    for (c2_i164 = 0; c2_i164 < 4; c2_i164++) {
      c2_b_u[c2_i164 + c2_i162] = c2_b_inData[c2_i164 + c2_i162];
    }

    c2_i162 += 4;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 4, 3),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_f_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_b_y[12])
{
  real_T c2_dv4[12];
  int32_T c2_i165;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv4, 1, 0, 0U, 1, 0U, 2, 4,
                3);
  for (c2_i165 = 0; c2_i165 < 12; c2_i165++) {
    c2_b_y[c2_i165] = c2_dv4[c2_i165];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_K;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[12];
  int32_T c2_i166;
  int32_T c2_i167;
  int32_T c2_i168;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_K = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_K), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_K);
  c2_i166 = 0;
  for (c2_i167 = 0; c2_i167 < 3; c2_i167++) {
    for (c2_i168 = 0; c2_i168 < 4; c2_i168++) {
      (*(real_T (*)[12])c2_outData)[c2_i168 + c2_i166] = c2_b_y[c2_i168 +
        c2_i166];
    }

    c2_i166 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_task_3e_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 13, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgemm"), "name", "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393330858U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_b_u)
{
  const mxArray *c2_b_y = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 15, 0U, 0U, 0U, 2, 1, strlen
                 (c2_b_u)), false);
  return c2_b_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_b_u)
{
  const mxArray *c2_b_y = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 7, 0U, 0U, 0U, 0), false);
  return c2_b_y;
}

static void c2_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_threshold(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_c_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_d_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_e_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_f_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_g_eml_scalar_eg(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(int32_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_g_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_b_y;
  int32_T c2_i169;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_i169, 1, 6, 0U, 0, 0U, 0);
  c2_b_y = c2_i169;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_b_y;
  SFc2_task_3eInstanceStruct *chartInstance;
  chartInstance = (SFc2_task_3eInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_task_3e, const char_T *c2_identifier)
{
  uint8_T c2_b_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_y = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_task_3e), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_task_3e);
  return c2_b_y;
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_task_3eInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_b_y = c2_u0;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void init_dsm_address_info(SFc2_task_3eInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_task_3eInstanceStruct *chartInstance)
{
  chartInstance->c2_x_hat = (real_T (*)[4])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_u = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c2_y = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_P = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_x_hat_dot = (real_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_P_dot = (real_T (*)[16])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_A = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_B = (real_T (*)[4])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_C = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c2_E = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c2_Q = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c2_R_inv = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_task_3e_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2653244076U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2230147603U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2487902004U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1968759955U);
}

mxArray* sf_c2_task_3e_get_post_codegen_info(void);
mxArray *sf_c2_task_3e_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ZsBXWbqRoGMNjJ65V44iXB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,10,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(4);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_task_3e_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_task_3e_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_task_3e_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_task_3e_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_task_3e_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_task_3e(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[8],T\"P_dot\",},{M[1],M[7],T\"x_hat_dot\",},{M[8],M[0],T\"is_active_c2_task_3e\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_task_3e_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_task_3eInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_task_3eInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _task_3eMachineNumber_,
           2,
           1,
           1,
           0,
           12,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_task_3eMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_task_3eMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _task_3eMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"x_hat");
          _SFD_SET_DATA_PROPS(1,1,1,0,"u");
          _SFD_SET_DATA_PROPS(2,1,1,0,"y");
          _SFD_SET_DATA_PROPS(3,1,1,0,"P");
          _SFD_SET_DATA_PROPS(4,2,0,1,"x_hat_dot");
          _SFD_SET_DATA_PROPS(5,2,0,1,"P_dot");
          _SFD_SET_DATA_PROPS(6,1,1,0,"A");
          _SFD_SET_DATA_PROPS(7,1,1,0,"B");
          _SFD_SET_DATA_PROPS(8,1,1,0,"C");
          _SFD_SET_DATA_PROPS(9,1,1,0,"E");
          _SFD_SET_DATA_PROPS(10,1,1,0,"Q");
          _SFD_SET_DATA_PROPS(11,1,1,0,"R_inv");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,196);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_x_hat);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_u);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c2_y);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c2_P);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c2_x_hat_dot);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c2_P_dot);
        _SFD_SET_DATA_VALUE_PTR(6U, *chartInstance->c2_A);
        _SFD_SET_DATA_VALUE_PTR(7U, *chartInstance->c2_B);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c2_C);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c2_E);
        _SFD_SET_DATA_VALUE_PTR(10U, *chartInstance->c2_Q);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c2_R_inv);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _task_3eMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "0QImnemyB93KBc4QjsAJaB";
}

static void sf_opaque_initialize_c2_task_3e(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_task_3eInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
  initialize_c2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_task_3e(void *chartInstanceVar)
{
  enable_c2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_task_3e(void *chartInstanceVar)
{
  disable_c2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_task_3e(void *chartInstanceVar)
{
  sf_gateway_c2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_task_3e(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_task_3e((SFc2_task_3eInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_task_3e(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_task_3e((SFc2_task_3eInstanceStruct*)chartInfo->chartInstance,
    st);
}

static void sf_opaque_terminate_c2_task_3e(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_task_3eInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_task_3e_optimization_info();
    }

    finalize_c2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_task_3e((SFc2_task_3eInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_task_3e(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c2_task_3e((SFc2_task_3eInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_task_3e(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_task_3e_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,10);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 10; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(895383223U));
  ssSetChecksum1(S,(544760288U));
  ssSetChecksum2(S,(1423466624U));
  ssSetChecksum3(S,(2133601595U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_task_3e(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_task_3e(SimStruct *S)
{
  SFc2_task_3eInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_task_3eInstanceStruct *)utMalloc(sizeof
    (SFc2_task_3eInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_task_3eInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_task_3e;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_task_3e;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_task_3e;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_task_3e;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_task_3e;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_task_3e;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_task_3e;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_task_3e;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_task_3e;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_task_3e;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_task_3e;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_task_3e_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_task_3e(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_task_3e(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_task_3e(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_task_3e_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
