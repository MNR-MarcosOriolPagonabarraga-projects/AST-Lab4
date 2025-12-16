% LAB 4: ADMITTANCE CONTROL

clear all; close all; clc;

%% Exercise 2.1: Force Sensor Calibration
% Datos
F = [0 0.49 0.98 1.96 4.90]';   % Fuerza en Newton
side1 = [394.82 390.28 386.33 378.67 354.37]';
side2 = [400.85 404.85 409.05 417.01 441.27]';

% Ajuste lineal: F = m*ADC + b
coeff1 = polyfit(side1, F, 1);
coeff2 = polyfit(side2, F, 1);

m1 = coeff1(1); b1 = coeff1(2);
m2 = coeff2(1); b2 = coeff2(2);

fprintf("Side 1: F = %.4f·ADC + %.4f\n", m1, b1);
fprintf("Side 2: F = %.4f·ADC + %.4f\n", m2, b2);

% Curvas ajustadas para plot
adc_fit1 = linspace(min(side1), max(side1), 200);
adc_fit2 = linspace(min(side2), max(side2), 200);

F_fit1 = polyval(coeff1, adc_fit1);
F_fit2 = polyval(coeff2, adc_fit2);

% Plot conjunto
figure;
hold on;

% Puntos medidos
plot(side1, -F, 'o', 'MarkerSize', 8, 'DisplayName', 'Side 1 data');
plot(side2, F, 's', 'MarkerSize', 8, 'DisplayName', 'Side 2 data');

% Rectas de ajuste
plot(adc_fit1, -F_fit1, 'LineWidth', 1.5, 'DisplayName', 'Side 1 fit');
plot(adc_fit2, F_fit2, 'LineWidth', 1.5, 'DisplayName', 'Side 2 fit');

xlabel('ADC value');
ylabel('Force (N)');
title('Force vs ADC for both load cell sides');
legend('Location','best');
grid on;
hold off;


%% Exercise 3. Varying parameters on the admittance model

clear all; close all; clc;

filename = 'data/ForceHumana.txt';

% Leer todo el fichero como un único string
txt = fileread(filename);

% Separar en líneas (string array)
lines = splitlines(string(txt));

% Índices de las líneas que contienen "trial"
idxTrial = find(startsWith(strtrim(lines), "trial", 'IgnoreCase', true));

nTrials = numel(idxTrial);

% Estructura para guardar cada caso
trials = struct('data', []);

for k = 1:nTrials
    % Primera línea de datos después de la palabra "trial"
    startLine = idxTrial(k) + 1;

    % Última línea de datos antes del siguiente "trial"
    if k < nTrials
        endLine = idxTrial(k+1) - 1;
    else
        endLine = numel(lines);
    end

    block = lines(startLine:endLine);

    % Quitar líneas vacías (por si las hay)
    block = block(block ~= "");

    % Prealocar matriz [N x 4] (tiempo, ref, posición, torque)
    data = nan(numel(block), 4);

    for i = 1:numel(block)
        vals = sscanf(block(i), "%f, %f, %f, %f");
        if numel(vals) == 4
            data(i,:) = vals(:).';
        end
    end

    trials(k).data = data;
end

%% PLOT TRIALS: desired vs motor position

% Mapeo: trial index -> (J, B, K)
trialInfo = {
    1, 'Trial 2',  'J=1, B=0, K=1';
    2, 'Trial 3',  'J=1, B=3, K=1';
    3, 'Trial 4',  'J=1, B=3, K=3';
    4, 'Trial 5',  'J=3, B=1, K=1';
    6, 'Trial 6',  'J=0.05, B=0.5, K=2.0';
    7, 'Trial 7',  'J=1, B=1, K=3'
};

for i = 1:size(trialInfo,1)

    k      = trialInfo{i,1};
    tlabel = trialInfo{i,2};
    pLabel = trialInfo{i,3};

    data = trials(k).data;
 
    t                   = cumsum(data(:,1));    % tiempo acumulado
    desired_position    = data(:,2);            % desired position
    motor_position      = data(:,3);            % motor position
    torque              = data(:,4);            % interaction torque

    figure('Name',[tlabel ' - Positions']);
    plot(t, desired_position, 'LineWidth', 1.5); hold on;
    plot(t, motor_position,  'LineWidth', 1.5);
    grid on;
    xlabel('Time [s]');
    ylabel('Position [deg]');
    title([tlabel ' | ' pLabel]);
    legend('Desired position','Motor position','Location','best');

end


%% SUBPLOT with all trials (Positions)

figure('Name','All Trials - Positions','NumberTitle','off');

for i = 1:size(trialInfo,1)

    k      = trialInfo{i,1};
    tlabel = trialInfo{i,2};
    pLabel = trialInfo{i,3};

    data = trials(k).data;

    t                = cumsum(data(:,1));
    desired_position = data(:,2);
    motor_position   = data(:,3);

    subplot(3,2,i)
    plot(t, desired_position, 'LineWidth', 1.2); hold on;
    plot(t, motor_position,  'LineWidth', 1.2);
    grid on;

    title([tlabel ' | ' pLabel])
    xlabel('Time [s]')
    ylabel('Position [deg]')

    if i == 1
        legend('Desired position','Motor position','Location','best')
    end

end
