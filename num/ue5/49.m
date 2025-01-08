% Aufgabe 49: Bestimme einen kubischen Spline

% Datenpunkte
t = [0 0.5 1.0 6.0 7.0 9.0];
y = [0 1.6 2.0 2.0 1.5 0.0];

% Kubischer Spline Interpolation
spline_coeffs = spline(t, y);

% Werte zum Plotten
t_fine = linspace(0, 9, 100);
y_spline = ppval(spline_coeffs, t_fine);

% Plot
figure;
plot(t, y, 'ro', 'MarkerSize', 8); % Gegebene Datenpunkte
hold on;
plot(t_fine, y_spline, 'b-', 'LineWidth', 2); % Kubischer Spline
xlabel('t');
ylabel('y');
title('Kubischer Spline')
legend('Datenpunkte', 'Kubischer Spline');
grid on;
hold off;

% Speichern als PNG
print('49.png', '-dpng');
