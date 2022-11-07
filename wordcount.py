import os
from pathlib import Path
import sys
import time

def print_dict(d):
    for k, v in d.items():
        print(f"{k} -> {v}")


if (len(sys.argv) < 3):
    print("Usage: python wordcount.py <folder> <extension>")
    print("Example: python wordcount.py /home/user/ .txt")
    sys.exit(1)

folder = sys.argv[1]
ext = sys.argv[2]

word_frequency = {}

start = time.time()

files = lambda x: [os.path.join('./', file) for file in Path(x).rglob('*' + ext)] 
open_files = lambda x: [open(file, 'r') for file in files(x)]
file_contents = lambda x: [file.read().replace('\n', ' ') for file in open_files(x)]
words = lambda x: [word.lower() for content in file_contents(x) for word in content.split(' ') if word != '']
inc = lambda x: x + 1; 
word_count = lambda x: [word_frequency.update({word: inc(word_frequency.get(word, 0))}) for word in words(x)]

# word_count = lambda x: [word_frequency.update({word: word_frequency.get(word, 0)+1}) for word in [word.lower() for content in [file.read().replace('\n', ' ') for file in [open(file, 'r') for file in [os.path.join('./', file) for file in Path(x).rglob('*' + ext)] ]] for word in content.split(' ') if word != '']]

word_count(folder)

print_dict(word_frequency)

print(time.time() - start)