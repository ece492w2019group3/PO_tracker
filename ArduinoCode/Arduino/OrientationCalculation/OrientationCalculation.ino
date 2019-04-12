

/*****************************************************************
OrientationCalculation.imo
Based off LSM9DS1_Basic_I2C.ino made by Jim Lindblom @ Sparkfun Electronics
The original code can be found below:
https://github.com/sparkfun/LSM9DS1_Breakout

Last Modification Date: April 12, 2019
Modifications made by Riley Voon @ University of Alberta

This Arduino sketch aims to read the LSM9DS1's gyroscope, 
accelerometer, and magnetomete rover the I2C connection and
find position and orientation by using several
algorithms originally from MATLAB converted into C code
using MATLAB C Coder. These algorithms include a Kalman filter
and a trajectory calculation algorithm.

*****************************************************************/
// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <math.h>
extern "C"{
#include <rtwtypes.h>
#include <kal_tool_types.h>
#include <rt_nonfinite.h>
#include <kal_tool.h>
#include <kal_tool_terminate.h>
#include <kal_tool_initialize.h>
#include <trajectory_tool.h>
#include <trajectory_tool_types.h>
#include <trajectory_tool_terminate.h>
#include <trajectory_tool_initialize.h>
#include <getQuaternion.h>
}

//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
LSM9DS1 imu;

// I2C Setup 
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M 0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

// Output Settings
#define PRINT_CALCULATED
#define PRINT_SPEED 20 // 20 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time
double g_xyz[3];
double a_xyz[3];
double m_xyz[3];
double acc_tmp[6];
double ang_vel_tmp[6];
double prev_position_tmp[3];
double prev_velocity_tmp[3];
c_matlabshared_rotations_intern prev_orientation = {1, 0, 0, 0};
d_matlabshared_rotations_intern orient;
const double g = 9.80;
const double acc_mag_threshold = 0.3;
double grav[3]; 
int fs = 50;

// Initialize the Kalman filter and trajectory algorithm tools, and
// begin communication with the IMU over the I2C connection.
void setup() 
{
  
  Serial.begin(115200);
  kal_tool_initialize();
  trajectory_tool_initialize();
  // Set IMU communication mode and addresses
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;

  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1)
      ;
  }

  // Calibrate accelerometer, gyroscope, and magnetometer
  Serial.println("accel and gyro calibration start");
  imu.calibrate(1);
  Serial.println("accel and gyro calibration finished");

  Serial.println("magnetometer calibration started");
  imu.calibrateMag(1);
  Serial.println("magnetometer Calibration fininshed"); 
  // Get initial acceleration 
  if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
  acc_tmp[0] = imu.calcAccel(imu.ax);
  acc_tmp[2] = imu.calcAccel(imu.ay);
  acc_tmp[4] = imu.calcAccel(imu.az);
  // Initialize global variables
  prev_position_tmp[0] = 0;
  prev_position_tmp[1] = 0;
  prev_position_tmp[2] = 0;
  prev_velocity_tmp[0] = 0;
  prev_velocity_tmp[1] = 0;
  prev_velocity_tmp[2] = 0;
  ang_vel_tmp[0] = 0;
  ang_vel_tmp[2] = 0;
  ang_vel_tmp[4] = 0;
  grav[0] = 0;
  grav[1] = 0;
  grav[2] = 0;
  getQuaternion(0, 0, 0, &prev_orientation);
}

// Constantly read from the IMU and calculate orientation and position
void loop()
{
  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    // Read from the gyroscope
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    // Read from the accelerometer
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    // Read from the magnetometer
    imu.readMag();
  }
  
  if ((lastPrint + PRINT_SPEED) < millis())
  {
    // Scale gyroscope, accelerometer, and magnetometer values to the
    // units needed by algorithms
    // Gyroscope from degrees to radians
    g_xyz[0] = imu.calcGyro(imu.gx) * 0.0174533;
    g_xyz[1] = imu.calcGyro(imu.gy) * 0.0174533;
    g_xyz[2] = imu.calcGyro(imu.gz) * 0.0174533;
    // Acceleration from g to m/s^2
    a_xyz[0] = imu.calcAccel(imu.ax) * g;
    a_xyz[1] = imu.calcAccel(imu.ay) * g;
    a_xyz[2] = imu.calcAccel(imu.az) * g;
    // Magnetometer from gauss to microTeslas
    m_xyz[0] = imu.calcMag(imu.mx) * 100;
    m_xyz[1] = imu.calcMag(imu.my) * 100;
    m_xyz[2] = imu.calcMag(imu.mz) * 100; 
    
    // Call the kalman filter algorithm and trajectory calculation
    main_kal_tool(a_xyz, g_xyz, m_xyz, acc_tmp, ang_vel_tmp, prev_position_tmp, prev_velocity_tmp, prev_orientation, orient);    
    lastPrint = millis(); // Update lastPrint time
  }
}

// Test function to check gyroscope values
void printGyro()
{
  Serial.print("G: ");
  // Print calculated angular velocity in degrees per second
#ifdef PRINT_CALCULATED
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
  // Print raw ADC values
#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
#endif
}

// Test function to check accelerometer values
void printAccel()
{  

  Serial.print("A: ");
  // Print calculated acceleration in g
#ifdef PRINT_CALCULATED
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
  // Print raw ADC values
#elif defined PRINT_RAW 
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
#endif

}

// Test function to check magnetometer values
void printMag()
{  
  Serial.print("M: ");
  // Print magnetometer values in gauss
#ifdef PRINT_CALCULATED
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
  // Print raw ADC values
#elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
#endif
}


