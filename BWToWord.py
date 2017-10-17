import win32com
import win32clipboard
import sys
import re

from sys import argv
from re import split
from win32com import client
from win32com.client import Dispatch
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

class WordAuto:
	def __init__(self):
		self.word = None
		self.doc = None
		self.sel = None

	def Initialize(self):
		self.word = client.Dispatch('Word.Application')
		assert(self.word != None)	

		self.doc = self.word.Documents.Add()
		assert(self.doc != None)

		self.word.Visible = True
		self.sel = self.word.Selection

	def PrintToWord(self, line, style = 'Normal', bold = 0):
		self.sel.Style = style
		self.sel.font.Bold = bold
		self.sel.font.Size = 12
		self.sel.TypeText(line)
	

class LBCTextToWord:

	def __init__(self):
		self.bw = None
		self.word = None

	def strip_nonalnum_re(self, word):
		return re.sub(r"^\W+|\W+$", "", word)

	def ParseDashPart(self, bookchap, rest):
		verses = []
		dashtoks = rest.split('-')
	
		p = dashtoks.pop(0)
		if(p != None):
			low = int(p)
			p = dashtoks.pop(0)
			if(p != None):
				hi = int(p)
				for x in range(low, hi + 1):
					verses.append(bookchap + str(x))

		return verses

	def PrintCommaVerses(self, bookchap, rest):
		return None

	def PrintDashedVerses(self, verses):
		results = []
		for v in verses:
			self.bw.GoToVerse(v);
			s = self.bw.GetVerse()
			results.append(s)
		
		#make one multi-verse line to print		
		#get the first verse
		first = results.pop(0)

		toks = first.split(':')
		bookchap = toks.pop(0) + ':'
		s = ''.join(toks)
		delim = ' '
		spaces  = [e+delim for e in s.split(delim) if e]
		v = spaces.pop(0)
		low = int(v)
		hi = low + len(verses)
		#bookchap += v + '-' + str(hi-1) + ': '		

		bookchap += ''.join(toks)

		for x in results:
			toks = x.split(':')
			first = toks.pop(0)
			s = ''.join(toks)
			delim = ' '
			spaces  = [e+delim for e in s.split(delim) if e]
			spaces.pop(0)
			low += 1
			rest = ' ' + str(low) + ' ' + ''.join(spaces)
			bookchap += rest
			
		self.PrintVerse(bookchap)

	def ParseVerse(self, verse):
		pattern = re.compile('^#[0-9]+')
		if(re.search(pattern, verse)):
			delim = ' '
			spaces  = [e+delim for e in verse.split(delim) if e]
			footnum = spaces.pop(0)
			
			self.word.PrintToWord('\n')
			self.word.PrintToWord(footnum, 'Normal', 0)
			verse = ''.join(spaces)

		stripped = self.strip_nonalnum_re(verse)

		#split by colon, first part is book and chapter, be sure to add the colon
		toks = stripped.split(':')
		bookchap = toks.pop(0)
		if(bookchap != None):
			bookchap += ':'

			rest = ''.join(toks)
			if(re.search('-', rest)):
				verses = self.ParseDashPart(bookchap, rest)
				if(verses != None):
					self.PrintDashedVerses(verses)
			elif(re.search(',', rest)):
				self.PrintCommaVerses(bookchap, rest)
			else:
				self.bw.GoToVerse(bookchap + rest)
				s = self.bw.GetVerse()
				self.PrintVerse(s + ' ')

	def PrintVerse(self, verse):
		#break into two calls, set bold on first, add colon to first
		verse = verse[4:]
		toks = verse.split(':')
		bookchap = toks.pop(0)
		bookchap += ':'
		
		s = ''.join(toks)
		delim = ' '
		spaces  = [e+delim for e in s.split(delim) if e]

		v = spaces.pop(0)
		v = self.strip_nonalnum_re(v)

		bookchap += v + ': '
		rest = ''.join(spaces)

		self.word.PrintToWord(bookchap, 'Normal', 1) 
		self.word.PrintToWord(rest + ' ', 'Normal', 0)
		

	def ParseVerseLine(self, verseline):
		toks = verseline.split(';')
		for tok in toks:
			self.ParseVerse(tok)
	
	def ParseFile(self, arg):
		self.bw = BibleWorksAuto()
		self.bw.Initialize()

		self.word = WordAuto()
		self.word.Initialize()

		bv = re.compile('[0-9]+:[0-9]+')

		f = open(arg)

		for line in f:	
			if('(' not in line):
				self.PrintNonVerseLine(line)
			else:
				toks = line.split('(')
				last = toks.pop()
				jline = '('.join(toks)
				self.PrintNonVerseLine(jline + '\n')
				self.ParseVerseLine(last)

		f.close()

	def PrintNonVerseLine(self, line):
		pattern = re.compile('^Chapter [0-9]+:')
		title = re.compile('^London Baptist Confession of Faith 1689')

		if(re.search(title, line)):
			self.word.PrintToWord(line, 'Title', 1)
		elif(re.search(pattern, line)):
			self.word.PrintToWord(line, 'Heading 1', 1)
		else:
			self.word.PrintToWord(line)

def main():
	assert(argv[1] != None)
	lbc = LBCTextToWord()
	lbc.ParseFile(argv[1])

main()
