clear all;
N=15;
h= fir1(N-1,[0.3 0.5],'bandpass',hanning(N));
figure(1)
freqz(h,1)
title('N=15,ººÄþ´°');
N=45;
h= fir1(N-1,[0.3 0.5],'bandpass',hanning(N));
figure(2)
freqz(h,1)
title('N=45,ººÄþ´°');
