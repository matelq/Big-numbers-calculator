//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (bigNumber(AtoS(Edit1->Text)) == bigNumber(AtoS(Edit2->Text)))
		Edit3->Text = "TRUE";
	else
		Edit3->Text = "FALSE";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if (bigNumber(AtoS(Edit1->Text)) != bigNumber(AtoS(Edit2->Text)))
		Edit3->Text = "TRUE";
	else
		Edit3->Text = "FALSE";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if (bigNumber(AtoS(Edit1->Text)) < bigNumber(AtoS(Edit2->Text)))
		Edit3->Text = "TRUE";
	else
		Edit3->Text = "FALSE";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	if (bigNumber(AtoS(Edit1->Text)) > bigNumber(AtoS(Edit2->Text)))
		Edit3->Text = "TRUE";
	else
		Edit3->Text = "FALSE";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	if (bigNumber(AtoS(Edit1->Text)) <= bigNumber(AtoS(Edit2->Text)))
		Edit3->Text = "TRUE";
	else
		Edit3->Text = "FALSE";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	if (bigNumber(AtoS(Edit1->Text)) >= bigNumber(AtoS(Edit2->Text)))
		Edit3->Text = "TRUE";
	else
		Edit3->Text = "FALSE";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Edit3->Text = BNtoA(bigNumber(AtoS(Edit1->Text)) + bigNumber(AtoS(Edit2->Text)));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
	Edit3->Text = BNtoA(bigNumber(AtoS(Edit1->Text)) - bigNumber(AtoS(Edit2->Text)));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
    Edit3->Text = BNtoA(bigNumber(AtoS(Edit1->Text)) / bigNumber(AtoS(Edit2->Text)));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
	Edit3->Text = BNtoA(bigNumber(AtoS(Edit1->Text)) * bigNumber(AtoS(Edit2->Text)));	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
	if(!(Edit3->Text.Pos("T") || Edit3->Text.Pos("F")))
		Edit1->Text = Edit3->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
	if(!(Edit3->Text.Pos("T") || Edit3->Text.Pos("F")))
		Edit2->Text = Edit3->Text;
}
//---------------------------------------------------------------------------

