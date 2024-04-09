       IDENTIFICATION DIVISION.
       PROGRAM-ID. CardDemo.
       
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01 Rank          PIC 9.
       01 Suit          PIC 9.
       01 SuitLabel     PIC X.
       01 Face          PIC X.
       
       PROCEDURE DIVISION.
           MOVE 10 TO Rank
           MOVE 2 TO Suit
       
           PERFORM InitCard
           PERFORM ToString
           PERFORM Compare
       
           DISPLAY 'Card: ' Rank Suit ' - ' Face SuitLabel
           STOP RUN.
       
       InitCard.
           *> Assign suit string
           IF suit = 0 MOVE "D" TO SuitLabel
           ELSE IF suit = 1 MOVE "C" TO SuitLabel
           ELSE IF suit = 2 MOVE "H" TO SuitLabel
           ELSE IF suit = 3 MOVE "S" TO SuitLabel
           ELSE IF suit = 4 MOVE "R" TO SuitLabel
           ELSE IF suit = 5 MOVE "B" TO SuitLabel
        
           *> Assign rank string
           IF rank = 2 MOVE "2" TO Face
           ELSE IF rank = 3 MOVE "3" TO Face
           ELSE IF rank = 4 MOVE "4" TO Face
           ELSE IF rank = 5 MOVE "5" TO Face
           ELSE IF rank = 6 MOVE "6" TO Face
           ELSE IF rank = 7 MOVE "7" TO Face
           ELSE IF rank = 8 MOVE "8" TO Face
           ELSE IF rank = 9 MOVE "10" TO Face
           ELSE IF rank = 10 MOVE "J" TO Face
           ELSE IF rank = 11 MOVE "J" TO Face
           ELSE IF rank = 12 MOVE "Q" TO Face
           ELSE IF rank = 13 MOVE "K" TO Face
           ELSE IF rank = 14 MOVE "A" TO Face
           ELSE IF rank = 15 MOVE "X" TO Face.
       
       ToString.
           IF Face = SPACES
               DISPLAY Rank SuitLabel
           ELSE
               DISPLAY Face SuitLabel.
       
       Compare.
           MOVE 8 TO Rank
           MOVE 1 TO Suit
       
           DISPLAY 'Comparing with another card: ' Rank Suit
       
           MOVE 7 TO Rank
           MOVE 1 TO Suit
       
           DISPLAY 'Result of comparison: ' Rank Suit.
       