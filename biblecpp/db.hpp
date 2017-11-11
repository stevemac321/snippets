#pragma once
#include "precompile.hpp"

class dbase {
 public:
  dbase(const char *name) { _name = name; }

  MYSQL *connect() {
    _conn = mysql_init(nullptr);
    assert(_conn);
    return mysql_real_connect(_conn, _machine, _user, _pw, _name, 0, nullptr,
                              0);
  }

  void close() { mysql_close(_conn); }
  MYSQL_RES *lookup(const char *select) {
    assert(select);
    if (mysql_query(_conn, select))
      return nullptr;
    else
      return mysql_store_result(_conn);
  }

 private:
  const char *_name;
  const char *_machine = "localhost";
  const char *_user = "root";
  const char *_pw = "sqlpw";
  MYSQL *_conn = nullptr;
};
