#include <fstream>
#include <Windows.h>
#include "resource.h"
#include <stdio.h>
#include <string.h>

#include <commdlg.h> //1. 

using namespace std;



struct node
{
	char	date[11];      // Fecha
	char	time[9];       // Hora
	char	CltName[30];   // Nombre del Cliente
	char	Phone[13];     // Teléfono del contacto
	char	species[30];   // Especie de la mascota
	char	MasName[30];   // Nombre de la mascota
	char	Motivo[150];   // Motivo de la consulta
	char	cost[10];      // Costo de la Consulta

	//bool	urgent;
	//bool	gender;

	node	*sig;
	node	*ante;
};
	

node *inicio = 0, *last = 0, *prev = 0, *ant = 0, *nuevo;

char file[80]        = "citas.txt";      //Nombre del archivo donde están, de forma binaria, todos todos los datos de las CITAS.
char _arch_esp[]     = "species.txt";    //Nombre del archivo donde estan todos los nombres de las "ESPECIES de la MASCOTAS".
char _arch_dat[]     = "Datos.txt";      //Nombre del archivo donde estan todas las direcciones de las IMAGENES.

char _pic[MAX_PATH]  =  "" ;             //Variable que almacena la direccion de la imágen 1.
char _pic2[MAX_PATH] =  "";              //Variable que almacena la direccion de la imágen 2.


void AgregaNodo    (node Datos);
void MostarLista   (HWND objeto, UINT mensa);
void LlenaEspecies (HWND objeto, UINT mensa, char *file);
void PonImagen     (HWND dialog, WPARAM IDC, char *imagen, int m, int n);
bool CapturaNodo   (HWND Dlg, node*Punt);                  //Funcion tipo bool

char*ConvierteFecha(char*Fecha);                           //Funcion tipo char
//node*BuscarDato(int id);





void LeeArchivo();
void EscribirArchivo();

void LeeDatos();                                           //imágenes

HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;


