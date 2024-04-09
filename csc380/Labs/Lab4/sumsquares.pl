sumsquares(1,1).
sumsquares(N, Result) :-
    Nsub1 is N - 1,
    sumsquares(Nsub1, PrevResult),
    Result is N * N + PrevResult.