#pragma once

#define COUNTOF(x) (sizeof(x) / sizeof(x[0]))

#define FIX_PI 512
#define FIX_2PI 1024
//#define FROM_DEGREE(x) ((((x) % 360) << 10) / 360)

#define V2f16ZERO(v) (v).x = FIX16(0); (v).y = FIX16(0)
#define V2f32ZERO(v) (v).x = FIX32(0); (v).y = FIX32(0)

#ifndef nullptr
#define nullptr NULL
#endif


