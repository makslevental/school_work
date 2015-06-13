data = randi([0 3],64,64);

modSignal = [];
receivedData5db = [];
receivedData15db = [];
receivedData25db = [];

fftSignal5db = [];
fftSignal15db = [];
fftSignal25db = [];
hMod = comm.QPSKModulator('PhaseOffset',pi/4);
% hAWGN = comm.AWGNChannel('NoiseMethod',...
%     'Signal to noise ratio (SNR)','SNR',15);
hDemod = comm.QPSKDemodulator('PhaseOffset',pi/4);

for i=1:64
    modSignal = [modSignal;step(hMod, data(:,i))];
    ifftSignal = ifft(step(hMod, data(:,i)));
%     noisySignal = step(hAWGN, modSignal);
%     noisySignal = step(hAWGN,ifftSignal);
    noisySignal25db = ifftSignal + (1/10^(25/20))*exp(1i *2*pi*(rand(2^6,1)));
    noisySignal15db = ifftSignal + (1/10^(15/20))*exp(1i *2*pi*(rand(2^6,1)));
    noisySignal5db = ifftSignal + (1/10^(5/20))*exp(1i *2*pi*(rand(2^6,1)));
    fftSignal5db = [fftSignal5db;fft(noisySignal5db)];
    fftSignal15db = [fftSignal15db;fft(noisySignal15db)];
    fftSignal25db = [fftSignal25db;fft(noisySignal25db)];
%     receivedData = step(hDemod, noisySignal);
   
    
end

receivedData5db = step(hDemod, fftSignal5db);
receivedData15db = step(hDemod, fftSignal15db);
receivedData25db = step(hDemod, fftSignal25db);
%Create an error rate calculator
hError = comm.ErrorRate;
errorStats1 = step(hError, reshape(data,2^12,1), receivedData5db);
fprintf('Error rate = %f\nNumber of errors for 5dB = %d\n', ...
    errorStats1(1), errorStats1(2))
%Create an error rate calculator
hError = comm.ErrorRate;
errorStats2 = step(hError, reshape(data,2^12,1), receivedData15db);
fprintf('Error rate = %f\nNumber of errors for 15dB = %d\n', ...
    errorStats2(1), errorStats2(2))
%Create an error rate calculator
hError = comm.ErrorRate;
errorStats3 = step(hError, reshape(data,2^12,1), receivedData25db);
fprintf('Error rate = %f\nNumber of errors for 25dB = %d\n', ...
    errorStats3(1), errorStats3(2))




figure
subplot(2,2,1)
plot(modSignal,'.');
title('No noise')
xlabel('In-phase')
ylabel('Quadrature')

subplot(2,2,2)
plot(fftSignal25db,'.');
title('SNR 25dB')
xlabel('In-phase')
ylabel('Quadrature')


subplot(2,2,3)
plot(fftSignal15db,'.');
title('SNR 15dB')
xlabel('In-phase')
ylabel('Quadrature')

subplot(2,2,4)
plot(fftSignal5db,'.');
title('SNR 5dB')
xlabel('In-phase')
ylabel('Quadrature')











% 
% 
% 
% % generate the 64*64 qpsk symbols { 1+j0, 0+j1, -1+j0, 0-j1}
% 
% qpsk = exp(1i *((pi/4)+ (pi/2) * randi([0 3],2^6,2^6)));
% 
% hue = dsp.UniformEncoder;
% hue.PeakValue = 1;
% hue.NumBits = 12;
% hue.OutputDataType = 'Signed integer';
% qpsk_encoded = step(hue, reshape(qpsk,2^12,1));
% 
% 
% % these agree
% qpskifft = ifft(qpsk,[],1);
% figure
% plot(qpsk,'o')
% 
% % test_qpskfft = ifft(qpsk(:,1));
% 
% % noise (25db,15db,5db) {z -> 17.7828}, {z -> 5.62341}, {z -> 1.77828}
% % noise {{{z -> 316.228}}, {{z -> 31.6228}}, {{z -> 3.16228}}}
% % noise25db = (1/17.7828)*exp(1i *2*pi*(rand(2^6,2^6)));
% % noise15db = (1/5.63241)*exp(1i *2*pi*(rand(2^6,2^6)));
% % noise5db = (1/1.77828)*exp(1i *2*pi*(rand(2^6,2^6)));
% % 
% noise25db = (1/316.228)*exp(1i *2*pi*(rand(2^6,2^6)));
% noise15db = (1/31.6228)*exp(1i *2*pi*(rand(2^6,2^6)));
% noise5db = (1/3.16228)*exp(1i *2*pi*(rand(2^6,2^6)));
% 
% % hist(angle(reshape(noise25db(:,:),1,64*64)),100)
% 
% qpskifft25db = qpskifft + noise25db;
% qpskifft15db = qpskifft + noise15db;
% qpskifft5db = qpskifft + noise5db;
% 
% qpskfft25db = 64*ifft(qpskifft25db,[],1);
% qpskfft15db = 64*ifft(qpskifft15db,[],1);
% qpskfft5db = 64*ifft(qpskifft5db,[],1);
% qpskfft0db = 64*ifft(qpskifft,[],1);
% 
% 
% qpskfft25db_encoded = step(hue, reshape(qpskfft25db,2^12,1));
% qpskfft15db_encoded = step(hue, reshape(qpskfft15db,2^12,1));
% qpskfft5db_encoded = step(hue, reshape(qpskfft5db,2^12,1));
% 
% decodedVec = step(comm.ErrorRate,qpsk_encoded,qpskfft25db_encoded);
% 
% disp(['Error rate after decoding: ',num2str(decodedVec(1))])
% 
% figure
% subplot(2,2,1)
% plot(qpskfft0db,'.');
% title('No noise')
% xlabel('In-phase')
% ylabel('Quadrature')
% 
% subplot(2,2,2)
% plot(qpskfft25db,'.');
% title('SNR 25dB')
% xlabel('In-phase')
% ylabel('Quadrature')
% 
% 
% subplot(2,2,3)
% plot(qpskfft15db,'.');
% title('SNR 15dB')
% xlabel('In-phase')
% ylabel('Quadrature')
% 
% subplot(2,2,4)
% plot(qpskfft5db,'.');
% title('SNR 5dB')
% xlabel('In-phase')
% ylabel('Quadrature')
% 
% hMod = comm.QPSKModulator('PhaseOffset',pi/4);
% hAWGN = comm.AWGNChannel('NoiseMethod',...
%     'Signal to noise ratio (SNR)','SNR',15);
% hDemod = comm.QPSKDemodulator('PhaseOffset',pi/4);
% %Create an error rate calculator
% hError = comm.ErrorRate;
% for counter = 1:1
%     % Transmit a 50-symbol frame
%     data = randi([0 3],50,1);
%     modSignal = step(hMod, data);
%     noisySignal = step(hAWGN, modSignal);
%     receivedData = step(hDemod, noisySignal);
%     errorStats = step(hError, data, receivedData);
% end
% fprintf('Error rate = %f\nNumber of errors = %d\n', ...
%     errorStats(1), errorStats(2))
