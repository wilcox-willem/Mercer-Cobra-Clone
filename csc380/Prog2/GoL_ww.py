# Willem Wilcox, Dr. Digh, CSC 380, MU, 3/10/24
# note: when printing the board, I used "-" instead of "X" because it was easier for me to see
#       it can be changed on line 66! I swapped it back to "X" for submission though

import sys,os,random,copy
def intro_to_game():
    # in, nothing
    # out, user input num of generation 1-100
    print("\n\n\n\n\n\n")
    print("Artificial Life Simulation of Game of Life")
    print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
    print("Each cell with one or no neighbors dies, as if by loneliness")
    print("Each cell with four or more neighbors dies, as if by overpopulation") 
    print("Each cell with two or three neighbors survives") 
    print("Each cell with three neighbors becomes populated") 
    print("Each cell that ages over 10 generations dies.\n")
    print("How many generations would you like to simulate? ")
    
    player_selection = int(input())
    
    if (player_selection > 100 or player_selection < 1):
        while (player_selection > 100 or player_selection < 1):
            print("\nInvalid input, please use 1-100\n")
            player_menu_selection = int(input())
    return player_selection


def prep_board(board_filename, board):
    # in: board_filename string, current board
    # out: board from file

    with open(board_filename, 'r') as file:
        for row, line in enumerate(file):
            # split the line into individual characters
            elements = line.split()
            for col, element in enumerate(elements):
                # Update the board based on 'X' presence
                if element == 'X':
                    board[row][col] = 1

    return board

def random_start(board):
    # in: current board
    # out: random positions selected for start

    for col in range(20):
        for row in range(20):
            rand_int = random.randint(0,100)
            if rand_int < 10: # adjust this or the line above to affect starting odds
                board[col][row] = 1
    return board

def print_board(generation_count, board):
    # in: generation_count int, current board
    # out: nothing

    if generation_count == 0:
        print("Initial colony prior to evolution")
    else:
        print("Evolution over", generation_count+1, "generation(s)")
    
    for col in range(20):
        row_text = ""
        for row in range(20): 
            row_character = "0 "

            if board[col][row] > 0:
                row_character = "X "
                # row_character = "-  " 

            row_text += row_character
        
        print(row_text)
    print(" ")
     
def update_board(board):
    # in: current board
    # out: updated board according to rules of life

    # Create a new board to store the updated state
    updated_board = [[0 for _ in range(20)] for _ in range(20)]

    for col in range(20):
        for row in range(20):
            # count neighbors for this cell
            neighbor_count = 0

            for i in range(-1, 2):
                for j in range(-1, 2):
                    # skip self
                    if i == 0 and j == 0:
                        continue

                    # check if neighbor is inbounds
                    if 0 <= col + i < 20 and 0 <= row + j < 20:
                        neighbor_count += board[col + i][row + j]

            # Apply the rules based on the number of neighbors
            if neighbor_count <= 1:
                # Rule 1: Loneliness
                updated_board[col][row] = 0
            elif neighbor_count == 2:
                # Rule 2: Stable
                updated_board[col][row] = board[col][row]
            elif neighbor_count == 3:
                # Rule 3: Birth or remains alive
                if updated_board[col][row] == 0:
                    updated_board[col][row] = 1
            else:
                # Rule 4: Overcrowding
                updated_board[col][row] = 0

            # Rule 5: Age limit
            if board[col][row] > 0:
                if board[col][row] > 10:
                    updated_board[col][row] = 0
                else:
                    updated_board[col][row] = board[col][row] + 1

    return updated_board


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
    num_of_generations = 1 # update with player input
    board = [[0 for _ in range(20)] for _ in range(20)] # blank board
    
    if len(sys.argv) > 2 and sys.argv[1] == "-f":
        board_filename = sys.argv[2]
        board = prep_board(board_filename, board)
    else:
        board = random_start(board)

    num_of_generations = intro_to_game()

    for generation_count in range(num_of_generations):
        board = update_board(board)
        print_board(generation_count, board)
      
    
# execute main()
if __name__ ==  "__main__":
    main()
