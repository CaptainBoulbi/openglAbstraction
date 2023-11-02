#ifndef SG_WINDOW_HPP
#define SG_WINDOW_HPP

namespace sg{

  class Window{
    public:
    Window(const char* title = "simple window", unsigned int width = 1280, unsigned int height = 720);
    ~Window();

    unsigned int getWidth();
    unsigned int getHeight();

    bool setVSync();
    bool isVSync();

    private:
    const char* _title;
    unsigned int _width;
    unsigned int _height;
    bool _VSync;
  };

}

#endif //SG_WINDOW_HPP
