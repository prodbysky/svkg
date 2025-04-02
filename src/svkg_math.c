#include <svkg_math.h>

SVKG_Vec2 SVKG_Vec2_Zero() { return (SVKG_Vec2){0}; }
SVKG_Vec2 SVKG_Vec2_Make(float x, float y) {
  return (SVKG_Vec2){.x = x, .y = y};
}

SVKG_Vec2 SVKG_Vec2_Add(SVKG_Vec2 v1, SVKG_Vec2 v2) {
  return (SVKG_Vec2){
      .x = v1.x + v2.x,
      .y = v1.y + v2.y,
  };
}
SVKG_Vec2 SVKG_Vec2_Sub(SVKG_Vec2 v1, SVKG_Vec2 v2) {
  return (SVKG_Vec2){
      .x = v1.x - v2.x,
      .y = v1.y - v2.y,
  };
}
SVKG_Vec2 SVKG_Vec2_Mul(SVKG_Vec2 v1, SVKG_Vec2 v2) {
  return (SVKG_Vec2){
      .x = v1.x * v2.x,
      .y = v1.y * v2.y,
  };
}
SVKG_Vec2 SVKG_Vec2_Div(SVKG_Vec2 v1, SVKG_Vec2 v2) {
  return (SVKG_Vec2){
      .x = v1.x / v2.x,
      .y = v1.y / v2.y,
  };
}

SVKG_Vec2 SVKG_Vec2_Scale(SVKG_Vec2 v1, float v2) {
  return (SVKG_Vec2){
      .x = v1.x * v2,
      .y = v1.y * v2,
  };
}
SVKG_Vec2 SVKG_Vec2_Add_Scalar(SVKG_Vec2 v1, float v2) {
  return (SVKG_Vec2){
      .x = v1.x + v2,
      .y = v1.y + v2,
  };
}

SVKG_Vec2 SVKG_Vec2_Sub_Scalar(SVKG_Vec2 v1, float v2) {
  return (SVKG_Vec2){
      .x = v1.x - v2,
      .y = v1.y - v2,
  };
}
