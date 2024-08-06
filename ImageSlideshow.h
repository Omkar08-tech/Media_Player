#ifndef IMAGE_SLIDESHOW_H
#define IMAGE_SLIDESHOW_H

#include <wx/wx.h>
#include <vector>
#include <string>

class ImageSlideshow : public wxPanel {
public:
    ImageSlideshow(wxWindow* parent);

    void nextImage();
    void prevImage();
    void startSlideshow();
    void addImage(const std::string& imagePath);

private:
    void displayImage(const std::string& imagePath);
    void OnWindowDestroy(wxWindowDestroyEvent& event);
    void SomeMethod();

    wxStaticBitmap* staticBitmap;
    std::vector<std::string> images;
    size_t currentIndex;
    bool windowDestroyed;

    wxDECLARE_EVENT_TABLE();
};

#endif // IMAGE_SLIDESHOW_H
