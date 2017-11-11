#pragma once
#include "precompile.hpp"

class win {
public:
  win(int lines, int cols, int y, int x)
    :_lines(lines), _cols(cols), _y(y), _x(x) {
    _pwin=nullptr;
  }

protected:
  WINDOW * _pwin=nullptr;
  int _lines = 0;
  int _cols = 0;
  int _y = 0;
  int _x = 0;
  
};

class winsql: public win {
 public:
  winsql(int lines, int cols, int y, int x)
    :win(lines, cols, y, x) {
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
  WINDOW * _other=NULL;
};

class wininput : public win {
 public:
  enum mode {quit, bible, dict};  
  wininput(int lines, int cols, int y, int x)
    : win(lines, cols, y, x) {
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
  
  mode getcmd(char *str, int n) {

    wclrtoeol(_pwin);
    wborder(_pwin, 0,0,0,0,0,0,0,0);
    wrefresh(_pwin);
    refresh();
    
    int ret = wgetnstr(_pwin, str, n);
    if(str && *str == 27)
      return quit;
    else
      return is_dict(str) ? dict : bible;
  }
  
private:
  bool is_dict(char *str) {
    int len = strlen(str);
    if(len < 3)
      return false;

    if(str[0] != 'd' && str[0] != 'D')
      return false;

    if(str[1] != 'i' && str[1] != 'I')
      return false;

    if(str[2] != 'c' && str[2] != 'C')
      return false;

    return true;
  }
  WINDOW * _other = NULL;
};
