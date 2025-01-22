#include "extra_maths.h"


/*
 * Calculate a point along a spline definition give a t point.
 * 
 * The spline definition cointains multiple spline coordinates with their 
 * control toggles. 
*/
void E_MATH_CalculateSplinePoint(const control_point_t * from, const control_point_t * to, const double t, vec3_t * out){
    vec3_t a;
    vec3_t b;
    vec3_t c;

    vec3_t d;
    vec3_t e;

    double t_lim = t - (uint32_t)(t);
    E_MATH_Lerp3D(&from->coordinate, &from->forward_toggle, t_lim, &a);
    E_MATH_Lerp3D(&from->forward_toggle, &to->backward_toggle, t_lim, &b);
    E_MATH_Lerp3D(&to->backward_toggle, &to->coordinate, t_lim, &c);

    E_MATH_Lerp3D(&a, &b, t_lim, &d);
    E_MATH_Lerp3D(&b, &c, t_lim, &e);

    E_MATH_Lerp3D(&d, &e, t_lim, out);
}


void E_MATH_Lerp3D(const vec3_t * A, const vec3_t * B, const double t, vec3_t * out){
    out->x = A->x + t * (B->x - A->x);
    out->y = A->y + t * (B->y - A->y);
    out->z = A->z + t * (B->z - A->z);
}