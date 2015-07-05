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
m2=y2(abs(y2) >= max(y2))/max(y2);

% M=[m;m1;m2];

%noise
powerp1=sum(p1.^2);
awgn=10*randn(100);
p1=S1.*d;