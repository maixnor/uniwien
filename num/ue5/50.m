
%% part a)

% Given data
t = [1 4 9 16 25 36 49 64];
y = [1 2 3 4 5 6 7 8];

% Fit a polynomial of degree 8
p = polyfit(t, y, 8);

% Generate points for plotting the polynomial
x_vals = linspace(0, 64, 100);
y_vals = polyval(p, x_vals);

% Plot the polynomial
plot(t, y, 'o', x_vals, y_vals);
title('Polynomial Interpolation of Degree 8');
xlabel('t');
ylabel('y');
grid on;

print('output_50_a.png', '-dpng');

%% part b)

% Generate square root values
sqrt_vals = sqrt(x_vals);

% Plot the polynomial and square root function
plot(x_vals, y_vals, x_vals, sqrt_vals, t, y, 'o');
title('Polynomial vs. Square Root Function');
xlabel('t');
ylabel('y');
%legend('Polynomial', 'Square Root');
legend({'Polynomial', 'Square Root'}, 'location', 'southeast');
grid on;

print('output_50_b.png', '-dpng');

%% part c)

% Restrict the x values to [0, 1]
x_vals_restricted = linspace(0, 1, 100);
y_vals_restricted = polyval(p, x_vals_restricted);
sqrt_vals_restricted = sqrt(x_vals_restricted);

% Plot the polynomial and square root
plot(x_vals_restricted, y_vals_restricted, x_vals_restricted, sqrt_vals_restricted);
title('Polynomial vs. Square Root Function in Range [0, 1]');
xlabel('t');
ylabel('y');
legend({'Polynomial', 'Square Root'}, 'location', 'southeast');
grid on;

print('output_50_c.png', '-dpng');

