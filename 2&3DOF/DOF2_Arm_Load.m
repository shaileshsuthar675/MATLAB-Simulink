clear;
close all;
Ts = 0.001;
[DOF2_Arm,ArmInfo] = importrobot('DOF2_Test1');
% wp = [0.35 0 0.11;0.25 0.01 0.11;0.25 0.11 0.11;0.15 0.11 0.11;0.15 0.01 0.11;0.25 0.01 0.11];
wp = [0.35 0.25 0.25 0.15 0.15 0.25; 0 0.01 0.11 0.11 0.01 0.01; 0.11 0.11 0.11 0.11 0.11 0.11];
tp = [0 0.5 1.5 2.5 3.5 4.5];
