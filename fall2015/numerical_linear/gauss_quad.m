
T=@(k)(diag(.5./sqrt(1-(2*(1:k-1)).^(-2)),1)+diag(.5./sqrt(1-(2*(1:k-1)).^(-2)),-1));

I=[];
for n=1:40
    [Q,D]=eig(T(n));
    x = diag(D);
    w = 2*(Q(1,:).^2);
    I(n)=dot(w,exp(x));
end

I=[];
for n=1:40
    [Q,D]=eig(T(n));
    x = diag(D);
    w = 2*(Q(1,:).^2);
    I(n)=dot(w,exp(abs(x)));
end

