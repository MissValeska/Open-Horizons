#include <irrlicht.h>
#include <cstdlib>
#include "inisetup.hpp"
#include "bimap.hpp" // http://collabedit.com/sn782
//#include "ExperimentalGame/keybinds.hpp"
#include "EventReceiver.hpp"
#include "DriverChoice.hpp"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

int main(int argc, char ** argv) // The options here define an argument count apparently, I don't fully understand it.
//http://collabedit.com/sab53 A friend explained here if it is still up next you check.
{

  optionsselect();

    EventReceiver receiver;

    //Create an Irrlicht Device.
    IrrlichtDevice * device = irr::createDevice(displaysoftware,dimension2d<u32>(screenwidth,screenheight), colourbits,
                fullscreendefine, shadowsdefine, vsyncdefine, &receiver);
    if (!device ) return 1;

    //Get the Video Driver from the device.
    IVideoDriver * driver = device->getVideoDriver();
    if (!driver) return 1;

    //Get the Scene Manager from the device.
    ISceneManager * smgr = device->getSceneManager();
    if (!smgr) return 1;

    //Add a Cube to the Scene.
    ISceneNode * n = smgr->addCubeSceneNode();

        //An animated cube.

    if (n)
    {
    //Add texture to the cube.
    n->setMaterialTexture(0,driver->getTexture("/home/missvaleska/IMG_1457.JPG"));

    //Needed to make the object's texture visible without a light source.
    n->setMaterialFlag(EMF_LIGHTING, false);

    n->setPosition(core::vector3df(0,0,100));
        //Set cube 100 units further in forward direction (Z axis), And animate it.
        /*scene::ISceneNodeAnimator* anim =
            smgr->createFlyCircleAnimator(core::vector3df(0,0,100), 20.0f);
        if (anim)
        {
            n->addAnimator(anim);
            anim->drop();
        }*/
    }


        //scene::IAnimatedMeshSceneNode* nodecharacter = smgr->addAnimatedMeshSceneNode
        //(smgr->getMesh("Models/ninja.b3d"));

    /*if(mesh2)
{
    nodecharacter = smgr->addOctreeSceneNode(mesh2->getMesh(0), 0, 0, 0);
    //nodecharacter = smgr->addMeshSceneNode(mesh2->getMesh(0));
    nodecharacter->setMaterialFlag(EMF_LIGHTING,false);
}*/

    //IAnimatedMesh* irr::scene::ISceneManager::addHillPlaneMesh(nodehill, 10.0f, 10.0f, "/home/missvaleska/Documents/Blender/textures/greenhillsmalljg0.jpg", 5.0f, 2.0f, 2.0f);


    //Currently non-functional test of the animation/rendering capabilities of irrlicht
    //from here http://irrlicht.sourceforge.net/docu/example001.html
    /*IAnimatedMesh* mesh = smgr->getMesh("/home/missvaleska/Documents/Blender/sun.obj");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    IAnimatedMeshSceneNode* nodestuff = smgr->addAnimatedMeshSceneNode( mesh );

    nodestuff->setPosition(vector3df(0,10,100));

    nodestuff->setMaterialFlag(video::EMF_LIGHTING, false);

    irr::scene::ISceneManager::addLightSceneNode(

		nodestuff,

		core::vector3df(0,0,0),

		video::SColorf(1.0f, 0.5f, 1.0f),

		800.0f);*/

             SKeyMap keyMap[8];
         keyMap[0].Action = EKA_MOVE_FORWARD;
         keyMap[0].KeyCode = KEY_UP;
         keyMap[1].Action = EKA_MOVE_FORWARD;
         keyMap[1].KeyCode = KEY_KEY_W;

         keyMap[2].Action = EKA_MOVE_BACKWARD;
         keyMap[2].KeyCode = KEY_DOWN;
         keyMap[3].Action = EKA_MOVE_BACKWARD;
         keyMap[3].KeyCode = KEY_KEY_S;

         keyMap[4].Action = EKA_STRAFE_LEFT;
         keyMap[4].KeyCode = KEY_LEFT;
         keyMap[5].Action = EKA_STRAFE_LEFT;
         keyMap[5].KeyCode = KEY_KEY_A;

         keyMap[6].Action = EKA_STRAFE_RIGHT;
         keyMap[6].KeyCode = KEY_RIGHT;
         keyMap[7].Action = EKA_STRAFE_RIGHT;
         keyMap[7].KeyCode = KEY_KEY_D;

    //Add FPS Camera to allow movement using Keyboard and Mouse.
    smgr->addCameraSceneNodeFPS(0, 100, 0.07, -1, keyMap, 8);

    //Changes cursor visibility.
    device->getCursorControl()->setVisible(false);

    // create event handler
   // PressedKeysMonitor receiver;

	int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();

    // This is the movement speed in units per second.
	const f32 MOVEMENT_SPEED = 5.f;

    //Run simulation
    while(device->run())
    {

        if(receiver.IsKeyDown(irr::KEY_ESCAPE))
           break;

        //Begin Scene with a gray backdrop #rgb(125,125,125)
        driver->beginScene(true,true,SColor(0,125,125,125));

        //Render the scene at this instant.
        smgr->drawAll();

        //End the scene
        driver->endScene();

        //Logic to update the scene will go here.

		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

        //Character Model Movement here.
        core::vector3df nodePosition = n->getPosition();

        if(receiver.IsKeyDown(irr::KEY_KEY_W))
            nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_S))
            nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

        if(receiver.IsKeyDown(irr::KEY_KEY_A))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

        n->setPosition(nodePosition);


        //Detects and displays FPS dynamically.
        int fps = driver->getFPS();
    if (lastFPS != fps)
        {
    //This defines a string of text to be the window caption, The Irrlicht engine apparently uses
    //something called "wide character strings" when displaying text by the way.
    core::stringw str = L"Yet to be Named Game - Irrlicht Engine [";

        str += driver->getName();
        str += "] FPS:";
        str += fps;
        device->setWindowCaption(str.c_str());
        lastFPS = fps;
    if (!device ) return 1;
        }
    }
    device->drop();
    return 0;
}
