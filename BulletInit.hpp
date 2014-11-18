#ifndef BULLETINIT_HPP_INCLUDED
#define BULLETINIT_HPP_INCLUDED

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Functions
static void CreateStartScene();
static void CreatePlayer(const btVector3 &TPosition, btScalar TMass, scene::IAnimatedMeshSceneNode* Player);
static void CreateWorld(const btVector3 &TPosition, btScalar TMass);
static void CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass);
static void CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass);
static void UpdatePhysics(u32 TDeltaTime);
static void UpdateRender(btRigidBody *TObject);
static void ClearObjects();
static int GetRandInt(int TMax) { return rand() % TMax; }
static void GUIOverlay(IGUIEnvironment* env);

// Globals
static btDiscreteDynamicsWorld *World;
static IrrlichtDevice * device;
static EventReceiver receiver;
static SAppContext context;
static IGUIListBox * listbox;
static IVideoDriver * driver;
static ISceneManager * smgr;
static IFileSystem *irrFile;
static ITimer *irrTimer;
static ILogger *irrLog;
static list<btRigidBody *> Objects;

#endif // BULLETINIT_HPP_INCLUDED
