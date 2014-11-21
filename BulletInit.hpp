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
static void GUIOverlay(IGUIEnvironment* env, 
        irr::core::vector2d<s32> Mouse_Coords, IGUIComboBox* cmbbox);
static void DeviceSetup();

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
static const std::basic_string<wchar_t> AllResolutionsPrint[72]{L"720x480",

L"1152x768",
L"1280x854",
L"1440x960",
L"2880x1920",

L"320x240",
L"640x480",
L"800x600",
L"1024x768",
L"1152x864",
L"1280x960",
L"1400x1050",
L"1600x1200",
L"2048x1536",
L"3200x2400",
L"4000x3000",
L"6400x4800",

L"800x480",
L"1280x768",

L"1280x1024",
L"2560x2048",
L"5120x4096",

L"852x480",
L"1280x720",
L"1365x768",
L"1600x900",
L"1920x1080",

L"320x200",
L"640x400",
L"1280x800",
L"1440x900",
L"1680x1050",
L"1920x1200",
L"2560x1600",
L"3840x2400",
L"7680x4800",

L"2048x1080"};

static char* AllResolutionsUse[72]{"720x480",

"1152x768",
"1280x854",
"1440x960",
"2880x1920",

"320x240",
"640x480",
"800x600",
"1024x768",
"1152x864",
"1280x960",
"1400x1050",
"1600x1200",
"2048x1536",
"3200x2400",
"4000x3000",
"6400x4800",

"800x480",
"1280x768",

"1280x1024",
"2560x2048",
"5120x4096",

"852x480",
"1280x720",
"1365x768",
"1600x900",
"1920x1080",

"320x200",
"640x400",
"1280x800",
"1440x900",
"1680x1050",
"1920x1200",
"2560x1600",
"3840x2400",
"7680x4800",

"2048x1080"};

#endif // BULLETINIT_HPP_INCLUDED
