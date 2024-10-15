% Task 9: Read Matrix A and Vector b from CSV files and solve Ax = b

% Load matrix A and vector b from respective csv files
A = csvread('matrix_A.csv');
b = csvread('vector_b.csv');

% Solve the linear system Ax = b
x = A \ b;

% Output the result
disp('The solution x is:');
disp(x);

