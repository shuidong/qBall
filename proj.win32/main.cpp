#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "Confings.h"

USING_NS_CC;

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setViewName("QBA");
    eglView.setFrameSize(WIN_WIDTH / SCALE_V, WIN_HEIGHT / SCALE_V);
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
    eglView.setDesignResolutionSize(WIN_WIDTH, WIN_HEIGHT);

    int ret = CCApplication::sharedApplication().run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
