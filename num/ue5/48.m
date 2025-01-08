% Given data
t = [0 0.5 1.0 6.0 7.0 9.0];
y = [0.0 1.6 2.0 2.0 1.5 0.0];

% Fit a polynomial of degree 5
p = polyfit(t, y, 5);

% Generate points for plotting the polynomial
x_vals = linspace(0, 9, 100);
y_vals = polyval(p, x_vals);

% Plot the polynomial
plot(t, y, 'o', x_vals, y_vals);
title('Polynomial Interpolation of Degree 5');
xlabel('t');
ylabel('y');
grid on;

% Save the plot to a file
print('output_48.png', '-dpng');
disp(p)
