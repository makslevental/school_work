D = diag(-ones(32,1))+diag(ones(31,1),1)+diag(ones(31,1),-1);
eps = 10.^(-(1:8));
M=zeros(1000,1000);
f=@(x,y)(min(svds((x+1i*y).*eye(32)-D,32)));

[X,Y] = meshgrid(-2:.002:2, -2:.002:2);
Z = zeros(2001,2001);
for i=1:2001
    for j=1:2001
        Z(i,j)=f(X(i,j),Y(i,j));
    end
end