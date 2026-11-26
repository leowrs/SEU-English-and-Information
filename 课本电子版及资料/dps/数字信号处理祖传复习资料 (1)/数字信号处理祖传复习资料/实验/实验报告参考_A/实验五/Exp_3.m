clear all; %矩形窗
N=15;h= fir1(N-1,[0.3 0.5],'bandpass',kaiser(N,0));
[h1,w1]=freqz(h,1);
subplot(2,1,1); plot(w1/pi,20*log10(abs(h1)));
axis([0,1,-80,10]);grid;
xlabel('归一化频率/\pi'); ylabel('幅度/dB');title('N=15,矩形窗');
N=45;h= fir1(N-1,[0.3 0.5],'bandpass',kaiser(N,0));
[h1,w1]=freqz(h,1);
subplot(2,1,2); plot(w1/pi,20*log10(abs(h1)));
axis([0,1,-80,10]);grid;
xlabel('归一化频率/\pi'); ylabel('幅度/dB');title('N=45,矩形窗');
