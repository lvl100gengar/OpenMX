#include "MyMainFrame.h"

MyMainFrame::MyMainFrame() : MainFrame(nullptr) {

}

void MyMainFrame::m_buttonNetworksOnButtonClick( wxCommandEvent& event ) { 
    m_mainContentView->SetSelection(0);
}

void MyMainFrame::m_buttonLibraryOnButtonClick( wxCommandEvent& event ) { 
    m_mainContentView->SetSelection(1);
}

void MyMainFrame::m_buttonChatOnButtonClick( wxCommandEvent& event ) { 
    m_mainContentView->SetSelection(2);
}

void MyMainFrame::m_buttonHotlistOnButtonClick( wxCommandEvent& event ) { 
    m_mainContentView->SetSelection(3);
}

void MyMainFrame::m_buttonSearchOnButtonClick( wxCommandEvent& event ) {
    m_mainContentView->SetSelection(4);
}

void MyMainFrame::m_buttonTransfersOnButtonClick( wxCommandEvent& event ) { 
    m_mainContentView->SetSelection(5);
}