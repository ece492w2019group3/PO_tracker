#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1600

int main(int argc, char *argv[]) {
	float acc[1600][3];
	float gyro[1600][3];
	float mag[1600][3];
	const char s[2] = " ";
	char *token;



	fprintf(stdout, "hello\n");
	FILE* acc_file = fopen("acc.txt", "r"); // read only
	if (! acc_file ) // equivalent to saying if ( in_file == NULL )
	{
		fprintf(stderr,"oops, acc file can't be read\n");
		exit(-1);
	}
	FILE* gyro_file = fopen("gyro.txt", "r"); // read only
	if (! gyro_file ) // equivalent to saying if ( in_file == NULL )
	{
		fprintf(stderr,"oops, gyro file can't be read\n");
		exit(-1);
	}
	FILE* mag_file = fopen("mag.txt", "r"); // read only
	if (! mag_file ) // equivalent to saying if ( in_file == NULL )
	{
		fprintf(stderr,"oops, mag file can't be read\n");
		exit(-1);
	}

	//fscanf(acc_file, "%d %d %d", acc[0][0], acc[0][1], acc[0][2]);
	char str[60];
	int i = 0;
	while( fgets (str, 60, acc_file)!=NULL ) {
	      /* writing content to stdout */
//	      puts(str);
	      /* get the first token */
		int j = 0;
	     token = strtok(str, s);

		 /* walk through other tokens */
		 while( token != NULL ) {
//			printf( "%s\n", token );
			sscanf(token, "%f", &acc[i][j]);
			j++;

			token = strtok(NULL, s);
		 }

//		 printf( "get %f %f %f\n",  acc[i][0], acc[i][1], acc[i][2]);
		 i++;
	}


	i = 0;
	while( fgets (str, 60, gyro_file)!=NULL ) {
		  /* writing content to stdout */
//	      puts(str);
		  /* get the first token */
		int j = 0;
		 token = strtok(str, s);

		 /* walk through other tokens */
		 while( token != NULL ) {
//			printf( "%s\n", token );
			sscanf(token, "%f", &gyro[i][j]);
			j++;

			token = strtok(NULL, s);
		 }

//		 printf( "get %f %f %f\n",  acc[i][0], acc[i][1], acc[i][2]);
		 i++;
	}

	i = 0;
	while( fgets (str, 60, mag_file)!=NULL ) {
		  /* writing content to stdout */
//	      puts(str);
		  /* get the first token */
		int j = 0;
		 token = strtok(str, s);

		 /* walk through other tokens */
		 while( token != NULL ) {
//			printf( "%s\n", token );
			sscanf(token, "%f", &mag[i][j]);
			j++;

			token = strtok(NULL, s);
		 }

//		 printf( "get %f %f %f\n",  acc[i][0], acc[i][1], acc[i][2]);
		 i++;
	}
	printf("acc data\n");
	for (int i = 0; i<1600; i++){
		printf( "%f %f %f\n",  acc[i][0], acc[i][1], acc[i][2]);
	}
	fclose(acc_file);
	fclose(gyro_file);
	fclose(mag_file);

	return 0;
}
