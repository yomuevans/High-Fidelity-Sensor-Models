#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Accelerometer parameters
#define MEASUREMENT_RANGE 19.6
#define RESOLUTION 0.598e-3
#define CONSTANT_BIAS 0.49
#define NOISE_DENSITY 3920e-6
#define TEMPERATURE_BIAS 0.294
#define TEMPERATURE_SCALE_FACTOR 0.02
#define AXES_MISALIGNMENT 2

// Function to generate noise based on parameters
double generate_noise() {
    // Generate random noise using a normal distribution
    // In a real implementation, you might use a proper random number generator
    return NOISE_DENSITY * sqrt(-2 * log((double) rand() / RAND_MAX)) *
           cos(2 * M_PI * (double) rand() / RAND_MAX);
}

// Simulate accelerometer measurements based on true acceleration
double simulate_accelerometer(double true_acceleration) {
    // Calculate temperature-dependent bias
    double temperature = 25.0; // Assumed temperature in Celsius
    double temperature_bias = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (temperature - 25.0);

    // Add constant bias and temperature-dependent bias
    double measured_acceleration = true_acceleration + CONSTANT_BIAS + temperature_bias;

    // Apply resolution and generate noise
    measured_acceleration += RESOLUTION * round(generate_noise() / RESOLUTION);

    // Apply misalignment
    measured_acceleration += AXES_MISALIGNMENT * generate_noise();

    return measured_acceleration;
}

int main() {
    srand(time(NULL)); // Seed random number generator

    double true_acceleration = 9.81; // True linear acceleration (m/s^2)

    // Simulate accelerometer measurement
    double measured_acceleration = simulate_accelerometer(true_acceleration);

    printf("True Acceleration: %.2f m/s^2\n", true_acceleration);
    printf("Measured Acceleration: %.2f m/s^2\n", measured_acceleration);

    return 0;
}
