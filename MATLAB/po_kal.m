
% Date: February 3, 2019
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
gyroscopeReadings = 0.98*A(:,2:4)*0.0174533;
magnetometerReadings = 0.0488*A(:,8:10);

% ld = load('rpy_9axis.mat');
% 
% accelerometerReadings = ld.sensorData.Acceleration;
% gyroscopeReadings = ld.sensorData.AngularVelocity;
% magnetometerReadings = ld.sensorData.MagneticField;

% For visulization of the orientation of the object
% viewer = fusiondemo.OrientationViewer;
% ifilt = imufilter;
% for ii = 1:size(accelerometerReadings, 1)
%     qimu = ifilt(accelerometerReadings(ii,:), gyroscopeReadings(ii, :));
%     viewer(qimu);
%     pause(0.01);
% end
% Create the ahrsfilter object and fuse it with each reading from the IMU.
decim = 2;

%Init the Kalman Filter
fuse = ahrsfilter;
[orientation, angularvelocity] = fuse(accelerometerReadings,gyroscopeReadings,magnetometerReadings);
% Plot the changes in orientation.
time = (0:size(accelerometerReadings,1)-1);

figure(1)
subplot(2,1,1);
plot(time,eulerd(orientation,'ZYX','frame'))
title('Orientation Estimate')
legend('z-axis', 'y-axis', 'x-axis')
ylabel('Rotation (degrees)')
fclose(data);

trajectory = kinematicTrajectory;
[position,orientation,velocity,acceleration,angularVelocity] = trajectory(accelerometerReadings, angularvelocity);
length = size(position(:,1));
subplot(2,1,2)

plot3(position(:,1), position(:,2), position(:,3),'b-', position(length(1,1), 1), position(length(1,1), 2), position(length(1,1), 3), 'r*');
title('Actual trajectory')


%Generating noises
rng(0,'twister');
a = 0;
b = 0.01;
r1 = a.*randn(size(accelerometerReadings, 1),1) + b;
rng(0,'twister');
r2 = a.*randn(size(accelerometerReadings, 1),1) + b;
rng(0,'twister');
r3 = a.*randn(size(accelerometerReadings, 1),1) + b;

accelerometerReadings_noise = accelerometerReadings + r1;
gyroscopeReadings_noise = gyroscopeReadings +r2;
magnetometerReadings_noise = magnetometerReadings +r3;
[orientation_noise, angularvelocity_noise] = fuse(accelerometerReadings_noise,gyroscopeReadings_noise,magnetometerReadings_noise);

figure(2)
subplot(2,1,1);
plot(time,eulerd(orientation_noise,'ZYX','frame'))
title('Orientation Estimate')
legend('z-axis', 'y-axis', 'x-axis')
ylabel('Rotation (degrees)')

trajectory_noise = kinematicTrajectory;
[position_noise,orientation,velocity,acceleration,angularVelocity] = trajectory_noise(accelerometerReadings_noise, angularvelocity_noise);

subplot(2,1,2)

plot3(position_noise(:,1), position_noise(:,2), position_noise(:,3), 'b-', position_noise(length(1,1),1), position_noise(length(1,1),2), position_noise(length(1,1),3),'r*');
title('Trajectory with noises in sensor reading')

%reconstruting the trijectory
FUSE_noise = ahrsfilter('AccelerometerNoise', 0.001, 'GyroscopeNoise', 0.001, 'MagnetometerNoise', 0.001);
[orientation_kal,angularVelocity_kal] = FUSE_noise(accelerometerReadings_noise,gyroscopeReadings_noise,magnetometerReadings_noise);
orientationEuler_kal = eulerd(orientation_kal,'ZYX','frame');

figure(3)
subplot(2,1,1);
plot(time,eulerd(orientation_kal,'ZYX','frame'))
title('Orientation Estimate')
legend('z-axis', 'y-axis', 'x-axis')
ylabel('Rotation (degrees)')

trajectory_noise = kinematicTrajectory;
[position_kal,orientation_kal,velocity_kal,acceleration_kal,angularVelocity_kal] = trajectory_noise(accelerometerReadings_noise, angularVelocity_kal);

subplot(2,1,2)

plot3(position_kal(:,1), position_kal(:,2), position_kal(:,3), 'b-', position_kal(length(1,1),1), position_kal(length(1,1), 2),position_kal(length(1,1),3),'r*');

% plot3(position_kal(length(1,1),1), position_kal(length(1,1), 2),position_kal(length(1,1),3),'r*');
title('Corrected trajectory with using Kalman Filter')

figure(4)
plot(time, gyroscopeReadings);