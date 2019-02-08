ld = load('rpy_9axis.mat');

acc = ld.sensorData.Acceleration;
gyro = ld.sensorData.AngularVelocity;
mag = ld.sensorData.MagneticField;
% rate = ld.fs;

viewer = fusiondemo.OrientationViewer;
 
ifilt = imufilter('SampleRate', ld.Fs);
 for ii=1:size(acc,1)
     qimu = ifilt(acc(ii,:), gyro(ii,:));
     viewer(qimu);
     pause(0.01);
end
t = [1:1:1600];
FUSE = ahrsfilter;
[orientation_kal,angularVelocity_kal] = FUSE(acc,gyro, mag);
orientationEuler_kal = eulerd(orientation_kal,'ZYX','frame');
figure(1)
plot(t,orientationEuler_kal)
legend('Z-axis','Y-axis','X-axis')
xlabel('Time (s)')
ylabel('Rotation (degrees)')
title('Orientation')


% % https://www.mathworks.com/help/fusion/ref/imusensor-system-object.html#mw_9ead7fa6-0380-4312-813f-34e13f66b39d
% % fs = 100;
% % t = (0:(size(acc,1)-1))/fs;
% % orientation = ecompass(acc,gyro);
% % orientationEuler = eulerd(orientation,'ZYX','frame');
% % figure(2)
% % plot(t,orientationEuler)
% % legend('Z-axis','Y-axis','X-axis')
% % xlabel('Time (s)')
% % ylabel('Rotation (degrees)')
% % title('Orientation')

% adding noises to measurment data
rng(0,'twister');
a = 0;
b = 0.001;
r1 = a.*randn(1600,1) + b;
rng(0,'twister');
r2 = a.*randn(1600,1) + b;
rng(0,'twister');
r3 = a.*randn(1600,1) + b;



acc_noise = acc +r1;
gyro_noise = gyro + r2;
mag_noise = mag + r3;

[orientation_kal,angularVelocity_kal] = FUSE(acc_noise,gyro_noise, mag_noise);
orientationEuler_kal = eulerd(orientation_kal,'ZYX','frame');
figure(2)
plot(t,orientationEuler_kal)
legend('Z-axis','Y-axis','X-axis')
xlabel('Time (s)')
ylabel('Rotation (degrees)')
title('Orientation with noise')


%considering noise
FUSE_noise = ahrsfilter('AccelerometerNoise', 0.001, 'GyroscopeNoise', 0.001, 'MagnetometerNoise', 0.001);
[orientation_kal,angularVelocity_kal] = FUSE_noise(acc_noise,gyro_noise, mag_noise);
orientationEuler_kal = eulerd(orientation_kal,'ZYX','frame');
figure(3)
plot(t,orientationEuler_kal)
legend('Z-axis','Y-axis','X-axis')
xlabel('Time (s)')
ylabel('Rotation (degrees)')
title('Orientation with considering noise')