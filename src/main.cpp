#include "main.h"
#include "ui/components.h"
#include "ui/MyMainFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyMainFrame *frame = new MyMainFrame();
    frame->Show(true);
    return true;
}

