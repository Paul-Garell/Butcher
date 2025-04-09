%% Data Analysis Script
% Use 3 functions to
% (1) Obtain a and C values
% (2) Plot stress strain curves
% (3) Plot bar graph to compare different materials


function [alpha_coeff, C_coeff, eff_modulus, mean_modulus, std_modulus] = analyze(fit_type, stretch, varargin)
%{
Returns: None
Parameters: arrays of stress values to be analyzed. Arrays can be of
different sizes
- takes each stress array, finds a fit value
- trims down the stretch array as needed to match sizes
- Adds 0 starting point to input stress arrays
%}
alpha_coeff = zeros(size(varargin));
C_coeff = zeros(size(varargin));
eff_modulus = zeros(size(varargin));
    for t = 1:max(size(varargin))
        % Process Stretch and Strain Arrays
        cur_stress = [0 varargin{t}]*-1;
        if max(size(cur_stress)) ~= max(size(stretch))
            cur_stretch = stretch(1:max(size(cur_stress)));
        else
            cur_stretch = stretch;
        end
        % Perform Curve Fitting
        fit_values = fit(cur_stretch' ,cur_stress',fit_type, 'StartPoint', [1, 1]);
        coeff = coeffvalues(fit_values);
        alpha_coeff(t) = coeff(1);
        C_coeff(t) = coeff(2);
        eff_modulus(t) = alpha_coeff(t)*C_coeff(t)*(-0.052*(alpha_coeff(t)^3)+0.252*(alpha_coeff(t)^2)+(0.053*alpha_coeff(t))+1.09);
    end
    mean_modulus = mean(eff_modulus);
    std_modulus = std(eff_modulus);
end

function [] = plot_all(a, C, stretch, varargin)
%{
Returns: None
Parameters: derived alpha and C values from the analyze function
- stretch 
%}
    for t = 1:max(size(varargin))
        % Process Stretch and Strain Arrays
        cur_stress = [0 varargin{t}]*-1;
        if max(size(cur_stress)) ~= max(size(stretch))
            cur_stretch = stretch(1:max(size(cur_stress)));
        else
            cur_stretch = stretch;
        end
        plot(cur_stretch, cur_stress, '.', 'MarkerSize', 12, 'Color', '#808080');
        x = stretch(1) : 0.001 : stretch(max(size(cur_stress)));
        y = a(t).*C(t).*((x.^2)-(1./x)).*exp(a(t).*((x.^2)+(2./x)-3));
        plot(x,y, '-b');
    end
end

function [] = plot_youngs(legend, varargin)
%{
Returns: None
Parameters: array of modulus after analyzing data, plots bar graph with different 
arrays of modulus
- legend: labels of array
%}
    for t = 1:max(size(varargin))
        mean_modulus = mean(varargin{t});
        std_modulus = std(varargin{t});
        bar(t-1, mean_modulus);
        
        % Plot Error Bars
        er = errorbar(t-1,mean_modulus,std_modulus,std_modulus);    
        er.Color = [0 0 0];                            
        er.LineStyle = 'none';
        
        % Plot Individual Values
        x_values = ones(size(varargin{t}))*(t-1);
        plot(x_values, varargin{t}, '.', 'MarkerSize', 15, 'Color', '#808080');
    end
    curtick = get(gca, 'xTick');
    xticks(unique(round(curtick)));
    % Set x bounds
    ax = gca;
    ax.XLim = [-0.5, max(size(varargin))-0.5];
    set(gca,'xticklabel', legend);
end

%% Example Workflow
% Raw Data 

cauchy = fittype("a*C*((x^2)-(1/x))*exp(a*((x^2)+(2/x)-3))",dependent="y",independent="x",coefficients=["a" "C"]);

% Stretch is dependent on the geometry of the flex PCB
stretch = [1 1.2415 1.406 1.572 1.738 1.9045 2.071 2.2375];

% Process 2% Agarose Data
s1 = [-3.08 -7.28 -15.98 -23.98 -30.91 -36.81];
s2 = [-3.22 -5.15 -12.04 -17.96 -26.93 -40.81];
s3 = [-2.11 -4.11 -11 -16 -25.89 -38.84];
s5 = [-2.02 -5.05 -12.06 -16.04 -24.02 -35.02];
s6 = [-4.03 -9.08 -15.04 -19.06 -28.05 -39.10];

[a1, c1, e1, e_avg, e_std] = analyze(cauchy, stretch, s1, s2, s3, s5, s6);

figure;
hold on
plot_all(a1, c1, stretch, s1, s2, s3, s5, s6);

xlabel("Strain");
ylabel("Stress (kPa)");
fontsize(20, "points");
title("2% Agarose Stress Strain Curves");
hold off

% Process

l1 = [-14.94 -20.95 -26.97 -35.02];
l3 = [-5.01 -12.95 -20.95 -33.02];
l4 = [-7 -18.96 -20.95 -23.02 -29 -32.96 -36.99];
l5 = [-5.01 -7.04 -14.96 -24.98 -26.92 -30.99 -38.94];
l6 = [-8.92 -18.96 -20.92 -22.98 -25 -26.92 -28.95];
l7 = [-3.15 -14.96 -16.99 -18.98];

[a2, c2, e2, e_avg2, e_std2] = analyze(cauchy, stretch, l1, l3, l4, l5, l6, l7);

figure;
hold on
plot_all(a2, c2, stretch, l1, l3, l4, l5, l6, l7);

xlabel("Strain");
ylabel("Stress (kPa)");
fontsize(20, "points");
title("Chicken Liver Stress Strain Curves");
hold off

cb1 = [-11.01 -20.92 -26.9 -28.89 -32.83 -34.87 -42.77];
cb2 = [-16.99 -24.92 -32.91 -36.86];
cb3 = [-10.99 -22.93 -36.85];
cb4 = [-5.09 -11.1 -13.07 -17.05 -29.05 -39.07];

[a3, c3, e3, e_avg3, e_std3] = analyze(cauchy, stretch, cb1, cb2, cb3, cb4);

figure;
hold on
plot_all(a3, c3, stretch, cb1, cb2, cb3, cb4);

xlabel("Strain");
ylabel("Stress (kPa)");
fontsize(20, "points");
title("Chicken Breast Interior Stress Strain Curves");
hold off

figure;
hold on;
plot_youngs(["holder", "2% Agarose (n = 5)", "Chicken Liver (n = 6)", "Chicken Breast Interior (n = 4)"], e1, e2, e3);
hold off;
