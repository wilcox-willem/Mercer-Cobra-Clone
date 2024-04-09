# Willem Wilcox, Dr. Digh, CSC 380, MU, 1/31/24
# note: in the function try_educated_machine_move(), it is set to say "~Interesting move!~" 
#       if a new "unsafe" move is added. It was originally just to debug, but as I played
#       it started to happen less and less, so that was something cool to watch
#
#       -- TO CHANGE CURRENT SAVE FILE -- current file name "unsafe"
#       the file name it is intended to read and write to, and is hard coded in 2 places.
#       while working with different files, I most easily find with a ctrl+f "currentfilename"
#           - in the def try_educated_machine_move(board, move_set) 
#               - update_unsafe_moves("unsafe", move_set)
#           - in the def main()
#               - move_set = read_unsafe_moves("unsafe")
import sys,os,random

def intro_to_game():
    # in, nothing
    # out, user input num 1-4
    # os.system('cls') # clear screen
    print("\n\n\n\n\n\n")
    print("Welcome to the game of NIM! \n---------------------------\nOptions include: ")
    print("1) Human Starts, and picks piles")
    print("2) Computer starts, and human picks piles")
    print("3) Random start, random piles (pile size up to 1000)") # ADJUST MAX SIZE *vvvv*
    #print("4) Computer plays against itself") # secret menu choice for comp training
    print("\nPlease Make a selection to get started\n")
    player_menu_selection = int(input())
    if (player_menu_selection > 4 or player_menu_selection < 1):
        while (player_menu_selection > 4 or player_menu_selection < 1):
            print("\nInvalid input, please select 1-4\n")
            player_menu_selection = int(input())
    return player_menu_selection

def create_game_board(menu_selection):
    # in, 1-4
    # out, board [A,B,C]

    board = [-1,-1,-1]    # empty board
    board_positions = ['A','B','C']    # board spots
    is_board_ready = False    # board readiness state
    max_pile_size = 1000    # max pile size allowed, must be >= 2, ADJUST PRINT OUT *^^^^*
    current_pile_size = 0    # temp value for pile sizes
    current_pile_pos = 0    # temp val for current pile

    
    # according to intro_to_game() menu, menu_selection =
    # 1 or 2, human picks piles
    # 3 or 4, random with cap (defined above) per pile

    # options 1 & 2
    if (menu_selection == 1 or menu_selection == 2):
        for current_pile_pos in range(3):
            print("\nNow selecting pile: ",board_positions[current_pile_pos])
            print("\nPlease pick a pile size between 1 and ",max_pile_size,"\n")
            current_pile_size = int(input())
            while (current_pile_size < 1 or current_pile_size > max_pile_size):
                print("\nTry again, Please pick a pile size between 1 and ",max_pile_size)
                current_pile_size = int(input())
            board[current_pile_pos] = current_pile_size
    # options 3 & 4
    elif (menu_selection == 3 or menu_selection == 4):
        for current_pile_pos in range(3):
            current_pile_size = random.randint(1,max_pile_size)
            board[current_pile_pos] = current_pile_size
        
            
    return board  

def print_board(board):
    # in, current board
    # out, void but prints 
    print(f"A:{board[0]}\tB:{board[1]}\tC:{board[2]}\n")

def print_board_update(board, the_player, the_pile, the_chips):
    # in, board int[3] the_player bool (T = computer, F = human), the_pile char, the_chips int
    # out, print change and updated board

    current_player = "You"
    if the_player:
        current_player = "I"

    # catch for machine misprinting piles
    if the_pile == 0:
        the_pile = "A"
    elif the_pile == 1:
        the_pile = "B"
    elif the_pile == 2:
        the_pile = "C"
        
    print(f"{current_player} removed {the_chips} chip/s from pile {the_pile}\n")
    print_board(board)

#### Unsafe Moves Functions

