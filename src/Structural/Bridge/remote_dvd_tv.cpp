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

class entertainmentDevice
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

class tvDevice: public entertainmentDevice
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

class remoteButton
{
    private:
        entertainmentDevice *theDevice;
    public:
        remoteButton(entertainmentDevice *theDevice):theDevice(theDevice){}

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

class tvRemoteMute: public remoteButton
{
public:
    tvRemoteMute(entertainmentDevice *theDevice):remoteButton(theDevice)
    {

    }

    void buttonNinePressed()
    {
        std::cout<<"Tv was muted"<<std::endl;

    }
};

class tvRemotePause: public remoteButton
{
public:
    tvRemotePause(entertainmentDevice *theDevice):remoteButton(theDevice)
    {

    }

    void buttonNinePressed()
    {
        std::cout<<"Tv was paused"<<std::endl;

    }
};

int main()
{
    remoteButton *theTv1=new tvRemoteMute(new tvDevice);
    remoteButton *theTv2=new tvRemotePause(new tvDevice);
}
