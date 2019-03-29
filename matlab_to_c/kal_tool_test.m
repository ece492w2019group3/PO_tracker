ld = load('rpy_9axis.mat');

% ld = load('magJamming.mat');

acc = ld.sensorData.Acceleration;
gyro = ld.sensorData.AngularVelocity;
mag = ld.sensorData.MagneticField;
fs = ld.Fs;

time = 0:length(acc);

Gyroscope = gyro;
Accelerometer = acc;
Magnetometer = mag;
save('sample1.mat','Gyroscope','Accelerometer', 'Magnetometer','time');


accID = fopen('acc.txt','w');
for i=1:length(acc(:,1))
    fprintf(accID,'%6.4f %6.4f %6.4f\n',acc(i,1), acc(i,2), acc(i,3));
end 

fclose(accID);

gyroID = fopen('gyro.txt','w');
for i=1:length(acc(:,1))
    fprintf(gyroID,'%6.4f %6.4f %6.4f\n',gyro(i,1), gyro(i,2), gyro(i,3));
end 

fclose(gyroID);

magID = fopen('mag.txt','w');
for i=1:length(acc(:,1))
    fprintf(magID,'%6.4f %6.4f %6.4f\n',mag(i,1), mag(i,2), mag(i,3));
end 

fclose(magID);

% [acc, gyro, mag] = txt_parsing('acc.txt', 'gyro.txt', 'mag.txt');

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
% [orientation, angularVelocity_kal] = kal_tool(acc, gyro, mag);
% figure(1)
% t = [1:1:1600];
% plot(t,orientation)
% legend('Z-axis','Y-axis','X-axis')
% xlabel('Time (s)')
% ylabel('Rotation (degrees)')
% title('Orientation with noise')

% r_orid = fopen('orientation.txt', 'r');
% r_or = zeros(length(acc(:,1)), 3);
% tline = fgetl(r_orid);
% t= 1;
% while ischar(tline)
%    r_or(t, :) = str2double(strsplit(tline,' '));
%    t = t+1;
%    tline = fgetl(r_orid);
% end
% fclose(r_orid);
% figure(1)
% t = [1:1:length(acc(:,1))];
% plot(t,r_or)
% legend('Z-axis','Y-axis','X-axis')
% xlabel('Time (s)')
% ylabel('Rotation (degrees)')
% title('Orientation with noise')


orientation = zeros(length(acc(:,1)),3);
angularVelocity_kal = zeros(length(acc(:,1)),3);
% orientation = kal_tool(acc, gyro, mag);
% figure(1)

for i = 1:length(acc(:,1))
     [o,a] = kal_tool(acc(i,:), gyro(i,:), mag(i,:));
     orientation(i,:) = o;
     angularVelocity_kal(i,:) = a;
     disp(a);
  
% %      angularVelocity_kal(i,:) = a;     
end
% orientation_kal = kal_tool(acc, gyro, mag);
% orientation = eulerd(orientation_kal,'XYZ','frame');

figure(2)
t = [1:1:length(acc(:,1))];
plot(angularVelocity_kal)
legend('Z-axis','Y-axis','X-axis')
xlabel('Time (s)')
ylabel('Rotation (degrees)')
title('Orientation with noise')