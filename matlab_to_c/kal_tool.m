function [orientationEuler_kal, angularVelocity] = kal_tool(acc, gyro, mag)
% FUSE = ahrsfilter('AccelerometerNoise', 0.001, 'GyroscopeNoise', 0.001, 'MagnetometerNoise', 0.001);
FUSE = ahrsfilter();
% mu = [0 0 0];
% sigma = [0.001 0 0; 0 0.001 0; 0 0 0.001];
% R = chol(sigma);
% r1 = repmat(mu,1,1) + randn(1,3)*R; 
% r2 = repmat(mu,1,1) + randn(1,3)*R;
% r3 = repmat(mu,1,1) + randn(1,3)*R;
% acc = acc + r1;
% gyro = gyro + r2;
% mag = mag + r3;
% t = acc1 +1

[orientation_kal, angularVelocity] = FUSE(acc,gyro, mag);
orientationEuler_kal = eulerd(orientation_kal,'ZYX','frame');

end