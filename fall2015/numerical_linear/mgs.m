function [ Q,R ] = mgs( A )

n=size(A,2);
V = A;
R = zeros(n);
Q = zeros(size(A));

for i=1:n
    R(i,i) = norm(V(:,i));
    Q(:,i) = V(:,i)/R(i,i);
    for j=i+1:n
        R(i,j) = dot(conj(Q(:,i)),V(:,j));
        V(:,j) = V(:,j) - R(i,j)*Q(:,i);
    end
end

