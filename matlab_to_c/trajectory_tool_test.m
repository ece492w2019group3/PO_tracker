ld = load('rpy_9axis.mat');

acc = ld.sensorData.Acceleration;
angularVelocity = ld.sensorData.AngularVelocity;
fs = ld.Fs;

time = 0:length(acc);

accID = fopen('acc.txt','w');
for i=1:length(acc(:,1))
    fprintf(accID,'%6.4f %6.4f %6.4f\n',acc(i,1), acc(i,2), acc(i,3));
    
end 
fclose(accID);

angularVelocityID = fopen('angularVelocity.txt','w');
for i=1:length(acc(:,1))
    fprintf(angularVelocityID,'%6.4f %6.4f %6.4f\n',angularVelocity(i,1), angularVelocity(i,2), angularVelocity(i,3));
end
fclose(angularVelocityID);

position = zeros(length(acc(:,1)),3);

% [position] = trajectory_tool(acc, gyro);
acc_temp = zeros(2,3);
angularVelocity_temp = zeros(2,3);
acc_temp(1,:) = acc(1,:);
angularVelocity_temp(1,:) = angularVelocity(1,:); 
prev_pos = zeros(1, 3);
prev_orientation = zeros(3,3);
prev_velocity = zeros(1, 3); 
prev_acc = zeros(1,3);
for i = 1:length(acc(:,1))
     acc_temp(2,:) = acc(i,:);
     angularVelocity_temp(2,:) = angularVelocity(i,:);
     [p, o, v, a, av]  = trajectory_tool(acc_temp, angularVelocity_temp, prev_pos,prev_orientation, prev_velocity, prev_acc);
     prev_pos = p;
     prev_acc = a(2, :);
     % prev_orientation = o(:, :, 2);
     disp(p);
     prev_velocity = v(2, :);
     position(i,:) = p;
     acc_temp(1,:) = acc_temp(2,:);
     angularVelocity_temp(1,:) = angularVelocity(2,:);
     % angularVelocity_kal(i,:) = a;     
end

figure(1)
t = [1:1:1600];
plot(t,position)
legend('X-axis','Y-axis','Z-axis')
xlabel('Time (s)')
ylabel('Displacement (m)')
title('Displacement over Time')
%}
%{
accID = fopen('acc.txt','w');
fprintf(accID,'%6.4f %6.4f %6.4f\n',acc);
fclose(accID);

angularVelocityID = fopen('angularVelocity.txt','w');
fprintf(angularVelocityID,'%6.4f %6.4f %6.4f\n',angularVelocity);
fclose(angularVelocityID);

trajectory = kinematicTrajectory;
position1 = trajectory(acc, angularVelocity);
% disp(position1)

figure(2)
t = [1:1:1600];
plot(t,position1)
legend('X-axis','Y-axis','Z-axis')
xlabel('Time (s)')
ylabel('Displacement (m)')
title('Displacement over Time')
%}