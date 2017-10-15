import win32com
import win32clipboard
import sys
import re

from sys import argv
from re import split
from win32com import client
from win32clipboard import OpenClipboard
from win32clipboard import CloseClipboard
from win32clipboard import GetClipboardData

class BibleWorksAuto:
	def __init__(self):
		self.bw = None

	def Initialize(self):
		self.bw = client.Dispatch('Bibleworks.Automation')
		assert(self.bw != None)
		hr = self.bw.ClipGoToVerse(True)
		assert(hr == None)

	def GoToVerse(self, verse):
		return self.bw.GoToVerse(verse)

	#returns string if pass, None if fails
	def GetVerse(self):
		handle = OpenClipboard(None)
		assert(handle == None)

		s = GetClipboardData(win32clipboard.CF_UNICODETEXT)
		CloseClipboard();

		return s  

def CommandMode(arg):
	bv = re.compile('[0-9]+:[0-9]+')
	if(re.search(bv, arg) != None):
		bwo = BibleWorksAuto()
		bwo.Initialize()
		bwo.GoToVerse(arg)
		s = bwo.GetVerse()

		if(s != None):
			print(s)
	else:
		print('bad format')

def strip_nonalnum_re(word):
    return re.sub(r"^\W+|\W+$", "", word)

def ParseDashPart(bookchap, rest):
	verses = []
	dashtoks = rest.split('-')
	
	p = dashtoks.pop(0)
	if(p != None):
		low = int(p)
		p = dashtoks.pop(0)
		if(p != None):
			hi = int(p)
			for x in range(low, hi):
				verses.append(bookchap + str(x))

	return verses
				

def ParseCommas(bookchap, rest):
	print(bookchap + rest)

def FixupFormerDashed(verses):
	# pop first verse, call GetVerse
		# get rid of version ASV, KJV
		# restore dash format on retrieved data, then print without newline, end = ''
	# loop thru the rest, call GetVerse from BS
		# split(':') on retrived data, pop last and print just the number, with space
		# in Word you will make it smaller, maybe we add a special ^ character 
		# for bulk replace
	# newline after last
	for v in verses:
		print(v)

def ParseVerse(verse):
	stripped = strip_nonalnum_re(verse)

	#split by colon, first part is book and chapter, be sure to add the colon
	toks = stripped.split(':')
	bookchap = toks.pop(0)
	if(bookchap != None):
		bookchap += ':'

		rest = ''.join(toks)
		if(re.search('-', rest)):
			verses = ParseDashPart(bookchap, rest)
			if(verses != None):
				FixupFormerDashed(verses)
		elif(re.search(',', rest)):
			ParseCommas(bookchap, rest)
		else:
			print(bookchap + rest)

def ParseLine(line):
	toks = line.split(';')
	for tok in toks:
		ParseVerse(tok)

def FileMode(arg):
	bv = re.compile('[0-9]+:[0-9]+')
	f = open(arg)

	for line in f:	
		toks = line.split('(')
		last = toks.pop()
		jline = '('.join(toks)
		print(jline)
		ParseLine(last)


def main():
	#Parse command line.  Three args is command mode, two args is file mode
	#Examples:
		#Command Mode: John 3:16
		#File Mode: text.txt
	if(len(argv) < 3):
		FileMode(argv[1])
	else:
		newarg = argv[1] + ' ' + argv[2]
		CommandMode(newarg)

main()	
