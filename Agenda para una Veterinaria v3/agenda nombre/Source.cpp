#include <fstream>
#include <Windows.h>
#include "resource.h"
#include <stdio.h>
#include <string.h>

#include <CommDlg.h> //1. #include <CommDlg.h>
#include <iostream>
#include <conio.h>

using namespace std;

OPENFILENAME ofn;


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

	
	bool	gender;        // Género del Animal

	node	*sig;
	node	*ante;
};
	

node *inicio = 0, *last = 0, *prev = 0, *ant = 0, *nuevo;

char file[80]        = "citas.txt";      //Nombre del archivo donde están, de forma binaria, todos todos los datos de las CITAS.
char _arch_esp[]     = "species.txt";    //Nombre del archivo donde estan todos los nombres de las "ESPECIES de la MASCOTAS".
char _arch_dat[]     = "";      //Nombre del archivo donde estan todas las direcciones de las IMAGENES.
char *p;
char _arch_dat2[]     = "Datos2.txt";      //Nombre del archivo donde estan todas las direcciones de las IMAGENES.
char _conta[]        = "contador.txt";          //almacena un contador

//char _pic[MAX_PATH]  =  "" ;             //Variable que almacena la direccion de la imágen 1.
char _pic2[MAX_PATH] =  "";              //Variable que almacena la direccion de la imágen 2.
char Folder[MAX_PATH] = ""; ;


void AgregaNodo    (node Datos);                //en des-uso   
void MostarLista   (HWND objeto, UINT mensa);
void LlenaEspecies (HWND objeto, UINT mensa, char *file);
void PonImagen     (HWND dialog, WPARAM IDC, char *imagen, int m, int n);
bool CapturaNodo   (HWND Dlg, node*Punt);       //en des-uso           //Funcion tipo bool

char szFileName[MAX_PATH] = "";
void openfilename();

char*ConvierteFecha(char*Fecha);                           //Funcion tipo char
//node*BuscarDato(int id);
void icon (HWND Dlg);
int cont = 0;                                              //Contador del número de citas
bool lineas = true;                                        //vanndera se ira por menu principal o ver agenda


int v, w;                                                  //Para el list box GetCursel
char *cad;
bool flag=false;








void LeeArchivo();                                         //Lista con citas
void EscribirArchivo();

void LeeDatos();                                           //Imágenes y contador
void EscribirDatos();

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
BOOL CALLBACK ima          (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);









