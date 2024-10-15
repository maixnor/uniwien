function result = multiply_matrices(A, B)
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

