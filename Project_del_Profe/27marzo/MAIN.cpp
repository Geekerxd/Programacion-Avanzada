#include <fstream>
#include <Windows.h>
#include "resource.h"

#include <stdio.h>
#include <string.h>

using namespace std;

#define Cero 0

struct node
{
	int		id;
	char	specie[30];
	char	name[30];
	char	date[9];
	char	time[5];
	bool	urgent;
	bool	gender;
	node	*next;
	node	*prev;
};
node*first = Cero, *last = Cero, *prev = Cero, *ant = Cero;
char file[80] = "contactos.txt";
char _arch_esp[] = "spc.txt";


node CapturaNodo(HWND Dlg);
void AgregaNodo(node Datos);
void MostarLista();
node*BuscarDato(int id);

char*ConvierteFecha(char*Fecha);

void LeeArchivo();
void EscribirArchivo();

HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;


BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK ProcDialog2(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam); 
BOOL CALLBACK ProcDialog3(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);

void LlenaEspecies(HWND objeto, UINT mensa, char *file);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{
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


BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	char cliente[20] = "";
	static HWND hCte = 0;

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		hCte = GetDlgItem(Dlg, IDC_EDIT1);
		
		return true; }
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
			//SendMessage(hCte, WM_GETTEXT, 20, (LPARAM)cliente);

			GetWindowText(hCte, cliente, 20);

			MessageBox(Dlg, cliente, "Cecy", MB_OK);
			SetWindowText(hCte, "Nuevo texto");


			return true;
		case ID_VER_MODAL:
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG2), Dlg, ProcDialog2);
			return true;
		case ID_VER_NOMODAL:
			HWND Dialg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG3), Dlg, ProcDialog3);

			ShowWindow(Dialg, _show);

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

BOOL CALLBACK ProcDialog2(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	char cliente[20] = "";
	static HWND hCte = 0;

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		hCte = GetDlgItem(Dlg, IDC_EDIT1);
		SendDlgItemMessage(Dlg, IDC_LIST1, LB_RESETCONTENT, 0, 0);
		LlenaEspecies(GetDlgItem(Dlg, IDC_LIST1), LB_ADDSTRING, _arch_esp);

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
		return true; }
	case WM_DESTROY:
	{return true; }
	}
	return false;
}

BOOL CALLBACK ProcDialog3(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	char cliente[20] = "";
	static HWND hCboSpc = 0;
	node temp;

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		LeeArchivo();
		hCboSpc = GetDlgItem(Dlg, IDC_ESPECIE);
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
		case IDC_ADD:
		{
			temp = CapturaNodo(Dlg);
			AgregaNodo(temp);

			MessageBox(Dlg,"Elemento agregado","Agregar Cita", MB_OK+MB_ICONINFORMATION);

			return true;
		}
		case IDOK:
			DestroyWindow(Dlg);

			return true;
		case IDCANCEL:
			PostQuitMessage(0);
			return true;
		case IDC_ESPECIE:
		{
			/*if (HIWORD(wParam) == CBN_KILLFOCUS)
			{
				MessageBox(Dlg, "SE FUE EL FOCO", "SI SE FUE", MB_YESNOCANCEL);
			}*/

			return true;
		}
		}
		return true; }
	case WM_CLOSE:
	{
		return true; }
	case WM_DESTROY:
	{
		EscribirArchivo();
		return true; }
	}
	return false;
}

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

node CapturaNodo(HWND Dlg) {
	node datitos;
	static HWND hCombo = 0;
	hCombo = GetDlgItem(Dlg, IDC_ESPECIE);
	char Text[80];
	char Nombre[80];
	char fecha_temp[11] = "";

	int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	SendMessage(hCombo, CB_GETLBTEXT, (WPARAM)index, (LPARAM)Text);
	SendDlgItemMessage(Dlg, IDC_NOMBRE,	WM_GETTEXT, (WPARAM)80, (LPARAM)Nombre);
	
	SendDlgItemMessage(Dlg, IDC_FECHA, WM_GETTEXT, (WPARAM)11, (LPARAM)fecha_temp);
	SendDlgItemMessage(Dlg, IDC_HORA, WM_GETTEXT, (WPARAM)6, (LPARAM)datitos.time);

	strcpy(datitos.date, ConvierteFecha(fecha_temp));

	// AQUI: validar...

	datitos.id = 0;
	strcpy(datitos.specie, Text);
	strcpy(datitos.name, Nombre);

	return datitos;
};
void AgregaNodo(node Datos) {
	node*aux = Cero;
	aux = new node;
	aux->next = Cero;
	aux->prev = Cero;
	aux->id = Datos.id;
	strcpy(aux->name, Datos.name);

	if (first == Cero)
	{
		first = aux;
		last = aux;
	}
	else
	{
		last->next = aux;
		aux->prev = last;
		last = aux;
	}
};

void MostarLista() {

	system("cls");
	printf("id\tname\n");
	printf("--------------------------\n");

	node*aux;
	aux = last;
	while (aux != 0)
	{
		printf("%d\t%s\n", aux->id, aux->name);
		//cout << aux->id << "\t" << aux->name << endl;
		aux = aux->prev;
	}

	printf("-- fin de lista\n");

};


node*BuscarDato(int id)
{
	bool siloencontre = false;
	node*aux;
	aux = first;
	ant = 0;
	while (aux != 0)
	{
		if (id == aux->id)
		{
			siloencontre = true;
			break;
		}
		ant = aux;
		aux = aux->next;
	}
	if (siloencontre)
		return aux;
	else
		return 0;
};

void LeeArchivo()
{
	node info;
	node *pinfo = Cero;

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
	node *aux = Cero, *borrar;;

	ofstream archivaldo;
	archivaldo.open(file, ios::binary | ios::trunc);
	if (archivaldo.is_open())
	{
		// LEER la lista ligada
		aux = first;
		while (aux != Cero)
		{
			archivaldo.write((char*)aux, sizeof(node));
			borrar = aux;
			aux = aux->next;
			delete borrar;
		}
		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}


}

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