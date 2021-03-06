#include "ElevatorRoom.h"

using namespace cvr;
using namespace osg;
using namespace std;

namespace ElevatorRoom
{

#define DING_OFFSET 1
#define EXPLOSION_OFFSET 9
#define LASER_OFFSET 17

ElevatorRoom * ElevatorRoom::_myPtr = NULL;

CVRPLUGIN(ElevatorRoom)


ElevatorRoom::ElevatorRoom()
{
    _myPtr = this;
    _loaded = false;
    _audioHandler = NULL;
    _sppConnected = false;
    _geoRoot = new osg::MatrixTransform();
    _modelHandler = new ModelHandler();
}

ElevatorRoom::~ElevatorRoom()
{
}

ElevatorRoom * ElevatorRoom::instance()
{
    return _myPtr;
}

bool ElevatorRoom::init()
{
    /*** Setup menus ***/
    _elevatorMenu = new SubMenu("Elevator Room");

    PluginHelper::addRootMenuItem(_elevatorMenu);

    _dingCheckbox = new MenuCheckbox("Ding Test", false);
    _dingCheckbox->setCallback(this);
    _elevatorMenu->addItem(_dingCheckbox);

    _loadButton = new MenuButton("Load");
    _loadButton->setCallback(this);
    _elevatorMenu->addItem(_loadButton);

    _clearButton = new MenuButton("Clear");
    _clearButton->setCallback(this);
    _elevatorMenu->addItem(_clearButton);

/*
    _checkerSpeedRV = new MenuRangeValue("Checker flash speed: ", 10, 30, 15);
    _checkerSpeedRV->setCallback(this);
    _elevatorMenu->addItem(_checkerSpeedRV);

    _alienChanceRV = new MenuRangeValue("Chance of alien: ", 0, 100, 50);
    _alienChanceRV->setCallback(this);
    _elevatorMenu->addItem(_alienChanceRV);

    char str[50];
    sprintf(str, "Alien: %d  Astro: %d  Checker: %d", _alienChance, _allyChance, _checkerChance);
    _chancesText = new MenuText(str);
    _elevatorMenu->addItem(_chancesText);
*/ 
    

    /*** Load from config ***/
    

    // extra output messages
    _debug = (ConfigManager::getEntry("Plugin.ElevatorRoom.Debug") == "on");
    

    // Scale and position of model
    float xscale, yscale, zscale, xpos, ypos, zpos;
    xscale = ConfigManager::getFloat("x", "Plugin.ElevatorRoom.Scale", 100.0);
    yscale = ConfigManager::getFloat("y", "Plugin.ElevatorRoom.Scale", 100.0);
    zscale = ConfigManager::getFloat("z", "Plugin.ElevatorRoom.Scale", 100.0);

    xpos = ConfigManager::getFloat("x", "Plugin.ElevatorRoom.Position", 0.0);
    ypos = ConfigManager::getFloat("y", "Plugin.ElevatorRoom.Position", 0.0);
    zpos = ConfigManager::getFloat("z", "Plugin.ElevatorRoom.Position", -100.0);
    osg::Vec3 scale = osg::Vec3(xscale, yscale, zscale);

    osg::Matrix mat;
    mat.makeScale(scale);
    _geoRoot->setMatrix(mat);
    mat.makeTranslate(osg::Vec3(xpos, ypos, zpos));
    _geoRoot->postMult(mat);

    PluginHelper::getObjectsRoot()->addChild(_geoRoot);


    // Probability values
    _alienChance   = ConfigManager::getInt("alien",   "Plugin.ElevatorRoom.Probabilities", 50);
    _allyChance    = ConfigManager::getInt("ally",    "Plugin.ElevatorRoom.Probabilities", 40);
    _checkerChance = ConfigManager::getInt("checker", "Plugin.ElevatorRoom.Probabilities", 10);
    _errorChance   = ConfigManager::getInt("value",   "Plugin.ElevatorRoom.ErrorProbability", 5);

    // if any probability is wrong, revert to defaults
    if ((_alienChance + _allyChance + _checkerChance > 100) ||
        (_alienChance < 0) || (_allyChance < 0) || (_checkerChance < 0))
    {
        _alienChance   = 50;
        _allyChance    = 40;
        _checkerChance = 10;
    }

    _startTime = PluginHelper::getProgramDuration();
    _pauseTime = -1;
    _mode = NONE;
    _phase = PAUSE;
    _activeDoor = -1;
    _score = 0;
    _hit = false;

    // TODO: read these from config
//    _avatarFlashPerSec = 10;
//    _lightFlashPerSec = 7;

    _avatarFlashPerSec = ConfigManager::getInt("value", "Plugin.ElevatorRoom.AvatarFlashSpeed", 10);
    _doorFlashSpeed = ConfigManager::getInt("value", "Plugin.ElevatorRoom.DoorFlashSpeed", 20);
    _checkSpeed = ConfigManager::getInt("value", "Plugin.ElevatorRoom.CheckerFlashSpeed", 20);

    _staticMode = (ConfigManager::getEntry("Plugin.ElevatorRoom.StaticMode") != "off");
    _staticDoor = (ConfigManager::getInt("value", "Plugin.ElevatorRoom.StaticDoor", -1) != -1);
    _doorMovement = (ConfigManager::getEntry("Plugin.ElevatorRoom.DoorMovement") != "off");
    _rotateOnly = (ConfigManager::getEntry("Plugin.ElevatorRoom.RotateOnlyNavigation") != "off");


    if(ComController::instance()->isMaster())
    {
        int seed = time(NULL);
		ComController::instance()->sendSlaves(&seed, sizeof(seed));
        srand(seed);
    } 
    else 
    {
        int seed = 0;
		ComController::instance()->readMaster(&seed, sizeof(seed));
        srand(seed);
    }
    srand(0);


    // Sound
    osg::Vec3 handPos, headPos, headDir, handDir;
    handPos = cvr::PluginHelper::getHandMat().getTrans();
    headPos = cvr::PluginHelper::getHeadMat().getTrans();
    headDir = osg::Vec3(0, 0, -1); 
    handDir = handPos - headPos;

    if (ComController::instance()->isMaster())
    {
        _audioHandler = new AudioHandler();
        _audioHandler->connectServer();
        // user position
        _audioHandler->loadSound(0, headDir, headPos);
        // laser sound
        _audioHandler->loadSound(17, handDir, handPos);
    }
    

    // Sound directional representation
    osg::Cone *headCone, *handCone;
    osg::ShapeDrawable *headSD, *handSD;
    osg::Geode *headGeode, *handGeode;
    _headsoundPAT = new osg::PositionAttitudeTransform();
    _handsoundPAT = new osg::PositionAttitudeTransform();

    headGeode = new osg::Geode(); 
    handGeode = new osg::Geode(); 

    headSD = new osg::ShapeDrawable();
    handSD = new osg::ShapeDrawable();

    headCone = new osg::Cone(osg::Vec3(0,0,0), 20, 3000);
    handCone = new osg::Cone(osg::Vec3(0,0,0), 20, 3000);

    headSD = new osg::ShapeDrawable(headCone);
    headSD->setColor(osg::Vec4(0,0,1,1));
    headGeode->addDrawable(headSD);

    handSD = new osg::ShapeDrawable(handCone);
    handSD->setColor(osg::Vec4(1,0,0,1));
    handGeode->addDrawable(handSD);
    
    _headsoundPAT->addChild(headGeode);
    _handsoundPAT->addChild(handGeode);

    //_geoRoot->addChild(geode);
    //PluginHelper::getObjectsRoot()->addChild(_headsoundPAT);
    //PluginHelper::getObjectsRoot()->addChild(_handsoundPAT);


    // Spacenav
    _transMult = ConfigManager::getFloat("Plugin.SpaceNavigator.TransMult", 1.0);
    _rotMult = ConfigManager::getFloat("Plugin.SpaceNavigator.RotMult", 1.0);
    _transcale = -0.05 * _transMult;
    _rotscale = -0.005 * _rotMult;//-0.000009 * _rotMult;

    bool status = false;
    if(ComController::instance()->isMaster())
    {
        if(spnav_open() == -1) 
        {
            cerr << "SpaceNavigator: Failed to connect to the space navigator daemon" << endl;
        }
        else
        {
            status = true;
        }
    }


    // Serial port communication
    if (ComController::instance()->isMaster())
    {
        int port = 12345;
        init_SPP(port);
    }

    return true;
}

void ElevatorRoom::preFrame()
{
    // Separate sound test
    if (_dingCheckbox->getValue())
    {
        dingTest();
        return;
    }

    if (!_loaded)
        return;
    
    // Game logic independent updates (e.g. crosshair position)
    _modelHandler->update();
   

    if (_phase == PAUSE)
    {
        if (PluginHelper::getProgramDuration() - _startTime > _pauseTime)
        {
            int door = 0;
            Mode mode = CHECKER;
            bool switched = false;
            chooseGameParameters(door, mode, switched);

            _activeDoor = door;
            _mode = mode;
            
            _modelHandler->setActiveDoor(_activeDoor);
            _modelHandler->setMode(_mode);
            _modelHandler->setSwitched(switched);

            if (_audioHandler)
            {
                _audioHandler->playSound(_activeDoor + DING_OFFSET, "ding");
            }

            unsigned char c = 'a';
            sendChar(c);

            _phase = FLASHNEUTRAL;
            _startTime = PluginHelper::getProgramDuration();
            _flashStartTime = PluginHelper::getProgramDuration();
        }
    }

    else if (_phase == FLASHNEUTRAL)
    {
        if ( (PluginHelper::getProgramDuration() - _flashStartTime) > (1 / _doorFlashSpeed) )
        {
             _modelHandler->flashActiveLight();
             _flashStartTime = PluginHelper::getProgramDuration();
        }

        if (PluginHelper::getProgramDuration() - _startTime > _pauseTime && _modelHandler->doorInView())
        {
            _modelHandler->setLight(true);        

            if (_mode == ALLY)
            {
                unsigned char c = 'c';
                sendChar(c);
            }
            else if (_mode == ALIEN)
            {
                unsigned char c = 'd';
                sendChar(c);
            }

            // Choose solid door time and transmit code

            unsigned char c;
            int x = rand() % 3;

            if (x == 0)
            {
                c = 'e';
                _pauseTime = 1;
            }
            else if (x == 1)
            {
                c = 'f';
                _pauseTime = 1.5;
            }
            else if (x == 2)
            {
                c = 'g';
                _pauseTime = 2;
            }
            sendChar(c);

            _phase = DOORCOLOR;
            _startTime = PluginHelper::getProgramDuration();
        }
    }

    else if (_phase == DOORCOLOR)
    {
        if (PluginHelper::getProgramDuration() - _startTime > _pauseTime)
        {
            _phase = OPENINGDOOR;

            if (_mode == ALIEN)
                sendChar('h');
            else if (_mode == ALLY)
                sendChar('i');
        }
    }

    else if (_phase == OPENINGDOOR)
    {
        if (_modelHandler->getDoorDistance() > 0.8)
        {
            _phase = DOOROPEN;
            _startTime = PluginHelper::getProgramDuration();
            _pauseTime = rand() % 2; // time door stays open
        }
        _modelHandler->openDoor();
    }

    else if (_phase == DOOROPEN)
    {
        if (PluginHelper::getProgramDuration() - _startTime > _pauseTime)
        {
            _phase = CLOSINGDOOR;
        }

        // Flashing avatars - checkers always flash, alien and ally flash when hit
        if (_mode == CHECKER)
        {
            if (PluginHelper::getProgramDuration() - _flashStartTime > (1 / _checkSpeed))
            {
                _modelHandler->flashCheckers();
                _flashCount++;
                _flashStartTime = PluginHelper::getProgramDuration();
            }
        }

        else if (_mode == ALIEN)
        {
            if (_hit)
            {
                if (_flashCount > NUM_ALIEN_FLASH)
                {
                    _modelHandler->setAlien(false);
                }

                else if (PluginHelper::getProgramDuration() - _flashStartTime > 1 / _avatarFlashPerSec)
                {
                    _modelHandler->flashAlien();
                    _flashCount++; 
                    _flashStartTime = PluginHelper::getProgramDuration();
                }
            }
        }

        else if (_mode == ALLY)
        {
            if (_hit)
            {
                if (_flashCount > NUM_ALLY_FLASH)
                {
                    _modelHandler->setAlly(true);
                }

                else if (PluginHelper::getProgramDuration() - _flashStartTime > 1 / _avatarFlashPerSec)
                {
                    _modelHandler->flashAlly();
                    _flashCount++; 
                    _flashStartTime = PluginHelper::getProgramDuration();
                }
            }
        }
    }

    else if (_phase == CLOSINGDOOR)
    {
        if (_modelHandler->getDoorDistance() < 0.001)
        {
            _phase = PAUSE;
            _startTime = PluginHelper::getProgramDuration();
            _pauseTime = (rand() % 2) + .5; // time until next door dings
            _modelHandler->setLight(false);

            if (_noResponse)
            {
                unsigned char c = 'm';
                sendChar(c);
            }
            _noResponse = true;
            _hit = false;
        }
        _modelHandler->closeDoor();
    }
   

/*
    // Pick a door to open 
    if (_activeDoor < 0)
    {
        if ((PluginHelper::getProgramDuration() - _pauseStart) > _pauseLength)
        {
            if (_staticDoor)
            {
                _activeDoor = ConfigManager::getInt("Plugin.ElevatorRoom.StaticDoor", 0); // constant door
            }
            else
            {
                _activeDoor = rand() % NUM_DOORS; // random door
            }

            _modelHandler->setActiveDoor(_activeDoor);

            if (_audioHandler)
            {
                _audioHandler->playSound(_activeDoor + DING_OFFSET, "ding");
            }
            
            unsigned char buf[1];
            buf[0] = '1';
            write_SPP(sizeof(buf), buf);
            
            if (_staticMode)
            {
                string str;
                str = ConfigManager::getEntry("Plugin.ElevatorRoom.StaticMode");
                if (str == "Checker")
                {
                    _mode = CHECKER;
                    std::cout << _activeDoor << " - checker" << std::endl;
                }
                else if (str == "Ally")
                {
                    _mode = ALLY;
                    std::cout << _activeDoor << " - ally" << std::endl;
                }
                else if (str == "Alien")
                {
                    _mode = ALIEN;
                    std::cout << _activeDoor << " - alien" << std::endl;
                }

            }
            else
            {
                int num = rand() % 10; // random mode
                if (num <= 4)
                {
                    if (_debug)
                    {
                        std::cout << _activeDoor << " - alien" << std::endl;
                    }
                    _mode = ALIEN;

                    int r = rand() % 2;

                    if (_gameMode == FOUR && r == 0)
                    {

                    }
                    else
                    {

                    }
                }
                else if (num <= 7)
                {
                    if (_debug)
                    {
                        std::cout << _activeDoor << " - ally" << std::endl;
                    }
                    _mode = ALLY;
                }
                else
                {
                    if (_debug)
                    {
                        std::cout << _activeDoor << " - checker " << std::endl;
                    }
                    _mode = CHECKER;
                }
            }
                _modelHandler->setMode(_mode);
                _flashCount = 0;
        }

        if (_activeDoor > -1)
        {
            _flashStartTime = PluginHelper::getProgramDuration();
            _pauseStart = PluginHelper::getProgramDuration();
            _pauseLength = LIGHT_PAUSE_LENGTH;
        }
    }



    // Handle light flashes
    if (_activeDoor >= 0 && _activeDoor < NUM_DOORS &&
        (PluginHelper::getProgramDuration() - _pauseStart) < _pauseLength)
    {
        if ( (PluginHelper::getProgramDuration() - _flashStartTime) > (1 / _lightFlashPerSec) )
        {
             _modelHandler->flashActiveLight();
             _flashStartTime = PluginHelper::getProgramDuration();
        }
    }
   
    // Handle door movement and animation
    if (_activeDoor >= 0 && _activeDoor < NUM_DOORS &&
        (PluginHelper::getProgramDuration() - _pauseStart) > _pauseLength)
    {
        // Turn on light and start timer for door opening
        _modelHandler->setLight(true);        


        if (_doorClosed)
        {
            _doorPauseStart = PluginHelper::getProgramDuration();
            int x = rand() % 3;
            unsigned char buf[1];
            if (x == 0)
            {
                _doorPauseLength = .1;
                buf[0] = '5';
                std::cout << "Pausing 100 ms" << std::endl;
            }
            if (x == 1)
            {
                _doorPauseLength = .5;
                buf[0] = '6';
                std::cout << "Pausing 500 ms" << std::endl;
            }
            if (x == 2)
            {
                _doorPauseLength = .9;
                buf[0] = '7';
                std::cout << "Pausing 900 ms" << std::endl;
            }
            write_SPP(sizeof(buf), buf);
            _doorClosed = false;
        }


        // Flashing avatars
        if (_mode == CHECKER)
        {
            unsigned char buf[1];
            buf[0] = '5';
            //write_SPP(sizeof(buf), buf);

            if (PluginHelper::getProgramDuration() - _flashStartTime > (1 / _checkSpeed))
            {
                _modelHandler->flashCheckers();
                
                unsigned char buf[1];
                buf[0] = '2';
                //write_SPP(sizeof(buf), buf);

                _checkSpeed = 10;//((rand() % 2) + 1); // .5 -> 1
                _flashCount++;
                _flashStartTime = PluginHelper::getProgramDuration();
            }
        }

        else if (_mode == ALIEN)
        {
            unsigned char buf[1];
            buf[0] = '4';
            write_SPP(sizeof(buf), buf);

            if (_hit)
            {
                if (_flashCount > NUM_ALIEN_FLASH)
                {
                    _modelHandler->setAlien(false);
                }

                else if (PluginHelper::getProgramDuration() - _flashStartTime > 1 / _avatarFlashPerSec)
                {
                    _modelHandler->flashAlien();
                    _flashCount++; 
                    _flashStartTime = PluginHelper::getProgramDuration();
                }
            }
        }

        else if (_mode == ALLY)
        {
            unsigned char buf[1];
            buf[0] = '3';
            write_SPP(sizeof(buf), buf);

            if (_hit)
            {
                if (_flashCount > NUM_ALLY_FLASH)
                {
                    _modelHandler->setAlly(true);
                }

                else if (PluginHelper::getProgramDuration() - _flashStartTime > 1 / _avatarFlashPerSec)
                {
                    _modelHandler->flashAlly();
                    _flashCount++; 
                    _flashStartTime = PluginHelper::getProgramDuration();
                }
            }
        }

        if (_isOpening)
        {
            if (_modelHandler->doorInView() && 
                (PluginHelper::getProgramDuration() - _doorPauseStart) > _doorPauseLength)
            {
                _doorPauseLength = -1;
                _modelHandler->openDoor();
                
                if (_firstOpening)
                {
                    unsigned char buf[1];
                    if (_mode == ALIEN)
                    {
                        buf[0] = '8';
                    }
                    else if (_mode == ALLY)
                    {
                        buf[0] = '9';
                    }

                    write_SPP(sizeof(buf), buf);
                    _firstOpening = false;
                }
            }

            if (_modelHandler->getDoorDistance() > 0.8)
            {
                _isOpening = false;
                _firstOpening = true;
            }
        }
        else
        {
            if (_doorMovement)
            { 
                 _modelHandler->closeDoor();
            }

            if (_modelHandler->getDoorDistance() < 0.001)//DOOR_SPEED)
            {
                _modelHandler->setLight(false);
               
                _isOpening = true;
                _activeDoor = -1;
                _pauseStart = PluginHelper::getProgramDuration();
                _pauseLength = 1 + rand() % 5;
                _hit = false;
                _doorClosed = true;

                if (_debug)
                {
                    std::cout << "Pause for " << _pauseLength << " seconds" << std::endl;
                }
            }
        }
    }
*/


    // Update sound
    osg::Vec3 handPos, headPos, headDir, handDir;
    Matrixf w2o = PluginHelper::getWorldToObjectTransform(),
            head2w = PluginHelper::getHeadMat(),
            hand2w = PluginHelper::getHandMat();

    /*handPos = cvr::PluginHelper::getHandMat().getTrans();
    headPos = cvr::PluginHelper::getHeadMat().getTrans();
    headDir = osg::Vec3(0, 0, -1); 
    handDir = handPos - headPos;*/

    headPos = osg::Vec3(0, 1, 0) * head2w * w2o;
    headDir = headPos - (head2w.getTrans() * w2o);
    headDir.normalize();

    handPos = osg::Vec3(0, 1, 0) * hand2w * w2o;
    handDir = handPos - (hand2w.getTrans() * w2o);
    handDir.normalize();

    osg::Matrix mat;
    osg::Vec3 vec = _headsoundPAT->getAttitude().asVec3();//_headCone->getRotation().asVec3();
    mat.makeRotate(vec, headDir);
    _headsoundPAT->setAttitude(mat.getRotate());
    //_headsoundPAT->setPosition(headPos);

    vec = _handsoundPAT->getAttitude().asVec3();//_handCone->getRotation().asVec3();
    mat.makeRotate(vec, handDir);
    _handsoundPAT->setAttitude(mat.getRotate());
    //_handsoundPAT->setPosition(handPos);

    if (_audioHandler)
    {
        // user position
        _audioHandler->update(0, headDir, headPos);
        // laser sound
        _audioHandler->update(17, handDir, handPos);
    }


    // Spacenav and update rotation-only navigation
    if (!_rotateOnly)
        return;

    Matrixd finalmat;

    if(ComController::instance()->isMaster())
    {
        spnav_event sev;

        double x, y, z;
        x = y = z = 0.0;
        double rx, ry, rz;
        rx = ry = rz = 0.0;

        while(spnav_poll_event(&sev)) 
        {
            if(sev.type == SPNAV_EVENT_MOTION) 
            {
                x += sev.motion.x;
                y += sev.motion.z;
                z += sev.motion.y;
                rx += sev.motion.rx;
                ry += sev.motion.rz;
                rz += sev.motion.ry;
                // printf("got motion event: t(%d, %d, %d) ", sev.motion.x, sev.motion.y, sev.motion.z);
                // printf("r(%d, %d, %d)\n", sev.motion.rx, sev.motion.ry, sev.motion.rz);
            } 
            else 
            {	// SPNAV_EVENT_BUTTON 
                //printf("got button %s event b(%d)\n", sev.button.press ? "press" : "release", sev.button.bnum);
            }
        }

        x *= 0;//_transcale;
        y *= 0;//_transcale;
        z *= 0;//_transcale;
        rx *= 0;//_rotscale;
        ry *= 0;//_rotscale;
        rz *= _rotscale;

        Matrix view = PluginHelper::getHeadMat();
        Vec3 headpos = view.getTrans();
        Vec3 trans = Vec3(x, y, z);

        trans = (trans * view) - headpos;

        Matrix tmat;
        tmat.makeTranslate(trans);
        Vec3 xa = Vec3(1.0, 0.0, 0.0);
        Vec3 ya = Vec3(0.0, 1.0, 0.0);
        Vec3 za = Vec3(0.0, 0.0, 1.0);

        xa = osg::Vec3();//(xa * view) - campos;
        ya = osg::Vec3();//(ya * view) - campos;
        za = (za * view) - headpos;

        Matrix rot;
        rot.makeRotate(rx, xa, ry, ya, rz, za);

        Matrix ctrans, nctrans;
        ctrans.makeTranslate(headpos);
        nctrans.makeTranslate(-headpos);

        finalmat = PluginHelper::getObjectMatrix() * nctrans * rot * tmat * ctrans;

        ComController::instance()->sendSlaves((char *)finalmat.ptr(), sizeof(double[16]));
    }
    else
    {
        ComController::instance()->readMaster((char *)finalmat.ptr(), sizeof(double[16]));
    }

    PluginHelper::setObjectMatrix(finalmat);
}

void ElevatorRoom::menuCallback(MenuItem * item)
{
    if(item == _loadButton)
    {
        if (!_loaded)
        {
            _modelHandler->loadModels(_geoRoot);
            _loaded = true;
        }
    }

    else if (item == _clearButton)
    {
        if (_loaded)
        {
            clear();
            _loaded = false;
        }
    }

    else if(item == _checkerSpeedRV)
    {
        _checkSpeed = (int)_checkerSpeedRV->getValue();
    }

    else if(item == _alienChanceRV)
    {
        int newVal = _alienChanceRV->getValue();
        if (_alienChance + _allyChance + _checkerChance <= 100 &&
            newVal > -1  && 100 - newVal - _checkerChance > -1  && _checkerChance > -1)
        {
            _alienChance = newVal;
            _allyChance = 100 - _alienChance - _checkerChance;

            char str[50];
            sprintf(str, "Alien: %d  Astro: %d  Checker: %d", _alienChance, _allyChance, _checkerChance);
            _chancesText->setText(str);
        }
    }

    else if (item == _dingCheckbox)
    {
        if (_audioHandler)
        {
            osg::Vec3 pos, dir;
            pos = cvr::PluginHelper::getHeadMat().getTrans();
            dir = osg::Vec3(0, 0, -1); 

            _audioHandler->loadSound(0 + DING_OFFSET, dir, pos);
        }
    }
}

bool ElevatorRoom::processEvent(InteractionEvent * event)
{
    if (!_loaded)
        return false;

    TrackedButtonInteractionEvent * tie = event->asTrackedButtonEvent();

    if (tie)
    {
        if(tie->getHand() == 0 && tie->getButton() == 0)
        {
            if (tie->getInteraction() == BUTTON_DOWN)
            {
                unsigned char c = 'j';
                sendChar(c);

                osg::Vec3 pointerStart, pointerEnd;
                std::vector<IsectInfo> isecvec;
                
                osg::Matrix pointerMat = tie->getTransform();
                pointerStart = pointerMat.getTrans();
                pointerEnd.set(0.0f, 10000.0f, 0.0f);
                pointerEnd = pointerEnd * pointerMat;

                isecvec = getObjectIntersection(cvr::PluginHelper::getScene(),
                        pointerStart, pointerEnd);

                _eventRot = tie->getTransform().getRotate();
                _eventPos = tie->getTransform().getTrans();

                if (isecvec.size() == 0) // no intersection
                {
                    unsigned char c = 'l';
                    sendChar(c);
                    return false;
                }

                if (_phase == OPENINGDOOR || _phase == DOOROPEN || _phase == CLOSINGDOOR)
                {
                    // intersect the character and door is still open
                    if (isecvec[0].geode == _modelHandler->getActiveObject().get() && _modelHandler->getDoorDistance() > 0)
                    {
                        if (_audioHandler)
                        {
                            _audioHandler->playSound(LASER_OFFSET, "laser");
                        }
                        
                        // if haven't already hit the alien
                        if (_mode == ALIEN && !_hit)
                        {
                            if (_audioHandler)
                            {
                                _audioHandler->playSound(_activeDoor + EXPLOSION_OFFSET, "explosion");
                            }

                            std::cout << "Hit!" << std::endl; 
                            _score++;
                            _modelHandler->setScore(_score);

                            unsigned char c = 'k';
                            sendChar(c);

                            std::cout << "Score: " << _score << std::endl;
                            _hit = true;
                        }
                        else if (_mode == ALLY && !_hit)
                        {
                            if (_audioHandler)
                            {
                                _audioHandler->playSound(_activeDoor + EXPLOSION_OFFSET, "explosion");
                            }

                            unsigned char c = 'k';
                            sendChar(c);

                            std::cout << "Whoops!" << std::endl;
                            if (_score > 0)
                            {
                                _score--;
                            }
                            _modelHandler->setScore(_score);
                            std::cout << "Score: " << _score << std::endl;
                            _hit = true;
                        }
                        return true;
                    }
                }
            }
            else if (tie->getInteraction() == BUTTON_DRAG)
            {
                if (!_rotateOnly)
                    return false;

                osg::Matrix mat = tie->getTransform();

                osg::Vec3 pos, offset;
                SceneManager::instance()->getPointOnTiledWall(mat,pos);
                offset.y() = -(pos.z() - _eventPos.z()) * 50.0 / SceneManager::instance()->getTiledWallHeight();
                offset = offset * Navigation::instance()->getScale();
                offset = osg::Vec3(0,0,0);
                osg::Matrix m;

                osg::Matrix r;
                r.makeRotate(_eventRot);
                osg::Vec3 pointInit = osg::Vec3(0,1,0);
                pointInit = pointInit * r;
                pointInit.z() = 0.0;

                r.makeRotate(mat.getRotate());
                osg::Vec3 pointFinal = osg::Vec3(0,1,0);
                pointFinal = pointFinal * r;
                pointFinal.z() = 0.0;

                osg::Matrix turn;
                
                if(pointInit.length2() > 0 && pointFinal.length2() > 0)
                {
                    pointInit.normalize();
                    pointFinal.normalize();
                    float dot = pointInit * pointFinal;
                    float angle = acos(dot) / 15.0;

                    if(dot > 1.0 || dot < -1.0)
                    {
                        angle = 0.0;
                    }
                    else if((pointInit ^ pointFinal).z() < 0)
                    {
                        angle = -angle;
                    }
                    turn.makeRotate(-angle, osg::Vec3(0, 0, 1));
                }

                osg::Matrix objmat =
                        SceneManager::instance()->getObjectTransform()->getMatrix();
                
                osg::Vec3 origin = mat.getTrans();
                origin = _geoRoot->getMatrix().getTrans();

                m.makeTranslate(origin + offset);
                m = objmat * osg::Matrix::translate(-(origin+offset)) * turn * m;
                SceneManager::instance()->setObjectMatrix(m);

                return true;
            }
            else if (tie->getInteraction() == BUTTON_UP)
            {
                return true;
            }
            return true;
        }
    }

    KeyboardInteractionEvent * kie = event->asKeyboardEvent();
    if (kie)
    {
       /* if (kie->getInteraction() == KEY_UP && kie->getKey() == 'o')
        {
            return true;
        }*/
    }

    return true;
}

void ElevatorRoom::chooseGameParameters(int &door, Mode &mode, bool &switched)
{
    // Choose door
    if (_staticDoor)
    {
        door = ConfigManager::getInt("Plugin.ElevatorRoom.StaticDoor", 0); // constant door
    }
    else
    {
        door = rand() % NUM_DOORS; // random door
    }
    
    // Choose mode 
    if (_staticMode)
    {
        string str;
        str = ConfigManager::getEntry("Plugin.ElevatorRoom.StaticMode");
        if (str == "Checker")
        {
            mode = CHECKER;
            std::cout << _activeDoor << " - checker" << std::endl;
        }
        else if (str == "Ally")
        {
            mode = ALLY;
            std::cout << _activeDoor << " - ally" << std::endl;
        }
        else if (str == "Alien")
        {
            mode = ALIEN;
            std::cout << _activeDoor << " - alien" << std::endl;
        }
    }
    else
    {
        int num = rand() % 10; // random mode
        if (num <= 4)
        {
            if (_debug)
            {
                std::cout << _activeDoor << " - alien" << std::endl;
            }
            mode = ALIEN;
        }
        else if (num <= 7)
        {
            if (_debug)
            {
                std::cout << _activeDoor << " - ally" << std::endl;
            }
            mode = ALLY;
        }
        else
        {
            if (_debug)
            {
                std::cout << _activeDoor << " - checker " << std::endl;
            }
            mode = CHECKER;
        }
    }

}

void ElevatorRoom::clear()
{
    PluginHelper::getObjectsRoot()->removeChild(_geoRoot);
}

void ElevatorRoom::dingTest()
{
    if (!_audioHandler)
        return;

    if ((PluginHelper::getProgramDuration() - _startTime) > _pauseTime)
    {
        _audioHandler->playSound(0 + DING_OFFSET, "ding");

        sendChar('a');      

        _startTime = PluginHelper::getProgramDuration();
        _pauseTime = (rand() % 3) + 1;
        
        std::cout << "Ding! Pause for " << _pauseTime << " seconds." << std::endl;
    }
}

void ElevatorRoom::sendChar(unsigned char c)
{
    buf[0] = c;
    write_SPP(1, buf);
}



/*** Server Functions ***/

void ElevatorRoom::connectToServer()
{
    // get server address and port number
    string server_addr = ConfigManager::getEntry("Plugin.Maze2.EOGDataServerAddress");
    int port_number = ConfigManager::getInt("Plugin.Maze2.EOGDataServerPort", 8084);
    if( server_addr == "" ) server_addr = "127.0.0.1";
    
    cerr << "Maze2::ECGClient::Server address: " << server_addr << endl;
    cerr << "Maze2::ECGClient::Port number: " << port_number << endl;

    // build up socket communications
    int portno = port_number, protocol = SOCK_STREAM;
    struct sockaddr_in server;
    struct hostent *hp;

    _sockfd = socket(AF_INET, protocol, 0);
    if (_sockfd < 0)
    {
        cerr << "Maze2::ECGClient::connect(): Can't open socket." << endl;
        return;
    }

    server.sin_family = AF_INET;
    hp = gethostbyname(server_addr.c_str());
    if (hp == 0)
    {
        cerr << "Maze2::ECGClient::connect(): Unknown host." << endl;
        close(_sockfd);
        return;
    }
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons((unsigned short)portno);

    // connect to ECG data server
    if (connect(_sockfd, (struct sockaddr *) &server, sizeof (server)) < 0)
    {
	cerr << "Maze2::ECGClient::connect(): Failed connect to server" << endl;
        close(_sockfd);
        return;
    }

    cerr << "Maze2::ECGClient::Successfully connected to EOG Data Server." << endl;
    _connected = true;
}

int ElevatorRoom::init_SPP(int port)
{
    char com[100];

    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != 0)
    {
        std::cout << "FT_Open failed. Error " << ftStatus << std::endl;
        return -1;
    }
    FT_SetBaudRate(ftHandle, 57600);
    FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    FT_SetLatencyTimer(ftHandle, 2);

