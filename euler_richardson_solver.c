/*
 * Solves the damped and driven pendulum ordinary differential equation 
 * numerically using the Euler-Richardson method
 * 
 * Input:
 * 
 * struct parameters
 * 
 * Output: 
 * float t: time
 * float x: angular position
 * float v: angular speed
 * float theta: angular position in [-pi, pi]
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;                /* angular position */
    float v;                /* angular speed */
    float omega_0;          /* natural frequency of pendulum */
    float damping_constant; /* pendulum damping constant */
    float amplitude;        /* pendulum driving force amplitude */
    float omega;            /* pendulum driving force frequency  */
    float delta_t;          /* time step for integration */
    float t_max;            /* maximum time */
} parameters;

double
acceleration(parameters param, float t) {
    return (
        -param.omega_0 * param.omega_0 * sin(param.x) - param.damping_constant * param.v - 2 * param.amplitude * cos(param.omega * t) * sin(param.x));
}

int main(int argc, char *argv[]) {
    float x = atof(argv[1]);
    float v = atof(argv[2]);
    float omega_0 = atof(argv[3]);
    float damping_constant = atof(argv[4]);
    float amplitude = atof(argv[5]);
    float omega = atof(argv[6]);
    float delta_t = atof(argv[7]);
    float t_max = atof(argv[8]);

    parameters param = {x, v, omega_0, damping_constant, amplitude, omega, delta_t, t_max};

    double n, theta;
    double t = 0.0;

    /* Euler-Richardson */
    while (t < t_max) {
        param.x = param.x + 0.5 * param.v * delta_t;
        param.v = param.v + 0.5 * acceleration(param, t) * delta_t;

        param.x += param.v * delta_t;
        param.v += acceleration(param, t + 0.5 * delta_t) * delta_t;

        t += delta_t;

        theta = (2 * M_PI) * modf(param.x / (2 * M_PI), &n);
        theta = (theta > M_PI) ? theta - 2 * M_PI : theta;
        theta = (theta < -M_PI) ? theta + 2 * M_PI : theta;

        printf("%f\t%f\t%f\t%f\n", t, param.x, param.v, theta);
    }
    return 0;
}
