%% This algorithm takes in an audio and gives out an audio based on modifications made in the GUIequalizer
function y = audioAlgorithm(u)

    persistent PE1 PE2;
    hfrequency1 = findobj('Tag','frequency1');
    frequency1 = get(hfrequency1,'Value');
    hfrequency2 = findobj('Tag','frequency2');
    frequency2 = get(hfrequency2,'Value');
    
    hbandwidth1 = findobj('Tag','bandwidth1');
    bandwidth1 = get(hbandwidth1,'Value');
    hbandwidth2 = findobj('Tag','bandwidth2');
    bandwidth2 = get(hbandwidth2,'Value');
    
    hgain1 = findobj('Tag','gain1');
    gain1 = get(hgain1,'Value');
    hgain2 = findobj('Tag','gain2');
    gain2 = get(hgain2,'Value');
    
    if isempty(PE1)
        PE1 = dsp.ParametricEQFilter('Bandwidth', bandwidth1,'CenterFrequency', frequency1, 'PeakGaindB', gain1);
        PE2 = dsp.ParametricEQFilter('Bandwidth', bandwidth2,'CenterFrequency', frequency2, 'PeakGaindB', gain2);
    end

    % u = audio In
    [PE1, PE2] = processParameters(PE1, PE2);
    v = step(PE1, u); % v = audio In after PE1 modifications
    y = step(PE2, v); % y = audio Out after PE1 and PE2 modifications
end
%% GUIequalizer part
function [PE1, PE2] = processParameters(PE1, PE2)
    
    hfrequency1 = findobj('Tag','frequency1');
    frequency1 = get(hfrequency1,'Value');
    hfrequency2 = findobj('Tag','frequency2');
    frequency2 = get(hfrequency2,'Value');
    
    hbandwidth1 = findobj('Tag','bandwidth1');
    bandwidth1 = get(hbandwidth1,'Value');
    hbandwidth2 = findobj('Tag','bandwidth2');
    bandwidth2 = get(hbandwidth2,'Value');
    
    hgain1 = findobj('Tag','gain1');
    gain1 = get(hgain1,'Value');
    hgain2 = findobj('Tag','gain2');
    gain2 = get(hgain2,'Value');
    
    PE1 = dsp.ParametricEQFilter('Bandwidth',bandwidth1,'CenterFrequency',frequency1,'PeakGaindB',gain1);
    PE2 = dsp.ParametricEQFilter('Bandwidth',bandwidth2,'CenterFrequency',frequency2,'PeakGaindB',gain2);  
end