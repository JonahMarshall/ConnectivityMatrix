THE FOLLOWING README WAS CREATED TO THE SPECIFICATIONS OF THE MARKER FOR THE COURSE THIS WAS PART OF.


Jonah Marshall

100% Complete

I recommend changing main to use printed_full_process()

Program assumes user will give proper input for a connectivity matrix if they want the correct results.
cmatrix is not limited to exclusively 1 or 0 to allow for functionality of what you would use a connectivity matrix for.

-------------------------------------------------------------------------------------------------------------------------
An alternative solution if you want to implement restrictions would be to create additional classes for
    a Stochastic Matrix, a Transition Matrix, and a Column Matrix.

cmatrix:
        myMatrix will be type bool instead to prevent values from being anything except 1 or 0.
        will contain function find_imp(), which now returns a Stochastic Matrix (smatrix).
        will contain functions full_process() and printed_full_process(), which will return a Column Matrix (col_matrix).

smatrix:
        will contain variable "p" for random walk.
        will contain function find_tran(), which now returns a Transition Matrix (tmatrix).

tmatrix:
        will contain functions markov() and printed_markov(), both of which now return a Column Matrix.

col_matrix:
        constructors will be written to ensure it only has 1 column.
        will contain function print_result().


