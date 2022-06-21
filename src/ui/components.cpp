///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "components.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonNetworks = new wxButton( this, wxID_ANY, wxT("Networks"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonNetworks->SetBitmap( wxBitmap( wxT("../../../../Pictures/Icons/WinMX Icons/WinMX_377.ico"), wxBITMAP_TYPE_ANY ) );
	bSizer2->Add( m_buttonNetworks, 0, wxALL, 5 );

	m_buttonLibrary = new wxButton( this, wxID_ANY, wxT("Library"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonLibrary->SetBitmap( wxBitmap( wxT("../../../../Pictures/Icons/WinMX Icons/WinMX_378.ico"), wxBITMAP_TYPE_ANY ) );
	bSizer2->Add( m_buttonLibrary, 0, wxALL, 5 );

	m_buttonChat = new wxButton( this, wxID_ANY, wxT("Chat"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonChat->SetBitmap( wxBitmap( wxT("../../../../Pictures/Icons/WinMX Icons/WinMX_379.ico"), wxBITMAP_TYPE_ANY ) );
	bSizer2->Add( m_buttonChat, 0, wxALL, 5 );

	m_buttonHotlist = new wxButton( this, wxID_ANY, wxT("Hotlist"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonHotlist->SetBitmap( wxBitmap( wxT("../../../../Pictures/Icons/WinMX Icons/WinMX_381.ico"), wxBITMAP_TYPE_ANY ) );
	bSizer2->Add( m_buttonHotlist, 0, wxALL, 5 );

	m_buttonSearch = new wxButton( this, wxID_ANY, wxT("Search"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonSearch->SetBitmap( wxBitmap( wxT("../../../../Pictures/Icons/WinMX Icons/WinMX_380.ico"), wxBITMAP_TYPE_ANY ) );
	bSizer2->Add( m_buttonSearch, 0, wxALL, 5 );

	m_buttonTransfers = new wxButton( this, wxID_ANY, wxT("Transfers"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonTransfers->SetBitmap( wxBitmap( wxT("../../../../Pictures/Icons/WinMX Icons/WinMX_384.ico"), wxBITMAP_TYPE_ANY ) );
	bSizer2->Add( m_buttonTransfers, 0, wxALL, 5 );


	bSizer1->Add( bSizer2, 0, 0, 5 );

	m_mainContentView = new wxSimplebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelNetworks = new wxPanel( m_mainContentView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelNetworks->SetBackgroundColour( wxColour( 255, 128, 128 ) );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_radioBtn2 = new wxRadioButton( m_panelNetworks, wxID_ANY, wxT("RadioBtn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_radioBtn2, 0, wxALIGN_CENTER|wxALL, 5 );

	m_radioBtn3 = new wxRadioButton( m_panelNetworks, wxID_ANY, wxT("RadioBtn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_radioBtn3, 0, wxALIGN_CENTER|wxALL, 5 );


	m_panelNetworks->SetSizer( bSizer7 );
	m_panelNetworks->Layout();
	bSizer7->Fit( m_panelNetworks );
	m_mainContentView->AddPage( m_panelNetworks, wxT("a page"), false );
	m_panelLibrary = new wxPanel( m_mainContentView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelLibrary->SetBackgroundColour( wxColour( 255, 128, 64 ) );

	m_mainContentView->AddPage( m_panelLibrary, wxT("a page"), false );
	m_panelChat = new wxPanel( m_mainContentView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelChat->SetBackgroundColour( wxColour( 255, 255, 128 ) );

	m_mainContentView->AddPage( m_panelChat, wxT("a page"), false );
	m_panelHotlist = new wxPanel( m_mainContentView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelHotlist->SetBackgroundColour( wxColour( 128, 255, 128 ) );

	m_mainContentView->AddPage( m_panelHotlist, wxT("a page"), false );
	m_panelSearch = new wxPanel( m_mainContentView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelSearch->SetBackgroundColour( wxColour( 128, 255, 255 ) );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_textCtrl1 = new wxTextCtrl( m_panelSearch, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_textCtrl1, 0, wxALL|wxEXPAND, 5 );

	m_listCtrl3 = new wxListCtrl( m_panelSearch, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer6->Add( m_listCtrl3, 1, wxALL|wxEXPAND, 5 );


	m_panelSearch->SetSizer( bSizer6 );
	m_panelSearch->Layout();
	bSizer6->Fit( m_panelSearch );
	m_mainContentView->AddPage( m_panelSearch, wxT("a page"), false );
	m_panelTransfers = new wxPanel( m_mainContentView, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelTransfers->SetBackgroundColour( wxColour( 128, 128, 192 ) );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_splitter1 = new wxSplitterWindow( m_panelTransfers, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitter1OnIdle ), NULL, this );

	m_panel7 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_listCtrl1 = new wxListCtrl( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	bSizer9->Add( m_listCtrl1, 1, wxALL|wxEXPAND, 5 );


	m_panel7->SetSizer( bSizer9 );
	m_panel7->Layout();
	bSizer9->Fit( m_panel7 );
	m_panel8 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_listCtrl2 = new wxListCtrl( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	bSizer10->Add( m_listCtrl2, 1, wxALL|wxEXPAND, 5 );


	m_panel8->SetSizer( bSizer10 );
	m_panel8->Layout();
	bSizer10->Fit( m_panel8 );
	m_splitter1->SplitHorizontally( m_panel7, m_panel8, 215 );
	bSizer3->Add( m_splitter1, 1, wxEXPAND, 5 );


	m_panelTransfers->SetSizer( bSizer3 );
	m_panelTransfers->Layout();
	bSizer3->Fit( m_panelTransfers );
	m_mainContentView->AddPage( m_panelTransfers, wxT("a page"), false );

	bSizer1->Add( m_mainContentView, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonNetworks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonNetworksOnButtonClick ), NULL, this );
	m_buttonLibrary->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonLibraryOnButtonClick ), NULL, this );
	m_buttonChat->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonChatOnButtonClick ), NULL, this );
	m_buttonHotlist->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonHotlistOnButtonClick ), NULL, this );
	m_buttonSearch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonSearchOnButtonClick ), NULL, this );
	m_buttonTransfers->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonTransfersOnButtonClick ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_buttonNetworks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonNetworksOnButtonClick ), NULL, this );
	m_buttonLibrary->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonLibraryOnButtonClick ), NULL, this );
	m_buttonChat->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonChatOnButtonClick ), NULL, this );
	m_buttonHotlist->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonHotlistOnButtonClick ), NULL, this );
	m_buttonSearch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonSearchOnButtonClick ), NULL, this );
	m_buttonTransfers->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_buttonTransfersOnButtonClick ), NULL, this );

}
