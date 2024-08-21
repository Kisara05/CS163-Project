#ifndef APP_H
#define APP_H

class Application {
public:
    static constexpr float WINDOW_WIDTH = 1024;
    static constexpr float WINDOW_HEIGHT = 640;
    static constexpr char* WINDOW_TITLE = "CS163 - Dictionary App";

    static constexpr int FPS = 30;

public:
    Application();
    ~Application();

    void run();

private:
};

#endif // APP_H