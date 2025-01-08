% Aufgabe 50: Interpolation mit einem Polynom vom Grad 8

% Gegebene Datenpunkte
t = [0 1 4 9 16 25 36 49 64];
y = [0 1 2 3 4 5 6 7 8];

% a) Bestimmen Sie ein Polynom vom Grad 8
p = polyfit(t, y, 8); % Interpolation mit einem Polynom vom Grad 8

% Werte zum Plotten
t_fine = linspace(0, 64, 100);
y_fit = polyval(p, t_fine);

% b) Grafische Darstellung des erhaltenen Polynoms und der Wurzelwerte (sqrt)
y_sqrt = sqrt(t_fine); % Berechnung der Quadratwurzelwerte
figure;
plot(t, y, 'ro', 'MarkerSize', 8); % Gegebene Datenpunkte
hold on;
plot(t_fine, y_fit, 'b-', 'LineWidth', 2); % Interpoliertes Polynom
plot(t_fine, y_sqrt, 'g--', 'LineWidth', 2); % Quadratwurzelwerte
xlabel('t');
ylabel('y');
title('Interpolation (Grad 8) und Wurzelwerte');
legend('Datenpunkte', 'Interpoliertes Polynom', 'sqrt(t)');
grid on;
hold off;

% Speichern als PNG für Teil b
print('aufgabe_50_plot_b.png', '-dpng');

% c) Grafische Darstellung des erhaltenen Polynoms und der Werte sqrt(t)
figure;
plot(t, y, 'ro', 'MarkerSize', 8); % Gegebene Datenpunkte
hold on;
plot(t_fine, y_fit, 'b-', 'LineWidth', 2); % Interpoliertes Polynom
xlabel('t');
ylabel('y');
title('Interpolation (Grad 8)');
legend('Datenpunkte', 'Interpoliertes Polynom');
grid on;
hold off;

% Speichern als PNG für Teil c
print('aufgabe_50_plot_c.png', '-dpng');

