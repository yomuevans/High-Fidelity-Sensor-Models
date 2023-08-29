#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Gyroscope parameters
#define MEASUREMENT_RANGE 4.363
#define RESOLUTION 1.332e-04
#define CONSTANT_BIAS 0.349
#define NOISE_DENSITY 8.727e-4
#define TEMPERATURE_BIAS 0.349
#define TEMPERATURE_SCALE_FACTOR 0.02
#define AXES_MISALIGNMENT 2
#define ACCELERATION_BIAS 0.178e-3

// Function to generate noise based on parameters
double generate_noise() {
    // Generate random noise using a normal distribution
    // In a real implementation, you might use a proper random number generator
    return NOISE_DENSITY * sqrt(-2 * log((double) rand() / RAND_MAX)) *
           cos(2 * M_PI * (double) rand() / RAND_MAX);
}

// Simulate gyroscope measurements based on true angular velocity
double simulate_gyroscope(double true_angular_velocity) {
    // Calculate temperature-dependent bias
    double temperature = 25.0; // Assumed temperature in Celsius
    double temperature_bias = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (temperature - 25.0);

    // Calculate acceleration-dependent bias
    double acceleration_bias = ACCELERATION_BIAS;

    // Add constant bias, temperature-dependent bias, and acceleration-dependent bias
    double measured_angular_velocity = true_angular_velocity + CONSTANT_BIAS + temperature_bias + acceleration_bias;

    // Apply resolution and generate noise
    measured_angular_velocity += RESOLUTION * round(generate_noise() / RESOLUTION);

    // Apply misalignment
    measured_angular_velocity += AXES_MISALIGNMENT * generate_noise();

    return measured_angular_velocity;
}

int main() {
    srand(time(NULL)); // Seed random number generator

    double true_angular_velocity = 0.1; // True angular velocity (rad/s)

    // Simulate gyroscope measurement
    double measured_angular_velocity = simulate_gyroscope(true_angular_velocity);

    printf("True Angular Velocity: %.3f rad/s\n", true_angular_velocity);
    printf("Measured Angular Velocity: %.3f rad/s\n", measured_angular_velocity);

    return 0;
}
