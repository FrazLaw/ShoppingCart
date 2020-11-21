#include "cMain.h"
#include "produce.h"
#include <string>
#include "logo_xpm.xpm"

//event table
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(BUTTON_ENTER, OnAddButtonClicked)
	EVT_BUTTON(BUTTON_TOTAL, OnTotalButtonClicked)
wxEND_EVENT_TABLE()

//item name and price
unordered_map<string, float> shopContents = {
	{ "APPLES", 0.3 },
{ "BANANAS", 0.5 },
{ "ORANGES", 0.4 } ,
{"PEARS", 0.3},
{ "MINCED BEEF", 1.7 } ,
{ "CHICKEN", 2.5 } ,
{ "TURKEY", 1.3 } ,
{ "KNIFE", 0.5 } ,
{ "FORK", 0.5 } ,
{ "SPOON", 0.5 }
};

//Vector to hold receipt contents
vector<market::produce> v;

//set deals as you wish (only 1 deal at a time :) )
vector<string> dealItems{ "KNIFE", "FORK", "SPOON" };

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Shopping Cart" , wxPoint(25,25), wxSize(600,400))
{
	m_title = new wxStaticText(this, wxID_ANY, "SBG SHOPPING CART", wxPoint(x_title_start, padding), 
		wxSize(title_width,title_height), wxALIGN_CENTRE_HORIZONTAL);

	m_itemList = new wxStaticText(this, wxID_ANY, "Item", wxPoint(padding, title_height),
		wxSize(itemListWidth, text_height));

	m_itemQty = new wxStaticText(this, wxID_ANY, "Quantity", wxPoint(itemQtyStart, title_height),
		wxSize(itemQtyWidth, text_height));

	m_basket = new wxStaticText(this, wxID_ANY, "Basket", wxPoint(basket_start, title_height),
		wxSize(basketWidth, text_height));
	
	//shopping stock
	m_list1 = new wxListBox(this, LIST_CHOICE, wxPoint(padding, listStart_y),
		wxSize(itemListWidth, itemListWidth));

	m_list1->InsertItems(10,str, 0);

	//quantity text
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(itemQtyStart, listStart_y),
		wxSize(itemQtyWidth, 30));
	 
	m_basket_list = new wxListCtrl(this, wxID_ANY, wxPoint(basket_start, listStart_y),
		wxSize(basketWidth, itemListWidth), wxLC_REPORT);
	int column_width = 10;

	// Add first column       
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("Item"));
	col0.SetWidth(100);
	m_basket_list->InsertColumn(0, col0);

	// Add second column
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(_("Quantity"));
	m_basket_list->InsertColumn(1, col1);

	// Add third column     
	wxListItem col2;
	col2.SetId(2);
	col2.SetText(_("Price Ea."));
	m_basket_list->InsertColumn(2, col2);

	m_addBtn1 = new wxButton(this, BUTTON_ENTER, "Add to Basket", wxPoint(padding, button_start), 
		wxSize(100, 75));
	m_totalBtn1 = new wxButton(this, BUTTON_TOTAL, "Total", wxPoint(totalbutton_start, button_start), 
		wxSize(100, 75));
	m_totaltxt = new wxStaticText(this, wxID_ANY, "Total: £", wxPoint(total_txt_display, button_start),
		wxSize(itemQtyWidth, 30));
	m_totaltxt_display = new wxTextCtrl(this, wxID_ANY, "", wxPoint(total_txt_display+itemQtyWidth, button_start),
		wxSize(itemQtyWidth + 35, 30), wxTE_READONLY);

	wxPNGHandler *handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxStaticBitmap *image;
	image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(logo_xpm, wxBITMAP_TYPE_XPM), wxPoint(458 - 2 * padding, padding), wxSize(142, 53));
	//image = new wxStaticBitmap(this, wxID_ANY, wxBitmap("logo.PNG", wxBITMAP_TYPE_PNG), wxPoint(458- 2* padding, padding), wxSize(142, 53));
	
}


cMain::~cMain()
{
}

void cMain::OnAddButtonClicked(wxCommandEvent &evt) 
{
	int qtyforconv = 0;
	int pos = 0;
	wxString holdSel;
	wxString quantity;

	//get selected item, 
	pos = m_list1->GetSelection();
	holdSel = m_list1->GetString(pos);
	sel = &holdSel;

	string str_input = sel->ToStdString();

	//get quantity from text box, convert to int, therefore usable in func
	quantity = m_txt1->GetLineText(0);
	qtyforconv = wxAtoi(quantity);

	//convert produce floats to wx usable value, then float to string for display
	float price2 = market::getPrice(shopContents, str_input, qtyforconv);
	wxString price;
	price << price2;

	long item_index = m_basket_list->InsertItem(0, *sel);
	m_basket_list->SetItem(item_index, 1, quantity);
	m_basket_list->SetItem(item_index, 2, price);

	market::produce p(str_input,qtyforconv,price2);
	v.push_back(p);

	evt.Skip();
}

void cMain::OnTotalButtonClicked(wxCommandEvent &evt)
{
	float total = 0.00;
	wxString sum;
	float deductions = 0.00;

	deductions = market::applyDiscount(v, dealItems);
	int vLen = v.size();
	for (int i = 0; i < vLen; i++)
	{
		total += v[i].qty * v[i].price;
	}

	total -= deductions;
	sum << total;
	m_totaltxt_display->AppendText(sum);
}
