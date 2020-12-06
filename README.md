# Application Format

User input(important ones)
* Number of matrices to write to the file
* Number of filter matrices to write to the file
* Names of the files that the application must use for writing and reading matrices
* Matrix and filter indexes on which the filter operation must be performed

Overall files’ formats must look like this: 
* Number of matrices 
* Number of rows and columns for the first matrix
* First matrix data
* An empty line between the matrices
* Number of rows and columns for the second matrix
* Second matrix data
* ...

For the implementation of this problem, a Matrix class was created. It consists of static and non-static functions, which perform read and write operations on the files and do some operations on the Matrix class objects(such as applying a filter to the main matrix). 

Convolution is run on 2D matrices. The filter from a user-specified index is read from a vector with a Matrix as a type, which contains the matrices that are read from the file. Afterward, the filter is run on the main matrix elements from left to right for each row. When the filter runs through the main matrix, it must not pass the borders of it. For example, if the main matrix is of size 9x9 and the filter matrix is of size 3x3, then convolution operation will cover the 7x7 leftmost submatrix. 

Various filters of different sizes can be run on the main matrix. In my implementation, I have written a function that can be used to fill both the input and output matrices with random elements from a specific range. Individual(elements are all inputted by the user) matrices can be inputted using the Matrix class's setMatrix(...) function.

