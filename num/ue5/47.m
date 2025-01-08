% Werte für x definieren
x1 = linspace(-1, 0, 100);
x2 = linspace(0, 1, 100);
y1 = (x1 + 1) + (x1 + 1).^3;
y2 = 4 + (x2 - 1) + (x2 - 1).^3;

% Plotte die Funktion
figure;
hold on;
plot(x1, y1, 'b', 'LineWidth', 2);
plot(x2, y2, 'r', 'LineWidth', 2);
xlabel('x');
ylabel('f(x)');
title('Plot der Funktion f(x)');
legend('f(x) für x \in [-1, 0]', 'f(x) für x \in (0, 1]');
grid on;
hold off;

% Ausgeben als PNG
print('47.png', '-dpng');