def read_unsafe_moves(filename):
    # in, relative filepath
    # out, list of unsafe moves stored in int tuples (A,B,C)
    tokenized_lines = []
    unsafe_move_set = []

    with open(filename, "r") as file:
        for line in file:
            #tokens = list(map(int, line.strip().split()))
            tokenized_lines.append(line)
            #print("READ: ",line) # debug

            if line.strip():  # Check if the line is not empty
                tokens = line.strip().split(" ")
                unsafe_move = (int(tokens[0]),int(tokens[1]),int(tokens[2]))
                unsafe_move_set.append(unsafe_move)
    
    return unsafe_move_set
    
def add_unsafe_move_set(current_moves, new_move):
    # in, current_moves set and int tuple (A, B, C) of new move
    # out, current_moves updated
    if new_move not in current_moves:
        original_piles = (new_move[0], new_move[1], new_move[2])


        for i in range(3):
            for j in range(1,4):
                pA, pB, pC = (original_piles[0], original_piles[1], original_piles[2])

                # adjust 1 move out                
                if i == 0:
                    pA += j
                elif i == 1:
                    pB += j
                elif i == 2:
                    pC += j

                # check if any piles below 0, then add to current_moves
                if (pA >= 0 and pB >= 0 and pC >= 0):
                    new_move = (pA, pB, pC)
                    if new_move not in current_moves:
                        current_moves.append(new_move)

    return current_moves

def update_unsafe_moves(filename, current_moves):
    # in, filename is relative filepath current_moves set of int tuple (A,B,C)

    with open(filename, "w") as file:
        current_moves = sorted(current_moves)
        for move in current_moves:
            file.write(" ".join(map(str, move)) + "\n")
    
#### Unsafe Moves ^^^^

def is_move_valid(board, the_pile, the_chips, the_player):
    # in, board int[3] the_pile 0-2 the_chips 1-3 the_player (T= comp, F=human)
    # out, bool if move is legal

    # no negative moves
    if the_pile < 0 or the_chips < 1:
        return False

    if (the_pile >= 0 and the_pile <= 2)  and (the_chips >= 1 and the_chips <= 3): # move in bounds
        if (board[the_pile] - the_chips >= 0 and get_board_sum(board) > 1):
            return True

    if not the_player:
        if get_board_sum(board) == 1 and board[the_pile] - the_chips >= 0:
            return True
    
    return False

def get_nim_sum(board):
    # in, current board
    # out, int of xor of each board pile
    return (board[0] ^ board[1] ^ board[2])

def get_board_sum(board):
    # in, current board
    # out, int sum of each board pile
    sum = 0
    for i in range(3):
        sum += board[i]

    return sum

    
def take_turn_human(board):
    # in, board int[3]
    # out, updated board
    
    # display board and get initial input
    print("Enter the pile letter (A, B, C) & 1, 2, or 3 chips to remove (EX: A1): \n")
    print_board(board)
    user_input = input()

    # prep for input validation
    valid_input = False
    player_choice_chips = -1
    player_choice_pile = -1

    # validate input
    while not valid_input:
        while len(user_input) != 2 or not (user_input[0] in ['A', 'B', 'C'] and user_input[1] in ['1', '2', '3']):
            print("Invalid input. Please enter a valid combination (A1, A2, ..., C3).\n")            
            user_input = input()
        
        player_choice_pile = ord(user_input[0]) - ord('A')  # convert A, B, C to 0, 1, 2
        player_choice_chips = int(user_input[1])

        if (is_move_valid(board, player_choice_pile, player_choice_chips, False)):
            valid_input = True
    
    # remove chips from board and print update
    
    board[player_choice_pile] -= player_choice_chips
    print_board_update(board, False, user_input[0], user_input[1])
    

    return board

def take_turn_random(board):
    # in, board int[3]
    # out, updated board

    # this is my overall strategy here
    # generate a random int (r) 3-11, 
    # then r%3 = pile to select, r/3 round down = amount to remove
    # check if a valid move, if so take it. Otherwise keep trying
   
    no_move_found = True

    while no_move_found:
        potential_move = random.randint(3,11)

        the_pile = potential_move % 3
        the_chips = int(potential_move/3)

        if is_move_valid(board, the_pile, the_chips, False):
            board[the_pile] -= the_chips
            print_board_update(board, False, the_pile, the_chips)
            no_move_found = False

    return board


