#include <fstream>
#include <Windows.h>
#include "resource.h"
#include <stdio.h>
#include <string.h>

using namespace std;



struct node
{
	char	CltName[30];
	char	Phone[13];
	char	species[30];
	char	MasName[30];
	char	Motivo[150];
	char	cost[10];

	char	date[11];
	char	time[9];

	//bool	urgent;
	//bool	gender;
	node	*sig;
	node	*ante;
};
	


node *inicio = 0, *last = 0, *prev = 0, *ant = 0;
node *nuevo;
char file[80] = "citas.txt";
char _arch_esp[] = "species.txt";
char _arch_dat[] = "Datos.txt";
char _pic[MAX_PATH] =  "" ;
char _pic2[MAX_PATH] = "";


void AgregaNodo(node Datos);
void MostarLista(HWND objeto, UINT mensa);
void LlenaEspecies(HWND objeto, UINT mensa, char *file);

bool CapturaNodo(HWND Dlg, node*Punt);
//node*BuscarDato(int id);


char*ConvierteFecha(char*Fecha);


void LeeArchivo();
void EscribirArchivo();

void LeeDatos();

HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;


BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK informacion(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK informacion2(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK InfDoc(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Alta(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Baja(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Ver_Agen(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Modificar(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);


void PonImagen(HWND dialog, WPARAM IDC, char *imagen);






//************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{

	LeeArchivo();
	_hInst = hInst;
	_show = show;

	LeeDatos();



	ghDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1),
		0, ProcDialog1);
	ShowWindow(ghDlg, show);



	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	EscribirArchivo();
	return (int)msg.wParam;
}

//************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************






BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	static HBITMAP bmp2;
	static HBITMAP bmp2_02;
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{


	

		//Al objeto bmp2, se le asigna una imagen local:
		bmp2 = (HBITMAP)LoadImage(NULL, _pic,
			IMAGE_BITMAP,83, 108, LR_LOADFROMFILE);

		SendDlgItemMessage(Dlg, IDC_hi, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);


		//Al objeto bmp2, se le asigna una imagen local:
		bmp2_02 = (HBITMAP)LoadImage(NULL, _pic2,
			IMAGE_BITMAP, 500, 50, LR_LOADFROMFILE);

		SendDlgItemMessage(Dlg, IDC_bienve, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2_02);


		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Doc_Inf), Dlg, InfDoc);
			return true;

		case IDC_BUTTON2:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_alta), Dlg, Alta);
			return true;
		case IDC_BUTTON3:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_ver_agenda), Dlg, Ver_Agen);
			return true; 
		case IDC_BUTTON4:
			//Guardar el Archivo


			PostQuitMessage(0);
			return true;



		case ID_MENU_INFORMACIONDELDOCTOR:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Doc_Inf), Dlg, InfDoc);
			return true;
		case ID__DARDEALTA:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_alta), Dlg, Alta);
			return true;
		case ID__DARDEBAJA:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_baja), Dlg, Baja);
			return true;
		case ID__VERAGENDA:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_ver_agenda), Dlg, Ver_Agen);
			return true;
		case ID__MODIFICAR_CITA:

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_modi_cita), Dlg, Modificar);
			return true;
			
		case ID_salir:
			//Guardar el Archivo

			PostQuitMessage(0);
			return true;

		case ID_VER_INFORMAION:
		
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Ven_Inf), Dlg, informacion);//Mismo callback informacion
			return true;
		case ID_ACERCA:
			HWND Dialg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_Ven_Ace), Dlg, informacion2);

			ShowWindow(Dialg, _show);

			//DialogBox(_hInst, MAKEINTRESOURCE(IDD_Ven_Ace), Dlg, informacion);//Mismo callback informacion 
			return true;

		

		}
		return true; }
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}
BOOL CALLBACK informacion(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	static HBITMAP bmp1, bmp2;
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		bmp1 = (HBITMAP)SendDlgItemMessage(Dlg, IDC_hola,
			STM_GETIMAGE, IMAGE_BITMAP, 0);

		//Al objeto bmp2, se le asigna una imagen local:
		bmp2 = (HBITMAP)LoadImage(NULL, _pic,
			IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

		SendDlgItemMessage(Dlg, IDC_hola, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
		
		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:

			EndDialog(Dlg, 0);
			return true;
		}
		return true; }
	case WM_CLOSE:
	{
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}
BOOL CALLBACK informacion2(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{

		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:

			DestroyWindow(Dlg);
			return true;
		}
		return true; }
	case WM_CLOSE:
	{
		DestroyWindow(Dlg);;
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}
BOOL CALLBACK InfDoc(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	static HBITMAP bmp1, bmp2;


	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		//PonImagen(Dlg, IDC_IMAGEN, _pic);

		
		//Al objeto bmp1, se le asigna sin imagen:
		bmp1 = (HBITMAP)SendDlgItemMessage(Dlg, IDC_h,
			STM_GETIMAGE, IMAGE_BITMAP, 0);

		//Al objeto bmp2, se le asigna una imagen local:
		bmp2 = (HBITMAP)LoadImage(NULL, _pic,
			IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

		SendDlgItemMessage(Dlg, IDC_h, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
		//SendDlgItemMessage(
		//	Dlg,
		//	IDC_IMAGEN,
		//	STM_SETIMAGE,
		//	IMAGE_BITMAP,
		//	(LPARAM)bmp2);

		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			
				
			
			return true;
		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDC_Edi_Inf:
			MessageBox(Dlg, "Aún No Está Definida Esta Función", " ", MB_ICONINFORMATION);
			return true;


		}
		return true; }
	case WM_CLOSE:
	{
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}
BOOL CALLBACK Alta(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	char cliente[20] = "";
	static HWND hCboSpc = 0;
	node temp;

	



	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		
		hCboSpc = GetDlgItem(Dlg, IDC_COMBO1);
		/*
		SendMessage(hCboSpc, CB_ADDSTRING, 0, (LPARAM)"BOA");
		SendMessage(hCboSpc, CB_ADDSTRING, 0, (LPARAM)"PITON");
		SendMessage(hCboSpc, CB_ADDSTRING, 0, (LPARAM)"ANACONDA");
		*/
		LlenaEspecies(hCboSpc, CB_ADDSTRING, _arch_esp);


		return true; 
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			return true;
		case IDC_AGREGAR:
			if (CapturaNodo(Dlg, &temp) == false){
			AgregaNodo(temp);
			MessageBox(Dlg, "Elemento agregado", "Agregar Cita", MB_OK + MB_ICONINFORMATION);
			}
			else
			{

				MessageBox(Dlg, "No se pudo abrir", "hmmm", MB_OK + MB_ICONINFORMATION);
			}
			//CapturaNodo(Dlg,temp);
			//AgregaNodo(temp);
			//
			//MessageBox(Dlg, "Elemento agregado", "Agregar Cita", MB_OK + MB_ICONINFORMATION);

			return true;


		}
		return true; }
	case WM_CLOSE:
	{
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{
		
	return true; }
	}
	return false;
}
BOOL CALLBACK Baja(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{


	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{


		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			return true;
		}
		return true; }
	case WM_CLOSE:
	{
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}
BOOL CALLBACK Ver_Agen(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	static HWND hlist = 0;

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{


		hlist = GetDlgItem(Dlg, IDC_LIST1);
		
		
		//SendDlgItemMessage(Dlg, IDC_LIST1, LB_RESETCONTENT, 0, 0);

		MostarLista(hlist, LB_ADDSTRING);
		
		

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			return true;
		case IDC_BUTTON1:
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_baja), Dlg, Baja);

			return true;
		case IDC_BUTTON2:
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_modi_cita), Dlg, Modificar);
			return true;


		}
		return true; }
	case WM_CLOSE:
	{
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}


