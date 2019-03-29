function [cur_position, orientation, velocity, acceleration, angularVelocity] = trajectory_tool(accelerometerReadings,angularvelocity, prev_position, prev_orientation, prev_velocity, prev_acc)
%TRAJECTORY_TOOL Summary of this function goes here
%   Detailed explanation goes here
trajectory = kinematicTrajectory('Position', prev_position, 'Orientation', prev_orientation, 'Velocity', prev_velocity, 'AccelerationSource', 'Property', 'Acceleration', prev_acc);
[position, orientation, velocity, acceleration, angularVelocity] = trajectory(angularvelocity);
cur_position = position(2,:)
end
