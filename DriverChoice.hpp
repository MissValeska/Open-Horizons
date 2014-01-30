#ifndef DRIVERCHOICE_HPP_INCLUDED
#define DRIVERCHOICE_HPP_INCLUDED

int chooseswitchstuff;

int colourbits = 32;
bool fullscreendefine = false;
bool shadowsdefine = true;
bool vsyncdefine = false;

int screenwidth;
int screenheight;

irr::video::E_DRIVER_TYPE displaysoftware; //This defines a string basically (It's probably not technically a string)
//Which I can name what ever I want, And is compatible with defining the renderer.
//This prevents me from needing to set up multiple nearly identical functions, Or, Worse,
//Some kind of complicated go to this function, run this, then return, and please don't fail.

std::string displaysoftwarestring;

void optionalconfig() {

    inisetup::IniSetup ini("config.ini");

    screenwidth = ini.get_number("screenwidth");
    screenheight = ini.get_number("screenheight");
    displaysoftwarestring = ini.get_string("displayrender");
// this gets back the value from the config file and saves to a variable

        IrrDriversBimap drivers;
    displaysoftware = drivers.from[displaysoftwarestring];
    displaysoftwarestring = drivers.to[displaysoftware];

}

void displaysoftwareselect() {
  int chooseswitchstuff;

    std::cout << "Choose Display Software." << std::endl;
    std::cout << "(1) OpenGL" << std::endl;
    std::cout << "(2) Direct3D9" << std::endl;
    std::cout << "(3) Direct3D8" << std::endl;
    std::cout << "(4) Software" << std::endl;

    do {//This is connected to the while statement a bit later.
        std::cout << ">";
        std::cin >> chooseswitchstuff;

        switch (chooseswitchstuff){
        case 1: displaysoftware = irr::video::E_DRIVER_TYPE::EDT_OPENGL; break;
        case 2: displaysoftware = irr::video::E_DRIVER_TYPE::EDT_DIRECT3D9; break;
        case 3: displaysoftware = irr::video::E_DRIVER_TYPE::EDT_DIRECT3D8; break;
        case 4: displaysoftware = irr::video::E_DRIVER_TYPE::EDT_SOFTWARE; break;
        default:
            chooseswitchstuff = 0;
            std::cout << "\nYour selection is invalid" << std::endl;
        }
    } while(chooseswitchstuff == 0);

    std::cout << "Please chose a screen size." << std::endl;
    std::cout << "x axis:";
    std::cin >> screenwidth;
    std::cout << "y axis:";
    std::cin >> screenheight;

    // Save configuration
    inisetup::IniSetup ini("config.ini");
    ini.set_number("screenwidth", screenwidth);
    ini.set_number("screenheight", screenheight);

        IrrDriversBimap drivers;
    displaysoftwarestring = drivers.to[displaysoftware];

    ini.set_string("displayrender", displaysoftwarestring);
}

void optionsselect(){
  int chooseswitchstuff;

    std::cout << "Do you want to load the configurations file?" << std::endl;
    std::cout << "(1) Yes" << std::endl;
    std::cout << "(2) No" << std::endl;
        do {//This is connected to the while statement a bit later.
        std::cout << ">";
        std::cin >> chooseswitchstuff;

        switch (chooseswitchstuff){
        case 1: optionalconfig(); break;
        case 2: displaysoftwareselect(); break;
        default:
            chooseswitchstuff = 0;
            std::cout << "\nYour selection is invalid" << std::endl;
                    }
    } while(chooseswitchstuff == 0);
}

#endif // DRIVERCHOICE_HPP_INCLUDED
