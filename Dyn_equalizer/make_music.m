% we want to make one file out of the free .wav we have
function make_music
    fs = 44100;
    %frame_duration = .1; % duration of a frame, unneeded here
    %frame_length = frame_duration*fs; % length of a frame, unneeded here

    % Create the file if it doesn't exist
    if exist('music.wav','file') ~= 2
        
        bass = audioread('bass.wav');
        drums = audioread('drums.wav');
        guitar = audioread('guitar.wav');

        Nb = length(bass);
        Nd = length(drums);
        Ng = length(guitar);
        
        % Find the longest file
        if Nb >= Nd
            Nmax = Nb;
        else
            Nmax = Nd;
        end
        if Ng >= Nmax
            Nmax = Ng;
        end
        
        % Give all files same length
        bass(Nb:Nmax)=0;
        drums(Nd:Nmax)=0;
        guitar(Ng:Nmax)=0;
        
        % we make music.wav with two channels, and will probably try later on to influence one of them at a time
        music = zeros(Nmax,2);
        music(:,1) = bass + drums + guitar;
        music(:,2) = bass + drums + guitar;
        
        % Create the final file
        audiowrite('music.wav',music,fs);

    % If the file already exists    
    else
        % then do nothing
    end
end