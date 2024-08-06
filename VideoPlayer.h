#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include <wx/wx.h>
#include <wx/mediactrl.h>

class VideoPlayer : public wxPanel {
public:
    VideoPlayer(wxWindow* parent, wxWindowID id = wxID_ANY);
    ~VideoPlayer();

    void play(const wxString& videoPath);
    void pause();
    void stop();
    void setVolume(int volume);

private:
    void OnWindowDestroy(wxWindowDestroyEvent& event);

    wxMediaCtrl* mediaCtrl;
    bool windowDestroyed;

    void SomeMethod(); // Placeholder for additional operations

    wxDECLARE_EVENT_TABLE();
};

#endif // VIDEO_PLAYER_H
