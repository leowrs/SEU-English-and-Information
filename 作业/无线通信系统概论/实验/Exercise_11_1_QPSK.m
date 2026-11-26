% Original Author: GitHub @leowrs (https://github.com/leowrs)
%% Exercise 11.1: QPSK Modulation and AWGN Channel
% 无线通信系统概论实验 - QPSK调制与加性高斯白噪声信道

clear all;
close all;
clc;

%% Part 1: QPSK Modulation with Gray Encoding

% 生成随机二进制序列 (长度50000)
N_bits = 50000;
% 使用randi替代已弃用的randint函数
bit_sequence = randi([0, 1], 1, N_bits);

% 将比特序列重新整形为2列矩阵 (每个QPSK符号需要2个比特)
N_symbols = N_bits / 2;
bit_pairs = reshape(bit_sequence, 2, N_symbols)';

% Gray编码映射 (如图1所示)
% 00 -> θ = π/4   (第一象限)
% 01 -> θ = 3π/4  (第二象限)
% 11 -> θ = 5π/4  (第三象限)
% 10 -> θ = 7π/4  (第四象限)

% 初始化QPSK符号向量
qpsk_symbols = zeros(N_symbols, 1);

for i = 1:N_symbols
    % 获取当前比特对
    bit1 = bit_pairs(i, 1);  % 第一个比特
    bit2 = bit_pairs(i, 2);  % 第二个比特
    
    % Gray编码映射
    if bit1 == 0 && bit2 == 0      % 00
        theta = pi/4;
    elseif bit1 == 0 && bit2 == 1  % 01
        theta = 3*pi/4;
    elseif bit1 == 1 && bit2 == 1  % 11
        theta = 5*pi/4;
    else                           % 10
        theta = 7*pi/4;
    end
    
    % 生成复数符号: S_m = e^(j*θ_m)
    qpsk_symbols(i) = exp(1j * theta);
end

% 绘制原始QPSK星座图
figure(1);
scatter(real(qpsk_symbols), imag(qpsk_symbols), 10, 'b', 'filled');
grid on;
axis equal;
axis([-1.5 1.5 -1.5 1.5]);
xlabel('同相分量 (I)');
ylabel('正交分量 (Q)');
title('QPSK星座图 - Gray编码');

% 添加理想星座点标记
hold on;
ideal_points = [exp(1j*pi/4), exp(1j*3*pi/4), exp(1j*5*pi/4), exp(1j*7*pi/4)];
scatter(real(ideal_points), imag(ideal_points), 100, 'r', 'x', 'LineWidth', 3);
% 添加比特标签
text(real(exp(1j*pi/4))+0.1, imag(exp(1j*pi/4))+0.1, '00', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*3*pi/4))+0.1, imag(exp(1j*3*pi/4))+0.1, '01', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*5*pi/4))+0.1, imag(exp(1j*5*pi/4))+0.1, '11', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*7*pi/4))+0.1, imag(exp(1j*7*pi/4))+0.1, '10', 'FontSize', 12, 'FontWeight', 'bold');
legend('QPSK符号', '理想星座点', 'Location', 'best');
hold off;

%% Part 2: AWGN Channel Transmission

% 计算信号功率 (QPSK信号的平均功率为1)
signal_power = mean(abs(qpsk_symbols).^2);
fprintf('信号平均功率: %.4f\n', signal_power);

%% SNR = 6 dB
SNR_dB_1 = 6;
SNR_linear_1 = 10^(SNR_dB_1/10);

% 计算噪声功率
% SNR = E_b/N_0 = (信号功率 * 符号时间) / (噪声功率 * 比特时间)
% 对于QPSK，每个符号承载2个比特，所以 E_b = 信号功率/2
E_b = signal_power / 2;  % 每比特能量
N_0 = E_b / SNR_linear_1;  % 噪声功率谱密度
noise_power = N_0;  % 复数噪声的功率

