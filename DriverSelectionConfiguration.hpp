#ifndef DRIVERCHOICE_HPP_INCLUDED
#define DRIVERCHOICE_HPP_INCLUDED
extern irr::video::E_DRIVER_TYPE display_software;
extern int screen_width;
extern int screen_height;
extern int colour_bits;
extern bool fullscreen_define;
extern bool shadows_define;
extern bool vsync_define;
extern std::string ipaddress;
extern int portnumber;



void fatal(const char * error, int exit_code);
void Play_Now();
void Advanced_Options();
void MulitplayerInfo();
void display_software_select();
void optional_config();
void options_select();
void save_all();
#endif //!< DRIVERCHOICE_HPP_INCLUDED