    /*
    if (ftdi_init(&_ftdic) < 0)
    {
        std::cout << "FTDI init failed." << std::endl;
        return -1;
    }
    
    int result = ftdi_usb_open(&_ftdic, 0x0403, 0x6001);
    if (result < 0)
    {
        std::cout << result << std::endl; 
        std::cout << "Unable to open FTDI device." << std::endl;
        return -1;
    }
    
    ftdi_set_baudrate(&_ftdic, 57600);
    ftdi_set_line_property(&_ftdic, BITS_8, STOP_BIT_1, (ftdi_parity_type)NONE);
    ftdi_setflowctrl(&_ftdic, SIO_DISABLE_FLOW_CTRL);
    ftdi_set_latency_timer(&_ftdic, 2);
   */ 
    std::cout << "Connected to FTDI device." << std::endl;
    _sppConnected = true;
    return 0;
}

void ElevatorRoom::close_SPP()
{
    if (!_sppConnected)
        return;

    FT_Close (ftHandle);
    //ftdi_deinit(&_ftdic);
}

void ElevatorRoom::write_SPP(int bytes, unsigned char* buf)
{
    if (!_sppConnected)
        return;
   
    std::cout << "Writing " << buf[0] << std::endl;

    DWORD BytesReceived;
    DWORD bytesToWrite = 1;
    int value;
    value = FT_Write(ftHandle, buf, bytesToWrite, &BytesReceived);
    int a = BytesReceived;

//    std::cout << "Wrote " << BytesReceived << " bytes." << std::endl;
//    std::cout << "Return value: " << value << std::endl;
    return;
    //ftdi_write_data(&_ftdic, buf, bytes);
}

};