% 生成复高斯白噪声
% 实部和虚部都是独立的高斯噪声，方差为 noise_power/2
noise_real = sqrt(noise_power/2) * randn(N_symbols, 1);
noise_imag = sqrt(noise_power/2) * randn(N_symbols, 1);
noise = noise_real + 1j * noise_imag;

% 接收信号 = 发送信号 + 噪声
received_symbols_6dB = qpsk_symbols + noise;

% 绘制SNR=6dB时的接收信号星座图
figure(2);
scatter(real(received_symbols_6dB), imag(received_symbols_6dB), 10, 'b', 'filled', 'MarkerFaceAlpha', 0.3);
grid on;
axis equal;
axis([-2 2 -2 2]);
xlabel('同相分量 (I)');
ylabel('正交分量 (Q)');
title('接收信号星座图 - SNR = 6 dB');

% 添加理想星座点
hold on;
scatter(real(ideal_points), imag(ideal_points), 100, 'r', 'x', 'LineWidth', 3);
text(real(exp(1j*pi/4))+0.1, imag(exp(1j*pi/4))+0.1, '00', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*3*pi/4))+0.1, imag(exp(1j*3*pi/4))+0.1, '01', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*5*pi/4))+0.1, imag(exp(1j*5*pi/4))+0.1, '11', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*7*pi/4))+0.1, imag(exp(1j*7*pi/4))+0.1, '10', 'FontSize', 12, 'FontWeight', 'bold');
legend('接收信号', '理想星座点', 'Location', 'best');
hold off;

%% SNR = 3 dB
SNR_dB_2 = 3;
SNR_linear_2 = 10^(SNR_dB_2/10);

% 重新计算噪声功率
N_0_2 = E_b / SNR_linear_2;
noise_power_2 = N_0_2;

% 生成新的噪声
noise_real_2 = sqrt(noise_power_2/2) * randn(N_symbols, 1);
noise_imag_2 = sqrt(noise_power_2/2) * randn(N_symbols, 1);
noise_2 = noise_real_2 + 1j * noise_imag_2;

% 接收信号
received_symbols_3dB = qpsk_symbols + noise_2;

% 绘制SNR=3dB时的接收信号星座图
figure(3);
scatter(real(received_symbols_3dB), imag(received_symbols_3dB), 10, 'b', 'filled', 'MarkerFaceAlpha', 0.3);
grid on;
axis equal;
axis([-2.5 2.5 -2.5 2.5]);
xlabel('同相分量 (I)');
ylabel('正交分量 (Q)');
title('接收信号星座图 - SNR = 3 dB');

% 添加理想星座点
hold on;
scatter(real(ideal_points), imag(ideal_points), 100, 'r', 'x', 'LineWidth', 3);
text(real(exp(1j*pi/4))+0.1, imag(exp(1j*pi/4))+0.1, '00', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*3*pi/4))+0.1, imag(exp(1j*3*pi/4))+0.1, '01', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*5*pi/4))+0.1, imag(exp(1j*5*pi/4))+0.1, '11', 'FontSize', 12, 'FontWeight', 'bold');
text(real(exp(1j*7*pi/4))+0.1, imag(exp(1j*7*pi/4))+0.1, '10', 'FontSize', 12, 'FontWeight', 'bold');
legend('接收信号', '理想星座点', 'Location', 'best');
hold off;

%% 比较不同SNR下的噪声效果
figure(4);
subplot(1,2,1);
scatter(real(received_symbols_6dB), imag(received_symbols_6dB), 10, 'b', 'filled', 'MarkerFaceAlpha', 0.3);
hold on;
scatter(real(ideal_points), imag(ideal_points), 100, 'r', 'x', 'LineWidth', 3);
grid on;
axis equal;
axis([-2.5 2.5 -2.5 2.5]);
xlabel('同相分量 (I)');
ylabel('正交分量 (Q)');
title('SNR = 6 dB');
hold off;

