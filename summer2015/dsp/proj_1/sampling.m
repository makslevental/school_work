%----------------------part 1


freqs = [689, 10002, 1716, 2589, 12088];
freqnumber = 4;

f=freqs(freqnumber + 1);

siglength = 1;
samprate = 44100;

t = 0:0.0000005:siglength; 
xa = sin(2*pi*f*t); 

% subplot(2,2,1) 
% plot(t,xa);grid 
% xlabel('Time, msec');ylabel('Amplitude'); 
% title(['Continuous-time signal x_{' num2str(freqnumber) '}(t)']); 
% %axis([0 1 -1.2 1.2]) 
% axis([0 .01 -1.2 1.2])
% 
% T = 1/samprate; 
% n = 0:T:siglength;
% L = length(n);
% xs = sin(2*pi*f*n); 
% k = 0:length(n)-1; 
% 
% subplot(2,2,2); 
% stem(k,xs);grid; 
% xlabel('Time index n');ylabel('Amplitude'); 
% title(['Discrete-time signal x_{' num2str(freqnumber) '}[n]']); 
% %axis([0 (length(n)-1) -1.2 1.2]) 
% axis([0 (L-1)*.01 -1.2 1.2])


signals = arrayfun(@(x)(sin(2*pi*x*n)),freqs,'UniformOutput', false); 
signalscont = arrayfun(@(x)(sin(2*pi*x*t)),freqs,'UniformOutput', false); 

sumsig = signals{1} + .5*signals{2} + (1/3)*signals{3} + .25*signals{4} + .2*signals{5};
sumsigcont = signalscont{1} + .5*signalscont{2} + (1/3)*signalscont{3} + .25*signalscont{4} + .2*signalscont{5};
downsumsig = downsample(sumsig,4);

subplot(2,2,1) 
plot(t,sumsigcont);grid 
xlabel('Time, msec');ylabel('Amplitude'); 
title('x(t)=x_{0}(t)+ .5 x_{1}(t)+ .333 x_{2}(t)+ .25 x_{3}(t)+ .25 x_{4}(t)')
%axis([0 1 -1.2 1.2]) 
axis([0 .01 -2.2 2.2])

T = 1/samprate; 
n = 0:T:siglength;
L = length(n);
xs = sin(2*pi*f*n); 
k = 0:length(n)-1; 

subplot(2,2,2); 
plot(downsample(n,4),downsumsig);
stem(downsample(n,4),downsumsig);grid; 

xlabel('Time index n');ylabel('Amplitude'); 
title(['Down-sampled x[4n]=x(4nT_s)']); 
%axis([0 (length(n)-1) -1.2 1.2]) 
axis([0 .01 -2 2])





sumNFFT = 2^nextpow2(L);
sumft = fft(sumsig,sumNFFT)/L;
f = samprate/2*linspace(0,1,sumNFFT/2+1);

% Plot single-sided amplitude spectrum of full sampled signal.
subplot(2,2,3);
plot(f,2*abs(sumft(1:sumNFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of x(t)=x_{0}(t)+x_{1}(t)+x_{2}(t)+x_{3}(t)+x_{4}(t)')
xlabel('Frequency (Hz)')
ylabel('|X(\omega)|')


downsumNFFT = 2^nextpow2(L/4);
downsumft = fft(downsumsig,downsumNFFT)/(L/4);
f = (samprate/4)/2*linspace(0,1,downsumNFFT/2+1);

% Plot single-sided amplitude spectrum of down sampled signal.
subplot(2,2,4);
plot(f,2*abs(downsumft(1:downsumNFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of down-sampled x[4n]=x(4nT_s)')
xlabel('Frequency (Hz)')
ylabel('|X(\omega)|')








%-----------------------part 2

chripp=chirp(n,0,1,8000);

%plot actual chirp
subplot(3,2,1)
plot(n,chripp);grid 
xlabel('Time, msec');ylabel('Amplitude'); 
title(['Chirp signal sampled @ 44.1kHz']); 
axis([0 .25 -1.2 1.2])

chirpNFFT = 2^nextpow2(L);
chirpft = fft(chripp,chirpNFFT)/L;
f = samprate/2*linspace(0,1,chirpNFFT/2+1);

%plot fft of chirp
subplot(3,2,2)
plot(f,2*abs(chirpft(1:chirpNFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of Chirp')
xlabel('Frequency (Hz)')
ylabel('|X(\omega)|')


[num,den]=cheby2(5,40,(samprate/16)/(samprate/2));
[H,w]=freqz(num,den); 

z=filter(num,den,chripp);
zfft = fft(z,sumNFFT)/(L);



% down sample the original chirp and the filter chirp
downchirp = downsample(chripp,4);

%plot downsampled chirp 
subplot(3,2,3)
plot(downsample(n,4),downchirp);grid 
xlabel('Time, msec');ylabel('Amplitude'); 
title(['Down-sampled Chirp signal']); 
axis([0 .25 -1.2 1.2])



%plot filtered chirp fft

subplot(3,2,5);
plot(f,2*abs(zfft(1:sumNFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of filtered Chirp')
xlabel('Frequency (Hz)')
ylabel('|X(\omega)|')





downz = downsample(z,4);

f = (samprate/4)/2*linspace(0,1,downsumNFFT/2+1);

% fft downsampled chirp and downsampled then filtered chirp
downchirpfft = fft(downchirp,downsumNFFT)/(L/4);
downzfft = fft(downz,downsumNFFT)/(L/4);

%plot downsampled chirp fft
subplot(3,2,4);
plot(f,2*abs(downchirpfft(1:downsumNFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of down-sampled Chirp')
xlabel('Frequency (Hz)')
ylabel('|X(\omega)|')


subplot(3,2,6);
plot(f,2*abs(downzfft(1:downsumNFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of filtered Chirp down-sampled')
xlabel('Frequency (Hz)')
ylabel('|X(\omega)|')