import win32com
import win32clipboard
import sys
import re
import fileinput

#Word find
#\#([0-9]{1,2})
#word replace
#\1
#be sure to set format to superscript

from sys import argv
from re import split
from win32com import client
from win32com.client import Dispatch
from win32clipboard import OpenClipboard
from win32clipboard import CloseClipboard
from win32clipboard import GetClipboardData

# utilities
def split_keep_delims(line, delim):
	return [e+delim for e in line.split(delim) if e]

def strip_nonalnum_re(word):
	return re.sub(r"^\W+|\W+$", "", word)

def PrepreplaceFile(file, find, repl):
	with fileinput.FileInput(file, inplace=True, backup='.sav') as file:
		for line in file:
			print(line.replace(find, repl), end='')

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

	def PrintToWord(self, line, bold = 1, fontsize=9):	
		self.sel.Font.Bold = bold
		self.sel.Font.Name = 'Cambria'
		self.sel.Font.Size = fontsize
		self.sel.TypeText(line)
	
	def SaveDoc(self, name):
		self.word.Application.ActiveDocument.SaveAs2(name)

	def CloseDoc(self):
		self.word.Application.ActiveDocument.Close()

	def RunMacro(self, name):
		self.word.Application.Run(name)

class LBCTextToWord:

	def __init__(self, refs = False):
		self.bw = None
		self.word = None
		self.just_refs = refs
		self.infile = ''

	def IsJustRefs(self):
		return self.just_refs

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
		savebookchap = bookchap
		toks = rest.split(',')
	
		for tok in toks:
			tok = strip_nonalnum_re(tok)
			bookchap += tok
			self.bw.GoToVerse(bookchap)
			s = self.bw.GetVerse()
			self.PrintVerse(s)
			bookchap = savebookchap

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
		spaces = split_keep_delims(s, ' ')
		v = spaces.pop(0)
		low = int(v)
		hi = low + len(verses)
		bookchap += ''.join(toks)

		for x in results:
			toks = x.split(':')
			first = toks.pop(0)
			s = ''.join(toks)
			spaces = split_keep_delims(s, ' ')
			spaces.pop(0)
			low += 1
			rest = ' ' + str(low) + ' ' + ''.join(spaces)
			bookchap += rest
			
		self.PrintVerse(bookchap)

	def ParseVerse(self, verse):
		pattern = re.compile('^#[0-9]+')
		if(re.search(pattern, verse)):
			spaces = split_keep_delims(verse, ' ')
			footnum = spaces.pop(0)
			
			self.word.PrintToWord('\n', 1, 9)
			self.word.PrintToWord(footnum, 1, 9)
			verse = ''.join(spaces)

		stripped = strip_nonalnum_re(verse)

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
		spaces = split_keep_delims(s, ' ')

		v = spaces.pop(0)
		v = strip_nonalnum_re(v)

		bookchap += v + ': '
		rest = ''.join(spaces)

		self.word.PrintToWord(bookchap, 1, 9) 
		self.word.PrintToWord(rest, 0, 9)
		

	def ParseVerseLine(self, verseline):
		if(self.just_refs == False):
			toks = verseline.split(';')
			for tok in toks:
				self.ParseVerse(tok)
		
			self.word.PrintToWord('\n')
		else:
			toks = verseline.split('#')
			for tok in toks:
				p = tok.replace(')', '')
				self.word.PrintToWord('#' + p + '\n')
	
	def ParseFile(self, file):

		self.infile = file

		PrepreplaceFile(file, 'Psalms', 'Psalm')
		PrepreplaceFile(file, 'Jude ', 'Jude 1:')

		if(self.IsJustRefs() == False):
			self.bw = BibleWorksAuto()
			self.bw.Initialize()

		self.word = WordAuto()
		self.word.Initialize()

		bv = re.compile('[0-9]+:[0-9]+')

		f = open(file)

		for line in f:	
			if('(' not in line):
				self.PrintNonVerseLine(line)
			else:
				toks = line.split('(')
				last = toks.pop()
				jline = '('.join(toks)
				self.PrintNonVerseLine(jline)
				self.ParseVerseLine(last)

		f.close()

	def PrintNonVerseLine(self, line):
		pattern = re.compile('^Chapter [0-9]+:')
		title = re.compile('^London Baptist Confession of Faith 1689')

		if(re.search(title, line)):
			self.word.PrintToWord(line, 1, 16)
		elif(re.search(pattern, line)):
			self.word.PrintToWord(line, 1, 14)
		else:
			self.word.PrintToWord(line, 0, 12)

	def RunWordMacro(self, name):
		self.word.RunMacro(name)

	def SaveWordDoc(self, name):
		self.word.SaveDoc(name)

	def CloseWordDoc(self):
		self.word.CloseDoc()
		
def CreateOne(just_refs = False):
	lbc = LBCTextToWord(just_refs) #True means just print refs
	lbc.ParseFile(argv[1])

	lbc.RunWordMacro('Normal.NewMacros.ReplaceHashes')
	lbc.RunWordMacro('Normal.NewMacros.ChapterHeadings1')

	if(lbc.IsJustRefs() == True):
		lbc.SaveWordDoc(argv[1] + '.logos' + '.docx')
	else:
		lbc.SaveWordDoc(argv[1] + '.print' + '.docx')

	lbc.CloseWordDoc()

def main():
	CreateOne(True)
	CreateOne(False)

main()
