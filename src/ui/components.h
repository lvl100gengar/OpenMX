///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/simplebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:

	protected:
		wxButton* m_buttonNetworks;
		wxButton* m_buttonLibrary;
		wxButton* m_buttonChat;
		wxButton* m_buttonHotlist;
		wxButton* m_buttonSearch;
		wxButton* m_buttonTransfers;
		wxSimplebook* m_mainContentView;
		wxPanel* m_panelNetworks;
		wxRadioButton* m_radioBtn2;
		wxRadioButton* m_radioBtn3;
		wxPanel* m_panelLibrary;
		wxPanel* m_panelChat;
		wxPanel* m_panelHotlist;
		wxPanel* m_panelSearch;
		wxTextCtrl* m_textCtrl1;
		wxListCtrl* m_listCtrl3;
		wxPanel* m_panelTransfers;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel7;
		wxListCtrl* m_listCtrl1;
		wxPanel* m_panel8;
		wxListCtrl* m_listCtrl2;

		// Virtual event handlers, override them in your derived class
		virtual void m_buttonNetworksOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonLibraryOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonChatOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonHotlistOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonSearchOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonTransfersOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OpenMX v0.1"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 822,441 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 215 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter1OnIdle ), NULL, this );
		}

};

