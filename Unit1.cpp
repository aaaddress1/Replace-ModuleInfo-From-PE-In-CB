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

String FakeStr  = "hahaha";
bool HideModualName(long BaseADR){
		asm{
				mov  eax,fs:[0x30]        //;eax-->PEB
				mov  eax,[eax + 0x0c]     //;eax==Ldr-->PEB_LDR_DATA
				mov  eax,[eax+0x0c]       //LIST
				Scan:
				mov  ecx,[eax + 0x18]     //;[eax + 18h]為當前處理的模塊的基址
				cmp  ecx,[BaseADR]        //;找到本模塊的LDR_DATA_TABLE_ENTRY
				jne  Next
			   //	mov  ebx,[eax + 0x24 + 0x4]
				push FakeStr
				pop [eax + 0x28]
				push FakeStr
				pop [eax + 0x30]
			  /*	movzx  ecx,word ptr [eax + 0x24]   // ;Unicode String length 獲得子串長度
				mov  edi,ebx        //  ;Unicode String Address
				mov  dword ptr [ebx],0      //;(確保String首4個byte為0)  */
				jmp  Exit

				Next:
				mov eax,[eax]
				jmp Scan
				Exit:
		}
}

void __fastcall TForm1::FormShow(TObject *Sender)
{
	HideModualName(0x400000);
}
//---------------------------------------------------------------------------
