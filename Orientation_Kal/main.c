/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "kal_tool_pkg/rt_nonfinite.h"
#include "kal_tool_pkg/kal_tool.h"
#include "main.h"
#include "kal_tool_pkg/kal_tool_terminate.h"
#include "kal_tool_pkg/kal_tool_initialize.h"

#include <stdio.h>
#include <stdlib.h>

/* Function Declarations */
static void argInit_1x3_real_T(double result[3]);
static double argInit_real_T(void);
static void main_kal_tool(void);

/* Function Definitions */
static void argInit_1x3_real_T(double result[3])
{
  double result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[2] = argInit_real_T();
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void getData(double acc[1600][3], double gyro[1600][3], double mag[1600][3]){

	const char s[2] = " ";
	char *token;
	FILE* acc_file;
	FILE* gyro_file;
	FILE* mag_file;
	char str[60];
	int i = 0;
	int j = 0;

	acc_file = fopen("acc.txt", "r"); // read only
	if (! acc_file ) // equivalent to saying if ( in_file == NULL )
	{
		fprintf(stderr,"oops, acc file can't be read\n");
		exit(-1);
	}
	gyro_file = fopen("gyro.txt", "r"); // read only
	if (! gyro_file ) // equivalent to saying if ( in_file == NULL )
	{
		fprintf(stderr,"oops, gyro file can't be read\n");
		exit(-1);
	}
	mag_file = fopen("mag.txt", "r"); // read only
	if (! mag_file ) // equivalent to saying if ( in_file == NULL )
	{
		fprintf(stderr,"oops, mag file can't be read\n");
		exit(-1);
	}

	while( fgets (str, 60, acc_file)!=NULL ) {
		  /* writing content to stdout */
//	      puts(str);
		  /* get the first token */
		 j = 0;
		 token = strtok(str, s);

		 /* walk through other tokens */
		 while( token != NULL ) {
//			printf( "%s\n", token );
			sscanf(token, "%lf", &acc[i][j]);
			j++;

			token = strtok(NULL, s);
		 }

//		 printf( "get %f %f %f\n",  acc[i][0], acc[i][1], acc[i][2]);
		 i++;
	}

	i =0;
	while( fgets (str, 60, gyro_file)!=NULL ) {
		  /* writing content to stdout */
//	      puts(str);
		  /* get the first token */
		 j = 0;
		 token = strtok(str, s);

		 /* walk through other tokens */
		 while( token != NULL ) {
			sscanf(token, "%lf", &gyro[i][j]);
			j++;

			token = strtok(NULL, s);
		 }

//		 printf( "get %f %f %f\n",  acc[i][0], acc[i][1], acc[i][2]);
		 i++;
	}

	i=0;
	while( fgets (str, 60, mag_file)!=NULL ) {
		  /* writing content to stdout */
//	      puts(str);
		  /* get the first token */
		int j = 0;
		 token = strtok(str, s);

		 /* walk through other tokens */
		 while( token != NULL ) {
			sscanf(token, "%lf", &mag[i][j]);
			j++;

			token = strtok(NULL, s);
		 }

//		 printf( "get %lf %lf %lf\n",  mag[i][0], mag[i][1], mag[i][2]);
		 i++;
	}

	fclose(acc_file);
	fclose(gyro_file);
	fclose(mag_file);

}

static void main_kal_tool(void)
{
  double acc_tmp_tmp[3];
  static double orientationEuler_kal[3];
  static double angularvelocity[3];
  static double acc[30000][3];
  static double gyro[30000][3];
  static double mag[30000][3];
  int i =0;
  getData(acc, gyro, mag);
  /* Initialize function 'kal_tool' input arguments. */
  /* Initialize function input argument 'acc'. */
  argInit_1x3_real_T(acc_tmp_tmp);

  /* Initialize function input argument 'gyro'. */
  /* Initialize function input argument 'mag'. */
  /* Call the entry-point 'kal_tool'. */
//  kal_tool(acc_tmp_tmp, acc_tmp_tmp, acc_tmp_tmp, orientationEuler_kal);
  FILE* orientation_file;
  orientation_file = fopen("orientation.txt", "w");
  for(i = 0; i<30000; i++){
	  kal_tool(acc[i], gyro[i], mag[i], orientationEuler_kal, angularvelocity);
	  printf("acc i %lf %lf %lf\n", orientationEuler_kal[0], orientationEuler_kal[1], orientationEuler_kal[2]);
	  fprintf(orientation_file, "%lf %lf %lf\n", orientationEuler_kal[0],orientationEuler_kal[1], orientationEuler_kal[2]);
  }
  fclose(orientation_file);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  kal_tool_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_kal_tool();

  /* Terminate the application.
     You do not need to do this more than one time. */
  kal_tool_terminate();
  return 0;
}

/* End of code generation (main.c) */
