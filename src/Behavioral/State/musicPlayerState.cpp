#include "musicPlayerState.hpp"
#include <iostream>


void  MusicPlayerState::play(MusicPlayer *player)
{
    std::cout<<"Illegal state transition from "<<statuseName<<" to play" <<std::endl;
}
 void  MusicPlayerState::pause(MusicPlayer *player)
{
    std::cout<<"Illegal state transition from "<<statuseName<<" to pause" <<std::endl;

}
void  MusicPlayerState::stop(MusicPlayer *player)
{
    std::cout<<"Illegal state transition from "<<statuseName<<" to pause" <<std::endl;
}
MusicPlayerState::MusicPlayerState(std::string statuseName):statuseName(statuseName){}

std::string MusicPlayerState::getName()
{
    return statuseName;
}
 MusicPlayerState::~MusicPlayerState(){}

