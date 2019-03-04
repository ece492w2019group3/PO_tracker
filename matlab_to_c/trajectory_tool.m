function [position] = trajectory_tool(accelerometerReadings,angularvelocity)
%TRAJECTORY_TOOL Summary of this function goes here
%   Detailed explanation goes here
trajectory = kinematicTrajectory;
[position,orientation,velocity,acceleration,angularVelocity] = trajectory(accelerometerReadings, angularvelocity);
end
