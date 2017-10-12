// BWAuto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class CBibleworks {
public:
	HRESULT Initialize()
	{
		auto hr = m_ptr.CoCreateInstance(L"bibleworks.automation");
		assert(hr == S_OK);

		CComVariant varClip(TRUE);
		hr = m_ptr.Invoke1(L"ClipGoToVerse", &varClip);
		assert(hr == S_OK);
		return hr;
	}
	std::wstring GetVerse(std::string &word)
	{
		CComVariant varVerse(const_cast<char*>(word.c_str()));
		std::wstring verse(L"");

		auto hr = m_ptr.Invoke1(L"GoToVerse", &varVerse);

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
private:
	CComPtr<IDispatch> m_ptr = nullptr;
};

class LBCExpandRefs {
public:
	enum mode { COMMANDLINE, FILE };
	void PopulateMap()
	{
		const char* books[] = {
			"Acts","Amos","Baruch","1 Chronicles","1 Corinthians","2 Chronicles",
			"2 Corinthians","Colossians","Daniel","Deuteronomy","Ecclesiastes",
			"Ephesians","Esther","Exodus","Ezekiel","Ezra","Galatians","Genesis",
			"Habakkuk","Haggai","Hebrews","Hosea","Isaiah","James","Jeremiah",
			"Job","Joel","John","1 John","2 John","3 John","Jonah","Joshua","Jude",
			"Judges","Judith","1 Kings","2 Kings","Lamentations","Leviticus","Luke",
			"1 Maccabees","2 Maccabees","Malachi","Mark","Matthew","Micah","Nahum",
			"Nehemiah","Numbers","Obadiah","1 Peter","2 Peter","Philemon","Philippians",
			"Proverbs","Psalms","Revelation","Romans","Ruth","1 Samuel","2 Samuel",
			"Sirach","Song of Songs","1 Thessalonians","2 Thessalonians","1 Timothy",
			"2 Timothy","Titus","Tobit","Wisdom","Zechariah","Zephaniah"
		};

		for (auto i : books)
			m_map.push_back(i);

		std::sort(std::begin(m_map), std::end(m_map));
	}
	std::vector<std::string> ParseDash(char * word)
	{
		std::vector<std::string> vVerses;

		char *dash = strstr(word, "-");

		if (dash) {
			char *colon = strstr(word, ":");
			char *lowerbound = colon;
			++lowerbound;

			*dash = '\0';
			vVerses.push_back(word);

			++dash;

			char *upperbound = dash;
			while (dash && *dash != '\0' && *dash != ' ')
				dash++;

			*dash = '\0';

			int low = atoi(lowerbound);
			int upper = atoi(upperbound);

			char versebuf[30];
			++colon;
			*colon = '\0';
			strcpy(versebuf, word);

			char itoabuf[30];

			for (int i = low + 1; i <= upper; i++) {
				_itoa(i, itoabuf, 10);
				strcat(versebuf, itoabuf);
				vVerses.push_back(versebuf);
				colon = strstr(versebuf, ":");
				++colon;
				*colon = '\0';
			}
		}
		else
			vVerses.push_back(word);

		return vVerses;

	}
	std::vector<std::string> ParseComma(char * word)
	{
		std::vector<std::string> vVerses;
		char *comma = strstr(word, ",");

		if (comma) {
			*comma = '\0';
			vVerses.push_back(word);

			++comma;

			char * colon = strstr(word, ":");
			char versebuf[30];
			++colon;
			*colon = '\0';
			strcpy(versebuf, word);

			char *left = colon + 1;
			char * right = comma;
			++right;

			while (right && !isdigit(*right))
				++right;

			while (right && *right != '\0') {
				while (!isdigit(*right))
					++right;
				while (isdigit(*right)) {
					*left = *right;
					++left;
					++right;
				}
				char c = *right;
				*right = '\0';
				strcat(versebuf, left);
				vVerses.push_back(versebuf);

				if (c == '\0')
					break;
				else {
					++right;
					if (*left != '\0') {
						char *shift = left + 1;
						while (*shift != '\0') {
							*(shift - 1) = *shift;
							++shift;
						}
					}
					colon = strstr(versebuf, ":");
					left = colon + 1;
				}
			}
		}
		else
			vVerses.push_back(word);

		return vVerses;
	}
	std::vector<std::string> ParseMultiVerseRef(char * word)
	{
		char * comma = strstr(word, ",");

		if (comma)
			return ParseComma(word);
		else
			return ParseDash(word);
	}
	void ParseLine(std::string & line)
	{
		char seps[] = ";";
		char *word = strtok(&line[0], seps);

		while (word != nullptr) {
			auto v = ParseMultiVerseRef(word);
			for (auto s : v) {
				std::wstring verse = m_bw.GetVerse(s);
				if (verse != L"")
					std::wcout << verse.c_str() << " ";
			}
			word = strtok(nullptr, seps);
		}
		std::wcout << L"\n\n";
	}

	void ParseFile()
	{
		if (m_mode != FILE) {
			auto v = ParseMultiVerseRef(const_cast<char*>(m_line.c_str()));
			for (auto s : v) {
				std::wstring verse = m_bw.GetVerse(s);
				if (verse != L"")
					std::wcout << verse << " ";
			}

			std::cout << "\n\n";
		}
		else {
			std::fstream fs;
			std::string line;

			fs.open(m_file);
			if (fs.is_open()) {
				while (std::getline(fs, line))
					ParseLine(line);
			}

			fs.close();
		}
	}
	void ParseCommandLine(int argc, char* argv[])
	{
		if (argc < 3)
			Usage();

		if (strcmp(argv[1], "file") == 0) {
			m_mode = FILE;
			m_file = argv[2];
		}
		else {
			m_mode = COMMANDLINE;
			m_line = argv[1];
			m_line += " ";
			m_line += argv[2];
		}
	}

	HRESULT InitializeBW()
	{
		return m_bw.Initialize();
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
private:
	std::vector<std::string> m_map;
	CBibleworks m_bw;
	mode m_mode = COMMANDLINE;
	std::string m_line = "";
	std::string m_file = "";
};


int main(int argc, char* argv[])
{
	auto hr = CoInitialize(nullptr);
	assert(hr == S_OK);
	{
		LBCExpandRefs lbc;
		lbc.InitializeBW();
		lbc.ParseCommandLine(argc, argv);
		lbc.ParseFile();
	}

	CoUninitialize();
}