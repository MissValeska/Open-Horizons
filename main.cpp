#include "OpenHorizonsIncludes.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char ** argv) //!<!<  The options here define an argument count apparently, I don't fully understand it.
	//!<!< http://!<collabedit.com/sab53 A friend explained here if it is still up next you check.
{
	options_select();
        
        DeviceSetup();
        
	//!<!< Exclamation means negation
	if(!display_software)
		fatal("Fatal Error: The Renderer was not correctly specified!", 1);
	else if(display_software == 0)
		fatal("Fatal Error: The Renderer was not correctly specified!", 1);

	//!<!< Create an Irrlicht Device.
	device = irr::createDevice(display_software,dimension2d<u32>(screen_width,screen_height), colour_bits,
			fullscreen_define, shadows_define, vsync_define);

	if (!device ) fatal("Fatal Error: The Irrlicht Device could not be created!", 2);

	//!<!< Get the Video Driver from the device.
	driver = device->getVideoDriver();
	if (!driver) fatal("Fatal Error: Could not get the Video Driver from the Irrlicht Device.", 3);
        
        IGUIEnvironment* env = device->getGUIEnvironment();
        if (!env) fatal("Fatal Error: Could not get the GUI Environment from the Irrlicht Device.", 4);
        
	//!<!< Get the Scene Manager from the device.
	smgr = device->getSceneManager();
	if (!smgr) fatal("Fatal Error: Could not get the Scene Manager from the Irrlicht Device.", 5);
        
        irrTimer = device->getTimer();
        if (!irrTimer) fatal("Fatal Error: Could not get the Irrlicht Timer from the Irrlicht Device.", 6);
        
        if(fullscreen_define == false)
            device->setResizable(true);
        
        //GUIOverlay(env);
    
    IGUISkin* skin = env->getSkin();
    IGUIFont* font = env->getFont("Fonts/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);
    
    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
    env->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits Program");
    
    IGUIComboBox* cmbbox = 
            env->addComboBox(rect<s32>(10,280,110,280 + 32), 0, -1);
    
    cmbbox->setSelected(-1);
    
    cmbbox->addItem(L"Rawr And Such! ^_^");
    cmbbox->addItem(L"Rawr And Such: Second Edition!");
    
	    env->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
    IGUIScrollBar* scrollbar = env->addScrollBar(true,
            rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMax(255);
    scrollbar->setPos(255);
    setSkinTransparency( scrollbar->getPos(), env->getSkin());

    // set scrollbar position to alpha value of an arbitrary element
    scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

    env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
    listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
    env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));
    
    // Store the appropriate data in a context structure.
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;
    
    // Then create the event receiver, giving it that context structure.
    EventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);
        
	//!<!<  create light

	scene::ISceneNode* node = 0;

	node = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
			video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
	scene::ISceneNodeAnimator* anim = 0;
	anim = smgr->createFlyCircleAnimator (core::vector3df(0,150,0),250.0f);
	node->addAnimator(anim);
	anim->drop();

	//!<!<  attach billboard to light

	node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	node->setMaterialTexture(0, driver->getTexture
			("Textures/particlewhite.bmp"));


	/*//!<Add CharacterNode
	  scene::IAnimatedMeshSceneNode* characternode =
	  smgr->addAnimatedMeshSceneNode(smgr->getMesh
	  ("Models/Female_Model_BaseMesh.obj"));

	  characternode->setPosition(core::vector3df(0,-7,0));
	  characternode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);*/

	//!<!< characternode->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"))

	//!<!< IAnimatedMesh* irr::scene::ISceneManager::addHillPlaneMesh(nodehill, 10.0f, 10.0f, "/home/missvaleska/Documents/Blender/textures/greenhillsmalljg0.jpg", 5.0f, 2.0f, 2.0f);

	/*
	//!<Adding a Room
	scene::IAnimatedMesh* roomMesh = smgr->getMesh("Structures/room.3ds");
	scene::ISceneNode* room = 0;
	scene::ISceneNode* earth = 0;

	if (roomMesh)
	{
	//!< The Room mesh doesn't have proper Texture Mapping on the
	//!< floor, so we can recreate them on runtime
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

	//!< Stones don't glitter..
	room->getMaterial(0).SpecularColor.set(0,0,0,0);
	room->getMaterial(0).Shininess = 0.f;

	room->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);
	//!< adjust height for parallax effect
	room->getMaterial(0).MaterialTypeParam = 1.f / 64.f;

	//!< drop mesh because we created it with a create.. call.
	tangentMesh->drop(); } */



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

	//!< Set a jump speed of 3 units per second, which gives a fairly realistic jump
	//!< when used with the gravity of (0, -9.80665, 0) in the collision response animator.
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0, 100, 0.3, 0, keyMap, 8, true, 3);
	camera->setPosition(core::vector3df(50,50,-60));
	camera->setTarget(core::vector3df(-70,30,-60));

	/*scene::ISceneNodeAnimatorCollisionResponse* camera_animator;

	camera_animator = smgr->createCollisionResponseAnimator(
			selector, camera, core::vector3df(10,40,10),
			core::vector3df(0,-9.80665,0), core::vector3df(0,30,0), 0);
	camera->addAnimator(camera_animator);

	InPlayer->setPosition(core::vector3df(50,50,-60));*/
	//InPlayer->setParent(camera);

	/*scene::ISceneNodeAnimatorCollisionResponse* in_player_animator;

	in_player_animator = smgr->createCollisionResponseAnimator(
			selector, InPlayer, core::vector3df(10,40,10),
			core::vector3df(0,-10,0), core::vector3df(0,30,0), 0);
	InPlayer->addAnimator(in_player_animator);

	ExPlayer->setPosition(core::vector3df(50,50,-60));

	scene::ISceneNodeAnimatorCollisionResponse* player_animator;

	player_animator = smgr->createCollisionResponseAnimator(
			selector, ExPlayer, core::vector3df(10,40,10),
			core::vector3df(0,-10,0), core::vector3df(0,30,0), 0);
	ExPlayer->addAnimator(player_animator);*/

	//!<Add FPS Camera to allow movement using Keyboard and Mouse.
	//!<smgr->addCameraSceneNodeFPS(0, 100, 0.07, -1, keyMap, 8);

	//!<Changes cursor visibility.
	device->getCursorControl()->setVisible(false);

	//!< create event handler
	//!< PressedKeysMonitor receiver;

	int lastFPS = -1;

	//!< In order to do framerate independent movement, we have to know
	//!< how long it was since the last frame
	u32 then = device->getTimer()->getTime();
        u32 then1;
        
	//!< This is the movement speed in units per second.
	const f32 MOVEMENT_SPEED = 70.f;

	//!<irr::core::vector3d<float>& PlayerPos;

	bool Camera_height_state = true;

    // Initialize bullet
	btDefaultCollisionConfiguration *CollisionConfiguration = new btDefaultCollisionConfiguration();
	btBroadphaseInterface *BroadPhase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
	btCollisionDispatcher *Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	btSequentialImpulseConstraintSolver *Solver = new btSequentialImpulseConstraintSolver();
	World = new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration);

    // Sets gravity to the exact force of gravity on earth on the Z axis
        World->setGravity(btVector3(0, -9.80665f, 0));

    //irrScene->addLightSceneNode(0, core::vector3df(2, 5, -2), video::SColorf(4, 4, 4, 1));
	CreateStartScene();
        
        //CreateWorld(btVector3(0.0f, -10.0f, 0.0f), 100.0f);
        
        /*scene::IAnimatedMeshSceneNode* InPlayer = 
                smgr->addAnimatedMeshSceneNode(smgr->getMesh
				("Models/Female_Model_BaseMesh.obj"));
        scene::IAnimatedMeshSceneNode* ExPlayer = 
                smgr->addAnimatedMeshSceneNode(smgr->getMesh
				("Models/Female_Model_BaseMesh.obj"));
                    CreatePlayer(btVector3(0.0f, 5.0f, 0.0f), 1.0f, InPlayer);
            CreatePlayer(btVector3(0.0f, 1.0f, 0.0f), 1.0f, ExPlayer);*/
        
	UDPSocket udpsocket(2000);
	ServAddr peeraddr(ipaddress.c_str(), portnumber);

	std::mutex ExPlayerMutex;
	ExPlayerMutex.lock();
    /*std::thread MultiplayerPos([&]{
			while(true)
			{
			core::vector3df pos;
			PacketUnpack(udpsocket.recv_string()) >> pos;
            core::vector3df rot;
			PacketUnpack(udpsocket.recv_string()) >> rot;
			{
			std::lock_guard<std::mutex> l(ExPlayerMutex);
			ExPlayer->setPosition(pos);
			ExPlayer->setRotation(rot);
			}
			}
			});

	MultiplayerPos.detach();*/

    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;
    
    int run_once = 0;
    
	//!<Run simulation
	while(device->run())
	{

		{
			// Send our player position
			PacketPack p;
			PacketPack r;
			p << camera->getAbsolutePosition();
			r << camera->getRotation();
			udpsocket.sendto(p.str().c_str(), p.str().length(), peeraddr);
            udpsocket.sendto(r.str().c_str(), r.str().length(), peeraddr);

			// Allow the ExPlayer position to be updated
			ExPlayerMutex.unlock();
			ExPlayerMutex.lock();
		}

            DeltaTime = irrTimer->getTime() - TimeStamp;
            TimeStamp = irrTimer->getTime();

            UpdatePhysics(DeltaTime);

		//!<irr::core::vector3d<float>& MyPlayerPos = MyPlayerPosX + MyPlayerPosY + MyPlayerPosZ;

		if(receiver.IsKeyDown(irr::KEY_ESCAPE))
			break;
		/*if(receiver.IsKeyDown(irr::KEY_SPACE)) {
			if (!camera_animator->isFalling()) {
				camera_animator->jump(3.8);
			}
		}
		if(!Camera_height_state && receiver.IsKeyDown(irr::KEY_LCONTROL)) {
			Camera_height_state = true;
			camera_animator->setEllipsoidRadius(core::vector3df(10,15,10));
		}
		if(Camera_height_state && !receiver.IsKeyDown(irr::KEY_LCONTROL)) {
			Camera_height_state = false;
			camera_animator->setEllipsoidRadius(core::vector3df(10,40,10));
		}*/

        if(receiver.IsKeyDown(irr::KEY_KEY_1))
            CreateBox(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), core::vector3df(GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f), 1.0f);

        if(receiver.IsKeyDown(irr::KEY_KEY_2))
            CreateSphere(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), GetRandInt(5) / 5.0f + 0.2f, 1.0f);

        if(receiver.IsKeyDown(irr::KEY_KEY_X)) {
            CreateStartScene();
            scene::IAnimatedMeshSceneNode* InPlayer = 
                smgr->addAnimatedMeshSceneNode(smgr->getMesh
				("Models/Female_Model_BaseMesh.obj"));
            CreatePlayer(btVector3(0.0f, 5.0f, 0.0f), 55.0f, InPlayer);
            /*CreatePlayer(btVector3(0.0f, 1.0f, 0.0f), 1.0f, ExPlayer);*/
        }
        
        const u32 now1 = device->getTimer()->getTime();
        const f32 frameDeltaTime1 = (f32)(now1 - then1) / 1000.f;
        
        if(receiver.IsKeyDown((irr::KEY_TAB))) {
            if(frameDeltaTime1 >= 0.05)
                run_once++;
            then1 = device->getTimer()->getTime();
            if(run_once == 1) {
               device->getCursorControl()->setVisible(true);
               camera->setInputReceiverEnabled(false);
            }
            if(run_once >= 2) {
                run_once = 0;
                device->getCursorControl()->setVisible(false);
                camera->setInputReceiverEnabled(true);
            }
        }
        
        if(receiver.IsKeyDown((irr::KEY_KEY_Z))) {
            irr::core::position2d<s32> Mouse_Coords = 
                    device->getCursorControl()->getPosition();
            std::cout << Mouse_Coords.X << " " << Mouse_Coords.Y << std::endl;
            GUIOverlay(env, Mouse_Coords, cmbbox);
        }
        
        if(cmbbox->getSelected() == 1) {
            
            
            
        }

		//!<std::thread beginrender([&]{
		//!<Begin Scene with a gray backdrop #rgb(125,125,125)
		driver->beginScene(true,true,SColor(0,125,125,125));
                
                //!<Render the scene at this instant.
		smgr->drawAll();
                
                //!<Draw the GUI
                if(run_once == 1 && run_once != 2) {
                    env->drawAll();
                    // Use to modify the resolution of the irrlicht device
                    //std::cout << cmbbox->getSelected() << std::endl;
                }

		//!<End the scene
		driver->endScene();
		//!<});

		//!<Logic to update the scene will go here.

		//!< Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; //!< Time in seconds
		then = now;

		//!<std::thread charactermovement([&](){
		//!<Character Model Movement here.
		/* core::vector3df nodePosition = characternode->getPosition();

		if(receiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;

		if(receiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

		characternode->setPosition(nodePosition);*/
		//!<});

		//!<std::thread fpsdetection([&](){
		//!<Detects and displays FPS dynamically.
                int fps = (int)driver->getFPS();
		if (lastFPS != fps)
		{
			//!<This defines a string of text to be the window caption, The Irrlicht engine apparently uses
			//!<something called "wide character strings" when displaying text by the way.
			core::stringw str = L"Open Horizons - Irrlicht Engine [";

			str += driver->getName();
			str += "] FPS:";
			str += fps;
			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
                
		//!<});

		//!<beginrender.join();
		//!<charactermovement.join();
		//!<fpsdetection.join();

	}

    ClearObjects();
	delete World;
	delete Solver;
	delete Dispatcher;
	delete BroadPhase;
	delete CollisionConfiguration;

	device->drop();

	return 0;
}

