%% GUIequalizer - main function
% In this script, we set 'Tag' values to the different graphic buttons to
% be able to find and use them in other functions
function GUIequalizer
    % Create the Graphic User Interface (GUI) for the equaliser
    figure('Name','Tuning GUI','Position',[100,400,520,500], 'Resize','off');

    % Construct the components, their Tags, their values and connexions
    % frequency1
    uicontrol('Style','text','String','Center Frequency','Position',[10, 450, 100, 35],...
              'Tag','frequencytitle1');
    uicontrol('Style','slider','Min',0,'Max',15000,'Value',11025,'Position',[120,450,250,25],...
              'Tag','frequency1','Callback',{@frequency1_callback});
    uicontrol('Style','edit', 'String', '11025', 'Position',[400,453,100,20],...
              'Tag','frequencycontrol1','Callback',{@frequencycontrol1_callback});

    % bandwidth1
    uicontrol('Style','text','String','Bandwidth','Position',[10,375,100,20],...
             'Tag','bandwidthtitle1');
    uicontrol('Style','slider','Min',0,'Max',10000,'Value',2205,'Position',[120,375,250,25],...
              'Tag','bandwidth1','Callback',{@bandwidth1_callback});
    uicontrol('Style','edit', 'String', '2205','Position',[400,378,100,20],...
              'Tag','bandwidthcontrol1','Callback',{@bandwidthcontrol1_callback});
   
    % gain1
    uicontrol('Style','text','String','Gain','Position',[10, 300, 100, 20],'Tag','gaintitle1');
    uicontrol('Style','slider','Max',20,'Min',-20,'Value',1,'Position',[120,300,250,25],...
              'Tag','gain1','Callback',{@gain1_callback});
    uicontrol('Style','edit','String','1','Position',[400,303,100,20],...
              'Tag','gaincontrol1','Callback',{@gaincontrol1_callback});
   
    % frequency2
    uicontrol('Style','text','String','Center Frequency 2','Position', [10,225,100,35],...
              'Tag', 'frequencytitle2');
    uicontrol('Style','slider','Min',0,'Max',15000,'Value',11025,'Position',[120,225,250,25],...
              'Tag', 'frequency2','Callback',{@frequency2_callback});
    uicontrol('Style','edit', 'String', '11025', 'Position',[400,228,100,20],...
              'Tag', 'frequencycontrol2','Callback',{@frequencycontrol2_callback});                              
   
    % bandwidth2
    uicontrol('Style','text','String', 'Bandwidth 2','Position',[10,150,100,20],...
              'Tag','bandwidthtitle2');
    uicontrol('Style','slider','Min',0,'Max',10000,'Value',2205,'Position',[120,150,250,25],...
              'Tag','bandwidth2','Callback',{@bandwidth2_callback});
    uicontrol('Style','edit', 'String', '2205', 'Position',[400,153,100,20],...
              'Tag','bandwidthcontrol2','Callback',{@bandwidthcontrol2_callback});                        

    % gain2
    uicontrol('Style','text', 'String', 'Gain 2','Position',[10, 75, 100, 20],'Tag','gaintitle2');
    uicontrol('Style','slider','Max',20,'Min',-20,'Value',0,'Position',[120,75,250,25],...
              'Tag','gain2','Callback',{@gain2_callback});
    uicontrol('Style','edit', 'String', '0', 'Position',[400,78,100,20],...
              'Tag','gaincontrol2','Callback',{@gaincontrol2_callback});                   

    % reset
    uicontrol('Style','pushbutton','Callback',{@resetButton_callback},...
              'String','Reset Values','Position',[175,20,100,30],'Tag','treset');
    % pause
    guiPause = uicontrol('Style','pushbutton','Callback',{@pauseButton_callback},...
                       'String','Pause','Position',[50,20,100,30], 'Tag', 'tpause');
    % stop
    guiStop = uicontrol('Style','pushbutton','Callback',{@stopButton_callback},...
                      'String','Stop','Position', [300,20,100,30], 'Tag', 'tstop');
    % storing data for pause and stop with setappdata for later use on other functions
    setappdata(guiPause, 'Value', 0);
    setappdata(guiStop, 'Value', 0);
end

%% function pause
    function  pauseButton_callback(~, ~)
        hpause = findobj('Tag','tpause');
        paused = getappdata(hpause, 'Value');
        switch paused
            case 1
                setappdata(hpause, 'Value', 0);    
                set(hpause,'String','Pause');
            case 0
                setappdata(hpause, 'Value', 1);
                set(hpause,'String','Resume');
        end
    end
    
%% function to stop/quit
    function stopButton_callback(~, ~)
        hstop = findobj('Tag', 'tstop');
        setappdata(hstop,'Value',1);
    end
    
