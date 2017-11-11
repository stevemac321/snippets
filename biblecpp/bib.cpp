#include "db.hpp"
#include "parse.hpp"
#include "win.hpp"

void biblemode(parsecmd &parse, dbase &db, winsql &out, char * cmd);
void dictmode(dbase &db, winsql &out, char * word);
void sql_out(dbase & db, winsql &out, string select);
	     
int main() {
  initscr();
  echo();
  move(1, 1);
  refresh();
  dbase db("bible");
  db.connect();

  dbase dictdb("entries");
  dictdb.connect();
  
  wininput in(5, 100, 0, 0);
  winsql out(40, 180, 6, 0);
  out.set_buddy_win(in.getwinprop());

  parsecmd parse;
  wininput::mode runmode = wininput::bible;
  while (runmode != wininput::quit) {
    char cmd[30] = {'\0'};
    runmode = in.getcmd(cmd, 30);

    if (runmode == wininput::quit)
      break;
    else if(runmode == wininput::dict)
      dictmode(dictdb, out, cmd);
    else
      biblemode(parse, db, out, cmd);
  }

  db.close();
  dictdb.close();
  endwin();
}

void biblemode(parsecmd &parse, dbase &db, winsql &out, char * cmd)
{
    auto p = parse.parse_cmd(cmd);
    char *arg1 = const_cast<char *>(p.first.c_str());
    char *arg2 = const_cast<char *>(p.second.c_str());

    //  check return for empty string
    string select("select t from bible.t_kjv where id between ");
    select += arg1;
    select += " and ";
    select += arg2;

    sql_out(db, out, select);

}
void dictmode(dbase &db, winsql &out, char * word)
{
  string w(word);
  std::regex r("[A-Za-z] (.*)");
  std::smatch m;
  if (std::regex_search(w, m, r)) {
    string select = "select * from entries where word = \'";
    string arg = m[1];
    select += arg;
    select += "\'";
    sql_out(db, out, select);
  }
}
void sql_out(dbase & db, winsql &out, string select)
{

    auto res = db.lookup(select.c_str());

    if (res)
      out.text_out(res);
    else
      addstr(select.c_str());
}
