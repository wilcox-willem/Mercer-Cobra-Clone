#!/usr/bin/python3

i = int(input("Enter a positive integer: "))
k = 0
while i != 1:
    print(int(i))
    if ( i % 2  == 0 ):
        i = i / 2
    else:
        i = i * 3 + 1
    k = k + 1
print ( int(i) )

print("The total number of sequences is: " , k)
