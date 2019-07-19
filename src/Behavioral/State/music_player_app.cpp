//https://www.robertlarsononline.com/2017/05/11/state-pattern-using-cplusplus/
#include <iostream>
#include <string>

#include "musicPlayer.hpp"
#include "musicPlayerState.hpp"



#include "playingState.hpp"
#include "stoppedState.hpp"
#include "pausedState.hpp"



int main()
{
    MusicPlayer myplayer;
    myplayer.play();
    myplayer.play();
    myplayer.pause();
    myplayer.play();
    myplayer.stop();
    myplayer.pause();
    //std::cout<< <<std::endl;

}