// Runs the physics simulation.
// - TDeltaTime tells the simulation how much time has passed since the last frame so the simulation can run independently of the frame rate.
void UpdatePhysics(u32 TDeltaTime) {

	World->stepSimulation(TDeltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(list<btRigidBody *>::Iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {

		UpdateRender(*Iterator);
	}
}

// Creates a base box
void CreateStartScene() {

	ClearObjects();
	CreateBox(btVector3(0.0f, 0.0f, 0.0f), vector3df(100.0f, 0.5f, 100.0f), 0.0f);
}

// Create Player rigid body
void CreatePlayer(const btVector3 &TPosition, btScalar TMass, scene::IAnimatedMeshSceneNode* Player) {
        // The player will control the body which moves the camera
    
        // Creates the Irrlicht player node
	Player->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

        // Set the initial position of the object
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);
        
        btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
        
        // Create the shape
	btScalar HalfExtents(3.0);
        btScalar HalfExtents1(10.0);
	btCollisionShape *Shape = new btCapsuleShape(HalfExtents, HalfExtents1);
        
        // Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	// Create the rigid body object
	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);

	// Store a pointer to the irrlicht node so we can update it later
	RigidBody->setUserPointer((void *)(Player));

	// Add it to the world
	World->addRigidBody(RigidBody);
	Objects.push_back(RigidBody);
    
}