%% function to reset all values
function resetButton_callback(~, ~)
    % frequency1 and 2
    hfrequency1 = findobj('Tag','frequency1');
    set(hfrequency1,'Value',11025);
    frequency1_callback;
    hfrequency2 = findobj('Tag','frequency2');
    set(hfrequency2,'Value',11025);
    frequency2_callback;
    
    % bandwidth1 and 2
    hbandwidth1 = findobj('Tag','bandwidth1');
    set(hbandwidth1,'Value',2205);
    bandwidth1_callback;
    hbandwidth2 = findobj('Tag','bandwidth2');
    set(hbandwidth2,'Value',2205);
    bandwidth2_callback;
    
    % gain1 and 2
    hgain1 = findobj('Tag','gain1');
    set(hgain1,'Value',1);
    gain1_callback;
    hgain2 = findobj('Tag','gain2');
    set(hgain2,'Value',0);
    gain2_callback;
end

%% functions to modify volumes
%% frequency1 and 2
function frequency1_callback(~, ~)
    hfrequency1 = findobj('Tag','frequency1');
    hfrequencycontrol1 = findobj('Tag','frequencycontrol1');
    frequency1 = get(hfrequency1,'Value');
    set(hfrequencycontrol1,'String',frequency1);
end
function frequencycontrol1_callback(~,~)
    hfrequencycontrol1 = findobj('Tag','frequencycontrol1');
    hfrequency1 = findobj('Tag','frequency1');
    frequency1 = get(hfrequencycontrol1,'String');
    frequency1 = str2num(frequency1);
    set(hfrequency1,'Value',frequency1);
end

function frequency2_callback(~, ~)
    hfrequency2 = findobj('Tag','frequency2');
    hfrequencycontrol2 = findobj('Tag','frequencycontrol2');
    frequency2 = get(hfrequency2,'Value');
    set(hfrequencycontrol2,'String',frequency2);    
end
function frequencycontrol2_callback(~,~)
    hfrequencycontrol2 = findobj('Tag','frequencycontrol2');
    hfrequency2 = findobj('Tag','frequency2');
    frequency2 = get(hfrequencycontrol2,'String');
    frequency2 = str2num(frequency2);
    set(hfrequency2,'Value',frequency2);
end
%% bandwidth1 and 2
function bandwidth1_callback(~, ~)
    hbandwidth1 = findobj('Tag','bandwidth1');
    hbandwidthcontrol1 = findobj('Tag','bandwidthcontrol1');
    bandwidth1 = get(hbandwidth1,'Value');
    set(hbandwidthcontrol1,'String',bandwidth1);
end
function bandwidthcontrol1_callback(~, ~)
    hbandwidth1 = findobj('Tag','bandwidth1');
    hbandwidthcontrol1 = findobj('Tag','bandwidthcontrol1');
    bandwidth1 = get(hbandwidthcontrol1,'String');
    bandwidth1 = str2num(bandwidth1);
    set(hbandwidth1,'Value',bandwidth1);
end

function bandwidth2_callback(~, ~)
    hbandwidth2 = findobj('Tag','bandwidth2');
    hbandwidthcontrol2 = findobj('Tag','bandwidthcontrol2');
    bandwidth2 = get(hbandwidth2,'Value');
    set(hbandwidthcontrol2,'String',bandwidth2);
end
function bandwidthcontrol2_callback(~, ~)
    hbandwidth2 = findobj('Tag','bandwidth2');
    hbandwidthcontrol2 = findobj('Tag','bandwidthcontrol2');
    bandwidth2 = get(hbandwidthcontrol2,'String');
    bandwidth2 = str2num(bandwidth2);
    set(hbandwidth2,'Value',bandwidth2);
end
%% gain1 and 2
function gain1_callback(~, ~)
    hgain1 = findobj('Tag','gain1');
    hgaincontrol1 = findobj('Tag','gaincontrol1');
    gain1 = get(hgain1,'Value');
    set(hgaincontrol1,'String',gain1);
end
function gaincontrol1_callback(~, ~)
    hgain1 = findobj('Tag','gain1');
    hgaincontrol1 = findobj('Tag','gaincontrol1');
    gain1 = get(hgaincontrol1,'String');
    gain1 = str2num(gain1);
    set(hgain1,'Value',gain1);
end

function gain2_callback(~, ~)
    hgain2 = findobj('Tag','gain2');
    hgaincontrol2 = findobj('Tag','gaincontrol2');
    gain2 = get(hgain2,'Value');
    set(hgaincontrol2,'String',gain2);
end
function gaincontrol2_callback(~, ~)
    hgain2 = findobj('Tag','gain2');
    hgaincontrol2 = findobj('Tag','gaincontrol2');
    gain2 = get(hgaincontrol2,'String');
    gain2 = str2num(gain2);
    set(hgain2,'Value',gain2);
end