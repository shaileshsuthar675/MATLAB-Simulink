clear;
close all;
TunedBlocks = {'PD3','PD4', 'PD5', 'PD6'};
ST0 = slTuner('Assembly3', TunedBlocks);

addPoint(ST0, TunedBlocks);

addPoint(ST0, 'Orthosis/qm');

RefSignals = {'Assembly3/Signal Builder/q3', 'Assembly3/Signal Builder/q4', 'Assembly3/Signal Builder/q5','Assembly3/Signal Builder/q6'};
addPoint(ST0, RefSignals);

Controls = TunedBlocks;
Measurements = 'Assembly3/Orthosis/qm';
options = looptuneOptions('RandomStart',80','UseParallel',false);
TR = TuningGoal.StepTracking(RefSignals, Measurements, 0.05,0);
ST1 = looptune(ST0, Controls, Measurements, TR, options);

writeBlockValue(ST1);
