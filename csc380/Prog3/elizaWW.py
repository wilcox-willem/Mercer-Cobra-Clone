# Willem Wilcox, Dr. Digh, CSC 380, MU, 4/1/24
# note: the readme contains descriptions of what methods and steps i took
#       but I still added comments along the way to explain what i am trying to do 

import sys,os,random,copy,time

def clean_input(user_input):
    # in, user_input
    # out, user_input, lowercase and noise reduced
    
    # noise set
    words_noise = set(["this", "that", "take", "which", "then", "than",
        "will", "with", "have", "after", "such", "when", "some", 
        "them", "could", "make", "through","from", "were", "also", 
        "into", "they", "their", "there", "my", "her", "his", "a", "the"])

    cleaned_text = user_input
    cleaned_text = cleaned_text.lower()
    cleaned_text = cleaned_text.split()

    # remove noise and rejoin text
    cleaned_text = ([word for word in cleaned_text if word not in words_noise])
    cleaned_text = ' '.join(cleaned_text)

    return cleaned_text


def load_dialogue(file_path):
    #  in, file_path of dialogue file
    # out, dictionary where keys are user input 
    #      that lead to all responses per key
    #
    #      note: this is a little wasteful memory wise,
    #            but i found that sorting the dict by key size L-S
    #            increased response accuracy as i added more and more stuff

    dialogue = {}
    with open(file_path, 'r') as file:
        lines = file.readlines()
        current_key = None
        for line in lines:
            line = line.strip()
            if line.startswith('#') or line == '':
                current_key = None
            else:
                if current_key is None:
                    # split the line by "|" to handle multiple user inputs
                    keys = line.split("|")
                    for key in keys:
                        dialogue[key] = []
                    current_key = keys
                else:
                    # associate the same set of responses with all keys
                    for key in current_key:
                        dialogue[key].append(line)
    
    # sort the dialogue dict by key length, Longest to Shortest
    dialogue = dict(sorted(dialogue.items(), key=lambda x: len(x[0]), reverse=True)) 

    return dialogue

def load_facts(file_path):
    #  in, file_path of facts file
    # out, list of random facts

    facts = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            line = line.strip()
            facts.append(line)

    return facts


def get_response(user_input, dialogue):
    #  in, user_input
    # out, prints response from Eliza
    #
    # note: to speed up this it first checks if user input is a key,
    #       if not it then checks if any keys are within the user input,
    #       if found, it then pulls a random response and modifies if needed,
    #       otherwise it then pulls a random response from "__NO_MATCH__".
    #       finally, as soon as it finds an appropriate response it prints then returns
    user_input = clean_input(user_input)

    if user_input in dialogue:
        responses = dialogue[user_input]
        response = random.choice(responses)

        print("Eliza:", response)
        return

    else:
        for key in dialogue:
            if key in user_input:
                responses = dialogue[key]
                response = random.choice(responses)

                if "*" in response:
                    response = response.split("*")
                    response_snippet = user_input.split(key)

                    if response_snippet[1][0] == " ":
                        response_snippet[1] = response_snippet[1][1:]

                    print("Eliza: %s%s%s" % (response[0], response_snippet[1], response[1]))
                    return
                else:
                    print("Eliza:", response)
                    return

    responses = dialogue['__NO_MATCH__']
    response = random.choice(responses)
    print("Eliza:", response)
    return
            


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

    do_sleep = True

    # command arg disables Eliza Sleep
    if len(sys.argv) > 1:
        do_sleep = False
    
        

    # parse dialogue dict from file
    dialogue = load_dialogue("dialogue.txt")

    # parse fact dict from file
    facts = load_facts("Facts.txt")
        
    # greet user
    print("Hello, my name is Eliza")

    # to control rate of random facts
    fact_timer = random.randint(1,5)


    # response/dialogue loop of program
    while (True):
        # get user input and clean it
        print(" ", end="~ ")
        user_input = input()
        user_input = clean_input(user_input)
        print("  ")
        
    
        if ("bye" or "bye.") in user_input:
            sys.exit()
        else:
            # "thinking" step, to make user think Eliza is thinking
            #  making responses feel  more authentic.
            #  Disable by using any command arg after
            if do_sleep:
                time.sleep(random.randint(1,5))

            fact_timer -= 1

            if fact_timer < 1:
                print("Eliza: This is a little off topic, but do you know what I just thought about? The fact that")
                print(random.choice(facts))
                print("\nEliza: What do you think about that?")
                fact_timer = random.randint(6,10)
            else:        
                get_response(user_input, dialogue)
        
        
    
# execute main()
if __name__ ==  "__main__":
    main()