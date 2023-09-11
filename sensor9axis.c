#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Sensor data structure
typedef struct {
    // Gyroscope data
    double gyroFsr;        // Full Scale Range (dps)
    double gyroZRO;        // Zero Rate Output (dps)
    double gyroOffsetTC;   // Gyro Offset Stability TC (dps/ºC)
    double gyroSensitivityError; // Gyro Sensitivity Error (%)
    double gyroSensitivityTemp;  // Gyro Sensitivity/temp (%/ºC)
    double gyroCrossAxisSensitivity; // Gyro Cross-Axis Sensitivity (%)
    double gyroNonlinearity; // Gyro Nonlinearity (%)
    double gyroNoise;       // Gyro Noise (dps/√Hz)
    double gyroOutputDataRate; // Gyro Output Data Rate (Hz)

    // Accelerometer data
    double accelFsr;       // Full Scale Range (g)
    double accelZGO;       // Accel Zero G Offset (mg)
    double accelOffsetTC;  // Accel Offset Stability TC (mg/ºC)
    double accelSensitivityError; // Accel Sensitivity Error (%)
    double accelSensitivityTemp;  // Accel Sensitivity/temp (%/ºC)
    double accelCrossAxisSensitivity; // Accel Cross-Axis Sensitivity (%)
    double accelNonlinearity; // Accel Nonlinearity (%)
    double accelNoise;      // Accel Noise (μg/√Hz)
    double accelOutputDataRate; // Accel Output Data Rate (Hz)

    // Compass data
    double compassFsr;     // Compass Full Scale Range (µT)
    double compassSensitivityScale; // Compass Sensitivity Scale Factor (µT/LSB)
    double compassCurrent; // Compass Current (µA)
} SensorData;

// Function to generate random noise within a specified range
double generateNoise(double min, double max) {
    double range = max - min;
    double random_value = ((double)rand() / RAND_MAX) * range + min;
    return random_value;
}

// Function to simulate noisy gyroscope measurements
double simulateGyroMeasurement(SensorData sensor, double trueValue) {
    double noise = generateNoise(-sensor.gyroNoise, sensor.gyroNoise);
    return trueValue + noise;
}

// Function to simulate noisy accelerometer measurements
double simulateAccelMeasurement(SensorData sensor, double trueValue) {
    double noise = generateNoise(-sensor.accelNoise, sensor.accelNoise);
    return trueValue + noise;
}

// Function to simulate noisy compass measurements
double simulateCompassMeasurement(SensorData sensor, double trueValue) {
    double noise = generateNoise(-sensor.compassSensitivityScale, sensor.compassSensitivityScale);
    return trueValue + noise;
}

int main() {
    // Initialize sensor data
    SensorData sensor;
    
    sensor.gyroFsr = 2000;          // ±2000 dps
    sensor.gyroZRO = 5;             // ±5 dps
    sensor.gyroOffsetTC = 0.05;     // ±0.05 dps/ºC
    sensor.gyroSensitivityError = 1.5; // ±1.5%
    sensor.gyroSensitivityTemp = 0.024; // ±0.024 %/ºC
    sensor.gyroCrossAxisSensitivity = 2; // ±2%
    sensor.gyroNonlinearity = 0.1;  // ±0.1%
    sensor.gyroNoise = 0.015;       // 0.015 dps/√Hz
    sensor.gyroOutputDataRate = 9000; // 9 KHz

    sensor.accelFsr = 16;           // ±16 g
    sensor.accelZGO = 50;           // ±50 mg
    sensor.accelOffsetTC = 0.8;     // ±0.8 mg/ºC
    sensor.accelSensitivityError = 0.5; // ±0.5%
    sensor.accelSensitivityTemp = 0.026; // ±0.026 %/ºC
    sensor.accelCrossAxisSensitivity = 2; // ±2%
    sensor.accelNonlinearity = 0.5; // ±0.5%
    sensor.accelNoise = 230;        // 230 μg/√Hz
    sensor.accelOutputDataRate = 4500; // 4.5 kHz

    sensor.compassFsr = 4900;       // ±4900 µT
    sensor.compassSensitivityScale = 0.15; // ±0.15 µT/LSB
    sensor.compassCurrent = 90;     // 90 µA @ 8 Hz
    
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Simulate sensor measurements
    double trueGyroValue = 100.0; // Replace with your actual gyroscope reading
    double trueAccelValue = 9.81; // Replace with your actual accelerometer reading
    double trueCompassValue = 50.0; // Replace with your actual compass reading

    double noisyGyroValue = simulateGyroMeasurement(sensor, trueGyroValue);
    double noisyAccelValue = simulateAccelMeasurement(sensor, trueAccelValue);
    double noisyCompassValue = simulateCompassMeasurement(sensor, trueCompassValue);

    // Print simulated measurements
    printf("True Gyroscope Value: %.2f dps\n", trueGyroValue);
    printf("Noisy Gyroscope Measurement: %.2f dps\n", noisyGyroValue);

    printf("\nTrue Accelerometer Value: %.2f g\n", trueAccelValue);
    printf("Noisy Accelerometer Measurement: %.2f g\n", noisyAccelValue);

    printf("\nTrue Compass Value: %.2f µT\n", trueCompassValue);
    printf("Noisy Compass Measurement: %.2f µT\n", noisyCompassValue);

    return 0;
}
