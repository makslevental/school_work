m=50;n=12;
t=linspace(0,1,m);
A=fliplr(vander(t));
A=A(:,1:n);
b=cos(4*t);

% (a)
xa = (A'*A)\(A'*b');
% (b)
[Q,R]=mgs(A);
xb = inv(R)*Q'*b';
% (c)
[Q,~,R]=house(A);
xc = inv(R(1:n,:))*Q(:,1:n)'*b';
% (d)
[Q,R]=qr(A,0);
xd = inv(R)*Q'*b';
% (e)
xe = A\b';
% (f)


