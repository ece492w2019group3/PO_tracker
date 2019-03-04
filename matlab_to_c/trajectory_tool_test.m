acc = ld.sensorData.Acceleration;
gyro = ld.sensorData.AngularVelocity;

accID = fopen('acc.txt','w');
fprintf(accID,'%6.4f %6.4f %6.4f\n',acc);
fclose(accID);

gyroID = fopen('gyro.txt','w');
fprintf(gyroID,'%6.4f %6.4f %6.4f\n',gyro);
fclose(gyroID);

[position] = trajectory_tool(acc, gyro);