fact(0, 1). /* base case */
fact(N, Result) :-
    Nsub1 is N - 1,
    fact(Nsub1, PrevResult),
    Result is N * PrevResult.