// Create a World rigid body
void CreateWorld(const btVector3 &TPosition, btScalar TMass) {
    
    	enum
	{
		//!< I use this ISceneNode ID to indicate a scene node that is
		//!< not pickable by getSceneNodeAndCollisionPointFromRay()
		ID_IsNotPickable = 0,

		//!< I use this flag in ISceneNode IDs to indicate that the
		//!< scene node can be picked by ray selection.
		IDFlag_IsPickable = 1 << 0,

		//!< I use this flag in ISceneNode IDs to indicate that the
		//!< scene node can be highlighted.  In this example, the
		//!< homonids can be highlighted, but the level mesh can't.
		IDFlag_IsHighlightable = 1 << 1
	};

	device->getFileSystem()->addFileArchive("Structures/map-20kdm2.pk3");

	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
	scene::IMeshSceneNode* q3node = 0;

	//!< The Quake mesh is pickable, but doesn't get highlighted.
	//if (q3levelmesh)
		q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
        
        // Set the initial position of the object
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);
        
        btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);
        
        // Create the Collision Shape
        btCollisionShape *Shape = new btConvexHullShape();
        
	// Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);
        
	// Create the rigid body object
	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);

	// Store a pointer to the irrlicht node so we can update it later
	RigidBody->setUserPointer((void *)(q3node));

	// Add it to the world
	World->addRigidBody(RigidBody);
	Objects.push_back(RigidBody);
}

