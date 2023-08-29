#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Magnetometer parameters
#define MEASUREMENT_RANGE 1200
#define RESOLUTION 0.1
#define CONSTANT_BIAS 1
#define NOISE_DENSITY_X 0.6 / sqrt(100)
#define NOISE_DENSITY_Y 0.6 / sqrt(100)
#define NOISE_DENSITY_Z 0.9 / sqrt(100)
#define TEMPERATURE_BIAS_X 0.8
#define TEMPERATURE_BIAS_Y 0.8
#define TEMPERATURE_BIAS_Z 2.4
#define TEMPERATURE_SCALE_FACTOR 0.1

// Function to generate noise based on parameters
double generate_noise() {
    // Generate random noise using a normal distribution
    // In a real implementation, you might use a proper random number generator
    return sqrt(-2 * log((double) rand() / RAND_MAX)) *
           cos(2 * M_PI * (double) rand() / RAND_MAX);
}

// Simulate magnetometer measurements based on true magnetic field
void simulate_magnetometer(double true_magnetic_field[3], double measured_magnetic_field[3]) {
    // Calculate temperature-dependent biases
    double temperature_biases[3];
    temperature_biases[0] = TEMPERATURE_BIAS_X + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    temperature_biases[1] = TEMPERATURE_BIAS_Y + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    temperature_biases[2] = TEMPERATURE_BIAS_Z + TEMPERATURE_SCALE_FACTOR * (25.0 - 25.0);
    
    // Calculate noise terms
    double noise_x = NOISE_DENSITY_X * generate_noise();
    double noise_y = NOISE_DENSITY_Y * generate_noise();
    double noise_z = NOISE_DENSITY_Z * generate_noise();
    
    // Apply constant bias, temperature-dependent biases, and noise
    measured_magnetic_field[0] = true_magnetic_field[0] + CONSTANT_BIAS + temperature_biases[0] + noise_x;
    measured_magnetic_field[1] = true_magnetic_field[1] + CONSTANT_BIAS + temperature_biases[1] + noise_y;
    measured_magnetic_field[2] = true_magnetic_field[2] + CONSTANT_BIAS + temperature_biases[2] + noise_z;
}

int main() {
    srand(time(NULL)); // Seed random number generator
    
    double true_magnetic_field[3] = {20, 30, 40}; // True magnetic field (µT)
    double measured_magnetic_field[3];
    
    // Simulate magnetometer measurement
    simulate_magnetometer(true_magnetic_field, measured_magnetic_field);
    
    printf("True Magnetic Field: %.1f µT, %.1f µT, %.1f µT\n", true_magnetic_field[0], true_magnetic_field[1], true_magnetic_field[2]);
    printf("Measured Magnetic Field: %.1f µT, %.1f µT, %.1f µT\n", measured_magnetic_field[0], measured_magnetic_field[1], measured_magnetic_field[2]);
    
    return 0;
}
