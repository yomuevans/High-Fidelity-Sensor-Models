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
void simulate_accelerometer(double true_accelerations[3], double measured_accelerations[3]) {
    // Calculate temperature-dependent bias for all axes
    double temperature_biases[3];
    temperature_biases[0] = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    temperature_biases[1] = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    temperature_biases[2] = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    
    for (int axis = 0; axis < 3; axis++) {
        // Add constant bias and temperature-dependent bias
        measured_accelerations[axis] = true_accelerations[axis] + CONSTANT_BIAS + temperature_biases[axis];
        
        // Apply resolution and generate noise
        measured_accelerations[axis] += RESOLUTION * round(generate_noise() / RESOLUTION);
        
        // Apply misalignment
        measured_accelerations[axis] += AXES_MISALIGNMENT * generate_noise();
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator
    
    double true_accelerations[3] = {0.0, 0.0, 9.81}; // True linear accelerations (m/s^2)
    double measured_accelerations[3];
    
    // Simulate accelerometer measurements
    simulate_accelerometer(true_accelerations, measured_accelerations);
    
    printf("True Accelerations: %.2f m/s^2, %.2f m/s^2, %.2f m/s^2\n", true_accelerations[0], true_accelerations[1], true_accelerations[2]);
    printf("Measured Accelerations: %.2f m/s^2, %.2f m/s^2, %.2f m/s^2\n", measured_accelerations[0], measured_accelerations[1], measured_accelerations[2]);
    
    return 0;
}
