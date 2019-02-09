
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
accelerometerReadings = A(:,5:7);
gyroscopeReadings = A(:,2:4);
magnetometerReadings = A(:,8:10);
disp(accelerometerReadings);

% Create the ahrsfilter object and fuse it with each reading from the IMU.
decim = 2;
fuse = ahrsfilter('SampleRate',data,'DecimationFactor',decim);
[orientation, angularvelocity] = fuse(accelerometerReadings,gyroscopeReadings,magnetometerReadings);

% Plot the changes in orientation.
time = (0:decim:size(accelerometerReadings,1)-1)/data;

figure(1)
plot(time,eulerd(orientation,'ZYX','frame'))
title('Orientation Estimate')
legend('z-axis', 'y-axis', 'x-axis')
ylabel('Rotation (degrees)')
fclose(data);

trajectory = kinematicTrajectory;
[position,orientation,velocity,acceleration,angularVelocity] = trajectory(acc, angularVelocity_kal);

figure(2)
plot3(position(:,1), position(:,2), position(:,3));

