#include "wx/wx.h"
#include "ImageSlideshow.h"
#include "VideoPlayer.h"
#include <iostream>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame(); 

    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnNextImage(wxCommandEvent& event);

private:
    void OnWindowDestroy(wxWindowDestroyEvent& event);

    ImageSlideshow* slideshow;
    VideoPlayer* videoPlayer;
    bool windowDestroyed;  // Declare windowDestroyed here
};

/**
 * @brief Constructs a new instance of the MyFrame class.
 *
 * @param title The title of the frame.
 * @param pos The position of the frame.
 * @param size The size of the frame.
 */
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), windowDestroyed(false)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    try {
        slideshow = new ImageSlideshow(this);
        slideshow->addImage("download.jpg"); // Corrected file extension
        videoPlayer = new VideoPlayer(this, wxID_ANY);
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error creating slideshow or video player", wxOK | wxICON_ERROR);
        return;
    }

    if (slideshow && videoPlayer) {
        std::cout << "Slideshow and videoPlayer created" << std::endl;
        wxButton* playButton = new wxButton(this, wxID_ANY, "Play");
        wxButton* pauseButton = new wxButton(this, wxID_ANY, "Pause");
        wxButton* stopButton = new wxButton(this, wxID_ANY, "Stop");
        wxButton* nextImageButton = new wxButton(this, wxID_ANY, "Next Image");

        playButton->Bind(wxEVT_BUTTON, &MyFrame::OnPlay, this);
        pauseButton->Bind(wxEVT_BUTTON, &MyFrame::OnPause, this);
        stopButton->Bind(wxEVT_BUTTON, &MyFrame::OnStop, this);
        nextImageButton->Bind(wxEVT_BUTTON, &MyFrame::OnNextImage, this);

        sizer->Add(slideshow, 1, wxEXPAND);
        sizer->Add(videoPlayer, 1, wxEXPAND);
        sizer->Add(playButton);
        sizer->Add(pauseButton);
        sizer->Add(stopButton);
        sizer->Add(nextImageButton);

        this->SetSizer(sizer);
        std::cout << "Slideshow and videoPlayer end" << std::endl;
    } else {
        wxMessageBox("Error: Failed to create slideshow or video player.", "Error", wxOK | wxICON_ERROR);
    }

    Bind(wxEVT_DESTROY, &MyFrame::OnWindowDestroy, this);
}

/**
 * Event handler for the "Play" button.
 * @param event The event object associated with the button click.
 */
void MyFrame::OnPlay(wxCommandEvent& event)
{
    try {
        videoPlayer->play("video.mp4");
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error playing video", wxOK | wxICON_ERROR);
    }
}

/**
 * @brief Event handler for the "Pause" button.
 * @param event The event object associated with the button click.
 */
void MyFrame::OnPause(wxCommandEvent& event)
{
    try {
        videoPlayer->pause();
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error pausing video", wxOK | wxICON_ERROR);
    }
}

/**
 * Event handler for the "Stop" button click event.
 * @param event The wxCommandEvent object representing the event.
 */
void MyFrame::OnStop(wxCommandEvent& event)
{
    try {
        videoPlayer->stop();
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error stopping video", wxOK | wxICON_ERROR);
    }
}

/**
 * @brief Event handler for the "Next Image" event.
 * @param event The event object associated with the button click.
 */
void MyFrame::OnNextImage(wxCommandEvent& event)
{
    try {
        slideshow->nextImage();
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error advancing slideshow", wxOK | wxICON_ERROR);
    }
}

/**
 * @brief Initializes the application.
 * @return true if the initialization is successful, false otherwise.
 */
bool MyApp::OnInit()
{
    try {
        wxFrame* frame = new MyFrame("GloApp", wxPoint(50, 50), wxSize(450, 340));
        std::cout << "Frame created" << std::endl;
        frame->Show();
        std::cout << "Frame shown" << std::endl;
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Error creating window", wxOK | wxICON_ERROR);
        return false;
    }

    std::cout << "Hello World" << std::endl;
    return true;
}

void MyFrame::OnWindowDestroy(wxWindowDestroyEvent& event)
{
    windowDestroyed = true;
    std::cout << "Window destroyed event received." << std::endl;
}

/**
 * Destructor for the MyFrame class.
 */
MyFrame::~MyFrame() 
{
    if (!windowDestroyed) {
        std::cout << "Destroying slideshow and videoPlayer" << std::endl;
        delete slideshow;
        delete videoPlayer;
    }
}

IMPLEMENT_APP(MyApp)
