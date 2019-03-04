% Date: February 3, 2019
% Authors: MATLAB
% Modified By: Riley Voon
% Description: This code does some basic simulations on sample IMU data and
% graphs the orientation along 3 axises as the IMU is lifted from a
% surface.
data = fopen('FastPickup1.txt','r'); %get the IMU data

% Convert the data from the file into a matrix.
formatSpec = '%d %f';
sizeA = [12 Inf];
A = fscanf(data,formatSpec,sizeA)
A = A'
disp(A);
% Get the acclerometer, gyroscope, and magnetometer readings from the
% matrix.
accelerometerReadings = 2.93*9.81*A(:,5:7)/1000;
accelerometerReadings = accelerometerReadings - mean(accelerometerReadings)
gyroscopeReadings = 0.98*A(:,2:4)*0.0174533;
gyroscopeReadings = gyroscopeReadings - mean(gyroscopeReadings)
magnetometerReadings = 0.0488*A(:,8:10);
magnetometerReadings = magnetometerReadings - mean(magnetometerReadings)
viewer = fusiondemo.OrientationViewer;
ifilt = imufilter;
for ii = 1:size(accelerometerReadings, 1)
    qimu = ifilt(accelerometerReadings(ii,:), gyroscopeReadings(ii, :));
    viewer(qimu);
    pause(0.01);
end
% Create the ahrsfilter object and fuse it with each reading from the IMU.
decim = 2;
fuse = ahrsfilter;
q = fuse(accelerometerReadings,gyroscopeReadings,magnetometerReadings);
% Plot the changes in orientation.
time = (0:size(accelerometerReadings,1)-1);
subplot(2,1,1);
plot(time,eulerd(q,'ZYX','frame'))
title('Orientation Estimate')
legend('z-axis', 'y-axis', 'x-axis')
ylabel('Rotation (degrees)')
fclose(data);


