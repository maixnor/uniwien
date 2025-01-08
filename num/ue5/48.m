% Aufgabe 48: Interpolieren mit einem Polynom vom Grad 5

% Datenpunkte
t = [0 0.5 1.0 6.0 7.0 9.0];
y = [0 1.6 2.0 2.0 1.5 0.0];

% Grad 5 Polynomial Interpolation
p = polyfit(t, y, 5);

% Werte zum Plotten
t_fine = linspace(0, 9, 100);
y_fit = polyval(p, t_fine);

% Plot
figure;
plot(t, y, 'ro', 'MarkerSize', 8); % Gegebene Datenpunkte
hold on;
plot(t_fine, y_fit, 'b-', 'LineWidth', 2); % Interpoliertes Polynom
xlabel('t');
ylabel('y');
title('Interpolation mit einem Polynom vom Grad 5');
legend('Datenpunkte', 'Interpoliertes Polynom');
grid on;
hold off;

% Speichern als PNG
print('48.png', '-dpng');
