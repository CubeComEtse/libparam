#ifndef EXTRA_MATHS_H_
#define EXTRA_MATHS_H_

#include <stdint.h>


typedef struct {
    double x;
    double y;
    double z;
} vec3_t;

typedef struct {
    vec3_t coordinate;
    vec3_t forward_toggle;
    vec3_t backward_toggle;
} control_point_t;

typedef struct {
    int num_control_points;
    control_point_t * control_points;
} spline_definition_t;


#ifdef __cplusplus
extern "C" {
#endif

void E_MATH_CalculateSplinePoint(const spline_definition_t* spline, const double t, vec3_t * out);
void E_MATH_Lerp3D(const vec3_t * A, const vec3_t * B, const double t, vec3_t * out);

#ifdef __cplusplus
}
#endif

#endif /* EXTRA_MATHS_H_ */