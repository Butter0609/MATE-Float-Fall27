#include <Arduino.h>
#include <Wire.h>
#include "PID.h"





// PIN MAPPING (idk bro ask electrical)






// Constants Declaration
const float FIRST_DEPTH = 2.0f; //(m)
const float SECOND_DEPTH = 4.0f; //(m)
const float ACCENSION = 0.0f;  //(m)
const float NO_TOUCHY = 5.0f; //(m) Pretty please don't go below this depth, we might lose points (5)

const float FLUID_DENSITY = 1025.0f; // These seemed useful, previous program used them, find a use later
const float GRAVITY = 9.80665f;

const int PWM_MAX = 255; // Maximum PWM value for motor control

//Hull specifications
const float HULL_VOLUME = 0.00f; // Hull volume in cubic meters (m^3)
const float FLOAT_MASS = 0.0f; // Hull mass in kg

// Types & State (I swear I'm not copying last season's code, it just works)

static enum State { WAIT, DESCEND, PAUSE_SHALLOW, DESCEND, PAUSE_DEEP, ACEND, DONE, EMERGENCY_STOP } // E stop just seems helpful here (even if we cant access it manually)

// Pretty sure g_ references the sensor so imma just go with it

float g_depth = 0.0f; // initial depth is 0m
float g_kpa = 0.0f;
bool g_emergencyStop = false; // Emergency stop flag
bool g_sensorWork = false;
unsigned long g_lastSensorReadTime = 0; // Timestamp of the last sensor read

// Sensor estimator (pretty smart, but I don't know how it works)

float est_depth = 0.0f;
float est_kpa = 0.0f;
float est_vel = 0.0f;

