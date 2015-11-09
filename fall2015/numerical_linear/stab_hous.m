% (a)
n=zeros(5,4);
for i=1:5
    S=diag(sort(rand(1,50),'descend'));
    U = orth(rand(50));
    V = orth(rand(50));
    if(rank(U)+rank(V) ~= 100)
        error('rank deficient');
    end
    A=U*S*V';
    [U2,S2,V2]=svd(A);
    
    n(i,:)=[norm(U-U2),norm(S-S2),norm(V-V2),norm(A-U2*S2*V2')];
end

% (c)
n=zeros(5,5);
for i=1:5
    S=diag(sort(rand(1,50),'descend'));
    S=S.^6;
    U = orth(rand(50));
    V = orth(rand(50));
    if(rank(U)+rank(V) ~= 100)
        error('rank deficient');
    end
    A=U*S*V';
    [U2,S2,V2]=svd(A);
    U2 = U2*diag(sign(diag(U2'*U)));
    V2 = V2*diag(sign(diag(V2'*V)));
    n(i,:)=[norm(U-U2),norm(S-S2),norm(V-V2),norm(A-U2*S2*V2'),cond(A)];
end