#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "Global.h"
#include "AudioManager.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Ghosts");
    eglView->setFrameSize(G_DESIGN_WIDTH, G_DESIGN_HEIGHT);
    return CCApplication::sharedApplication()->run();
}
