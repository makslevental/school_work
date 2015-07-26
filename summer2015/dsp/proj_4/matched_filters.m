m=[-1,-1,1,1,-1];
s1=[-1,1,-1,1,1];
s2=[-1,-1,-1,-1,1];
s3=[-1,1,-1,-1,1];
s4=[1,-1,-1,-1,1];

d=reshape(repmat(m,5,1),1,25);
S1=repmat(s1,1,5);
S2=repmat(s2,1,5);
S3=repmat(s3,1,5);
S4=repmat(s4,1,5);

p1=S1.*d;
p2=S2.*d;
p3=S3.*d;
p4=S4.*d;

h1=fliplr(s1);
h2=fliplr(s2);
h3=fliplr(s3);
h4=fliplr(s4);

y1=conv(p1,h1);
y2=conv(p2,h2);
y3=conv(p3,h3);
y4=conv(p4,h4);

m1=y1(abs(y1) >= 5)/5;
m2=y2(abs(y2) >= 5)/5;
m3=y3(abs(y3) >= 5)/5;
m4=y4(abs(y4) >= 5)/5;

%%%%%%%%%%%%%%%%%%%%%%


m=datasample([-1 1],20);
s1=[-1,1,-1,1,1];
s2=[-1,-1,-1,-1,1];

%upsample m 5 times
d=reshape(repmat(m,5,1),1,100);
S1=repmat(s1,1,20);

p1=S1.*d;

h1=fliplr(s1);
h2=fliplr(s2);

y1=conv(p1,h1);
y2=conv(p1,h2);

%no noise correctly matched
m1=y1(abs(y1) >= max(y1))/max(y1);
%no noise incorreectly matched
m2=y2(abs(y2) >= 3)/3;

% M=[m;m1;m2];

%noise
awgnoise = struct();
awgnoise.reqSNR = 10;
%power in watts, i.e. energy divided by time
awgnoise.sigPower = sum(abs(p1(:)).^2)/length(p1(:));
%convert to dBW; dBW is ratio of power of signal relative to 1 watt
awgnoise.sigPower = 10*log10(awgnoise.sigPower);
%because both in db log(S/N)=logS-logN
awgnoise.noisePowerdBW = awgnoise.sigPower-awgnoise.reqSNR;
%invert
awgnoise.noisePowerW = 10^(awgnoise.noisePowerdBW/10);
%because the variance should be noise, hence sqrt
awgnoise.noise = (sqrt(awgnoise.noisePowerW))*randn(1, 100);


np1 = awgn(p1,10,'measured');
% nnp1 = p1+awgnoise.noise;
% plot(x,np1,'b',x,nnp1,'r')

ny1 = conv(np1,h1);
% plot(1:104,ny1)

%what happens when the threshholding produces too few values?
threshed = ny1(abs(ny1) >= 4);

hold on;
stem(threshed(1:20),'r')
stem(m)
hold off;

e=m.*threshed;
sum(e<0)/20