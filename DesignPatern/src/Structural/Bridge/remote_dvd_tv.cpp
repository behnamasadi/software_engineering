// Bridge — RemoteButton (abstraction) over EntertainmentDevice (implementation).
//
// Two axes vary independently:
//   - Devices: TV, DVD player, ...
//   - Remotes: with mute, with pause, ...
// Without the Bridge you'd write TVMuteRemote, TVPauseRemote, DVDMuteRemote,
// DVDPauseRemote ... With it, you compose any (remote × device) at runtime.
//
// Buttons 5/6 are device-specific (channel up/down vs DVD chapter prev/next).
// Buttons 7/8 are shared (volume up/down).
// Button 9 is remote-specific (mute, pause, ...).

#include <iostream>
#include <memory>
#include <utility>

// Implementor.
class EntertainmentDevice {
public:
    EntertainmentDevice(int initialState, int maxSetting)
        : state_(initialState), max_(maxSetting), volume_(10) {}

    virtual ~EntertainmentDevice() = default;

    virtual void buttonFivePressed() = 0;
    virtual void buttonSixPressed() = 0;

    void buttonSevenPressed() { ++volume_; std::cout << "  volume up: " << volume_ << '\n'; }
    void buttonEightPressed() { --volume_; std::cout << "  volume down: " << volume_ << '\n'; }

    void deviceFeedback() const {
        std::cout << "  currently on: " << state_ << '\n';
    }

protected:
    int state_;
    int max_;
    int volume_;
};

class TVDevice : public EntertainmentDevice {
public:
    TVDevice() : EntertainmentDevice(1, 100) {}

    void buttonFivePressed() override {
        if (state_ > 1) {
            --state_;
            std::cout << "  previous channel: " << state_ << '\n';
        }
    }

    void buttonSixPressed() override {
        if (state_ < max_) {
            ++state_;
            std::cout << "  next channel: " << state_ << '\n';
        }
    }
};

class DVDDevice : public EntertainmentDevice {
public:
    DVDDevice() : EntertainmentDevice(1, 12) {}

    void buttonFivePressed() override {
        if (state_ > 1) {
            --state_;
            std::cout << "  previous DVD chapter: " << state_ << '\n';
        }
    }

    void buttonSixPressed() override {
        if (state_ < max_) {
            ++state_;
            std::cout << "  next DVD chapter: " << state_ << '\n';
        }
    }
};

// Abstraction.
class RemoteButton {
public:
    explicit RemoteButton(std::unique_ptr<EntertainmentDevice> device)
        : device_(std::move(device)) {}

    virtual ~RemoteButton() = default;

    void buttonFivePressed()  { device_->buttonFivePressed(); }
    void buttonSixPressed()   { device_->buttonSixPressed(); }
    void buttonSevenPressed() { device_->buttonSevenPressed(); }
    void buttonEightPressed() { device_->buttonEightPressed(); }
    void deviceFeedback() const { device_->deviceFeedback(); }

    virtual void buttonNinePressed() = 0;

protected:
    std::unique_ptr<EntertainmentDevice> device_;
};

class TVRemoteMute : public RemoteButton {
public:
    using RemoteButton::RemoteButton;
    void buttonNinePressed() override { std::cout << "  TV muted\n"; }
};

class TVRemotePause : public RemoteButton {
public:
    using RemoteButton::RemoteButton;
    void buttonNinePressed() override { std::cout << "  TV paused\n"; }
};

int main() {
    std::unique_ptr<RemoteButton> tv1 =
        std::make_unique<TVRemoteMute>(std::make_unique<TVDevice>());
    std::unique_ptr<RemoteButton> tv2 =
        std::make_unique<TVRemotePause>(std::make_unique<DVDDevice>());

    std::cout << "TVRemoteMute + TVDevice:\n";
    tv1->buttonSixPressed();
    tv1->deviceFeedback();
    tv1->buttonNinePressed();

    std::cout << "TVRemotePause + DVDDevice:\n";
    tv2->buttonSixPressed();
    tv2->deviceFeedback();
    tv2->buttonNinePressed();
}
