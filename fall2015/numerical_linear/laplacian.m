t=randn(1,100); t1=randn(1,99); T = diag(t)+diag(t1,1)+diag(t1,-1);

[V,D]=eig(T);

figure; axes; hold on;
for i=1:10
    plot(1:100,log(abs(V(:,i))),'color',[rand rand rand]);
end

W = abs(V) >= 10.^(-10); sum(W(:))/10000

% part 2

T = diag(2.*ones(1,100))+diag(-ones(1,99),-1)+diag(-ones(1,99),1);

[V,D]=eig(T);

figure; axes; hold on;
for i=1:5
    plot(1:100,log(abs(V(:,i))),'color',[rand rand rand]);
end

W = abs(V) >= 10.^(-10); sum(W(:))/10000