BOOL CALLBACK Modificar(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{


	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{


		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			return true;
		}
		return true; }
	case WM_CLOSE:
	{
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}



void PonImagen(HWND dialog, WPARAM IDC, char *imagen) {

	static HBITMAP bmp1, bmp2;
	//Al objeto bmp1, se le asigna sin imagen:
	bmp1 = (HBITMAP)SendDlgItemMessage(dialog, IDC,
		STM_GETIMAGE, IMAGE_BITMAP, 0);
	//Al objeto bmp2, se le asigna una imagen local:
	bmp2 = (HBITMAP)LoadImage(NULL, imagen,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SendDlgItemMessage(
		dialog,
		IDC,
		STM_SETIMAGE,
		IMAGE_BITMAP,
		(LPARAM)bmp2);

}

void AgregaNodo(node Datos) {
	node*aux = 0;
	aux = new node;
	aux->sig = 0;
	aux->ante = 0;

	
	//strcpy(aux->CltName, Datos.CltName);

	if (inicio == 0)
	{
		inicio = aux;
		last = aux;
	}
	else
	{
		last->sig = aux;
		aux->ante = last;
		last = aux;
	}
};

void MostarLista(HWND objeto, UINT mensa) {
	node datitos;
	
	char TextCom[300];// cambiar este 300.
	char NombreClt[80];
	char PhoneClt[80];
	char NombreMas[80];
	char Motiv[150];
	char Dineros[80];
	char fecha_temp[11] = "";
	char hora_temp[11] = "";


	//--------------------------------------

	node*aux;
	aux = inicio;
	while (aux != 0)
	{
		

		strcpy(NombreClt, aux->CltName);

		strcpy(TextCom,   aux->species);

		/*
		strcpy(PhoneClt,  aux->Phone);
		strcpy(NombreMas, aux->MasName);
		strcpy(Motiv,     aux->Motivo);
		strcpy(Dineros,   aux->cost);
		strcpy(fecha_temp,aux->date);
		strcpy(hora_temp, aux->time);
*/
		SendMessage(objeto, mensa, 0, (LPARAM)NombreClt);

		//Me salen númerons raros como: íííííííííííííííííííííííí. seguramente están en binario

		//MessageBox(objeto, TextCom, "", MB_OK);
		
		//SendMessage(objeto, mensa, 0, (LPARAM)TextCom);
		//SendMessage(objeto, mensa, 0, (LPARAM)PhoneClt);
		//SendMessage(objeto, mensa, 0, (LPARAM)NombreMas);
		//SendMessage(objeto, mensa, 0, (LPARAM)Motiv);
		//SendMessage(objeto, mensa, 0, (LPARAM)Dineros);
		//SendMessage(objeto, mensa, 0, (LPARAM)fecha_temp);
		//SendMessage(objeto, mensa, 0, (LPARAM)hora_temp);
		

		/*
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);
		MessageBox(objeto,"", "" ,  MB_OK);*/
		
		SendMessage(objeto, mensa, 0, (LPARAM)"——————————————————————————————");
		
		aux = aux->sig;
	}

	

};
void LlenaEspecies(HWND objeto, UINT mensa, char *file)
{
	ifstream archi;
	char row[30] = "";
	archi.open(file);
	if (archi.is_open())
	{
		archi.getline(row, 30);
		while (!archi.eof())
		{
			SendMessage(objeto, mensa, 0, (LPARAM)row);
			archi.getline(row, 30);
		}

		archi.close();
	}

}
bool CapturaNodo(HWND Dlg, node*Punt) {
	bool exc = false;
	char mensa[] = "";
	node datitos;
	static HWND hCombo = 0;
	hCombo = GetDlgItem(Dlg, IDC_COMBO1);

	char TextCom[80];
	char NombreClt[80];
	char PhoneClt[80];
	char NombreMas[80];
	char Motiv[150];
	char Dineros[80];
	char fecha_temp[11] = "";

	int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	SendMessage(hCombo, CB_GETLBTEXT, (WPARAM)index, (LPARAM)TextCom);
	SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)NombreClt);
	SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)80, (LPARAM)PhoneClt);
	SendDlgItemMessage(Dlg, IDC_EDIT3, WM_GETTEXT, (WPARAM)80, (LPARAM)NombreMas);
	SendDlgItemMessage(Dlg, IDC_EDIT4, WM_GETTEXT, (WPARAM)150, (LPARAM)Motiv);
	SendDlgItemMessage(Dlg, IDC_EDIT5, WM_GETTEXT, (WPARAM)80, (LPARAM)Dineros);

	SendDlgItemMessage(Dlg, IDC_FECHA, WM_GETTEXT, (WPARAM)11, (LPARAM)fecha_temp);
	SendDlgItemMessage(Dlg, IDC_HORA, WM_GETTEXT, (WPARAM)6, (LPARAM)datitos.time);

	strcpy(datitos.date, ConvierteFecha(fecha_temp));

	
	// AQUI: validar...
	if (exc == true) {
		strcpy(mensa,"favor de capturar nombre\n");
	}
	
	strcpy(datitos.species, TextCom);
	strcpy(datitos.CltName, NombreClt);
	strcpy(datitos.Phone, PhoneClt);
	strcpy(datitos.MasName, NombreMas);
	strcpy(datitos.Motivo, Motiv);
	strcpy(datitos.cost, Dineros);
	if (exc) {
		Punt = 0;
		MessageBox(Dlg,mensa,"  ",MB_OK);
		Punt = &datitos;
	}
	
	return exc;

};
//
//node*BuscarDato(int id)
//{
//	bool siloencontre = false;
//	node*aux;
//	aux = first;
//	ant = 0;
//	while (aux != 0)
//	{
//		if (id == aux->id)
//		{
//			siloencontre = true;
//			break;
//		}
//		ant = aux;
//		aux = aux->next;
//	}
//	if (siloencontre)
//		return aux;
//	else
//		return 0;
//};

