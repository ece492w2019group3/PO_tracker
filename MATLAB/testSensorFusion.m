data = fopen('SlowPickup1.txt','r');
formatSpec = '%d %f';
sizeA = [12 Inf];
A = fscanf(data,formatSpec,sizeA)
A = A'
disp(A);
accelerometerReadings = A(:,5:7);
gyroscopeReadings = A(:,2:4);
magnetometerReadings = A(:,8:10);
disp(accelerometerReadings);

decim = 2;
fuse = ahrsfilter('SampleRate',data,'DecimationFactor',decim);
q = fuse(accelerometerReadings,gyroscopeReadings,magnetometerReadings);

time = (0:decim:size(accelerometerReadings,1)-1)/Fs;

plot(time,eulerd(q,'ZYX','frame'))
title('Orientation Estimate')
legend('z-axis', 'y-axis', 'x-axis')
ylabel('Rotation (degrees)')
fclose(data);