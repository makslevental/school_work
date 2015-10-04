d = rgb2gray(imread('durer.jpg'));
D = double(d);
e = rgb2gray(imread('escher.jpg'));
E = double(e);

ranks = [5,15,30];

[dU, dS, dV] = svd(D);

for i=1:3
    rank = ranks(i);
    t = dS;
    t(:,rank+1:end)=0;
    figure;
    image(dU*t*dV');
    colormap(gray(256));
end

[eU, eS, eV] = svd(E);


for i=1:3
    rank = ranks(i);
    t = eS;
    t(:,rank+1:end)=0;
    figure;
    image(eU*t*eV');
    colormap(gray(256));
end