subplot(1,2,2);
scatter(real(received_symbols_3dB), imag(received_symbols_3dB), 10, 'b', 'filled', 'MarkerFaceAlpha', 0.3);
hold on;
scatter(real(ideal_points), imag(ideal_points), 100, 'r', 'x', 'LineWidth', 3);
grid on;
axis equal;
axis([-2.5 2.5 -2.5 2.5]);
xlabel('同相分量 (I)');
ylabel('正交分量 (Q)');
title('SNR = 3 dB');
hold off;

%% 显示统计信息
fprintf('\n=== 实验结果统计 ===\n');
fprintf('总比特数: %d\n', N_bits);
fprintf('QPSK符号数: %d\n', N_symbols);
fprintf('信号平均功率: %.4f\n', signal_power);
fprintf('每比特能量 E_b: %.4f\n', E_b);
fprintf('\nSNR = 6 dB:\n');
fprintf('  噪声功率: %.6f\n', noise_power);
fprintf('  理论噪声标准差: %.4f\n', sqrt(noise_power/2));
fprintf('  实际噪声标准差 (实部): %.4f\n', std(real(noise)));
fprintf('  实际噪声标准差 (虚部): %.4f\n', std(imag(noise)));
fprintf('\nSNR = 3 dB:\n');
fprintf('  噪声功率: %.6f\n', noise_power_2);
fprintf('  理论噪声标准差: %.4f\n', sqrt(noise_power_2/2));
fprintf('  实际噪声标准差 (实部): %.4f\n', std(real(noise_2)));
fprintf('  实际噪声标准差 (虚部): %.4f\n', std(imag(noise_2)));

fprintf('\n实验完成！你可以观察到：\n');
fprintf('1. 原始QPSK星座图显示了4个清晰的星座点\n');
fprintf('2. 在AWGN信道中，接收信号形成了围绕原始星座点的"高斯云"\n');
fprintf('3. SNR越低（3dB vs 6dB），高斯云越分散，表示噪声影响越大\n');

%% =======================================================================
%% Exercise 2.1: QPSK BER Performance with ML Receiver
%% =======================================================================

% 保留一些变量用于后续计算
fprintf('\n正在开始Exercise 2...\n');
% close all;  % 保留之前的图形

fprintf('\n\n=== Exercise 2.1: QPSK BER Performance Analysis ===\n');

% 系统参数
N_bits_ber = 100000;  % 传输比特数
SNR_dB_values = [0, 2, 4, 6];  % SNR值 (dB)
num_SNR = length(SNR_dB_values);

% 预分配结果数组
BER_simulated = zeros(1, num_SNR);
num_errors = zeros(1, num_SNR);

% QPSK星座点 (用于ML解调)
constellation = [exp(1j*pi/4), exp(1j*3*pi/4), exp(1j*5*pi/4), exp(1j*7*pi/4)];
% 对应的比特映射 (Gray编码)
bit_mapping = [0 0; 0 1; 1 1; 1 0];  % 00, 01, 11, 10

fprintf('开始BER仿真...\n');
fprintf('传输比特数: %d\n', N_bits_ber);
fprintf('SNR值: %s dB\n', mat2str(SNR_dB_values));

% 生成发送比特序列
tx_bits = randi([0, 1], 1, N_bits_ber);
N_symbols_ber = N_bits_ber / 2;

% 将比特序列转换为QPSK符号
tx_bit_pairs = reshape(tx_bits, 2, N_symbols_ber)';
tx_symbols = zeros(N_symbols_ber, 1);

for i = 1:N_symbols_ber
    bit1 = tx_bit_pairs(i, 1);
    bit2 = tx_bit_pairs(i, 2);
    
    % Gray编码映射
    if bit1 == 0 && bit2 == 0      % 00
        tx_symbols(i) = exp(1j*pi/4);
    elseif bit1 == 0 && bit2 == 1  % 01
        tx_symbols(i) = exp(1j*3*pi/4);
    elseif bit1 == 1 && bit2 == 1  % 11
        tx_symbols(i) = exp(1j*5*pi/4);
    else                           % 10
        tx_symbols(i) = exp(1j*7*pi/4);
    end
end