// Create a box rigid body
void CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass) {

    //!<!< Add a Cube to the Scene.
	ISceneNode * n = smgr->addCubeSceneNode(1.0f);
    n->setScale(TScale);
	n->setMaterialFlag(EMF_LIGHTING, 1);
	n->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
    n->setMaterialTexture(0,driver->getTexture("Textures/dirty-metal-surface.jpg"));

	// Set the initial position of the object
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);

	// Create the shape
	btVector3 HalfExtents(TScale.X * 0.5f, TScale.Y * 0.5f, TScale.Z * 0.5f);
	btCollisionShape *Shape = new btBoxShape(HalfExtents);

	// Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	// Create the rigid body object
	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);

	// Store a pointer to the irrlicht node so we can update it later
	RigidBody->setUserPointer((void *)(n));

	// Add it to the world
	World->addRigidBody(RigidBody);
	Objects.push_back(RigidBody);
}

// Create a sphere rigid body
void CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass) {

	ISceneNode *Node = smgr->addSphereSceneNode(TRadius, 32);
	Node->setMaterialFlag(EMF_LIGHTING, 1);
	Node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	Node->setMaterialTexture(0, driver->getTexture("Textures/ice0.jpg"));

	// Set the initial position of the object
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);

	// Create the shape
	btCollisionShape *Shape = new btSphereShape(TRadius);

	// Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	// Create the rigid body object
	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);

	// Store a pointer to the irrlicht node so we can update it later
	RigidBody->setUserPointer((void *)(Node));

	// Add it to the world
	World->addRigidBody(RigidBody);
	Objects.push_back(RigidBody);
}

