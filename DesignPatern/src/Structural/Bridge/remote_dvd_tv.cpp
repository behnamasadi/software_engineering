#include <iostream>
//http://www.newthinktank.com/2012/10/bridge-design-pattern-tutorial/
/*
when you want to change you abstract class and concrete class independet of each other.


                         _______________
                        |,----------.  |\
                        ||           |=| |
                        ||          || | |
                        ||       . _o| | |
                        |`-----------' |/
                         ~~~~~~~~~~~~~~~
                              Tv1
 _______________
|,----------.  |\
||           |=| |
||          || | |
||       . _o| | |
|`-----------' |/
 ~~~~~~~~~~~~~~~
    Abstract
                         _______________
                        |,----------.  |\
                        ||           |=| |
                        ||          || | |
                        ||       . _o| | |
                        |`-----------' |/
                         ~~~~~~~~~~~~~~~
                         Tv2 with DVD player

                        .-========-.
                        | o [__]   |
                        | [__][__] |
                        |    ====  |
                        | 1 2 3 4  |
                        |    7     |
                        |  5 9 6   |
                        |    8     |
                        '-========-'
                         tv1 remote
    .-========-.
    | o [__]   |
    | [__][__] |
    |    ====  |
    | 1 2 3 4  |
    |    7     |
    |  5 9 6   |
    |    8     |
    '-========-'
      Abstract
                        .-========-.
                        | o [__]   |
                        | [__][__] |
                        |    ====  |
                        | 1 2 3 4  |
                        |    7     |
                        |  5 9 6   |
                        |    8     |
                        '-========-'
                     Tv2 with DVD player

7: Volume is up
8: Volume is down
5,6: For tv1 next channel
5,6: For tv2 next chapter on the DVD
9: For tv1, mute
9: For tv2, will connect to the dvd player

*/

//abstract class for tv1, tv2 with DVD, etc

#include <iostream>
#include <memory>

// Base class for entertainment devices
class EntertainmentDevice
{
public:
    int deviceState; // Either current channel or current DVD chapter
    int maxSetting;  // Maximum channel or DVD chapter
    int volume;

    EntertainmentDevice(int state, int max) : deviceState(state), maxSetting(max), volume(10) {}

    virtual void buttonFivePressed() = 0;
    virtual void buttonSixPressed() = 0;

    void buttonSevenPressed() { volume++; }
    void buttonEightPressed() { volume--; }

    void deviceFeedback() const
    {
        std::cout << "Currently on: " << deviceState << std::endl;
    }

    virtual ~EntertainmentDevice() = default;
};

// TV Device implementation
class TVDevice : public EntertainmentDevice
{
public:
    TVDevice() : EntertainmentDevice(1, 100) {} // Channels range from 1 to 100

    void buttonFivePressed() override
    {
        if (deviceState > 1)
        {
            deviceState--;
            std::cout << "Previous channel: " << deviceState << std::endl;
        }
    }

    void buttonSixPressed() override
    {
        if (deviceState < maxSetting)
        {
            deviceState++;
            std::cout << "Next channel: " << deviceState << std::endl;
        }
    }
};

// DVD Device implementation
class DVDDevice : public EntertainmentDevice
{
public:
    DVDDevice() : EntertainmentDevice(1, 12) {} // Assume a DVD has 12 chapters

    void buttonFivePressed() override
    {
        if (deviceState > 1)
        {
            deviceState--;
            std::cout << "Previous DVD chapter: " << deviceState << std::endl;
        }
    }

    void buttonSixPressed() override
    {
        if (deviceState < maxSetting)
        {
            deviceState++;
            std::cout << "Next DVD chapter: " << deviceState << std::endl;
        }
    }
};

// Remote control base class
class RemoteButton
{
protected:
    std::unique_ptr<EntertainmentDevice> theDevice;

public:
    RemoteButton(std::unique_ptr<EntertainmentDevice> device) : theDevice(std::move(device)) {}

    virtual ~RemoteButton() = default;

    void buttonFivePressed() { theDevice->buttonFivePressed(); }
    void buttonSixPressed() { theDevice->buttonSixPressed(); }
    void buttonSevenPressed() { theDevice->buttonSevenPressed(); }
    void buttonEightPressed() { theDevice->buttonEightPressed(); }
    void deviceFeedback() const { theDevice->deviceFeedback(); }

    virtual void buttonNinePressed() = 0; // Abstract function for additional feature
};

// TV Remote with Mute functionality
class TVRemoteMute : public RemoteButton
{
public:
    TVRemoteMute(std::unique_ptr<EntertainmentDevice> device) : RemoteButton(std::move(device)) {}

    void buttonNinePressed() override
    {
        std::cout << "TV is now muted." << std::endl;
    }
};

// TV Remote with Pause functionality
class TVRemotePause : public RemoteButton
{
public:
    TVRemotePause(std::unique_ptr<EntertainmentDevice> device) : RemoteButton(std::move(device)) {}

    void buttonNinePressed() override
    {
        std::cout << "TV is now paused." << std::endl;
    }
};

int main()
{
    std::unique_ptr<RemoteButton> theTv1 = std::make_unique<TVRemoteMute>(std::make_unique<TVDevice>());
    std::unique_ptr<RemoteButton> theTv2 = std::make_unique<TVRemotePause>(std::make_unique<TVDevice>());

    std::cout << "Using TV Remote with Mute:\n";
    theTv1->buttonSixPressed();
    theTv1->deviceFeedback();
    theTv1->buttonNinePressed();

    std::cout << "\nUsing TV Remote with Pause:\n";
    theTv2->buttonFivePressed();
    theTv2->deviceFeedback();
    theTv2->buttonNinePressed();

    return 0;
}
