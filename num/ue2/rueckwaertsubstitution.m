% Aufgabe 20: Rückwärtssubstitution zur Lösung von Ux = b

function x = rueckwaertssubstitution(U, b)
    % Bestimme die Anzahl der Zeilen
    n = length(b);
    
    % Initialisiere Lösungsvektor x
    x = zeros(n, 1);
    
    % Prüfe, ob U eine obere Dreiecksmatrix ist
    if any(diag(U) == 0)
        error('Das Gleichungssystem ist nicht eindeutig lösbar.');
    end
    
    % Rückwärtssubstitution
    for i = n:-1:1
        % Berechne den i-ten Wert von x
        x(i) = (b(i) - U(i, i+1:n) * x(i+1:n)) / U(i, i);
    end
end

% Test der Funktion mit Beispielwerten
U = [3, -1, 2; 0, 4, 1; 0, 0, 5];
b = [5; 6; 7];
x = rueckwaertssubstitution(U, b);

% Ausgabe des Ergebnisses
fprintf('Lösung x:\n');
disp(x);

