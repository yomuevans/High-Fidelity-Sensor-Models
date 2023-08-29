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

// Simulate gyroscope measurements based on true angular velocities
void simulate_gyroscope(double true_angular_velocities[3], double measured_angular_velocities[3]) {
    // Calculate temperature-dependent bias for all axes
    double temperature_biases[3];
    temperature_biases[0] = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    temperature_biases[1] = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    temperature_biases[2] = TEMPERATURE_BIAS + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    
    // Calculate acceleration-dependent bias for all axes
    double acceleration_bias = ACCELERATION_BIAS;
    
    for (int axis = 0; axis < 3; axis++) {
        // Add constant bias, temperature-dependent bias, and acceleration-dependent bias
        measured_angular_velocities[axis] = true_angular_velocities[axis] + CONSTANT_BIAS + temperature_biases[axis] + acceleration_bias;
        
        // Apply resolution and generate noise
        measured_angular_velocities[axis] += RESOLUTION * round(generate_noise() / RESOLUTION);
        
        // Apply misalignment
        measured_angular_velocities[axis] += AXES_MISALIGNMENT * generate_noise();
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator
    
    double true_angular_velocities[3] = {0.1, 0.2, 0.3}; // True angular velocities (rad/s)
    double measured_angular_velocities[3];
    
    // Simulate gyroscope measurements
    simulate_gyroscope(true_angular_velocities, measured_angular_velocities);
    
    printf("True Angular Velocities: %.3f rad/s, %.3f rad/s, %.3f rad/s\n", true_angular_velocities[0], true_angular_velocities[1], true_angular_velocities[2]);
    printf("Measured Angular Velocities: %.3f rad/s, %.3f rad/s, %.3f rad/s\n", measured_angular_velocities[0], measured_angular_velocities[1], measured_angular_velocities[2]);
    
    return 0;
}

