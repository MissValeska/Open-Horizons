#include <irrlicht.h>
#include <cstdlib>
#include "inisetup.hpp"
#include "bimap.hpp" // http://collabedit.com/sn782
//#include "keybinds.hpp"
#include "EventReceiver.hpp"
#include "DriverSelectionConfiguration.hpp"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

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
    n->setMaterialTexture(0,driver->getTexture("Textures/IMG_1457.JPG"));

    //Needed to make the object's texture visible without a light source.
    //n->setMaterialFlag(EMF_LIGHTING, false);

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

    // create light

    scene::ISceneNode* node = 0;

    node = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
        video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
    scene::ISceneNodeAnimator* anim = 0;
    anim = smgr->createFlyCircleAnimator (core::vector3df(0,150,0),250.0f);
    node->addAnimator(anim);
    anim->drop();

    // attach billboard to light

    node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    node->setMaterialTexture(0, driver->getTexture
    ("Textures/particlewhite.bmp"));


        //Add CharacterNode
        scene::IAnimatedMeshSceneNode* characternode =
        smgr->addAnimatedMeshSceneNode(smgr->getMesh
        ("Models/Female_Model_BaseMesh.obj"));

        characternode->setPosition(core::vector3df(0,-7,0));
        characternode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

    //characternode->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"))

    //IAnimatedMesh* irr::scene::ISceneManager::addHillPlaneMesh(nodehill, 10.0f, 10.0f, "/home/missvaleska/Documents/Blender/textures/greenhillsmalljg0.jpg", 5.0f, 2.0f, 2.0f);


            //Adding a Room
            scene::IAnimatedMesh* roomMesh = smgr->getMesh("Structures/room.3ds");
        scene::ISceneNode* room = 0;
        scene::ISceneNode* earth = 0;

    if (roomMesh)
    {
        // The Room mesh doesn't have proper Texture Mapping on the
        // floor, so we can recreate them on runtime
        smgr->getMeshManipulator()->makePlanarTextureMapping(
                roomMesh->getMesh(0), 0.003f);

                video::ITexture* normalMap =
            driver->getTexture("Textures/rockwall_height.bmp");

        if (normalMap)
            driver->makeNormalMapTexture(normalMap, 9.0f);
        scene::IMesh* tangentMesh = smgr->getMeshManipulator()->
                createMeshWithTangents(roomMesh->getMesh(0));

        room = smgr->addMeshSceneNode(tangentMesh);
        room->setMaterialTexture(0,
                driver->getTexture("Textures/rockwall.jpg"));
        room->setMaterialTexture(1, normalMap);

        room->setPosition(core::vector3df(0,-60,0));

        // Stones don't glitter..
        room->getMaterial(0).SpecularColor.set(0,0,0,0);
        room->getMaterial(0).Shininess = 0.f;

        room->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);
        // adjust height for parallax effect
        room->getMaterial(0).MaterialTypeParam = 1.f / 64.f;

        // drop mesh because we created it with a create.. call.
        tangentMesh->drop();
    }


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
	const f32 MOVEMENT_SPEED = 70.f;

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
        core::vector3df nodePosition = characternode->getPosition();

        if(receiver.IsKeyDown(irr::KEY_KEY_W))
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_S))
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;

        if(receiver.IsKeyDown(irr::KEY_KEY_A))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

        characternode->setPosition(nodePosition);


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
