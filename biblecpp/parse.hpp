#pragma once
#include "precompile.hpp"

struct book {
  const char *name;
  const char *num;
} books[] = {
    "GEN", "01",  "EXO", "02",  "LEV", "03",  "NUM", "04",  "DEU", "05",  "JOS",
    "06",  "JDG", "7",   "RUT", "8",   "1SA", "9",   "2SA", "10",  "1KI", "11",
    "2KI", "12",  "1CH", "13",  "2CH", "14",  "EZR", "15",  "NEH", "16",  "EST",
    "17",  "JOB", "18",  "PSA", "19",  "PRO", "20",  "ECC", "21",  "SOL", "22",
    "ISA", "23",  "JER", "24",  "LAM", "25",  "EZE", "26",  "DAN", "27",  "HOS",
    "28",  "JOE", "29",  "AMO", "30",  "OBA", "31",  "JON", "32",  "MIC", "33",
    "NAH", "34",  "HAB", "35",  "ZEP", "36",  "HAG", "37",  "ZEC", "38",  "MAL",
    "39",  "MAT", "40",  "MAR", "41",  "LUK", "42",  "JOH", "43",  "ACT", "44",
    "ROM", "45",  "1CO", "46",  "2CO", "47",  "GAL", "48",  "EPH", "49",  "PHI",
    "50",  "COL", "51",  "1TH", "52",  "2TH", "53",  "1TI", "54",  "2TI", "55",
    "TIT", "56",  "PHM", "57",  "HEB", "58",  "JAM", "59",  "1PE", "60",  "2PE",
    "61",  "1JO", "62",  "2JO", "63",  "3JO", "64",  "JUD", "65",  "REV", "66"};

using std::map;
using std::pair;
using std::regex;
using std::string;

template <typename T, size_t N>
constexpr size_t array_size(T (&)[N]) {
  return N;
}

struct mless {
  bool constexpr operator()(const char *s1, const char *s2) {
    return strcmp(s1, s2) < 0;
  }
};

class parsecmd {
 public:
  parsecmd() {
    for (size_t i = 0; i < array_size(books); i++)
      _m.insert(std::make_pair(books[i].name, books[i].num));
  }

  string build_bookname(std::smatch &parts, int dex) {
    string first_part = parts[dex];
    first_part.resize(3);

    std::transform(first_part.begin(), first_part.end(), first_part.begin(),
                   ::toupper);
    auto snum = _m.find(first_part.c_str());

    if (snum == _m.end()) return string("");
    string str = snum->second;
    return str;
  }

  string build_sql_pattern1(std::smatch &parts, int first, int last) {
    string str;

    for (int i = first; i < last + 1; i++) {
      string p = parts[i];
      str += get_padded_value(const_cast<char *>(p.c_str()));
    }

    return str;
  }

  pair<string, string> parse_cmd(const char *cmd) {
    string command(cmd);
    std::smatch parts;
    string ret1;
    string ret2;

    // pattern 0: Gen 1:1-Gen 2:1
    std::regex r0(
        "([A-za-z]+) ([0-9]+):([0-9]+)-([A-za-z]+) ([0-9]+):([0-9]+)");
    if (std::regex_search(command, parts, r0)) {
      ret1 = build_bookname(parts, 1);
      ret2 = build_bookname(parts, 4);
      ret1 += build_sql_pattern1(parts, 2, 3);
      ret2 += build_sql_pattern1(parts, 5, 6);
      return std::make_pair(ret1, ret2);
    }

    // pattern 1: Gen 1:1-2:1
    std::regex r1("([A-za-z]+) ([0-9]+):([0-9]+)-([0-9]+):([0-9]+)");
    if (std::regex_search(command, parts, r1)) {
      ret1 = build_bookname(parts, 1);
      ret2 = ret1;
      ret1 += build_sql_pattern1(parts, 2, 3);
      ret2 += build_sql_pattern1(parts, 4, 5);
      return std::make_pair(ret1, ret2);
    }

    // pattern 2: Gen 1:1-3
    std::regex r2("([A-za-z]+) ([0-9]+):([0-9]+)-([0-9]+)");
    if (std::regex_search(command, parts, r2)) {
      ret1 = build_bookname(parts, 1);
      ret1 += build_sql_pattern1(parts, 2, 2);
      ret2 = ret1;
      ret1 += build_sql_pattern1(parts, 3, 3);
      ret2 += build_sql_pattern1(parts, 4, 4);
      return std::make_pair(ret1, ret2);
    }

    // pattern 3: Gen 1:1
    std::regex r3("([A-za-z]+) ([0-9]+):([0-9]+)");
    if (std::regex_search(command, parts, r3)) {
      ret1 = build_bookname(parts, 1);
      ret1 += build_sql_pattern1(parts, 2, 3);
      return std::make_pair(ret1, ret1);
    }

    return std::make_pair("", "");
  }

  string get_padded_value(char *val) {
    int vallen = strlen(val);
    char padded[4] = "000";

    for (int i = 2, j = vallen - 1; j >= 0; i--, j--) padded[i] = val[j];

    return string(padded);
  }

 private:
  map<const char *, const char *, mless> _m;
};
