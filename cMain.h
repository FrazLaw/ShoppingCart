#pragma once

#include "wx/wx.h"
#include <wx/stc/stc.h>
#include "wx/listctrl.h"

//this header is used to set parameters for frames within main window
class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:

	wxButton * m_addBtn1 = nullptr;
	wxButton * m_totalBtn1 = nullptr;
	wxTextCtrl *m_txt1 = nullptr;
	wxTextCtrl *m_totaltxt_display = nullptr;
	wxStaticText *m_totaltxt = nullptr;
	wxListBox *m_list1 = nullptr;
	wxStaticText *m_title = nullptr;
	wxStaticText *m_itemList = nullptr;
	wxStaticText *m_itemQty = nullptr;
	wxStaticText *m_basket = nullptr;

	wxListCtrl *m_basket_list = nullptr;

	wxString *sel;

	wxString str[10] = 
	{	"APPLES", 
		"BANANAS", 
		"ORANGES",
		"PEARS",
		"MINCED BEEF",
		"CHICKEN",
		"TURKEY",
		"KNIFE",
		"FORK",
		"SPOON" };

	int width = 600;
	int height = 500;

	int padding = 10;
	int titleLen = padding + 30;

	int title_width = padding + 200;
	int title_height = 2 * padding + 30;
	int x_title_start = width / 2 - title_width / 2;

	int text_height = 30;

	int itemListWidth = 150;

	int itemQtyWidth = 50;
	int itemQtyStart = itemListWidth + (2 * padding);

	int basketWidth = 300;
	int basket_start = itemQtyWidth + itemQtyStart + padding;

	int listStart_y = title_height + text_height;// +padding;
	int button_start = listStart_y + itemListWidth + padding;

	int totalbutton_start = padding * 2 + 100;
	int total_txt_display = basket_start;

	void OnAddButtonClicked(wxCommandEvent &evt);
	void OnTotalButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();


	enum
	{
		BUTTON_ENTER = wxID_HIGHEST + 1,
		LIST_CHOICE,
		BUTTON_TOTAL
	};

};

