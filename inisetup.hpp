// This library was written by Michele Bini in 2014 and placed in the public domain

#ifndef INISETUP_HPP_INCLUDED
#define INISETUP_HPP_INCLUDED

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

// Please note that concurrent instances of IniSetup are not supported,
//because there is no locking mechanism for the ini file.

// Usage is very simple:

// IniSetup ini("config.ini");

    // This creates an instance for the file config.ini; settings are loaded and saved automatically

// int width = ini.get_number("width");

    // This gets option width= from the config file

// width = width + 400;

    // you can change it

// ini.set_number("width", width);

    // and save it back

// Three types are currently supported (bool, string and number),
//all with get_* and set_* methods, like set_bool() and get_bool()

namespace inisetup {
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::map;
  struct empty_class {};
  // This holds the mapping (option name -> setting)
  map<string, string> _m;
  map<string, string> _settings_on_file;
  map<string, empty_class> _possibly_changed_settings;

  // This class manages a simple .ini file
  // Sections like [foo] are ignored for now
  class IniSetup {
    string _filename;
  public:
    IniSetup() {};
    // Read a .ini file from FILENAME
    IniSetup(const char*filename) :_filename(filename) { read_ini_file(); }
    ~IniSetup() { write_ini_file(); }
  private:
    bool read_ini_file() {
      ifstream file(_filename);
      if (!file) return false;
      string line;
      while (std::getline(file, line)) {
    char ch;
    int c = 0;
    int s = line.length();

    int n_b = 0;
    int n_e = 0;
    int o_b = 0;

    if (c >= s) goto nextline;


    // Skip whitespace
    while ((ch = line[c]) == ' ') {
      c++;
      if (c >= s) goto nextline;
    };

    n_b = c; // Beginning of option name
    if (ch == '[') break; // Skip sections

    // Parse option name
    while (((ch >= 'A') && (ch <= 'Z')) ||
           ((ch >= 'a') && (ch <= 'z')) ||
           (ch == '_')) {
      c++;
      if (c >= s) goto nextline;
      ch = line[c];
    }
    n_e = c; // End of option name

    // Skip whitespace
    while (ch == ' ') {
      c++;
      if (c >= s) goto nextline;
      ch = line[c];
    };

        if (ch != '=') goto nextline;
    c++;

    o_b = c; // Beginning of option value

    _settings_on_file[string(line.begin() + n_b, line.begin() + n_e)] = string(line.begin() + o_b, line.end());
      nextline:
    ;
      }
      _m = _settings_on_file;
      return true;
    };

    bool write_ini_file() {
      ofstream file(_filename);
      if (!file.is_open())
            { throw std::runtime_error("Could not write/create configurations file."); }
      for (auto x: _m) {
        file << x.first;
        file << "=";
        file << x.second;
        file << "\n";
      };
      return true;
    }

  public:
    std::string get(const std::string &n) {
      return _m[n];
    };
    IniSetup &set(const std::string &n, const std::string &v) {
      _m[n] = v;
      return *this;
    };
    std::string get_string(const std::string &n) {
      return _m[n];
    };
    IniSetup &set_string(const std::string &n, const std::string &v) {
      _m[n] = v;
      return *this;
    };
    int get_number(const std::string &n) {
      int r = -1;
      std::istringstream(get(n)) >> r;
      return r;
    };
    IniSetup &set_number(const std::string &n, int v) {
      std::stringstream ss;
      ss << v;
      return set(n, ss.str());
    };
    bool get_bool(const std::string &n) {
      return get_number(n) == 1;
    };
    IniSetup &set_bool(const std::string &n, bool v) {
      return set_number(n, v ? 1 : 0);
    };
  };
};

#endif // INISETUP_HPP_INCLUDED
