#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "musicPlayerState.hpp"

class PlayingState: public MusicPlayerState
{
public:
    virtual void pause(MusicPlayer *player) ;

    virtual void stop(MusicPlayer *player) ;
    PlayingState();

    ~PlayingState();
};

#endif //PLAYINGSTATE_H
