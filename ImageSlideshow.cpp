#include "ImageSlideshow.h"
#include <iostream>

BEGIN_EVENT_TABLE(ImageSlideshow, wxPanel)
    EVT_WINDOW_DESTROY(ImageSlideshow::OnWindowDestroy)
END_EVENT_TABLE()

ImageSlideshow::ImageSlideshow(wxWindow* parent)
    : wxPanel(parent), currentIndex(0), windowDestroyed(false)
{
    staticBitmap = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(staticBitmap, 1, wxEXPAND);
    SetSizer(sizer);

    std::cout << "ImageSlideshow constructor called." << std::endl;
}

void ImageSlideshow::OnWindowDestroy(wxWindowDestroyEvent& event)
{
    windowDestroyed = true;
    event.Skip();
    std::cout << "Window destroyed event received." << std::endl;
}

void ImageSlideshow::nextImage() {
    if (!images.empty()) {
        currentIndex = (currentIndex + 1) % images.size();
        displayImage(images[currentIndex]);
    }
    std::cout << "Next image displayed." << std::endl;
}

void ImageSlideshow::prevImage() {
    if (!images.empty()) {
        currentIndex = (currentIndex - 1 + images.size()) % images.size();
        displayImage(images[currentIndex]);
    }
    std::cout << "Previous image displayed." << std::endl;
}

void ImageSlideshow::startSlideshow() {
    if (!images.empty()) {
        currentIndex = 0;
        displayImage(images[currentIndex]);
    }
    std::cout << "Slideshow started." << std::endl;
}

void ImageSlideshow::displayImage(const std::string& imagePath) {
    wxImage image;
    if (image.LoadFile(imagePath)) {
        wxBitmap bitmap(image);
        staticBitmap->SetBitmap(bitmap);
    } else {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
    }
    std::cout << "Image displayed: " << imagePath << std::endl;
}

void ImageSlideshow::addImage(const std::string& imagePath) {
    images.push_back(imagePath);
    std::cout << "Image added: " << imagePath << std::endl;
}

void ImageSlideshow::SomeMethod()
{
    if (windowDestroyed) {
        std::cout << "Window has been destroyed. Skipping operations." << std::endl;
        return;
    }

    // Perform operations on the window
    std::cout << "Performing operations on the window." << std::endl;
}