// Passes bullet's orientation to irrlicht
void UpdateRender(btRigidBody *TObject) {
	ISceneNode *Node = static_cast<ISceneNode *>(TObject->getUserPointer());

	// Set position
	btVector3 Point = TObject->getCenterOfMassPosition();
	Node->setPosition(vector3df((f32)Point[0], (f32)Point[1], (f32)Point[2]));

	// Set rotation
	vector3df Euler;
	const btQuaternion& TQuat = TObject->getOrientation();
	quaternion q(TQuat.getX(), TQuat.getY(), TQuat.getZ(), TQuat.getW());
	q.toEuler(Euler);
	Euler *= RADTODEG;
	Node->setRotation(Euler);
}

// Removes all objects from the world
void ClearObjects() {

	for(list<btRigidBody *>::Iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {
		btRigidBody *Object = *Iterator;

		// Delete irrlicht node
		ISceneNode *Node = static_cast<ISceneNode *>(Object->getUserPointer());
		Node->remove();

		// Remove the object from the world
		World->removeRigidBody(Object);

		// Free memory
		delete Object->getMotionState();
		delete Object->getCollisionShape();
		delete Object;
	}

	Objects.clear();
}

void GUIOverlay(IGUIEnvironment* env, 
        irr::core::vector2d<s32> Mouse_Coords, IGUIComboBox* cmbbox) {

    std::cout << "Hello, GUIOverlay Here!\n";
    
    cmbbox->move(Mouse_Coords);
    
    /*std::cout << strerror(errno) << std::endl;
    
    IGUISkin* skin = env->getSkin();
    IGUIFont* font = env->getFont("Fonts/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    std::cout << strerror(errno) << std::endl;
    
    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

    env->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits Program");
    env->addButton(rect<s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
            L"New Window", L"Launches a new Window");
    env->addButton(rect<s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
            L"File Open", L"Opens a file");

	    env->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
    IGUIScrollBar* scrollbar = env->addScrollBar(true,
            rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMax(255);
    scrollbar->setPos(255);
    setSkinTransparency( scrollbar->getPos(), env->getSkin());

    // set scrollbar position to alpha value of an arbitrary element
    scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

    env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
    listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
    env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));
    
    // Store the appropriate data in a context structure.
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;
    
    // Then create the event receiver, giving it that context structure.
    EventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);*/
    
}

std::wstring StringToWString(const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());

    return wsTmp;
}

