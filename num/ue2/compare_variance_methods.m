% Aufgabe 19: Funktion zur Mittelwert- und Varianzberechnung

function compare_variance_methods(data)
    % Berechnung nach der Standardformel
    mean_data = mean(data);
    variance_standard = mean((data - mean_data) .^ 2);

    % Berechnung nach der alternativen Formel
    variance_alternative = mean(data .^ 2) - mean_data^2;

    % Berechne die Abweichung der Varianzschätzungen vom erwarteten Wert
    true_variance = var(data); % Verwende Octaves var-Funktion als Referenz
    deviation_standard = abs(variance_standard - true_variance);
    deviation_alternative = abs(variance_alternative - true_variance);

    % Ausgabe der Ergebnisse
    fprintf('Standardformel Varianz: %.5f, Abweichung: %.5f\n', variance_standard, deviation_standard);
    fprintf('Alternative Formel Varianz: %.5f, Abweichung: %.5f\n', variance_alternative, deviation_alternative);

    % Plotten der Abweichungen
    bar([deviation_standard, deviation_alternative]);
    set(gca, 'xticklabel', {'Standard', 'Alternative'});
    ylabel('Abweichung der Varianz');
    title('Vergleich der Varianz-Berechnungsmethoden');
end

% Beispielaufruf (z.B. mit CSV-Daten):
% data = csvread('data.csv');
% compare_variance_methods(data);

