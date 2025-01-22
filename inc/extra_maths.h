#ifndef EXTRA_MATHS_H_
#define EXTRA_MATHS_H_

#include <stdint.h>
#include <string.h>

typedef struct {
    double x;
    double y;
    double z;
} vec3_t;

typedef struct {
    vec3_t coordinate;
    vec3_t forward_toggle;
    vec3_t backward_toggle;
	
	/* How many ticks to stay on this control point */
	uint32_t ticks_to_stay_on;
	
	/* How many ticks to use to transition to the next on. Use 0 for instant */
	uint32_t ticks_speed;
} control_point_t;

typedef struct {
    size_t num_control_points;
    control_point_t * control_points;
} spline_definition_t;


#ifdef __cplusplus
extern "C" {
#endif

void E_MATH_CalculateSplinePoint(const control_point_t * from, const control_point_t * to, const double t, vec3_t * out);
void E_MATH_Lerp3D(const vec3_t * A, const vec3_t * B, const double t, vec3_t * out);

#ifdef __cplusplus
}
#endif

#endif /* EXTRA_MATHS_H_ */
