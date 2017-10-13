import re
import sys

def has_verse(line):
    found = re.search('[0-9]:[0-9]', line)
    return found

def print_verses(line):
    parts = line.split(';')
    for cp in parts:
        p = cp.strip()
        print(p)

line = 'hello there (this is a test) no worries ( John 3:16; Eph 4:12 ; 1 John 3:3-7; 1 Corinthian 2:10-12,14,15 )'

delim = '('


parts  = [e+delim for e in line.split(delim) if e]

last = parts.pop()

for p in parts:
    print(p, end='')

verses = last.split(')');
verses.pop();

print_verses(''.join(verses))
    


#parts = s.split('(')

#last = parts.pop()

#for p in parts:
 #   print(p)

#last_paren

#print_verses(last)
