// BWAuto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

void ParseLine(CComPtr<IDispatch> &ptr, string &line);
void ParseFile(CComPtr<IDispatch> &ptr, string &file);
void ParseCommandLine(int argc, char* argv[]);
void Usage();
wstring GetVerse(CComPtr<IDispatch> &ptr, char* word);
void PopulateMap(vector<string> & v);


int main(int argc, char* argv[])
{

	ParseCommandLine(argc, argv);
}

void ParseLine(CComPtr<IDispatch> &ptr, string &line)
{
	char seps[] = ";";
	char *word = strtok(&line[0], seps);

	while (word != nullptr) {

		wstring verse = GetVerse(ptr, word);
		if (verse != L"")
			wcout << verse.c_str() << " ";

		word = strtok(nullptr, seps);
	}
	wprintf(L"\n");
}
void ParseFile(CComPtr<IDispatch> &ptr, string &file)
{
	fstream fs;
	string line;

	fs.open(file);
	if (fs.is_open())
		while (getline(fs, line))		
				ParseLine(ptr, line);	

	fs.close();
}
void ParseCommandLine(int argc, char* argv[])
{
	if (argc < 3) 
		Usage();

	auto hr = CoInitialize(nullptr);
	assert(hr == S_OK);
	{
		CComPtr<IDispatch> ptr;
		hr = ptr.CoCreateInstance(L"bibleworks.automation");
		assert(hr == S_OK);

		CComVariant varClip(TRUE);
		hr = ptr.Invoke1(L"ClipGoToVerse", &varClip);
		assert(hr == S_OK);

		if (strcmp(argv[1], "semi") == 0) 
			ParseFile(ptr, string(argv[2]));
		else {
			string line(argv[1]);
			line += " ";
			line += argv[2];
			ParseLine(ptr, line);
		}
	}
	CoUninitialize();
}
void Usage()
{
	puts("Usage: \n");
	puts("BWAuto.exe semi semi-colon-delimited.txt\n");
	puts("-or-\n");
	puts("BWAuto.exe fulltext fullfindandreplace.txt\n");
	puts("-or-\n");
	puts("BWAuto.exe <bibleworks format bibleref\n");
	exit(1);
}

wstring GetVerse(CComPtr<IDispatch> &ptr, char* word)
{
	CComVariant varVerse(word);
	wstring verse(L"");
	auto hr = ptr.Invoke1(L"GoToVerse", &varVerse);

	if (hr == S_OK) {
		if (OpenClipboard(nullptr)) {

			HANDLE h = nullptr;
			for (int i = 0; i < 1000 && h == nullptr; i++) {
				h = GetClipboardData(CF_UNICODETEXT);
			}

			if (!h)
				puts("GetClipboardData returned nullptr\n");
			else
				verse = (const wchar_t*)h;


			CloseClipboard();

		}
		else
			printf("OpenClipboard failed %x\n", GetLastError());
	}
	return verse;
}
void PopulateMap(vector<string> & v)
{
	const char* books[] = {
		"Acts", 
		"Amos", 
		"Baruch", 
		"1 Chronicles",
		"1 Corinthians",
		"2 Chronicles",
		"2 Corinthians",
		"Colossians",
		"Daniel",
		"Deuteronomy",
		"Ecclesiastes",
		"Ephesians",
		"Esther",
		"Exodus",
		"Ezekiel",
		"Ezra",
		"Galatians",
		"Genesis",
		"Habakkuk",
		"Haggai",
		"Hebrews",
		"Hosea",
		"Isaiah",
		"James",
		"Jeremiah",
		"Job",
		"Joel",
		"John",
		"1 John",
		"2 John",
		"3 John",
		"Jonah",
		"Joshua",
		"Jude",
		"Judges",
		"Judith",
		"1 Kings",
		"2 Kings",
		"Lamentations",
		"Leviticus",
		"Luke",
		"1 Maccabees",
		"2 Maccabees",
		"Malachi",
		"Mark",
		"Matthew",
		"Micah",
		"Nahum",
		"Nehemiah",
		"Numbers",
		"Obadiah",
		"1 Peter",
		"2 Peter",
		"Philemon",
		"Philippians",
		"Proverbs",
		"Psalms",
		"Revelation",
		"Romans",
		"Ruth",
		"1 Samuel",
		"2 Samuel",
		"Sirach",
		"Song of Songs",
		"1 Thessalonians",
		"2 Thessalonians",
		"1 Timothy",
		"2 Timothy",
		"Titus",
		"Tobit",
		"Wisdom",
		"Zechariah",
		"Zephaniah"
	};

	for (auto i : books)
		v.push_back(i);

	sort(begin(v), end(v));	
}