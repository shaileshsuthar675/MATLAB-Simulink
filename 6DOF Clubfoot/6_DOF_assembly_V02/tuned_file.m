clear;
close all;
TunedBlocks = {'PD1', 'PD2', 'PD3','PD4', 'PD5', 'PD6', 'PD7'};
ST0 = slTuner('Six_DOF_assembly2', TunedBlocks);

addPoint(ST0, TunedBlocks);

addPoint(ST0, 'Robot/qm');

RefSignals = {'Six_DOF_assembly2/Signal Builder/q1', 'Six_DOF_assembly2/Signal Builder/q2', 'Six_DOF_assembly2/Signal Builder/q3','Six_DOF_assembly2/Signal Builder/q4', 'Six_DOF_assembly2/Signal Builder/q5', 'Six_DOF_assembly2/Signal Builder/q6', 'Six_DOF_assembly2/Signal Builder/q7'};
addPoint(ST0, RefSignals);

Controls = TunedBlocks;
Measurements = 'Six_DOF_assembly2/Robot/qm';
options = looptuneOptions('RandomStart',80','UseParallel',false);
TR = TuningGoal.StepTracking(RefSignals, Measurements, 0.05,0);
ST1 = looptune(ST0, Controls, Measurements, TR, options);

writeBlockValue(ST1);
