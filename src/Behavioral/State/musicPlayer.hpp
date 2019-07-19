#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "musicPlayerState.hpp"


class MusicPlayerState;

class MusicPlayer
{

public:
    MusicPlayerState *status;
    void play();
    void pause();
    void stop();
    MusicPlayer();
    void setState(MusicPlayerState *state);
    ~MusicPlayer();
};

#endif //MUSICPLAYER_H
