import os
import sys

def mapper(file_name):
    array_word = []
    file=open(file_name, 'r+')
    for lines in file:
        word_count = lines.strip().split()
        for word in word_count:
            array_word+=[(word,1)]
    return array_word

def reducer(array):
    reduced_array = []
    Current_count = 0
    word = None
    Current_Word = None
    for word, count in array:
        try:
            count = int(count)
        except ValueError:
            continue
        if Current_Word == word:
            Current_count += count
        else:
            if Current_Word:
                reduced_array += [(Current_Word, Current_count)]
            Current_Word = word
            Current_count = count
    if Current_Word == word:
        reduced_array += [(Current_Word, Current_count)]
    return reduced_array

def run(filename):
    return reducer(mapper(filename))
def main():
    filename = sys.argv[1]
    if os.path.isfile(filename):
        print("=================Word_Map_Reduce===================\n")
        print(run(filename))
    else:
        print("File not exit")
        exit()

if __name__ == '__main__':
    main()