//*****************************************************************************************************************************
//*****************************************************************************************************************************
//*****************************************************************************************************************************

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{

	LeeArchivo();
	LeeDatos();

	//GetCurrentDirectory(MAX_PATH,Folder);

	_hInst = hInst;
	_show = show;

	ghDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1),0, ProcDialog1);
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
	static HWND hlist = 0;
	switch (Mensaje)
	{
	
	case WM_INITDIALOG:
	{
		icon(Dlg);//icono del perro
		
		hlist = GetDlgItem(Dlg, IDC_LIST_M);
		lineas = true;
		MostarLista(hlist, LB_ADDSTRING);
		

		PonImagen(Dlg, IDC_hi, szFileName, 83, 108);
		PonImagen(Dlg, IDC_bienve, _pic2, 500, 50);

		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			 // Botones de la área del menú principal
		case IDC_BUTTON1: { //Informacion del doctor

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Doc_Inf), Dlg, InfDoc);

			DestroyWindow(Dlg);
			ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
			ShowWindow(ghDlg, _show);

			return true;
		}
		case IDC_BUTTON2: { //Dar de Alta

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_alta), Dlg, Alta);
			DestroyWindow(Dlg);
			//EndDialog(Dlg, 0);
			ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
			ShowWindow(ghDlg, _show);

			return true;
		}
		case IDC_BUTTON3: { //Agenda

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_ver_agenda), Dlg, Ver_Agen);

			DestroyWindow(Dlg);
			ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
			ShowWindow(ghDlg, _show);

			return true;
		}
		case IDC_BUTTON4: { //salir y guardar

			if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
				"Alto",
				MB_YESNO |
				MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
			{
				//MessageBox(Dlg, "Se guardó", "informacion", MB_OK | MB_ICONINFORMATION);
				EscribirArchivo();
				EscribirDatos();  //contador eimagenes
				PostQuitMessage(0);
			}
			else {
				//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
				PostQuitMessage(0);
			}
			return true;
		}

			 // Botones del menú de arriba
		case ID_MENU_INFORMACIONDELDOCTOR: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Doc_Inf), Dlg, InfDoc);
			DestroyWindow(Dlg);
			ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
			ShowWindow(ghDlg, _show);
			return true;
		}
		case ID__DARDEALTA: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_alta), Dlg, Alta);
			DestroyWindow(Dlg);
			ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
			ShowWindow(ghDlg, _show);
			return true;
		}
		case ID__DARDEBAJA: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_baja), Dlg, Baja);
			return true;
		}
		case ID__VERAGENDA: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_ver_agenda), Dlg, Ver_Agen);
			DestroyWindow(Dlg);
			ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
			ShowWindow(ghDlg, _show);
			return true;
		}
		case ID__MODIFICAR_CITA: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_modi_cita), Dlg, Modificar);
			return true;
		}

		case ID_salir: {

					   if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
						   "Alto",
						   MB_YESNO |
						   MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
					   {
						   //MessageBox(Dlg, "Se guardó", "informacion", MB_OK | MB_ICONINFORMATION);
						   EscribirArchivo();
						   EscribirDatos();  //contador
						   PostQuitMessage(0);
					   }
					   else {
						   //MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
						   PostQuitMessage(0);
					   }


					   return true;
		}
			 // éxtras
		case ID_VER_INFORMAION: //éste es "modal"
		
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Ven_Inf), Dlg, informacion);
			return true;
		case ID_ACERCA:         //éste es "NO modal"

			HWND Dialg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_Ven_Ace), Dlg, informacion2);
			ShowWindow(Dialg, _show);
			return true;

		

		}/// fin de "switch (LOWORD(wParam))"
		return true; 
	}/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{

		//if (MessageBox(Dlg,"¿Quieres guardadr los cambios?",
		//	"Alto",
		//	MB_YESNO |
		//	MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
		//{
		//	//MessageBox(Dlg, "Se guardó","informacion",MB_OK | MB_ICONINFORMATION);
		//	EscribirArchivo();

		//	PostQuitMessage(0);
		//}
		//else {  
		//	//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
		//	PostQuitMessage(0); }
		PostQuitMessage(0);
		
		return true; }
	case WM_DESTROY:{return true;}
	}///fin de "switch (Mensaje)"
	return false;
}
BOOL CALLBACK informacion  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{

		PonImagen(Dlg, IDC_hola, szFileName, 83, 108);

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
	
	//char szFile[MAX_PATH];  // buffer for file name



	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		PonImagen(Dlg, IDC_h, szFileName, 83, 108);

		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
	
		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDC_Edi_Inf:

			EndDialog(Dlg, 0);
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_Im), Dlg, ima);
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Doc_Inf), Dlg, InfDoc);




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

			/*
			
				Me quede aquí. Voy agregar el bool gender y hacer validaciones, ademas de poner la foto, y tal vez el filtro
			
			*/



			node *aux = 0;
			aux = new node;
			aux->sig = 0;
			aux->ante = 0;



			/*int index = SendMessage(hCboSpc, CB_GETCURSEL, 0, 0);
			SendMessage(hCboSpc, CB_GETLBTEXT, (WPARAM)index, (LPARAM)aux->species);*/

			SendMessage(hCboSpc, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->species);
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

			MessageBox(Dlg, "Elemento agregado", "Agregar Cita", MB_OK + MB_ICONINFORMATION);
			cont += 1;

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
	static HWND hlist      = 0;
	static HWND HBorrar    = 0;
	static HWND HModificar = 0;
	//int index = 0;


	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{

		HBorrar = GetDlgItem(Dlg, IDC_BUTTON1);
		HModificar = GetDlgItem(Dlg, IDC_BUTTON2);

		hlist = GetDlgItem(Dlg, IDC_LIST1);
		lineas = false;
		MostarLista(hlist, LB_ADDSTRING);
		
		//SendDlgItemMessage(Dlg, IDC_LIST1, LB_RESETCONTENT, 0, 0);

	
		
		

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDOK:
			EndDialog(Dlg, 0);
			return true;
	
		case IDC_BUTTON1: {             //Quitar cita

			v = SendMessage(hlist, LB_GETCURSEL, 0, 0);
			
			if (cont < 5) {
				for (int i = 0; i < cont; i++) {
					if (v == 18 * i) {                  //modificar 18 si agrego datos
						flag = true;
						break;
					}
				}
			
			}
			else {
				for (int i = 0; i < cont; i++) {
					if (v == 17 * i) {                  //modificar 17 si agrego datos
						flag = true;
						break;
					}
				}
			}

			if (flag) {

				v += 7;

				if (v == -1) {
					break;
				}
				else {
					w = SendMessage(hlist, LB_GETTEXTLEN, (WPARAM)v, (LPARAM)cad);




					cad = (char*)malloc(w + 1);
					SendMessage(hlist, LB_GETTEXT, (WPARAM)v, (LPARAM)cad);
					

				}

				//DialogBox(_hInst, MAKEINTRESOURCE(IDD_baja), Dlg, Baja);
			}
			else { MessageBox(Dlg, "Favor de seleccionar una Cita", "Anuncio", MB_ICONEXCLAMATION); }

			flag = false;
			v = -1;
			return true;
		}
		case IDC_BUTTON2: {                                               //Modificar cita
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_modi_cita), Dlg, Modificar);

			return true;
		}


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
BOOL CALLBACK ima          (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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
		case IDC_BUTTON1:
		{
			openfilename();
			if (GetOpenFileName(&ofn) == TRUE) {
				SetWindowText(GetDlgItem(Dlg, IDC_EDIT1), ofn.lpstrFile);
			}
			return true;
		}

		case IDOK:
			EndDialog(Dlg, 0);
			return true;
		case IDCANCEL:
			int opc = MessageBox(0, "¿Esta seguro que desea salir?", "Aviso", MB_ICONINFORMATION + MB_OKCANCEL);
			if (opc == IDOK) {
				EndDialog(Dlg, 0);
			}
			
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
	
	char TextCom    [300]="";
	char NombreClt  [80] ="";
	char PhoneClt   [80] ="";
	char NombreMas  [80] ="";
	char Motiv      [150]="";
	char Dineros    [80] ="";
	char fecha_temp [11] ="";
	char hora_temp  [11] ="";


	//--------------------------------------

	node*aux;
	aux = inicio;
	while (aux != 0)
	{
		

		strcpy(NombreClt, aux->CltName );
		strcpy(TextCom,   aux->species );
		strcpy(PhoneClt,  aux->Phone   );
		strcpy(NombreMas, aux->MasName );
		strcpy(Motiv,     aux->Motivo  );
		strcpy(Dineros,   aux->cost    );
		strcpy(fecha_temp,aux->date    );
		strcpy(hora_temp, aux->time    );


		//Me salen númerons raros como: íííííííííííííííííííííííí. seguramente están en binario

		//MessageBox(objeto, TextCom, "", MB_OK);

		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"——<Seleccionar>——————");
		SendMessage(objeto, mensa, 0, (LPARAM)fecha_temp);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)hora_temp);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)NombreClt);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)PhoneClt);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)TextCom);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)NombreMas);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)Motiv);
		if (!lineas)SendMessage(objeto, mensa, 0, (LPARAM)"");
		SendMessage(objeto, mensa, 0, (LPARAM)Dineros);

		SendMessage(objeto, mensa, 0, (LPARAM)"—————————————————————————————————————————————");

		if (cont < 5) {
			SendMessage(objeto, mensa, 0, (LPARAM)"——————————————————————————————");

		}
		
	/*	MessageBox(ghDlg, aux->CltName, "", MB_OK);
		MessageBox(ghDlg, aux->species, "", MB_OK);
		MessageBox(ghDlg, aux->Phone, "", MB_OK);
		MessageBox(ghDlg, aux->MasName, "", MB_OK);
		MessageBox(ghDlg, aux->Motivo, "", MB_OK);
		MessageBox(ghDlg, aux->cost, "", MB_OK);
		MessageBox(ghDlg, aux->date, "", MB_OK);
		MessageBox(ghDlg, aux->time, "" ,  MB_OK);*/
		
		
		
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
	//node info;
	node *pinfo = 0;

	ifstream archivaldo;
	archivaldo.open(file, ios::binary);  // | ios::trunc
	if (archivaldo.is_open())
	{
		 pinfo = new node;
		archivaldo.read((char*)pinfo, sizeof(node));
		pinfo->ante = 0;
		pinfo->sig= 0;

		while (!archivaldo.eof()) {
			if (inicio == 0)
			{
				inicio = pinfo;
				last = pinfo;
			}
			else
			{
				last->sig = pinfo;
				pinfo->ante = last;

				last = pinfo;
			}

			pinfo = new node;
			archivaldo.read((char*)pinfo, sizeof(node));
			pinfo->ante = 0;
			pinfo->sig = 0;

		}
			//AgregaNodo(info);                                //aqui se acomoda el nodo en la lista ligada
			//archivaldo.read((char*)&info, sizeof(node));
		
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


	char c[10]="";

	//GetCurrentDirectory(MAX_PATH, szFileName);
	
	ifstream uno;
	uno.open("Datos3.txt", ios::in);
	if (uno.is_open()) {

		uno.getline(Folder, MAX_PATH);


		uno.close();
	}

	strcpy(_arch_dat, Folder);
	
	ifstream a;
	a.open(_arch_dat,ios::in);
	if (a.is_open()) {
		a.getline(szFileName, MAX_PATH);//szFileName

		
		a.close();
	}

	ifstream aechi02;
	aechi02.open(_conta, ios::in);
	if (aechi02.is_open()) {
		

		aechi02.getline(c, 10);
		cont = atoi(c);


		aechi02.close();
	}

	ifstream aechi3;
	aechi3.open(_arch_dat2, ios::in);
	if (aechi3.is_open()) {
		
		aechi3.getline(_pic2, MAX_PATH);
		



		aechi3.close();
	}


}