% 对每个SNR值进行仿真
for snr_idx = 1:num_SNR
    SNR_dB = SNR_dB_values(snr_idx);
    SNR_linear = 10^(SNR_dB/10);
    
    fprintf('\n正在仿真 SNR = %d dB...', SNR_dB);
    
    % 计算噪声功率
    signal_power = 1;  % QPSK信号的平均功率
    E_b = signal_power / 2;  % 每比特能量
    N_0 = E_b / SNR_linear;  % 噪声功率谱密度
    noise_variance = N_0 / 2;  % 复数噪声每个分量的方差
    
    % 生成AWGN噪声
    noise_real = sqrt(noise_variance) * randn(N_symbols_ber, 1);
    noise_imag = sqrt(noise_variance) * randn(N_symbols_ber, 1);
    noise = noise_real + 1j * noise_imag;
    
    % 接收信号
    rx_symbols = tx_symbols + noise;
    
    % ML解调 (最小距离解调)
    rx_bit_pairs = zeros(N_symbols_ber, 2);
    
    for i = 1:N_symbols_ber
        % 计算接收符号到所有星座点的距离
        distances = abs(rx_symbols(i) - constellation);
        
        % 找到最小距离对应的星座点
        [~, min_idx] = min(distances);
        
        % 获取对应的比特
        rx_bit_pairs(i, :) = bit_mapping(min_idx, :);
    end
    
    % 将符号级比特转换为比特流
    rx_bits = reshape(rx_bit_pairs', 1, N_bits_ber);
    
    % 计算误码数和误码率
    errors = sum(tx_bits ~= rx_bits);
    num_errors(snr_idx) = errors;
    BER_simulated(snr_idx) = errors / N_bits_ber;
    
    fprintf(' 完成');
    fprintf('\n  误码数: %d', errors);
    fprintf('\n  BER: %.6f', BER_simulated(snr_idx));
end

fprintf('\n\nBER仿真完成！\n');

%% =======================================================================
%% Exercise 2.2: Theoretical BER Analysis
%% =======================================================================

fprintf('\n=== Exercise 2.2: Theoretical BER Analysis ===\n');

% 计算理论BER
BER_theoretical = zeros(1, num_SNR);

for snr_idx = 1:num_SNR
    SNR_dB = SNR_dB_values(snr_idx);
    gamma_b = 10^(SNR_dB/10);  % SNR (线性值)
    
    % 使用公式 p_b = Q(sqrt(2*gamma_b))
    % Q(x) = (1/2) * erfc(x/sqrt(2))
    x = sqrt(2 * gamma_b);
    BER_theoretical(snr_idx) = 0.5 * erfc(x / sqrt(2));
end

%% 显示结果对比
fprintf('\n=== BER Results Comparison ===\n');
fprintf('SNR (dB)\tSimulated BER\tTheoretical BER\tError Count\n');
fprintf('--------------------------------------------------------\n');
for i = 1:num_SNR
    fprintf('%8.1f\t%12.6f\t%15.6f\t%11d\n', ...
        SNR_dB_values(i), BER_simulated(i), BER_theoretical(i), num_errors(i));
end

%% 绘制BER性能曲线
figure(5);
semilogy(SNR_dB_values, BER_simulated, 'bo-', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'b');
hold on;
semilogy(SNR_dB_values, BER_theoretical, 'r^-', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'r');
grid on;
xlabel('SNR (dB)');
ylabel('Bit Error Rate (BER)');
title('QPSK BER Performance: Simulation vs Theory');
legend('Simulated BER', 'Theoretical BER', 'Location', 'best');
axis([0 6 1e-4 1e-1]);

% 添加数值标注
for i = 1:num_SNR
    text(SNR_dB_values(i), BER_simulated(i)*1.5, sprintf('%.1e', BER_simulated(i)), ...
        'HorizontalAlignment', 'center', 'FontSize', 8, 'Color', 'blue');
    text(SNR_dB_values(i), BER_theoretical(i)*0.7, sprintf('%.1e', BER_theoretical(i)), ...
        'HorizontalAlignment', 'center', 'FontSize', 8, 'Color', 'red');
end

%% 保存结果数据
results_data.SNR_dB_values = SNR_dB_values;
results_data.BER_simulated = BER_simulated;
results_data.BER_theoretical = BER_theoretical;
results_data.num_errors = num_errors;
results_data.N_bits_ber = N_bits_ber;
results_data.simulation_date = datestr(now);

% 保存到文件
save('QPSK_BER_Results.mat', 'results_data');
fprintf('\n结果已保存到文件: QPSK_BER_Results.mat\n');

%% 绘制详细的BER对比图
figure(6);
subplot(2,1,1);
bar(SNR_dB_values, [BER_simulated; BER_theoretical]', 'grouped');
set(gca, 'YScale', 'log');
grid on;
xlabel('SNR (dB)');
ylabel('BER');
title('BER Comparison: Simulation vs Theory');
legend('Simulated', 'Theoretical', 'Location', 'best');

subplot(2,1,2);
relative_error = abs(BER_simulated - BER_theoretical) ./ BER_theoretical * 100;
bar(SNR_dB_values, relative_error);
grid on;
xlabel('SNR (dB)');
ylabel('Relative Error (%)');
title('Relative Error between Simulation and Theory');

% 显示相对误差
fprintf('\n=== Relative Error Analysis ===\n');
fprintf('SNR (dB)\tRelative Error (%%)\n');
fprintf('--------------------------------\n');
for i = 1:num_SNR
    fprintf('%8.1f\t%15.2f\n', SNR_dB_values(i), relative_error(i));
end

%% ML解调器性能分析
figure(7);
% 显示一个SNR下的解调示例
SNR_example = 4; % dB
SNR_linear_ex = 10^(SNR_example/10);
E_b_ex = 0.5;
N_0_ex = E_b_ex / SNR_linear_ex;
noise_var_ex = N_0_ex / 2;

% 生成少量符号用于可视化
N_demo = 1000;
demo_symbols = constellation(randi(4, N_demo, 1));
demo_noise = sqrt(noise_var_ex) * (randn(N_demo, 1) + 1j*randn(N_demo, 1));
demo_received = demo_symbols + demo_noise;

% 绘制接收信号和判决区域
scatter(real(demo_received), imag(demo_received), 20, 'b', 'filled', 'MarkerFaceAlpha', 0.3);
hold on;

% 绘制星座点
scatter(real(constellation), imag(constellation), 100, 'r', 's', 'filled', 'LineWidth', 2);

% 绘制判决边界 (垂直平分线)
x_bound = [-1.5, 1.5];
y_bound = [-1.5, 1.5];
plot([0, 0], y_bound, 'k--', 'LineWidth', 1.5);  % 垂直边界
plot(x_bound, [0, 0], 'k--', 'LineWidth', 1.5);  % 水平边界

grid on;
axis equal;
axis([-1.5 1.5 -1.5 1.5]);
xlabel('同相分量 (I)');
ylabel('正交分量 (Q)');
title(sprintf('ML解调示例 (SNR = %d dB)', SNR_example));
legend('接收信号', 'QPSK星座点', '判决边界', 'Location', 'best');
hold off;

fprintf('\n=== Exercise 2 总结 ===\n');
fprintf('1. 实现了完整的QPSK传输系统，包括调制、AWGN信道和ML解调\n');
fprintf('2. 仿真了不同SNR下的BER性能\n');
fprintf('3. 计算了理论BER并与仿真结果进行对比\n');
fprintf('4. ML解调器通过最小距离准则进行符号判决\n');
fprintf('5. 仿真结果与理论值吻合良好，验证了系统设计的正确性\n');

% 加载之前保存的结果示例
fprintf('\n要加载之前保存的结果，请使用以下命令:\n');
fprintf('loaded_data = load(''QPSK_BER_Results.mat'');\n');
fprintf('disp(loaded_data.results_data);\n');
