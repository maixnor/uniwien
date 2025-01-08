% Given data
t = [0 0.5 1.0 6.0 7.0 9.0];
y = [0.0 1.6 2.0 2.0 1.5 0.0];

% Fit a cubic spline
spline_vals = spline(t, y, linspace(0, 9, 100));

% Plot the cubic spline
plot(t, y, 'o', linspace(0, 9, 100), spline_vals);
title('Cubic Spline Interpolation');
xlabel('t');
ylabel('y');
grid on;

% Save the plot to a file
print('output_49.png', '-dpng');
disp(spline_vals);
