#include "db.hpp"
#include "parse.hpp"
#include "win.hpp"

int main() {
  /*
  initscr();
  echo();
  move(1,1);
  refresh();
  */
  dbase db("bible");
  db.connect();
  /*
  wininput in(5, 100, 0, 0);
  winsql out(25, 100, 21, 0);
  out.set_buddy_win(in.getwinprop());
  */
  parsecmd parse;
  //char cmd[] = "gen 1 1";

  //char cmd[30] = {'\0'};
  //in.getcmd(cmd, 30);
  char cmd[] = "gen 1:30-31";
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
  /*
  if (res)
    out.text_out(res);
  else
    addstr(select.c_str());

  getch();
  db.close();
  endwin();
  */
    MYSQL_ROW row;
        int num_fields = mysql_num_fields(res);
  if(res)
      while ((row = mysql_fetch_row(res)))
      for (int i = 0; i < num_fields; i++) 
        puts(row[i]);
  else
    puts("not count\n");

}
