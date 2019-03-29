

/*****************************************************************
LSM9DS1_Basic_I2C.ino
SFE_LSM9DS1 Library Simple Example Code - I2C Interface
Jim Lindblom @ SparkFun Electronics
Original Creation Date: April 30, 2015
https://github.com/sparkfun/LSM9DS1_Breakout

The LSM9DS1 is a versatile 9DOF sensor. It has a built-in
accelerometer, gyroscope, and magnetometer. Very cool! Plus it
functions over either SPI or I2C.

This Arduino sketch is a demo of the simple side of the
SFE_LSM9DS1 library. It'll demo the following:
* How to create a LSM9DS1 object, using a constructor (global
  variables section).
* How to use the begin() function of the LSM9DS1 class.
* How to read the gyroscope, accelerometer, and magnetometer
  using the readGryo(), readAccel(), readMag() functions and 
  the gx, gy, gz, ax, ay, az, mx, my, and mz variables.
* How to calculate actual acceleration, rotation speed, 
  magnetic field strength using the calcAccel(), calcGyro() 
  and calcMag() functions.
* How to use the data from the LSM9DS1 to calculate 
  orientation and heading.

Hardware setup: This library supports communicating with the
LSM9DS1 over either I2C or SPI. This example demonstrates how
to use I2C. The pin-out is as follows:
  LSM9DS1 --------- Arduino
   SCL ---------- SCL (A5 on older 'Duinos')
   SDA ---------- SDA (A4 on older 'Duinos')
   VDD ------------- 3.3V
   GND ------------- GND
(CSG, CSXM, SDOG, and SDOXM should all be pulled high. 
Jumpers on the breakout board will do this for you.)

The LSM9DS1 has a maximum voltage of 3.6V. Make sure you power it
off the 3.3V rail! I2C pins are open-drain, so you'll be 
(mostly) safe connecting the LSM9DS1's SCL and SDA pins 
directly to the Arduino.

Development environment specifics:
  IDE: Arduino 1.6.3
  Hardware Platform: SparkFun Redboard
  LSM9DS1 Breakout Version: 1.0

This code is beerware. If you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, 
please buy us a round!

Distributed as-is; no warranty is given.
*****************************************************************/
// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
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
}

//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M 0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time
double g_xyz[3];
double a_xyz[3];
double m_xyz[3];
double acc_tmp[6];
double ang_vel_tmp[6];
double prev_position_tmp[3];
double prev_velocity_tmp[3];

// Earth's magnetic field varies by location. Add or subtract 
// a declination to get a more accurate heading. Calculate 
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION +14.25 // Declination (degrees) in Boulder, CO.

void setup() 
{
  
  Serial.begin(57600);
  kal_tool_initialize();
  trajectory_tool_initialize();
  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // The above lines will only take effect AFTER calling
  // imu.begin(), which verifies communication with the IMU
  // and turns it on.
  imu.calibrateMag(true);
    acc_tmp[0] = a_xyz[0];
    acc_tmp[2] = a_xyz[1];
    acc_tmp[4] = a_xyz[2];
    ang_vel_tmp[0] = 0;
    ang_vel_tmp[2] = 0;
    ang_vel_tmp[4] = 0;
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
}

void loop()
{
  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    // To read from the gyroscope,  first call the
    // readGyro() function. When it exits, it'll update the
    // gx, gy, and gz variables with the most current data.
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    // To read from the accelerometer, first call the
    // readAccel() function. When it exits, it'll update the
    // ax, ay, and az variables with the most current data.
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    // To read from the magnetometer, first call the
    // readMag() function. When it exits, it'll update the
    // mx, my, and mz variables with the most current data.
    imu.readMag();
  }
  
  if ((lastPrint + PRINT_SPEED) < millis())
  {
    // printGyro();  // Print "G: gx, gy, gz"
    // printAccel(); // Print "A: ax, ay, az"
    // printMag();   // Print "M: mx, my, mz"
    // Print the heading and orientation for fun!
    // Call print attitude. The LSM9DS1's mag x and y
    // axes are opposite to the accelerometer, so my, mx are
    // substituted for each other.
    // printAttitude(imu.ax, imu.ay, imu.az, 
    //              -imu.my, -imu.mx, imu.mz);
    g_xyz[0] = imu.calcGyro(imu.gx) * 0.0174533;
    g_xyz[1] = imu.calcGyro(imu.gy) * 0.0174533;
    g_xyz[2] = imu.calcGyro(imu.gz) * 0.0174533;
    a_xyz[0] = imu.calcAccel(imu.ax) * 9.81;
    a_xyz[1] = imu.calcAccel(imu.ay) * 9.81;
    a_xyz[2] = imu.calcAccel(imu.az) * 9.81;
    m_xyz[0] = imu.calcMag(imu.mx);
    m_xyz[1] = imu.calcMag(imu.my);
    m_xyz[2] = imu.calcMag(imu.mz); 
    main_kal_tool(a_xyz, g_xyz, m_xyz, acc_tmp, ang_vel_tmp);
//    Serial.println();
    
    lastPrint = millis(); // Update lastPrint time
  }
}

