A=diag(1:100)+diag(ones(1,99),1)+diag(ones(1,99),-1);
b=ones(100,1);

CGx={};CGr={};CGp={};
CGx{1} = zeros(100,1); CGr{1} = b; CGp{1} = CGr{1};

for n=2:100    
    an = (CGr{n-1}'*CGr{n-1})/(CGp{n-1}'*A*CGp{n-1});
    CGx{n} = CGx{n-1} + an.*CGp{n-1};
    CGr{n} = CGr{n-1} - an.*(A*CGp{n-1});
    bn = (CGr{n}'*CGr{n})/(CGr{n-1}'*CGr{n-1});
    CGp{n} = CGr{n} + bn.*CGp{n-1};
end

norm(CGx{100}-A\b)


SDx={};SDr={};
SDx{1} = zeros(100,1); SDr{1} = b; 

for n=2:100
    an = (SDr{n-1}'*SDr{n-1})/(SDr{n-1}'*A*SDr{n-1});
    SDr{n} = SDr{n-1} - an.*(A*SDr{n-1});
    SDx{n} = SDx{n-1} + an.*SDr{n};
end

norm(SDx{100}-A\b)

ka = max(eig(A))/min(eig(A));

plot(1:100,cellfun(@(x)(log(norm(x))),CGr),'-.r*',...
    1:100,cellfun(@(x)(log(norm(x))),cellfun(@(x)(b-A*x),CGx,'UniformOutput',false)),'--mo',...
    1:100,cellfun(@(x)(log(norm(x))),SDr),':bs',...
    1:100,log(2*((sqrt(ka)-1)/(sqrt(ka)+1)).^(1:100)),':gx')
legend('est resid norms CG','act resid norms CG','resid norms SD','k');