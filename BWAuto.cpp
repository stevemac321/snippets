// BWAuto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

void ParseLine(CComPtr<IDispatch> &ptr, string &line);
void ParseFile(CComPtr<IDispatch> &ptr, string &file);
void ParseCommandLine(int argc, char* argv[]);
void Usage();

int main(int argc, char* argv[])
{
	ParseCommandLine(argc, argv);
}

void ParseLine(CComPtr<IDispatch> &ptr, string &line)
{
	char seps[] = ";.";
	char *word = strtok(&line[0], seps);

	while (word != nullptr) {

		CComVariant varVerse(word);
		CComVariant varClip(TRUE);

		auto hr = ptr.Invoke1(L"GoToVerse", &varVerse);
		Sleep(100);

		if (hr == S_OK) {
			if (OpenClipboard(nullptr)) {

				auto h = GetClipboardData(CF_UNICODETEXT);
				if (h) 
					wprintf(L"%s ", (const wchar_t*)h);
				

				CloseClipboard();		
			}
		}
		
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

		if (strcmp(argv[1], "file") == 0) 
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
	puts("BWAuto.exe file filetoread.txt\n");
	puts("-or-\n");
	puts("BWAuto.exe <bibleworks format bibleref\n");
	exit(1);
}