void EscribirDatos() {


	char c[10] = "";
	_itoa(cont, c, 10);

	//GetCurrentDirectory(MAX_PATH, _arch_dat);
	

	ofstream aechi;
	aechi.open(Folder, ios::out);
	if (aechi.is_open()) {


		aechi.write(szFileName, MAX_PATH);//szFileName
		
		
		aechi.close();
	}



	ofstream aechi02;
	aechi02.open(_conta, ios::out| ios::trunc);
	if (aechi02.is_open()) {
		
		aechi02.write(c, 10);           //este es el contador de citas


		aechi02.close();
	}
	/*ofstream aechi3;
	aechi3.open(_arch_dat2, ios::out);
	if (aechi3.is_open()) {
		aechi3.write(_pic2, MAX_PATH);

		aechi3.close();
	}*/


}

void icon (HWND Dlg) {
	HICON newSmallIco, newBigIco, oldSmallIco, oldBigIco;
	newSmallIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Icon_Dog.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
	newBigIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Icon_Dog.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
	oldSmallIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(newSmallIco)));
	oldBigIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(newBigIco)));
}
void openfilename() {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Todos\0*.*\0Archivos Texto\0*.TXT\0Archivos Word (97-2003)\0*.doc\0Archivos Word\0*.docx\0Imagenes jpg\0*.jpg\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; 
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST |
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = "txt";


	//if (GetSaveFileName(&ofn))
	//{
	//	// Do something usefull with the filename stored in szFileName
	//	MessageBox(ghDlg, ofn.lpstrFile, ofn.lpstrFile, MB_OK);

	//}
}