// Obtain orientation and position using
static void main_kal_tool(const double acc[3], 
        const double gyr[3], const double mg[3], double acc_tmp[6], double ang_vel_tmp[6], 
        double prev_position_tmp[3], double prev_velocity_tmp[3], 
        c_matlabshared_rotations_intern prev_orientation, 
        d_matlabshared_rotations_intern orient) {
  static double orientationEuler_kal[3];
  static double angularvelocity[3];
  static double pos[3];
  static double vel[3];
  static double cur_position[3];
  static double velocity[6];
  static double acceleration[6];
  static double angularVelocity[6];
  static double acc_filtered[3];
  float acc_magnitude;

  // Call the Kalman filter to obtain orientation and angular velocity
  // Inputs: acceleration, angular velocity, magnetic field strength
  // Outputs: orientation (in NED coordinates), angular velocity
  kal_tool(acc, gyr, mg, orientationEuler_kal, angularvelocity);
  // Convert the orientation in NED coordinates into orientation in quaternions
  // Inputs: Yaw, pitch, roll
  // Outputs: Orientation in quaternions
  getQuaternion(orientationEuler_kal[0], orientationEuler_kal[1], orientationEuler_kal[2], &prev_orientation);
  // Get the gravity acting on each axis
  // Inputs: Orientation in quaternions
  // Outputs: Gravity in X, Y, and Z. 
  gravity_calculation(prev_orientation);
  // Remove gravity from the acceleration;
  acc_tmp[1] = acc[0] - grav[0]*g;
  acc_tmp[3] = acc[1] - grav[1]*g;
  acc_tmp[5] = acc[2] - grav[2]*g;
  // If the magnitude of the linear acceleration is less than the threshold value,
  // force acceleration to 0. Minimizes drift due to improperly removed gravity.
  acc_magnitude = sqrt(acc_tmp[1]*acc_tmp[1] + acc_tmp[3]*acc_tmp[3] + acc_tmp[5]*acc_tmp[5]);
  if (acc_magnitude < acc_mag_threshold) {
    acc_tmp[1] = 0;
    acc_tmp[3] = 0;
    acc_tmp[5] = 0;
  }
  // Update angular velocity
  ang_vel_tmp[1] = angularvelocity[0];
  ang_vel_tmp[3] = angularvelocity[1];
  ang_vel_tmp[5] = angularvelocity[2];
  
  // Call the trajectory calculation tool to obtain new position and velocity given
  // linear acceleration and angular velocity.
  // Inputs: Linear acceleration, angular velocity, previous position, previous velocity,
  //         previous orientation
  // Outputs: New position, velocity, acceleration, angular velocity, orientation 
  trajectory_tool(acc_tmp, ang_vel_tmp,
                  prev_position_tmp, prev_orientation, prev_velocity_tmp, fs, cur_position, &orient, velocity,
                  acceleration, angularVelocity);
                  
  // Update old acceleration, position, and velocity
  acc_tmp[0] = acc_tmp[1];
  acc_tmp[2] = acc_tmp[3];
  acc_tmp[4] = acc_tmp[5];
  prev_position_tmp[0] = cur_position[0];
  prev_position_tmp[1] = cur_position[1];
  prev_position_tmp[2] = cur_position[2];

  // If the magnitude of the linear acceleration is less than the threshold value,
  // force velocity to 0. Minimizes drift due to improperly removed gravity.
  if (acc_magnitude < acc_mag_threshold) {
    prev_velocity_tmp[0] = 0;
    prev_velocity_tmp[1] = 0;
    prev_velocity_tmp[2] = 0;
  }
  else {
    prev_velocity_tmp[0] = velocity[1];
    prev_velocity_tmp[1] = velocity[3];
    prev_velocity_tmp[2] = velocity[5];
  }
  
  // Update the angular velocity
  ang_vel_tmp[0] = ang_vel_tmp[1];
  ang_vel_tmp[2] = ang_vel_tmp[3];
  ang_vel_tmp[4] = ang_vel_tmp[5];

  // Print the orientation and position to serial.
  Serial.print(orientationEuler_kal[0], 2);
  Serial.print(",");
  Serial.print(orientationEuler_kal[1], 2);
  Serial.print(",");
  Serial.print(orientationEuler_kal[2], 2); 
  Serial.print(",");
  Serial.print(cur_position[0]*1000, 2);
  Serial.print(",");
  Serial.print(cur_position[1]*1000, 2);
  Serial.print(",");
  Serial.print(cur_position[2]*1000, 2); 
  Serial.print(",");
  // If the position is 0, reset the graph to its original state.
  if (sqrt(prev_position_tmp[0]*prev_position_tmp[0] + prev_position_tmp[1]*prev_position_tmp[1] + prev_position_tmp[2]*prev_position_tmp[2]) == 0){
    Serial.println("0");
  }
  else {
    Serial.println("0");
  }
}

// Get gravity in each axis from orientation in quaternions
static void gravity_calculation(c_matlabshared_rotations_intern prev_orientation) {
  grav[0] = 2 * (prev_orientation.b*prev_orientation.d - prev_orientation.a*prev_orientation.c);
  grav[1] = 2 * (prev_orientation.a*prev_orientation.b + prev_orientation.c*prev_orientation.d);
  grav[2] = prev_orientation.a*prev_orientation.a - prev_orientation.b*prev_orientation.b - prev_orientation.c*prev_orientation.c + prev_orientation.d*prev_orientation.d;
}
