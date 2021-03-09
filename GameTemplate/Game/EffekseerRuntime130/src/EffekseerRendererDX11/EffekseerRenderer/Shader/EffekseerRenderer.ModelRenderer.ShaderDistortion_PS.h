#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0_level_9_3 /EPS /Fh
//    Shader/EffekseerRenderer.ModelRenderer.ShaderDistortion_PS.h
//    Shader/model_renderer_distortion_PS.fx
//
//
// Buffer Definitions: 
//
// cbuffer $Globals
// {
//
//   float4 g_scale;                    // Offset:    0 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// g_backSampler                     sampler      NA          NA    1        1
// g_backTexture                     texture  float4          2d    1        1
// $Globals                          cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// TEXCOORD                 0   xy          0     NONE  float       
// TEXCOORD                 1   xyzw        1     NONE  float       
// TEXCOORD                 2   xyzw        2     NONE  float   xy w
// TEXCOORD                 3   xyzw        3     NONE  float   xy w
// TEXCOORD                 4   xyzw        4     NONE  float   xy w
// COLOR                    0   xyzw        5     NONE  float   xy w
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c0         cb0             0         1  ( FLT, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s1              t1               
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c1, -1, -0, 1, 0
    def c2, 0.5, -0.5, 0, 1
    dcl t2
    dcl t3
    dcl t4
    dcl t5
    dcl_2d s0
    mul r0.w, t5.w, t5.w
    cmp r0, -r0.w, c1.x, c1.y
    texkill r0
    rcp r0.x, t4.w
    mul r0.xy, r0.x, t4
    rcp r0.z, t3.w
    mad r0.zw, t3.xyxy, r0.z, -r0.xyxy
    rcp r1.w, t2.w
    mad r1.xy, t2, r1.w, -r0
    mul r1.zw, t5.xyxy, c0.x
    mad r0.xy, r1, r1.z, r0
    mad r0.xy, r0.zwzw, r1.w, r0
    add r0.xy, r0, c1.z
    mad r0.xy, r0, c2, c2.zwzw
    texld r0, r0, s0
    mov r0.w, t5.w
    mov oC0, r0

// approximately 17 instruction slots used (1 texture, 16 arithmetic)
ps_4_0
dcl_constantbuffer cb0[1], immediateIndexed
dcl_sampler s1, mode_default
dcl_resource_texture2d (float,float,float,float) t1
dcl_input_ps linear v2.xyw
dcl_input_ps linear v3.xyw
dcl_input_ps linear v4.xyw
dcl_input_ps linear v5.xyw
dcl_output o0.xyzw
dcl_temps 2
eq r0.x, v5.w, l(0.000000)
discard r0.x
div r0.xy, v4.xyxx, v4.wwww
div r0.zw, v3.xxxy, v3.wwww
div r1.xy, v2.xyxx, v2.wwww
mul r1.zw, v5.xxxy, cb0[0].xxxx
add r1.xy, -r0.xyxx, r1.xyxx
mad r1.xy, r1.xyxx, r1.zzzz, r0.xyxx
add r0.xy, -r0.xyxx, r0.zwzz
mad r0.xy, r0.xyxx, r1.wwww, r1.xyxx
add r0.xy, r0.xyxx, l(1.000000, 1.000000, 0.000000, 0.000000)
mul r0.x, r0.x, l(0.500000)
mad r0.z, -r0.y, l(0.500000), l(1.000000)
sample r0.xyzw, r0.xzxx, t1.xyzw, s1
mov o0.xyz, r0.xyzx
mov o0.w, v5.w
ret 
// Approximately 17 instruction slots used
#endif

const BYTE g_PS[] =
{
     68,  88,  66,  67,  29,  34, 
     84, 229, 196, 166, 253, 201, 
     68,  29,   2, 217, 106, 132, 
    252, 204,   1,   0,   0,   0, 
    220,   6,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    244,   1,   0,   0,  84,   4, 
      0,   0, 208,   4,   0,   0, 
    248,   5,   0,   0, 168,   6, 
      0,   0,  65, 111, 110,  57, 
    180,   1,   0,   0, 180,   1, 
      0,   0,   0,   2, 255, 255, 
    128,   1,   0,   0,  52,   0, 
      0,   0,   1,   0,  40,   0, 
      0,   0,  52,   0,   0,   0, 
     52,   0,   1,   0,  36,   0, 
      0,   0,  52,   0,   1,   1, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 255, 255, 
     81,   0,   0,   5,   1,   0, 
     15, 160,   0,   0, 128, 191, 
      0,   0,   0, 128,   0,   0, 
    128,  63,   0,   0,   0,   0, 
     81,   0,   0,   5,   2,   0, 
     15, 160,   0,   0,   0,  63, 
      0,   0,   0, 191,   0,   0, 
      0,   0,   0,   0, 128,  63, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   2,   0,  15, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   3,   0,  15, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   4,   0,  15, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   5,   0,  15, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
      5,   0,   0,   3,   0,   0, 
      8, 128,   5,   0, 255, 176, 
      5,   0, 255, 176,  88,   0, 
      0,   4,   0,   0,  15, 128, 
      0,   0, 255, 129,   1,   0, 
      0, 160,   1,   0,  85, 160, 
     65,   0,   0,   1,   0,   0, 
     15, 128,   6,   0,   0,   2, 
      0,   0,   1, 128,   4,   0, 
    255, 176,   5,   0,   0,   3, 
      0,   0,   3, 128,   0,   0, 
      0, 128,   4,   0, 228, 176, 
      6,   0,   0,   2,   0,   0, 
      4, 128,   3,   0, 255, 176, 
      4,   0,   0,   4,   0,   0, 
     12, 128,   3,   0,  68, 176, 
      0,   0, 170, 128,   0,   0, 
     68, 129,   6,   0,   0,   2, 
      1,   0,   8, 128,   2,   0, 
    255, 176,   4,   0,   0,   4, 
      1,   0,   3, 128,   2,   0, 
    228, 176,   1,   0, 255, 128, 
      0,   0, 228, 129,   5,   0, 
      0,   3,   1,   0,  12, 128, 
      5,   0,  68, 176,   0,   0, 
      0, 160,   4,   0,   0,   4, 
      0,   0,   3, 128,   1,   0, 
    228, 128,   1,   0, 170, 128, 
      0,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,   3, 128, 
      0,   0, 238, 128,   1,   0, 
    255, 128,   0,   0, 228, 128, 
      2,   0,   0,   3,   0,   0, 
      3, 128,   0,   0, 228, 128, 
      1,   0, 170, 160,   4,   0, 
      0,   4,   0,   0,   3, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 160,   2,   0, 238, 160, 
     66,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 128, 
      0,   8, 228, 160,   1,   0, 
      0,   2,   0,   0,   8, 128, 
      5,   0, 255, 176,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      0,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
     88,   2,   0,   0,  64,   0, 
      0,   0, 150,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      1,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      1,   0,   0,   0,  85,  85, 
      0,   0,  98,  16,   0,   3, 
    178,  16,  16,   0,   2,   0, 
      0,   0,  98,  16,   0,   3, 
    178,  16,  16,   0,   3,   0, 
      0,   0,  98,  16,   0,   3, 
    178,  16,  16,   0,   4,   0, 
      0,   0,  98,  16,   0,   3, 
    178,  16,  16,   0,   5,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      2,   0,   0,   0,  24,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  58,  16, 
     16,   0,   5,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  13,   0,   4,   3, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  14,   0,   0,   7, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      4,   0,   0,   0, 246,  31, 
     16,   0,   4,   0,   0,   0, 
     14,   0,   0,   7, 194,   0, 
     16,   0,   0,   0,   0,   0, 
      6,  20,  16,   0,   3,   0, 
      0,   0, 246,  31,  16,   0, 
      3,   0,   0,   0,  14,   0, 
      0,   7,  50,   0,  16,   0, 
      1,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
    246,  31,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,   8, 
    194,   0,  16,   0,   1,   0, 
      0,   0,   6,  20,  16,   0, 
      5,   0,   0,   0,   6, 128, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   8,  50,   0,  16,   0, 
      1,   0,   0,   0,  70,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9,  50,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   8,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
    230,  10,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,   9, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   1,   0,   0,   0, 
     70,   0,  16,   0,   1,   0, 
      0,   0,   0,   0,   0,  10, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,  50,   0, 
      0,  10,  66,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  69,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0, 134,   0,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   1,   0,   0,   0, 
      0,  96,  16,   0,   1,   0, 
      0,   0,  54,   0,   0,   5, 
    114,  32,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,  32,  16,   0, 
      0,   0,   0,   0,  58,  16, 
     16,   0,   5,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     17,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   9,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
     32,   1,   0,   0,   1,   0, 
      0,   0, 164,   0,   0,   0, 
      3,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 255, 255, 
     16,   1,   0,   0, 236,   0, 
      0,   0, 124,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 138,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    152,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 103,  95,  98,  97, 
     99, 107,  83,  97, 109, 112, 
    108, 101, 114,   0, 103,  95, 
     98,  97,  99, 107,  84, 101, 
    120, 116, 117, 114, 101,   0, 
     36,  71, 108, 111,  98,  97, 
    108, 115,   0, 171, 171, 171, 
    152,   0,   0,   0,   1,   0, 
      0,   0, 188,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    212,   0,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
      2,   0,   0,   0, 220,   0, 
      0,   0,   0,   0,   0,   0, 
    103,  95, 115,  99,  97, 108, 
    101,   0,   1,   0,   3,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171, 171, 171,  73,  83, 
     71,  78, 168,   0,   0,   0, 
      6,   0,   0,   0,   8,   0, 
      0,   0, 152,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0, 152,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0, 152,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,  15,  11, 
      0,   0, 152,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,  15,  11, 
      0,   0, 152,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,  15,  11, 
      0,   0, 161,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,  15,  11, 
      0,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  67, 
     79,  76,  79,  82,   0, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171
};
