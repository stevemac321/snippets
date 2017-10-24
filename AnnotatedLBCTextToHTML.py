import re
import sys
import os
from sys import argv

def main():
	assert(len(argv) == 2)

	f = open(argv[1])
	for line in f:
		#
		toks = line.split('.')
		line = re.sub(r'^(Paragraph [0-9]+)', r'<p><strong>\1.</strong>', toks.pop(0))
		print(line, end='')
		line = ''.join(toks)
		#
		k = line.rfind('(')
		s1 = line[:k] + '</br>'
		print(re.sub(r'#([0-9+])', r'<sup>\1</sup>', s1))
		s2 = '(' + line[k+1:]
		toks = s2.split('(')
		s2 = toks.pop(0)	
		s2 = toks.pop(0)
		s2 = s2.rstrip(')')
		s2 = s2 + ' </p>'
		p = re.sub(r'#([0-9]+)', r'</br><sup>\1</sup>', s2)
		print(p)		
	
	f.close()
	
main()