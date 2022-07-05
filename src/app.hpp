#ifndef APP_HPP
#define APP_HPP

#include <piksel/baseapp.hpp>

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(800, 800, "Conway's Game of Life") {}
    void setup();
    void draw(piksel::Graphics& g);
    void keyPressed(int key);
};
#endif /* APP_HPP */