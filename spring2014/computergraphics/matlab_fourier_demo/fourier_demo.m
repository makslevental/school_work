img = imread('boat.png');
[sx, sy] = size(img);

F = fftshift(fft2(img));

F2 = F; q = .2; %q = 2/5;
q = q/2.0;
F2(1:floor(sx*q), :) = 0; F2(floor((1-q)*sx):end, :) = 0; 
F2(:, 1:floor(sy*q)) = 0; F2(:, floor((1-q)*sy):end) = 0;

imgrec = abs(ifft2(ifftshift(F2))); imgrec = imgrec/(max(imgrec(:)));

fimg = log(abs(F)+1); fimg = fimg/max(fimg(:));
fimg2 = log(abs(F2)+1); fimg2 = fimg2/max(fimg2(:));

subplot(2,2,1);
% imshow(img);
imagesc(img); colormap(gray);

subplot(2,2,2);
% imshow(fimg);
imagesc(fimg);

subplot(2,2,3);
% imshow(imgrec);
imagesc(imgrec);

subplot(2,2,4);
% imshow(fimg2);
imagesc(fimg2);
