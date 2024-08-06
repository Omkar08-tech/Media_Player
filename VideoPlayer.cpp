#include "VideoPlayer.h"
#include <wx/log.h>
#include <iostream>

BEGIN_EVENT_TABLE(VideoPlayer, wxPanel)
    EVT_WINDOW_DESTROY(VideoPlayer::OnWindowDestroy)
END_EVENT_TABLE()

VideoPlayer::VideoPlayer(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id), windowDestroyed(false)
{
    mediaCtrl = new wxMediaCtrl(this, wxID_ANY);
    std::cout << "VideoPlayer constructor" << std::endl;
}

VideoPlayer::~VideoPlayer()
{
    delete mediaCtrl;
    mediaCtrl = nullptr;
    std::cout << "VideoPlayer destructor" << std::endl;
}

void VideoPlayer::play(const wxString& videoPath)
{
    if (!mediaCtrl->Load(videoPath)) {
        wxLogError("Could not load video: %s", videoPath);
        std::cout << "Failed to load video: " << videoPath << std::endl;
        return;
    }
    mediaCtrl->Play();
    std::cout << "Video playback started" << std::endl;
}

void VideoPlayer::pause()
{
    mediaCtrl->Pause();
    std::cout << "Video playback paused" << std::endl;
}

void VideoPlayer::stop()
{
    mediaCtrl->Stop();
    std::cout << "Video playback stopped" << std::endl;
}

void VideoPlayer::setVolume(int volume)
{
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    mediaCtrl->SetVolume(static_cast<double>(volume) / 100);
    std::cout << "Volume set to: " << volume << std::endl;
}

void VideoPlayer::OnWindowDestroy(wxWindowDestroyEvent& event)
{
    windowDestroyed = true;
    event.Skip();  // Continue processing the event
    std::cout << "Window destroyed" << std::endl;
}

void VideoPlayer::SomeMethod()
{
    if (windowDestroyed) {
        std::cout << "Window has been destroyed, skipping operations" << std::endl;
        return;
    }
    // Perform operations on the window
    std::cout << "Performing operations on the window" << std::endl;
}
