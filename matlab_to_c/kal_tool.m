function [orientationEuler_kal, angularVelocity_kal] = kal_tool(acc,gyro, mag)
FUSE = ahrsfilter('AccelerometerNoise', 0.001, 'GyroscopeNoise', 0.001, 'MagnetometerNoise', 0.001);
rng(0,'twister');
a = 0;
b = 0.001;
r1 = a.*randn(1600,3) + b;
rng(0,'twister');
r2 = a.*randn(1600,3) + b;
rng(0,'twister');
r3 = a.*randn(1600,3) + b;
acc = acc +r1;
gyro = gyro + r2;
mag = mag + r3;
[orientation_kal,angularVelocity_kal] = FUSE(acc,gyro, mag);
orientationEuler_kal = eulerd(orientation_kal,'ZYX','frame');

end