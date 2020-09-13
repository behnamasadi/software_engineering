//https://www.robertlarsononline.com/2017/05/11/state-pattern-using-cplusplus/
#include <iostream>
#include <string>

///////////////////////////////////////Forward declertion//////////////////////////////
class MusicPlayerState;
class MusicPlayer;
class PausedState;
class PlayingState;
class StoppedState;

/////////////////////////////////////Headers//////////////////////////////////
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

//MusicPlayerState
class MusicPlayerState
{
    std::string statuseName;
    public:
    virtual void play(MusicPlayer *player);

    virtual void pause(MusicPlayer *player);

    virtual void stop(MusicPlayer *player);

    MusicPlayerState(std::string statuseName);

    std::string getName();

    virtual ~MusicPlayerState();


};

//StoppedState
class StoppedState: public MusicPlayerState
{
public:
    void play(MusicPlayer *player) override;
    StoppedState();

};

//PlayingState
class PlayingState: public MusicPlayerState
{
public:
    void pause(MusicPlayer *player) override;

    void stop(MusicPlayer *player) override;
    PlayingState();

    ~PlayingState();
};

//PausedState
class PausedState: public MusicPlayerState
{
public:
    void play(MusicPlayer *player) override;
    PausedState();

};


/////////////////////////////////////Definitions//////////////////////////////////

//MusicPlayer
void MusicPlayer::play()
{
    status->play(this);
}
void MusicPlayer::pause()
{
    status->pause(this);
}
void MusicPlayer::stop()
{
    status->stop(this);
}

//MusicPlayerState
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
MusicPlayerState::MusicPlayerState(std::string statuseName):statuseName(statuseName)
{}
std::string MusicPlayerState::getName()
{
    return statuseName;
}
MusicPlayerState::~MusicPlayerState()
{}

//PlayingState
MusicPlayer::MusicPlayer()
{
    this->status=new StoppedState();
}
void MusicPlayer::setState(MusicPlayerState *state)
{
    std::cout << "changing from " << this->status->getName() << " to "<<state->getName()<<std::endl;
    this->status=state;
}
MusicPlayer::~MusicPlayer()
{
    delete status;
}


//StoppedState
void StoppedState::play(MusicPlayer *player)
{
    player->setState(new PlayingState());
}
StoppedState::StoppedState():MusicPlayerState("STOP")
{}

//PlayingState
void  PlayingState::pause(MusicPlayer *player)
{
    player->setState(new PausedState());
}
void PlayingState::stop(MusicPlayer *player)
{
    player->setState(new StoppedState());
}
PlayingState::PlayingState():MusicPlayerState("PLAYING")
{
    //this->status=new StoppedState();

}
PlayingState::~PlayingState()
{

}

//PausedState
void PausedState::play(MusicPlayer *player)
{
    player->setState(new PlayingState());
}
PausedState::PausedState():MusicPlayerState("PAUSE"){}



int main()
{
    MusicPlayer myplayer;
    myplayer.play();
    myplayer.play();
    myplayer.pause();
    myplayer.play();
    myplayer.stop();
    myplayer.pause();
}
