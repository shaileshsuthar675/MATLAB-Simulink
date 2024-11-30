clear;
close all;
TunedBlocks = {'PD1', 'PD2', 'PD3'};
ST0 = slTuner('DOF3_Test3', TunedBlocks);

addPoint(ST0, TunedBlocks);

addPoint(ST0, 'Robot/qm');

RefSignals = {'DOF3_Test3/Signal Builder/q1', 'DOF3_Test3/Signal Builder/q2', 'DOF3_Test3/Signal Builder/q3'};
addPoint(ST0, RefSignals);

Controls = TunedBlocks;
Measurements = 'DOF3_Test3/Robot/qm';
options = looptuneOptions('RandomStart',80','UseParallel',false);
TR = TuningGoal.StepTracking(RefSignals, Measurements, 0.05,0);
ST1 = looptune(ST0, Controls, Measurements, TR, options);

writeBlockValue(ST1);

