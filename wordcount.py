import os
from pathlib import Path
import sys
import time
from collections import Counter
import regex as re

def write_dict(d):
    with open(r"output.txt", "w+") as f: 
        for words, count in d.most_common():
            if(words != ' ' and words != ''):
                f.write(f"{count} {words}\n")

if (len(sys.argv) < 3):
    print("Usage: python wordcount.py <folder> <extension>")
    print("Example: python wordcount.py /home/user/ .txt")
    sys.exit(1)

folder = sys.argv[1]
ext = sys.argv[2]

word_frequency = Counter()

start = time.time()

files = lambda x: [os.path.join('./', file) for file in Path(x).rglob('*' + ext)] 
open_files = lambda x: [open(file, 'r') for file in files(x)]
file_contents = lambda x: [file.read().replace('\n', ' ') for file in open_files(x)]
words = lambda x: [re.sub(r"[^a-z0-9 ]", "", word.lower()) for content in file_contents(x) for word in content.split(' ') if word != '' and word != ' ']
word_count = lambda x: word_frequency.update(sorted(words(x), reverse=True))

word_count(folder)

write_dict(word_frequency)

print(time.time() - start)