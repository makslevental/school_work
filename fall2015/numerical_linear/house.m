function [ Q,W,R ] = house( A )
%HOUSE computes implicit representation of QR using householder 
%orthogonal trianglurization
[m,n]=size(A);
W=zeros([m,n]);
R=A;
for k=1:n
    x = R(k:m,k);
    vk = sign(x(1))*norm(x)*vertcat(1,zeros(m-k,1)) + x;
    vk = vk/norm(vk);
    W(k:m,k) = vk;
    R(k:m,k:n) = R(k:m,k:n) - 2*vk*(vk'*R(k:m,k:n));
end

Q = formQ(W);

end

function Q=formQ(W)
%formQ reconstructs Q from W by computing Qe_i for i=1,..,m
[m,n]=size(W);
Q=eye(m);
for j=1:m
    for k=n:-1:1
        Q(k:m,j) = Q(k:m,j) - 2*W(k:m,k)*(W(k:m,k)'*Q(k:m,j));
    end
end

end


