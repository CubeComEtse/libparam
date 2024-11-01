#include "extra_maths.h"


/*
 * Calculate a point along a spline definition give a t point.
 * 
 * The spline definition cointains multiple spline coordinates with their 
 * control toggles. 
*/
void E_MATH_CalculateSplinePoint(const spline_definition_t* spline, const double t, vec3_t * out){
    // First, calulate which spline points we are using from the t parameters
    uint32_t start_index = ((uint32_t) t) % spline->num_control_points;
    uint32_t end_point = (((uint32_t) t) + 1) % spline->num_control_points;

    vec3_t * A = &spline->control_points[start_index].coordinate;
    vec3_t * B = &spline->control_points[start_index].forward_toggle;
    vec3_t * C = &spline->control_points[end_point].backward_toggle;
    vec3_t * D = &spline->control_points[end_point].coordinate;

    vec3_t a;
    vec3_t b;
    vec3_t c;

    vec3_t d;
    vec3_t e;

    double t_lim = t - (uint32_t)(t);
    E_MATH_Lerp3D(A, B, t_lim, &a);
    E_MATH_Lerp3D(B, C, t_lim, &b);
    E_MATH_Lerp3D(C, D, t_lim, &c);

    E_MATH_Lerp3D(&a, &b, t_lim, &d);
    E_MATH_Lerp3D(&b, &c, t_lim, &e);

    E_MATH_Lerp3D(&d, &e, t_lim, out);
}


void E_MATH_Lerp3D(const vec3_t * A, const vec3_t * B, const double t, vec3_t * out){
    out->x = A->x + t * (B->x - A->x);
    out->y = A->y + t * (B->y - A->y);
    out->z = A->z + t * (B->z - A->z);
}