char*ConvierteFecha(char*Fecha)
{
	char FechaOk[11] = "";

	string cutMonth, FechaOri;
	cutMonth = Fecha; //Guarda en un string el valor de un char
	string Day = cutMonth.substr(0, 2);
	string Month = cutMonth.substr(3, 2);
	string Year = cutMonth.substr(6, 4);

	FechaOri = Year + Month + Day;
	strcat(FechaOk, FechaOri.c_str());

	return FechaOk;
}



void LeeArchivo()
{
	node info;
	node *pinfo = 0;

	ifstream archivaldo;
	archivaldo.open(file, ios::binary);
	if (archivaldo.is_open())
	{
		// crear la lista ligada
		archivaldo.read((char*)&info, sizeof(node));
		while (!archivaldo.eof())
		{
			AgregaNodo(info);
			archivaldo.read((char*)&info, sizeof(node));
		}
		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}
};

void EscribirArchivo()
{
	node info;
	node *aux = 0, *borrar;;

	ofstream archivaldo;
	archivaldo.open(file, ios::binary | ios::trunc);
	if (archivaldo.is_open())
	{
		// LEER la lista ligada
		aux = inicio;
		while (aux != 0)
		{
			archivaldo.write((char*)aux, sizeof(node));
			borrar = aux;
			aux = aux->sig;
			delete borrar;
		}
		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}


}

void LeeDatos() {

	ifstream aechi;
	aechi.open(_arch_dat);
	if (aechi.is_open()) {
		aechi.getline(_pic,MAX_PATH);




		aechi.getline(_pic2, MAX_PATH);
		/*while (!aechi.eof())
		{
			
			aechi.getline(_pic2, MAX_PATH);
		}
*/

		aechi.close();
	}


}

