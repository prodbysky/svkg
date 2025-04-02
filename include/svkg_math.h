#ifndef SVKG_MATH_H
#define SVKG_MATH_H

typedef union {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
} SVKG_Vec2;

SVKG_Vec2 SVKG_Vec2_Zero();
SVKG_Vec2 SVKG_Vec2_Make(float x, float y);

SVKG_Vec2 SVKG_Vec2_Add(SVKG_Vec2 v1, SVKG_Vec2 v2);
SVKG_Vec2 SVKG_Vec2_Sub(SVKG_Vec2 v1, SVKG_Vec2 v2);
SVKG_Vec2 SVKG_Vec2_Mul(SVKG_Vec2 v1, SVKG_Vec2 v2);
SVKG_Vec2 SVKG_Vec2_Div(SVKG_Vec2 v1, SVKG_Vec2 v2);

SVKG_Vec2 SVKG_Vec2_Scale(SVKG_Vec2 v1, float v2);
SVKG_Vec2 SVKG_Vec2_Add_Scalar(SVKG_Vec2 v1, float v2);
SVKG_Vec2 SVKG_Vec2_Sub_Scalar(SVKG_Vec2 v1, float v2);

#endif