def try_educated_machine_move(board, move_set):
    # in, current board
    # out, bool if made move or not
    move_made = False

    if get_nim_sum(board) == 0:
        move_type = 0
        board_state = (board[0], board[1], board[2])
        move_set = add_unsafe_move_set(move_set, board_state)
        print("\n~ Interesting move! ~\n") # temp to log/debug, keeping active 
        update_unsafe_moves("unsafe", move_set)
    else:
        for i in range(3):
            if move_made:
                break
            for j in range(3,0,-1):
                pA, pB, pC = (board[0], board[1], board[2])

                # adjust move            
                if i == 0:
                    pA -= j
                elif i == 1:
                    pB -= j
                elif i == 2:
                    pC -= j
                
                potential_move = (pA,pB,pC)
                #print("Guess Moves- ", potential_move)# debug 

                # check if in unsafe moves
                if potential_move in move_set and is_move_valid(board, i, j, True):
                    board[i] -= j
                    print_board_update(board, True, i, j)
                    move_made = True
                    break 
        
    return board, move_made, move_set

def take_turn_machine(board, move_set):
    # in, board int[3] move_set is list of unsafe board states in int tuples
    # out, updated board
    
    board, move_made, move_set = try_educated_machine_move(board, move_set)

    # check for any moves to set nim score to 0
    if not move_made:
        for i in range(3):
            if move_made:
                break
            for j in range(3,0,-1):
                if is_move_valid(board, i, j, True) and get_nim_sum(board) == 0 and get_board_sum(board) > 1:
                    board[i] -= j
                    print_board_update(board, True, i, j)
                    move_made = True
                    break

    if not move_made: # if absolutely no move, take 3,2,1 from any pile A->C
        machine_move_pile = -1
        machine_move_chips = -1
        for i in range(3):
            if machine_move_pile != -1 and machine_move_chips != -1:
                break
            for j in range(3,0,-1):
                if is_move_valid(board, i, j, True) and get_board_sum(board) > 1:
                    machine_move_pile = i
                    machine_move_chips = j
                    break
        
        board[machine_move_pile] -= machine_move_chips
        print_board_update(board, True, machine_move_pile, machine_move_chips)
        
    return board




############################################
#                    _          __ __      #
#  _ __ ___    __ _ (_) _ __   / / \ \  _  #
# | '_ ` _ \  / _` || || '_ \ | |   | |(_) #
# | | | | | || (_| || || | | || |   | | _  #
# |_| |_| |_| \__,_||_||_| |_|| |   | |(_) #
#                              \_\ /_/     #
############################################
    # ^ it stands out better for me ^ #
def main():

    if len(sys.argv) > 1:
        player_menu_selection = 4
    else:
      player_menu_selection = intro_to_game()
      
    board = create_game_board(player_menu_selection)
    game_is_active = True
    current_player = False  #Defualt -> F=Human, and T=Machine
    
    
    

    if player_menu_selection == 2 or player_menu_selection == 4:
        current_player = True
    elif player_menu_selection == 3 :
        if random.randint(0,1) == 1:
            current_player = True

    # read in unsafe moves and store in list
    move_set = read_unsafe_moves("unsafe")
    

    # take first machine turn outside of loop to print board properly
    if current_player :
        print("\nI am starting first...\n")
        print_board(board)
        board = take_turn_machine(board,move_set)
        if player_menu_selection != 4:    
            current_player = False

    while game_is_active :
        if current_player : # is machine
            if get_board_sum(board) > 1:
                board = take_turn_machine(board,move_set)
            else:
                # the clear board and declare loss!
                board = [0,0,0]

            current_player = False
        else :
        
            # hidden menu option 4, random moves to stimulate learning in machine
            if player_menu_selection == 4:
                board = take_turn_random(board)
            else:
                board = take_turn_human(board)

            current_player = True
            
        
        board_value = get_board_sum(board)
              
        if board_value == 0 :
            if current_player : # human lost, machine won
                print("\nBetter Luck Next Time!\n")
            else :
                print("\nCongrats, you won!\n")
            game_is_active = False

# execute main()
if __name__ ==  "__main__":
    main()
