#include <Arduino.h>
#include <vqf.hpp>

// Sampling period in seconds
static constexpr vqf_real_t kSamplePeriod = 0.01;

// Instantiate the filter with the desired sampling period
VQF vqf(kSamplePeriod);

void setup()
{
    Serial.begin(115200);
#if defined(USBCON)
    while (!Serial) {
        ; // wait for serial port to connect if needed
    }
#endif
}

void loop()
{
    // Replace these with your IMU samples (gyr: rad/s, acc: m/s^2, mag: arbitrary units)
    const vqf_real_t gyr[3] = {0.01, 0.01, 0.01};
    const vqf_real_t acc[3] = {0.0, 9.81, 0.0};
    const vqf_real_t mag[3] = {0.3, 0.0, 0.4};

    vqf.update(gyr, acc, mag);

    vqf_real_t quat[4];
    vqf.getQuat9D(quat);

    Serial.print(F("Quaternion: "));
    for (size_t i = 0; i < 4; i++) {
        Serial.print(quat[i], 6);
        if (i < 3) {
            Serial.print(F(", "));
        }
    }
    Serial.println();

    delay(100);
}
