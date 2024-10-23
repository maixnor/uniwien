function result = matrix_multiply(A, B)  % Ändere den Funktionsnamen
    % Check if dimensions are compatible for multiplication
    [rows_A, cols_A] = size(A);
    [rows_B, cols_B] = size(B);

    if cols_A == rows_B
        result = A * B;  % Perform matrix multiplication
        disp('The result of A * B is:');
        disp(result);
    else
        error('Error: The number of columns in A must match the number of rows in B');
    end
end

A = [1 2; 3 4];  % 2x2 Matrix
B = [5 6; 7 8];  % 2x2 Matrix

% Aufruf der Funktion:
result = matrix_multiply(A, B);

disp(result)

