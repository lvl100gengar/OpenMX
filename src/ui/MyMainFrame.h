#pragma once

#include "components.h"

class MyMainFrame : public MainFrame {
public:
    MyMainFrame();
protected:
		virtual void m_buttonNetworksOnButtonClick( wxCommandEvent& event );
		virtual void m_buttonLibraryOnButtonClick( wxCommandEvent& event );
		virtual void m_buttonChatOnButtonClick( wxCommandEvent& event );
		virtual void m_buttonHotlistOnButtonClick( wxCommandEvent& event );
		virtual void m_buttonSearchOnButtonClick( wxCommandEvent& event );
		virtual void m_buttonTransfersOnButtonClick( wxCommandEvent& event );
private:
};