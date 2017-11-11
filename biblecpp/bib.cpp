#include "db.hpp"
#include "parse.hpp"
#include "win.hpp"

int main() {
  initscr();
  echo();
  move(1, 1);
  refresh();

  dbase db("bible");
  db.connect();

  wininput in(5, 100, 0, 0);
  winsql out(40, 180, 6, 0);
  out.set_buddy_win(in.getwinprop());

  parsecmd parse;
  int quit = 0;
  while (quit != 27) {
    char cmd[30] = {'\0'};
    quit = in.getcmd(cmd, 30);

    if (quit == 27) break;

    auto p = parse.parse_cmd(cmd);
    char *arg1 = const_cast<char *>(p.first.c_str());
    char *arg2 = const_cast<char *>(p.second.c_str());

    //  check return for empty string
    string select("select t from bible.t_kjv where id between ");
    select += arg1;
    select += " and ";
    select += arg2;

    // string select("select t from bible.t_kjv where id between 01001001 and
    // 01001002");
    auto res = db.lookup(select.c_str());

    if (res)
      out.text_out(res);
    else
      addstr(select.c_str());
  }

  db.close();
  endwin();
}
