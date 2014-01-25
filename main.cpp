#include <irrlicht.h>
#include <cstdlib>
#include "ExperimentalGame/inisetup.hpp"
#include "ExperimentalGame/bimap.hpp" // http://collabedit.com/sn782
//#include "ExperimentalGame/keybinds.hpp"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

int chooseswitchstuff;

int colourbits = 32;
bool fullscreendefine = false;
bool shadowsdefine = true;
bool vsyncdefine = false;

std::string displaysoftwarestring;

// Specialized bimap type (E_DRIVER_TYPE <-> string)
struct IrrDriversBimap : Bimap<irr::video::E_DRIVER_TYPE, std::string> {
  IrrDriversBimap() {
    to[EDT_OPENGL]     = "OpenGL";
    to[EDT_DIRECT3D9]  = "Direct3D9";
    to[EDT_DIRECT3D8]  = "Direct3D8";
    to[EDT_SOFTWARE]   = "Software";
    update_from_map();
  };
};

int screenwidth;
int screenheight;
irr::video::E_DRIVER_TYPE displaysoftware; //This defines a string basically (It's probably not technically a string)
//Which I can name what ever I want, And is compatible with defining the renderer.
//This prevents me from needing to set up multiple nearly identical functions, Or, Worse,
//Some kind of complicated go to this function, run this, then return, and please don't fail.
void optionalconfig() {

    IrrDriversBimap drivers;
    displaysoftware = drivers.from[displaysoftwarestring];
    displaysoftwarestring = drivers.to[displaysoftware];

    inisetup::IniSetup ini("config.ini");

    screenwidth = ini.get_number("screenwidth");
    screenheight = ini.get_number("screenheight");
    displaysoftwarestring = ini.get_string("displayrender");
// this gets back the value from the config file and saves to a variable


}

void displaysoftwareselect() {
  int chooseswitchstuff;

    cout << "Choose Display Software." << endl;
    cout << "(1) OpenGL" << endl;
    cout << "(2) Direct3D9" << endl;
    cout << "(3) Direct3D8" << endl;
    cout << "(4) Software" << endl;

    do {//This is connected to the while statement a bit later.
        cout << ">";
        cin >> chooseswitchstuff;

        switch (chooseswitchstuff){
        case 1: displaysoftware = EDT_OPENGL; break;
        case 2: displaysoftware = EDT_DIRECT3D9; break;
        case 3: displaysoftware = EDT_DIRECT3D8; break;
        case 4: displaysoftware = EDT_SOFTWARE; break;
        default:
            chooseswitchstuff = 0;
            cout << "\nYour selection is invalid" << endl;
        }
    } while(chooseswitchstuff == 0);

    cout << "Please chose a screen size." << endl;
    cout << "x axis:";
    cin >> screenwidth;
    cout << "y axis:";
    cin >> screenheight;

    inisetup::IniSetup ini("config.ini");
    screenwidth = ini.set_number("screenwidth", screenwidth);
    screenheight = ini.set_number("screenheight", screenheight);
    displaysoftwarestring = ini.set_string("displayrender", displaysoftwarestring);
}

void optionsselect(){
  int chooseswitchstuff;

    cout << "Do you want to load the configurations file?" << endl;
    cout << "(1) Yes" << endl;
    cout << "(2) No" << endl;
        do {//This is connected to the while statement a bit later.
        cout << ">";
        cin >> chooseswitchstuff;

        switch (chooseswitchstuff){
        case 1: optionalconfig(); break;
        case 2: displaysoftwareselect(); break;
        default:
            chooseswitchstuff = 0;
            cout << "\nYour selection is invalid" << endl;
                    }
    } while(chooseswitchstuff == 0);
}

int main(int argc, char ** argv) // The options here define an argument count apparently, I don't fully understand it.
//http://collabedit.com/sab53 A friend explained here if it is still up next you check.
{

  optionsselect();

    //Create an Irrlicht Device.
    IrrlichtDevice * device = irr::createDevice(displaysoftware,dimension2d<u32>(screenwidth,screenheight), colourbits,
                fullscreendefine, shadowsdefine, vsyncdefine, 0);
    if (!device ) return 1;

     //This defines a string of text to be the window caption, The Irrlicht engine apparently uses
    //something called "wide character strings" when displaying text by the way.
    device->setWindowCaption(L"Yet to be Named Game - Irrlicht Engine");
    if (!device ) return 1;

    //Get the Scene Manager from the device.
    ISceneManager * smgr = device->getSceneManager();
    if (!smgr) return 1;

    //Get the Video Driver from the device.
    IVideoDriver * driver = device->getVideoDriver();
    if (!driver) return 1;

    //Add a Cube to the Scene.
    ISceneNode * node = smgr->addCubeSceneNode();

    //Needed to make the object's texture visible without a light source.
    node->setMaterialFlag(EMF_LIGHTING, false);

    //Add texture to the cube.
    node->setMaterialTexture(0,driver->getTexture("/home/missvaleska/IMG_1457.JPG"));

    //Set cube 100 units further in forward direction (Z axis).
    node->setPosition(vector3df(0,0,100));

    //Currently non-functional test of the animation/rendering capabilities of irrlicht
    //from here http://irrlicht.sourceforge.net/docu/example001.html
    IAnimatedMesh* mesh = smgr->getMesh("/home/missvaleska/Documents/Blender/testcubeforirrlicht.x");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    IAnimatedMeshSceneNode* nodestuff = smgr->addAnimatedMeshSceneNode( mesh );

    nodestuff->setPosition(vector3df(0,10,100));

    //Add FPS Camera to allow movement using Keyboard and Mouse.
    smgr->addCameraSceneNodeFPS();

    //Run simulation
    while(device->run())
    {
        //Begin Scene with a gray backdrop #rgb(125,125,125)
        driver->beginScene(true,true,SColor(0,125,125,125));

        //Render the scene at this instant.
        smgr->drawAll();

        //End the scene
        driver->endScene();

        //Logic to update the scene will go here.
    }
    return 0;
}
