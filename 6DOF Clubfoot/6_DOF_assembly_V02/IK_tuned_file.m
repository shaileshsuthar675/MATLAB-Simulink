clear;
close all;
TunedBlocks = {'PD8', 'PD9', 'PD10','PD11', 'PD12', 'PD13', 'PD14'};
ST0 = slTuner('IK_Six_DOF_assembly2', TunedBlocks);

addPoint(ST0, TunedBlocks);

addPoint(ST0, 'Robot1/qm');

RefSignals = {'IK_Six_DOF_assembly2/Signal Builder/t1', 'IK_Six_DOF_assembly2/Signal Builder/t2', 'IK_Six_DOF_assembly2/Signal Builder/t3','IK_Six_DOF_assembly2/Signal Builder/t4', 'IK_Six_DOF_assembly2/Signal Builder/t5', 'IK_Six_DOF_assembly2/Signal Builder/t6', 'IK_Six_DOF_assembly2/Signal Builder/t7'};
addPoint(ST0, RefSignals);

Controls = TunedBlocks;
Measurements = 'IK_Six_DOF_assembly2/Robot1/qm';
options = looptuneOptions('RandomStart',80','UseParallel',false);
TR = TuningGoal.StepTracking(RefSignals, Measurements, 0.05,0);
ST1 = looptune(ST0, Controls, Measurements, TR, options);

writeBlockValue(ST1);
