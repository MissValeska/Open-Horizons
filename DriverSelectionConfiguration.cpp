#include <cstdlib>
#include <limits>
#include <ctype.h>
#include <functional>

#include <irrlicht/irrlicht.h>

#include "bimap.hpp"
#include "inisetup.hpp"

char choose_switch_stuff;

int colour_bits = 32;
bool fullscreen_define = false;
bool shadows_define = true;
bool vsync_define = false;

int screen_width;
int screen_height;

std::string ipaddress;

int portnumber;

irr::video::E_DRIVER_TYPE display_software; //!<This defines a string basically (It's probably not technically a string)
//!<Which I can name what ever I want, And is compatible with defining the renderer.
//!<This prevents me from needing to set up multiple nearly identical functions, Or, Worse,
//!<Some kind of complicated go to this function, run this, then return, and please don't fail.

std::string display_software_string;

void fatal(const char * error, int exit_code) {

    std::cerr << error << std::endl; exit(exit_code);

};

void Play_Now(){

    std::cout << "Do you want to play now?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    do {

    switch (choose_switch_stuff){
    case '1':; break;
    case '2': fatal("...Quitting...", 0); break;
    default:
    std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
    std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));

}

void Advanced_Options() {


    std::cout << "Enter colour bits Between 16 and 32 (32 is recommended)" << std::endl;
    std::cout << ">";
    std::cin >> colour_bits;

    std::cout << "Do you want shadows?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

      do {

    switch (choose_switch_stuff){
    case '1': shadows_define = true; break;
    case '2': shadows_define = false; break;
    default:
    std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
    std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));

 std::cout << "Do you want to use Vsync?" << std::endl;
 std::cout << "(1) Yes" << std::endl;
 std::cout << "(2) No" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

       do {

    switch (choose_switch_stuff){
    case '1': vsync_define = true; break;
    case '2': vsync_define = false; break;
    default:
    std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
    std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));


         //!< Save the advanced configuration.
    inisetup::IniSetup ini("config.ini");
    ini.set_number("colour_bits", colour_bits);
    ini.set_bool("shadows", shadows_define);
    ini.set_bool("vsync", vsync_define);

    Play_Now();

}

void MulitplayerInfo() {

    std::cout << "Please enter the IP address of the person you want to play with." << std::endl;
    std::cout << ">";

    std::cin >> ipaddress;

    std::cout << "Please enter the port you will both be using, Such as 2000." << std::endl;
    std::cout << ">";

    std::cin >> portnumber;

    inisetup::IniSetup ini("config.ini");
    ini.set_number("Last_Port_Number", portnumber);

}

void display_software_select() {

    std::cout << "Choose Display Software." << std::endl;
    std::cout << "(1) OpenGL" << std::endl;
    std::cout << "(2) Direct3D9" << std::endl;
    std::cout << "(3) Direct3D8" << std::endl;
    std::cout << "(4) Software" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    do {//!<This is connected to the while statement a bit later.

        switch (choose_switch_stuff){
        case '1': display_software = irr::video::E_DRIVER_TYPE::EDT_OPENGL; break;
        case '2': display_software = irr::video::E_DRIVER_TYPE::EDT_DIRECT3D9; break;
        case '3': display_software = irr::video::E_DRIVER_TYPE::EDT_DIRECT3D8; break;
        case '4': display_software = irr::video::E_DRIVER_TYPE::EDT_SOFTWARE; break;
        default:
        std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
        std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));


    std::cout << "Please chose a screen size, Such as 800 (Press Enter) 600." << std::endl;
    std::cout << "x axis:";
    std::cin >> screen_width;
    std::cout << "y axis:";
    std::cin >> screen_height;

    std::cout << "Do you want to be fullscreen?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

      do {

    switch (choose_switch_stuff){
    case '1': fullscreen_define = true; break;
    case '2': fullscreen_define = false; break;
    default:
    std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
    std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));

    std::cout << "Do you want to use multiplayer now?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

      do {

    switch (choose_switch_stuff){
    case '1': MulitplayerInfo(); break;
    case '2':; break;
    default:
    std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
    std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));

        //!< Save the standard configuration.
    inisetup::IniSetup ini("config.ini");
    ini.set_number("screen_width", screen_width);
    ini.set_number("screen_height", screen_height);
    ini.set_bool("fullscreen", fullscreen_define);

        IrrDriversBimap drivers;
    display_software_string = drivers.to[display_software];

    ini.set_string("displayrender", display_software_string);

    std::cout << "Do you want to configure the advanced options?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No" << std::endl;

    std::cout << ">";
    std::cin >> choose_switch_stuff;

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

  do {


    switch (choose_switch_stuff){
    case '1': Advanced_Options(); break;
    case '2':Play_Now(); break;
    default:
    std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
    std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));

}

void optional_config() {

    inisetup::IniSetup ini("config.ini");

    screen_width = ini.get_number("screen_width");
    screen_height = ini.get_number("screen_height");
    display_software_string = ini.get_string("displayrender");
    colour_bits = ini.get_number("colour_bits");
    shadows_define = ini.get_bool("shadows");
    vsync_define = ini.get_bool("vsync");
//!< this gets back the value from the config file and saves to a variable

        IrrDriversBimap drivers;
    display_software = drivers.from[display_software_string];
    display_software_string = drivers.to[display_software];

        if(display_software_string == ""){
            std::cout << "Error: config.ini does not exist." << std::endl;
            std::cout << "You cannot load a non-existent file. Please set one up by doing this." << std::endl << std::endl;
        display_software_select();
    }
}

void options_select(){

    std::cout << "Do you want to load the configurations file?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No (Recommended if you haven't run this game before, Or deleted the configurations file.)" << std::endl;
    std::cout << "(3) Exit" << std::endl;

        std::cout << ">";
        std::cin >> choose_switch_stuff;

        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

        do {

        switch (choose_switch_stuff){
        case '1': optional_config(); break;
        case '2': display_software_select(); break;
        case '3': fatal("...Quitting...", 0); break;
        default:
        std::cout << "\nYour selection is invalid, Please correct it.\n" << ">";
        std::cin >> choose_switch_stuff;
        }
    }while(isalpha(choose_switch_stuff));
 }

