% Define the function
f = @(x) ((x + 1) + (x + 1).^3) .* (x >= -1 & x <= 0) + ...
          (4 + (x - 1) + (x - 1).^3) .* (x > 0 & x <= 1);

% Create an array of x values
x = linspace(-1, 1, 100);

% Calculate the resulting function values
y = f(x);

% Plot the function
plot(x, y);
title('Plot of f(x)');
xlabel('x');
ylabel('f(x)');
grid on;

% Save the plot to a file
print('output_47.png', '-dpng');
