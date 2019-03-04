ld = load('rpy_9axis.mat');

acc = ld.sensorData.Acceleration;
gyro = ld.sensorData.AngularVelocity;
mag = ld.sensorData.MagneticField;

accID = fopen('acc.txt','w');
fprintf(accID,'%6.4f %6.4f %6.4f\n',acc);
fclose(accID);

gyroID = fopen('gyro.txt','w');
fprintf(gyroID,'%6.4f %6.4f %6.4f\n',gyro);
fclose(gyroID);

magID = fopen('mag.txt','w');
fprintf(magID,'%6.4f %6.4f %6.4f\n',mag);
fclose(magID);

%[acc, gyro, mag] = txt_parsing('acc.txt', 'gyro.txt', 'mag.txt');

% r_accid = fopen('acc.txt', 'r');
% r_acc = zeros(1600, 3);
% tline = fgetl(r_accid);
% t= 1;
% while ischar(tline)
%     r_acc(t, :) = str2double(strsplit(tline,' '));
%     t = t+1;
%     tline = fgetl(r_accid);
% end
% fclose(r_accid);
% 
% r_gyroid = fopen('gyro.txt', 'r');
% r_gyro = zeros(1600, 3);
% tline = fgetl(r_gyroid);
% t= 1;
% while ischar(tline)
%     r_acc(t, :) = str2double(strsplit(tline,' '));
%     t = t+1;
%     tline = fgetl(r_gyroid);
% end
% fclose(r_gyroid);
% 
% r_magid = fopen('acc.txt', 'r');
% r_mag = zeros(1600, 3);
% tline = fgetl(r_magid);
% t= 1;
% while ischar(tline)
%     r_acc(t, :) = str2double(strsplit(tline,' '));
%     t = t+1;
%     tline = fgetl(r_magid);
% end
% fclose(r_accid);
[orientation, angularVelocity] = kal_tool(acc, gyro, mag);