void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
#endif
}

void printAccel()
{  
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  Serial.print("A: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
#elif defined PRINT_RAW 
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
#endif

}

void printMag()
{  
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  Serial.print("M: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
#elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
#endif
}

// Calculate pitch, roll, and heading.
// Pitch/roll calculations take from this app note:
// http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf?fpsp=1
// Heading calculations taken from this app note:
// http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/Magnetic__Literature_Application_notes-documents/AN203_Compass_Heading_Using_Magnetometers.pdf
void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  
  float heading;
  if (my == 0)
    heading = (mx < 0) ? PI : 0;
  else
    heading = atan2(mx, my);
    
  heading -= DECLINATION * PI / 180;
  
  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);
  
  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
  
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); Serial.println(heading, 2);
}

static void main_kal_tool(const double acc[3], const double gyro[3], const double mag[3], double acc_tmp[6], double ang_vel_tmp[6]) {
  static double orientationEuler_kal[3];
  static double angularvelocity[3];
  static double pos[3];
  static double vel[3];
  static double cur_position[3];
  static double velocity[6];
  static double acceleration[6];
  static double angularVelocity[6];
  kal_tool(acc, gyro, mag, orientationEuler_kal, angularvelocity);
  acc_tmp[1] = acc[0];
  acc_tmp[3] = acc[1];
  acc_tmp[5] = acc[2];
  ang_vel_tmp[1] = angularvelocity[0];
  ang_vel_tmp[3] = angularvelocity[1];
  ang_vel_tmp[5] = angularvelocity[2];
  trajectory_tool(acc_tmp, ang_vel_tmp,
                  prev_position_tmp, prev_velocity_tmp, cur_position, velocity,
                  acceleration, angularVelocity);
  acc_tmp[0] = acceleration[1];
  acc_tmp[2] = acceleration[3];
  acc_tmp[4] = acceleration[5];
  prev_position_tmp[0] = cur_position[0];
  prev_position_tmp[1] = cur_position[1];
  prev_position_tmp[2] = cur_position[2];
  prev_velocity_tmp[0] = velocity[1];
  prev_velocity_tmp[1] = velocity[3];
  prev_velocity_tmp[2] = velocity[5];
  ang_vel_tmp[0] = angularVelocity[1];
  ang_vel_tmp[2] = angularVelocity[3];
  ang_vel_tmp[4] = angularVelocity[5];

  Serial.print(orientationEuler_kal[0], 2);
  Serial.print(",");
  Serial.print(orientationEuler_kal[1], 2);
  Serial.print(",");
  Serial.print(orientationEuler_kal[2], 2); 
  Serial.print(",");
  Serial.print(cur_position[0], 2);
  Serial.print(",");
  Serial.print(cur_position[1], 2);
  Serial.print(",");
  Serial.print(cur_position[2], 2); 
  Serial.println(",");
//  Serial.print(ang_vel_tmp[0], 2);
//  Serial.print(",");
//  Serial.print(ang_vel_tmp[1], 2);
//  Serial.print(",");
//  Serial.print(ang_vel_tmp[2], 2); 
//  Serial.print(",");
//  Serial.print(acc[0], 2);
//  Serial.print(",");
//  Serial.print(acc[1], 2);
//  Serial.print(",");
//  Serial.print(acc[2], 2); 
//  Serial.println(",");
//  Serial.print(mag[0], 2);
//  Serial.print(",");
//  Serial.print(mag[1], 2);
//  Serial.print(",");
//  Serial.print(mag[2], 2); 
//  Serial.println(",");
}
