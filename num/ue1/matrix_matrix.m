function result = matrix_matrix(A, B)
    % Task 10: Multiply Matrix-Vector or Matrix-Matrix
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

% direct eintippen bei octave REPL
A = [1 2; 3 4];       % 2x2 Matrix
B = [5 6; 7 8];       % 2x2 Matrix
matrix_matrix(A, B);  % Aufruf der Funktion
B = [1; 2];
matrix_matrix(A, B);

