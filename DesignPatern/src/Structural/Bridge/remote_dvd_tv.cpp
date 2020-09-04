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

class EntertainmentDevice
{
public:
    int deviceState;//either current channel ro current DVD chapter
    int maxSetting;//max channel / DVD chanpter
    int volume;

    virtual void buttonFivePressed(){}
    virtual void buttonSixPressed(){}

    void buttonSevenPressed()
    {
        volume++;
    }

    void buttonEightPressed()
    {
        volume--;
    }

    void deviceFeedback()
    {
        std::cout<<"On: "<<deviceState <<std::endl;
    }

};

class TVDevice: public EntertainmentDevice
{
    void buttonFivePressed()
    {
        std::cout<<"previous channel"<<std::endl;
        deviceState--;
    }
    void buttonSixPressed()
    {
        std::cout<<"next channel"<<std::endl;
        deviceState++;
    }
};

class DVDDevice: public EntertainmentDevice
{
   public:
    void buttonFivePressed()
    {
        std::cout<<"previous chapter on DVD"<<std::endl;
        deviceState--;
    }
    void buttonSixPressed()
    {
        std::cout<<"next chapter on DVD"<<std::endl;
        deviceState++;
    }
};

class RemoteButton
{
    private:
        EntertainmentDevice *theDevice;
    public:
        RemoteButton(EntertainmentDevice *theDevice):theDevice(theDevice){}

        void buttonFivePressed()
        {
            theDevice->buttonFivePressed();
        }

        void buttonSixPressed()
        {
            theDevice->buttonSixPressed();
        }

        void deviceFeedback()
        {
            theDevice->deviceFeedback();
        }

};

class TVRemoteMute: public RemoteButton
{
public:
    TVRemoteMute(EntertainmentDevice *theDevice):RemoteButton(theDevice)
    {

    }

    void buttonNinePressed()
    {
        std::cout<<"Tv was muted"<<std::endl;

    }
};

class TVRemotePause: public RemoteButton
{
public:
    TVRemotePause(EntertainmentDevice *theDevice):RemoteButton(theDevice)
    {

    }

    void buttonNinePressed()
    {
        std::cout<<"Tv was paused"<<std::endl;

    }
};

int main()
{
    RemoteButton *theTv1=new TVRemoteMute(new TVDevice);
    RemoteButton *theTv2=new TVRemotePause(new TVDevice);
}