void DeviceSetup() {
        
    	if(!display_software)
		fatal("Fatal Error: The Renderer was not correctly specified!", 1);
	else if(display_software == 0)
		fatal("Fatal Error: The Renderer was not correctly specified!", 1);
    
    	//!<!< Create an Irrlicht Device.
	IrrlichtDevice* device1 = irr::createDevice(video::EDT_OPENGL,dimension2d<u32>(800,600), 32,
			false, true, true);

	if (!device1 ) fatal("Fatal Error: The Irrlicht Device could not be created!", 2);
        
	//!<!< Get the Video Driver from the device.
	IVideoDriver* driver1 = device1->getVideoDriver();
	if (!driver1) fatal("Fatal Error: Could not get the Video Driver from the Irrlicht Device.", 3);
        
        IGUIEnvironment* env1 = device1->getGUIEnvironment();
        if (!env1) fatal("Fatal Error: Could not get the GUI Environment from the Irrlicht Device.", 4);
        
	//!<!< Get the Scene Manager from the device.
	ISceneManager* smgr1 = device1->getSceneManager();
	if (!smgr1) fatal("Fatal Error: Could not get the Scene Manager from the Irrlicht Device.", 5);
        
        ITimer* irrTimer1 = device1->getTimer();
        if (!irrTimer1) fatal("Fatal Error: Could not get the Irrlicht Timer from the Irrlicht Device.", 6);
        
        if(fullscreen_define == false)
            device1->setResizable(true);
        
            device1->setWindowCaption
            (L"Open Horizons Setup");
            
    IGUISkin* skin = env1->getSkin();
    IGUIFont* font = env1->getFont("Fonts/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);
    
    skin->setFont(env1->getBuiltInFont(), EGDF_TOOLTIP);
    
    rect<s32> StartButton = rect<s32>(300,440,450,440 + 32);
    
    env1->addButton(StartButton, 0, GUI_ID_START_BUTTON,
            L"Start Open-Horizons", L"Closes this window and opens the game");
    
    env1->addStaticText(L"Screen Resolution", 
            rect<s32>(10,255,110,255 + 32));
    
    IGUIComboBox* cmbbox = 
            env1->addComboBox(rect<s32>(10,280,110,280 + 32), 0, -1);
    
    cmbbox->setSelected(-1);
    
    for(int i=0; i<72; i++){
    const std::basic_string<wchar_t> * cmbboxargument1 = 
        &AllResolutionsPrint[i];
    const wchar_t* cmbboxargument =
        (wchar_t*)cmbboxargument1->c_str();
    cmbbox->addItem(cmbboxargument);
    }
	    env1->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
    IGUIScrollBar* scrollbar = env1->addScrollBar(true,
            rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMax(255);
    scrollbar->setPos(255);
    setSkinTransparency( scrollbar->getPos(), env1->getSkin());

    // set scrollbar position to alpha value of an arbitrary element
    scrollbar->setPos(env1->getSkin()->getColor(EGDC_WINDOW).getAlpha());

    env1->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
    listbox = env1->addListBox(rect<s32>(50, 140, 250, 210));
    IGUIEditBox* IPAddrEditBox = env1->addEditBox
            (L"Editable Text", rect<s32>(350, 80, 550, 100), 110);
    
    // Store the appropriate data in a context structure.
    context.device = device1;
    context.counter = 0;
    context.listbox = listbox;
    
    // Then create the event receiver, giving it that context structure.
    EventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device1->setEventReceiver(&receiver);
            
        
    while(device1->run() && driver1)
    {
        driver1->beginScene(true, true, SColor(0,200,200,200));

        env1->drawAll();
    
        if(receiver.IsKeyDown((irr::KEY_KEY_Q))) {
        
            std::wstring RawrRawr;
            
        for(int d=0; d<10; d++) {
            RawrRawr.append(IPAddrEditBox->getText());
        }
            std::cout << RawrRawr.c_str() << "\n";
    }
        
        if(receiver.IsKeyDown((irr::KEY_ESCAPE)))
            fatal("Closing the GUI and not starting the Game", 0);
        
        if(cmbbox->getSelected() >= 0) {
            for(int i=0; i<72; i++) {
                //FIX ME! Problem with strrchr here! Segfault on the next line!
                screen_width = atoi(std::strrchr(AllResolutionsUse[i], 'x'));
                screen_height = atoi(std::strchr(AllResolutionsUse[i], 'x'));
                
                std::cout << screen_width << " " << screen_height << "\n";
            }
        }
        
        driver1->endScene();
    }

    device1->drop();
}