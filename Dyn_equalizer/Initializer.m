% Just to be sure
close all

% Calls the function to make the audio file we want to use
make_music;

% Initiate important variables - We use dsp library from there
SamplesPerFrame = 1024;
audioFile = dsp.AudioFileReader('music.wav', 'SamplesPerFrame', SamplesPerFrame);
fs = audioFile.SampleRate;

% Initiate transfer function
transFunc = dsp.TransferFunctionEstimator('FrequencyRange', 'onesided',...
                                          'SpectralAverages', 50);
% Initiate plots
arrayPlot = dsp.ArrayPlot('PlotType', 'Line',...
                          'YLimits', [-20 20], 'SampleIncrement', fs/(2*512),...
                          'YLabel', 'Magnetude (dB)', 'XLabel', 'Frequency (Hz)',...
                          'Name', 'H=Y/X Transfer Function Estimate',...
                          'Position',[900,500,600,400]);
spectre = dsp.SpectrumAnalyzer('SampleRate', fs, 'PlotAsTwoSidedSpectrum', false,...
                               'SpectralAverages', 20, 'FrequencyScale','Log','Name','AudioOut Spectrum',...
                               'Position',[1000,50,600,400]);
scope = dsp.TimeScope('SampleRate', fs, 'BufferLength', 4*fs,...
                      'TimeSpan', 1, 'YLimits', [-4 4], 'ShowGrid', true,'Name','AudioOut Scope',...
                      'Position',[400,50,600,400]);
% Initiate player
player = dsp.AudioPlayer('SampleRate', fs);

% Initiate equalizer
GUIequalizer
hpause = findobj('Tag', 'tpause');
hstop = findobj('Tag', 'tstop');

% tic; % time initialisation, unneeded
while ~isDone(audioFile)
    pauseSim = getappdata(hpause, 'Value');
    stopSim = getappdata(hstop, 'Value');
    if pauseSim == 0
        audioIn = step(audioFile);
    end
    if pauseSim == 1
        drawnow;
        continue;
    end
    
    if stopSim == 1
        break;
    end

    audioOut = audioAlgorithm(audioIn); % process audio Out
    H = step(transFunc, audioIn, audioOut); % transfer function
    step(arrayPlot, 20*log10(abs(H)));  % plots result as arrayplot
    
    % if necessary, to analyse audioOut from other perspectives
    % step(spectre, audioOut); % plots result as spectre
    % step(scope, audioOut); % plots result as scope
    
    step(player, audioOut); % plays result % comment out to suppress sound
end

close 'Tuning GUI'

% Release the dsp components for a cleaner quit
release(arrayPlot)
release(scope)
release(spectre)
release(player)
release(transFunc)