N=3;

d = 100*rand(N,1); % The diagonal values
d = floor(d);
t = triu(bsxfun(@min,d,d.').*rand(N),1); % The upper trianglar random values
t = floor(t);
M = diag(d)+t+t.'; % Put them together in a symmetric matrix

U=chol(M'*M);
[Q,R]=qr(M,0);