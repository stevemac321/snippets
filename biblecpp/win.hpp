#pragma once
#include "precompile.hpp"

class winsql {
 public:
  winsql(int lines, int cols, int y, int x)
    :_lines(lines), _cols(cols), _y(y), _x(x){
    _pwin = newwin(lines, cols, y, x);
    wborder(_pwin, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(_pwin);
    refresh();
  }

  void text_out(MYSQL_RES *results) {
    assert(results);
    int num_fields = mysql_num_fields(results);
    wmove(_pwin, 1, 1);
    wclear(_pwin);
    wborder(_pwin, 0,0,0,0,0,0,0,0);
    wrefresh(_pwin);

    MYSQL_ROW row;
    // todo control output so that it does not overwrite border
    // also tokenize the line to put one word at a time, so that
    // words do not split between lines.
    // select t, b, c, v from bible.t_kjv where between...
    while ((row = mysql_fetch_row(results)))
      for (int i = 0; i < num_fields; i++) {
        waddstr(_pwin, row[i]);
        waddstr(_pwin, "  ");
      }

    puts("\n");
    wmove(_other, 1, 1);
    wrefresh(_pwin);
    refresh();
  }
  void set_buddy_win(WINDOW * pother) {
    _other = pother;
  }
  WINDOW * getwinprop() {
    return _pwin;
  }

private:
  WINDOW * _pwin=NULL;
  WINDOW * _other=NULL;
  int _lines = 0;
  int _cols = 0;
  int _y = 0;
  int _x = 0;
};

class wininput {
 public:
  wininput(int lines, int cols, int y, int x)
    : _lines(lines), _cols(cols), _y(y), _x(x) {
    _pwin = newwin(lines, cols, y, x);
    wborder(_pwin, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(_pwin, 1, 1);
    wrefresh(_pwin);
    refresh();
  }
  void set_buddy_win(WINDOW *pother) {
    _other = pother;
  }
  WINDOW * getwinprop() {
    return _pwin;
  }
  
  int getcmd(char *str, int n) {

    wclrtoeol(_pwin);
    wborder(_pwin, 0,0,0,0,0,0,0,0);
    wrefresh(_pwin);
    refresh();
    
    int ret = wgetnstr(_pwin, str, n);
    if(str && *str == 27)
      return 27;
    else
      return ret;
  }
private:
  WINDOW * _pwin=NULL;
  WINDOW * _other = NULL;
  int _lines = 0;
  int _cols = 0;
  int _y = 0;
  int _x = 0;
};