BOOL CALLBACK ProcDialog1  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK informacion  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK informacion2 (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK InfDoc       (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Alta         (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Baja         (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Ver_Agen     (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Modificar    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);









//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{

	LeeArchivo();
	LeeDatos();



	_hInst = hInst;
	_show = show;

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
	
	return (int)msg.wParam;
}

//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************






BOOL CALLBACK ProcDialog1  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		PonImagen(Dlg, IDC_hi, _pic, 83, 108);
		PonImagen(Dlg, IDC_bienve, _pic2, 500, 50);

		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			//botones de la área del menú principal
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

			if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
				"Alto",
				MB_YESNO |
				MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
			{
				//MessageBox(Dlg, "Se guardó", "informacion", MB_OK | MB_ICONINFORMATION);
				EscribirArchivo();

				PostQuitMessage(0);
			}
			else {
				//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
				PostQuitMessage(0);
			}
			return true;


			//botones del menú de arriba
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

			if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
				"Alto",
				MB_YESNO |
				MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
			{
				//MessageBox(Dlg, "Se guardó", "informacion", MB_OK | MB_ICONINFORMATION);
				EscribirArchivo();

				PostQuitMessage(0);
			}
			else {
				//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
				PostQuitMessage(0);
			}


			return true;

			//éxtras
		case ID_VER_INFORMAION: //éste es "modal"
		
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Ven_Inf), Dlg, informacion);//Mismo callback informacion
			return true;
		case ID_ACERCA:         //éste es "NO modal"
			HWND Dialg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_Ven_Ace), Dlg, informacion2);

			ShowWindow(Dialg, _show);

			return true;

		

		}// fin de "switch (LOWORD(wParam))"
		return true; 
	}// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{

		if (MessageBox(Dlg,"¿Quieres guardadr los cambios?",
			"Alto",
			MB_YESNO |
			MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
		{
			//MessageBox(Dlg, "Se guardó","informacion",MB_OK | MB_ICONINFORMATION);
			EscribirArchivo();

			PostQuitMessage(0);
		}
		else {  
			//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
			PostQuitMessage(0); }

		
		return true; }
	case WM_DESTROY:{return true;}
	}//fin de "switch (Mensaje)"
	return false;
}
BOOL CALLBACK informacion  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{

		PonImagen(Dlg, IDC_hola, _pic, 83, 108);

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
BOOL CALLBACK informacion2 (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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
BOOL CALLBACK InfDoc       (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		PonImagen(Dlg, IDC_h, _pic, 83, 108);

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
BOOL CALLBACK Alta         (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	static HWND hCboSpc = 0; //handle conbo box species

	char cliente[20] = "";

	node temp;
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		
		hCboSpc = GetDlgItem(Dlg, IDC_COMBO1);
		LlenaEspecies(hCboSpc, CB_ADDSTRING, _arch_esp);


		//El "hCboSpc"==="hCombo"  //esto es temporal
		
		
		return true; 
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL: {

					   /*if (MessageBox(Dlg, "¿Quieres salir sin agregar cita?","Alto",MB_YESNO |MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
					   {EndDialog(Dlg, 0);}else {}*/
					   EndDialog(Dlg, 0);
					   return true;
		}
		case IDC_AGREGAR:

			node *aux = 0;
			aux = new node;
			aux->sig = 0;
			aux->ante = 0;



			int index = SendMessage(hCboSpc, CB_GETCURSEL, 0, 0);
			SendMessage(hCboSpc, CB_GETLBTEXT, (WPARAM)index, (LPARAM)aux->species);
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->CltName);
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->Phone);
			SendDlgItemMessage(Dlg, IDC_EDIT3, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->MasName);
			SendDlgItemMessage(Dlg, IDC_EDIT4, WM_GETTEXT, (WPARAM)150, (LPARAM)aux->Motivo);
			SendDlgItemMessage(Dlg, IDC_EDIT5, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->cost);

			SendDlgItemMessage(Dlg, IDC_FECHA, WM_GETTEXT, (WPARAM)11, (LPARAM)aux->date);
			SendDlgItemMessage(Dlg, IDC_HORA, WM_GETTEXT, (WPARAM)6, (LPARAM)aux->time);


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

			//delete aux;

			//if (CapturaNodo(Dlg, &temp) == false){                                                 //todo esto es por las validaciones
			//AgregaNodo(temp);


			//MessageBox(Dlg, "Elemento agregado", "Agregar Cita", MB_OK + MB_ICONINFORMATION);      // Esto pasa cada vez que presiono el botón de agregar.
			//}
			//else{MessageBox(Dlg, "No se pudo abrir", "hmmm", MB_OK + MB_ICONINFORMATION);}

			////                                                                                        <<< Esto haría mas o menos lo mismo: >>>
			////CapturaNodo(Dlg,temp);                                                               << Primero se guardan los datos en el nodo                    >>
			////AgregaNodo(temp);                                                                    << Después el nodo es acomodado en la lista doblemente ligada >>

			////MessageBox(Dlg, "Elemento agregado", "Agregar Cita", MB_OK + MB_ICONINFORMATION);



			return true;    ///FIN de "case IDC_AGREGAR"
		}///FIN del switch (LOWORD(wParam))
		return true;
	}///FIN del case WM_COMMAND:
	case WM_CLOSE:
	{
		/*if (MessageBox(Dlg, "¿Quieres salir sin agregar cita?", "Alto", MB_YESNO | MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
		{
			EndDialog(Dlg, 0);
		}
		else {}*/
		EndDialog(Dlg, 0);
		return true; }
	case WM_DESTROY:
	{
		
	return true; }
	}//fin del switch (Mensaje)

	return false;
}
BOOL CALLBACK Baja         (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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
BOOL CALLBACK Ver_Agen     (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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
BOOL CALLBACK Modificar    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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



void PonImagen     (HWND dialog, WPARAM IDC, char *imagen,int m, int n) {

	static HBITMAP bmp1, bmp2;
	//Al objeto bmp1, se le asigna sin imagen:
	bmp1 = (HBITMAP)SendDlgItemMessage(dialog, IDC,
		STM_GETIMAGE, IMAGE_BITMAP, 0);
	//Al objeto bmp2, se le asigna una imagen local:
	bmp2 = (HBITMAP)LoadImage(NULL, imagen,
		IMAGE_BITMAP, m, n, LR_LOADFROMFILE);

	SendDlgItemMessage(
		dialog,
		IDC,
		STM_SETIMAGE,
		IMAGE_BITMAP,
		(LPARAM)bmp2);

}

bool CapturaNodo(HWND Dlg, node*Punt) {
	bool exc = false;
	char mensa[] = "";
	node datitos = *Punt;        //esto era el problema?
	static HWND hCombo = 0;
	hCombo = GetDlgItem(Dlg, IDC_COMBO1);

	char TextCom[80];    //bombo box
	char NombreClt[80];  //nombre del cliente
	char PhoneClt[80];   //telefono
	char NombreMas[80];  //nombre de la mascota
	char Motiv[150];     //
	char Dineros[80];    //
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
		strcpy(mensa, "favor de capturar nombre\n");
	}

	strcpy(datitos.species, TextCom);
	strcpy(datitos.CltName, NombreClt);
	strcpy(datitos.Phone, PhoneClt);
	strcpy(datitos.MasName, NombreMas);
	strcpy(datitos.Motivo, Motiv);
	strcpy(datitos.cost, Dineros);

	if (exc) {     //tene que pasar por aqui??
		Punt = 0;
		MessageBox(Dlg, mensa, "  ", MB_OK);
		Punt = &datitos;
	}

	return exc;

};
void AgregaNodo    (node Datos) {
	//ME QUEDÉ AQUÍ REVISANDO // ya no
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

void MostarLista   (HWND objeto, UINT mensa) {
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
		
		//SendMessage(objeto, mensa, 0, (LPARAM)"——————————————————————————————");
		
		aux = aux->sig;
	}

	

};
void LlenaEspecies (HWND objeto, UINT mensa, char *file)
{
	// objeto  ===   hCboSpc
	// mensa   ===   CB_ADDSTRING
	// file    ===   _arch_esp

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
			AgregaNodo(info);                                //aqui se acomoda el nodo en la lista ligada
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

