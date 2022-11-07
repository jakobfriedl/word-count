import os
import sys
import time

if (len(sys.argv) < 3):
    print("Usage: python wordcount.py <folder> <extension>")
    print("Example: python wordcount.py /home/user/ .txt")
    sys.exit(1)

folder = sys.argv[1]
ext = sys.argv[2]

word_frequency = {}

start = time.time()

# recursively walk through the folder
for root, dirs, files in os.walk(folder):
    for file in files:
        # only process files with the given extension
        if file.endswith(ext):
            with open(os.path.join(root, file), 'r') as f:
                for line in f:
                    for word in line.split():
                        w = word.lower()
                        if w in word_frequency:
                            word_frequency[w]+= 1
                        else:
                            word_frequency[w] = 1

print(word_frequency)
print(time.time() - start)