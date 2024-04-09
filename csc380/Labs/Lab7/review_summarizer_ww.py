# Willem Wilcox, 3/16/24
# CSC380, Dr. Digh, MU
# This had the most "python nifty features" in any assignment I have done at Mercer.
# I am starting to see the appeal, but I still don't love it

import os,re
from collections import Counter

# Classify review as pos or neg based on filename
def review_pos_or_neg(filename):
    stars = int(filename.split('_')[1].split('.')[0])
    return 'pos' if 6 <= stars <= 10 else 'neg'

# Data prep - remove special chars, syms, n punc; lowercase n tokenize; 
def prep_text(text):
    cleaned_text = re.sub(r'[^a-zA-Z\s]', '', text)
    cleaned_text = cleaned_text.lower()
    cleaned_text = cleaned_text.split()

    # Remove stop words
    stop_words = set(['this', 'that', 'take', 'want', 'which', 'then', 'than', 'will', 'with', 'have', 
                      'after', 'such', 'when', 'some', 'them', 'could', 'make', 'though', 'from', 'were', 
                      'also', 'into', 'they', 'their', 'there', 'and', 'because'])
    return [word for word in cleaned_text if len(word) >= 4 and word not in stop_words]
    # Stuff like this return statement, is what I like in python :) 
    
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

    # Set file path
    reviews_folder = './reviews'

    pos_words_counter = Counter()

    for filename in os.listdir(reviews_folder):
        with open(os.path.join(reviews_folder, filename), 'r', encoding='utf-8') as file:
            # Get review test
            review_text = file.read()
            
            # Prep text
            prepped_text = prep_text(review_text)
            
            # If pos review, count words
            if review_pos_or_neg(filename) == 'pos':
                pos_words_counter.update(prepped_text)

    # Output the first 100 words occurring most frequently in positive reviews
    pos_top_100 = pos_words_counter.most_common(100)

    # Print out the words in descending order by frequency, ten words per line
    words_per_line = 10
    temp_line = ""
    
    print("Top 100 Words Used in Positive Reviews")
    print("--------------------------------------")

    for i in range(100):
        temp_line += pos_top_100[i][0]
        temp_line += " "
        
        if i % words_per_line == 9:
            print(temp_line)
            temp_line = ""


# execute main()
if __name__ ==  "__main__":
    main()