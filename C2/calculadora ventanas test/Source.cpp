#include <Windows.h>
#include "resource.h"
#include <iostream>
#include <winuser.h>

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <math.h>
struct todaslash { HWND A[10]; }static HA[10], SHA[10], SHAR[10];

//**************************

using namespace std;

HWND ghDlg = 0;
HINSTANCE _ghInst;
int _gShow = 0;

BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
void handels(HWND);


void desactivarA(); void desactivarB(); void desactivarR(); 
void activarA(string, string); void activarB(string, string); void activarR(string, string);

void leerA(HWND h); void leerB(HWND h); void leerA_deci(HWND h); void leerB_deci(HWND h); void R_TO_A_deci(HWND h);
void EscribriResultado(HWND h); void EscribriResultado_con_decilames(HWND h);
void borrarA(HWND h); void borrarB(HWND h); void borrarR(HWND h);
float matrixA[10][10];
float matrixB[10][10];
float result[10][10];

int a1 = 0;
int a2 = 0;

int b1 = 0;
int b2 = 0;

char A1[10] = "";
char A2[10] = "";
char B1[10] = "";
char B2[10] = "";

BOOL flag = 0;
BOOL flag_aux = 0;

void Multiplicar(HWND h);
void Suma(HWND h);
void Resta(HWND h);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{

	_ghInst = hInst;
	_gShow = show;
	ghDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
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
	static HWND hE_A1 = 0;  //
	static HWND hE_A2 = 0;  //
							 //
	static HWND hE_B1 = 0;  //
	static HWND hE_B2 = 0;  //



	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		handels(Dlg);
		desactivarA(); desactivarB(); desactivarR();
		
		

		

		hE_A1 = GetDlgItem(Dlg, IDC_EDIT_A1);
		hE_A2 = GetDlgItem(Dlg, IDC_EDIT_A2);

		hE_B1 = GetDlgItem(Dlg, IDC_EDIT_B1);
		hE_B2 = GetDlgItem(Dlg, IDC_EDIT_B2);

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_ACEPTAR_1: {
			desactivarA();
			

			SendMessage(hE_A1, WM_GETTEXT, 10, (LPARAM)A1); a1 = atoi(A1);
			SendMessage(hE_A2, WM_GETTEXT, 10, (LPARAM)A2); a2 = atoi(A2);
			//...
			if (a1>=1 && a1 <= 10 && a2>=1 && a2 <= 10) {
				borrarA(Dlg);
				activarA(A1, A2);
			}
			else { MessageBox(Dlg, "el numero de filas y columnas tienen que ser mayor o igual a 1, o menor o igual a 10 ", "Advertencia", MB_ICONWARNING); }

			

			return true; }
		case IDC_ACEPTAR_2: {
			desactivarB();
			
			SendMessage(hE_B1, WM_GETTEXT, 10, (LPARAM)B1); b1 = atoi(B1);
			SendMessage(hE_B2, WM_GETTEXT, 10, (LPARAM)B2); b2 = atoi(B2);
			//...
			if (b1 >= 1 && b1 <= 10 && b2 >= 1 && b2 <= 10) {
				borrarB(Dlg);
				activarB(B1, B2);
			}
			else { MessageBox(Dlg, "el numero de filas y columnas tienen que ser mayor o igual a 1, o menor o igual a 10 ", "Advertencia", MB_ICONWARNING); }

			return true; }
		case IDC_MULTIPLICACION: {
			desactivarR();
			borrarR(Dlg);
			//...
			if (a2 == b1) {
				activarR(A1, B2);
				flag = 1;
			}
			else { MessageBox(Dlg, "El tamaño de la Columna 1 y fila 2 deben de coincidir", "Advertencia", MB_ICONWARNING); }


			if (flag == 1) {
				flag_aux = 1;
				leerA(Dlg);
				leerB(Dlg);

				Multiplicar(Dlg);
				//Aquí multiplica...
				flag_aux = 0;
			}

			flag = 0;
			return true;
		}
		case IDC_MULT_DEC: {
			desactivarR();
			borrarR(Dlg);
			//...
			if (a2 == b1) {
				activarR(A1, B2);

				flag = 1;
			}
			else { MessageBox(Dlg, "El tamaño de la Columna 1 y fila 2 deben de coincidir", "Advertencia", MB_ICONWARNING); }


			if (flag == 1) {
				leerA_deci(Dlg);
				leerB_deci(Dlg);

				Multiplicar(Dlg);
				//Aquí multiplica...
			}

			flag = 0;
			return true;
		}
		case IDC_SUMA: {
			
			desactivarR();
			borrarR(Dlg);
			//...
			if (a1 == b1 && a2==b2) {
				activarR(A2, B1);
				flag = 1;
			}
			else { MessageBox(Dlg, "El número filas y columas de mas matrices A y B deben ser iguales.", "Advertencia", MB_ICONWARNING); }


			if (flag == 1) {
				flag_aux = 1;
				leerA(Dlg);
				leerB(Dlg);

				Suma(Dlg);
				//Aquí Suma...
				flag_aux = 0;
			}
			
			
			
			flag = 0;
			return true; }
		case IDC_SUMA_DEC: {
			desactivarR();
			borrarR(Dlg);
			//...
			if (a1 == b1 && a2 == b2) {
				activarR(A2, B1);
				flag = 1;
			}
			else { MessageBox(Dlg, "El número filas y columas de mas matrices A y B deben ser iguales.", "Advertencia", MB_ICONWARNING); }


			if (flag == 1) {
				
				leerA_deci(Dlg);
				leerB_deci(Dlg);

				Suma(Dlg);
				//Aquí Suma...
				
			}



			flag = 0;
			return true; }
		case IDC_RESTA: {

			desactivarR();
			borrarR(Dlg);
			//...
			if (a1 == b1 && a2 == b2) {
				activarR(A2, B1);
				flag = 1;
			}
			else { MessageBox(Dlg, "El número filas y columas de mas matrices A y B deben ser iguales.", "Advertencia", MB_ICONWARNING); }


			if (flag == 1) {
				flag_aux = 1;
				leerA(Dlg);
				leerB(Dlg);

				Resta(Dlg);
				//Aquí Suma...
				flag_aux = 0;
			}



			flag = 0;

			return true; }
		case IDC_RESTA_DEC: {
			desactivarR();
			borrarR(Dlg);
			//...
			if (a1 == b1 && a2 == b2) {
				activarR(A2, B1);
				flag = 1;
			}
			else { MessageBox(Dlg, "El número filas y columas de mas matrices A y B deben ser iguales.", "Advertencia", MB_ICONWARNING); }


			if (flag == 1) {

				leerA_deci(Dlg);
				leerB_deci(Dlg);

				Resta(Dlg);
				//Aquí Suma...

			}



			flag = 0;


			return true; }



		case IDC_R_TO_A: {

			desactivarA();
			activarA(A1, B2);
			SetWindowText(hE_A1, A1);
			SetWindowText(hE_A2, B2);
			a1 = atoi(A1);
			a2 = atoi(B2);

			R_TO_A_deci(Dlg);
			
			borrarB(Dlg);
			borrarR(Dlg);

			
			desactivarR();
			
			return true;}



		case ID_ARCHIVO_SALIR40013:{PostQuitMessage(0);return true; }
		}//fin del switch (LOWORD(wParam))
		return true;
 
	}
	case WM_CLOSE: {PostQuitMessage(0); return true; }
	case WM_DESTROY: {return true; }

     
	}//fin del switch (Mensaje)


	return false;
}
void leerA(HWND h) {
	    char A_11	 [10]="";
		char A_12	 [10]="";
		char A_13	 [10]="";
		char A_14	 [10]="";
		char A_15	 [10]="";
		char A_16	 [10]="";
		char A_17	 [10]="";
		char A_18	 [10]="";
		char A_19	 [10]="";
		char A_110	 [10]="";
		char A_21	 [10]="";
		char A_22	 [10]="";
		char A_23	 [10]="";
		char A_24	 [10]="";
		char A_25	 [10]="";
		char A_26	 [10]="";
		char A_27	 [10]="";
		char A_28	 [10]="";
		char A_29	 [10]="";
		char A_210	 [10]="";
		char A_31	 [10]="";
		char A_32	 [10]="";
		char A_33	 [10]="";
		char A_34	 [10]="";
		char A_35	 [10]="";
		char A_36	 [10]="";
		char A_37	 [10]="";
		char A_38	 [10]="";
		char A_39	 [10]="";
		char A_310	 [10]="";
		char A_41	 [10]="";
		char A_42	 [10]="";
		char A_43	 [10]="";
		char A_44	 [10]="";
		char A_45	 [10]="";
		char A_46	 [10]="";
		char A_47	 [10]="";
		char A_48	 [10]="";
		char A_49	 [10]="";
		char A_410	 [10]="";
		char A_51	 [10]="";
		char A_52	 [10]="";
		char A_53	 [10]="";
		char A_54	 [10]="";
		char A_55	 [10]="";
		char A_56	 [10]="";
		char A_57	 [10]="";
		char A_58	 [10]="";
		char A_59	 [10]="";
		char A_510	 [10]="";
		char A_61	 [10]="";
		char A_62	 [10]="";
		char A_63	 [10]="";
		char A_64	 [10]="";
		char A_65	 [10]="";
		char A_66	 [10]="";
		char A_67	 [10]="";
		char A_68	 [10]="";
		char A_69	 [10]="";
		char A_610	 [10]="";
		char A_71	 [10]="";
		char A_72	 [10]="";
		char A_73	 [10]="";
		char A_74	 [10]="";
		char A_75	 [10]="";
		char A_76	 [10]="";
		char A_77	 [10]="";
		char A_78	 [10]="";
		char A_79	 [10]="";
		char A_710	 [10]="";
		char A_81	 [10]="";
		char A_82	 [10]="";
		char A_83	 [10]="";
		char A_84	 [10]="";
		char A_85	 [10]="";
		char A_86	 [10]="";
		char A_87	 [10]="";
		char A_88	 [10]="";
		char A_89	 [10]="";
		char A_810	 [10]="";
		char A_91	 [10]="";
		char A_92	 [10]="";
		char A_93	 [10]="";
		char A_94	 [10]="";
		char A_95	 [10]="";
		char A_96	 [10]="";
		char A_97	 [10]="";
		char A_98	 [10]="";
		char A_99	 [10]="";
		char A_910	 [10]="";
		char A_101	 [10]="";
		char A_102	 [10]="";
		char A_103	 [10]="";
		char A_104	 [10]="";
		char A_105	 [10]="";
		char A_106	 [10]="";
		char A_107	 [10]="";
		char A_108	 [10]="";
		char A_109	 [10]="";
		char A_1010	 [10]="";


	SendMessage(GetDlgItem(h, IDC_EDIT_A_11  ), WM_GETTEXT, 10, (LPARAM)A_11  ); matrixA[0 ][0  ] = atoi(A_11   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_12  ), WM_GETTEXT, 10, (LPARAM)A_12  ); matrixA[0 ][1  ] = atoi(A_12   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_13  ), WM_GETTEXT, 10, (LPARAM)A_13  ); matrixA[0 ][2  ] = atoi(A_13   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_14  ), WM_GETTEXT, 10, (LPARAM)A_14  ); matrixA[0 ][3  ] = atoi(A_14   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_15  ), WM_GETTEXT, 10, (LPARAM)A_15  ); matrixA[0 ][4  ] = atoi(A_15   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_16  ), WM_GETTEXT, 10, (LPARAM)A_16  ); matrixA[0 ][5  ] = atoi(A_16   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_17  ), WM_GETTEXT, 10, (LPARAM)A_17  ); matrixA[0 ][6  ] = atoi(A_17   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_18  ), WM_GETTEXT, 10, (LPARAM)A_18  ); matrixA[0 ][7  ] = atoi(A_18   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_19  ), WM_GETTEXT, 10, (LPARAM)A_19  ); matrixA[0 ][8  ] = atoi(A_19   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_110 ), WM_GETTEXT, 10, (LPARAM)A_110 ); matrixA[0 ][9  ] = atoi(A_110  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_21  ), WM_GETTEXT, 10, (LPARAM)A_21  ); matrixA[1 ][0  ] = atoi(A_21   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_22  ), WM_GETTEXT, 10, (LPARAM)A_22  ); matrixA[1 ][1  ] = atoi(A_22   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_23  ), WM_GETTEXT, 10, (LPARAM)A_23  ); matrixA[1 ][2  ] = atoi(A_23   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_24  ), WM_GETTEXT, 10, (LPARAM)A_24  ); matrixA[1 ][3  ] = atoi(A_24   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_25  ), WM_GETTEXT, 10, (LPARAM)A_25  ); matrixA[1 ][4  ] = atoi(A_25   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_26  ), WM_GETTEXT, 10, (LPARAM)A_26  ); matrixA[1 ][5  ] = atoi(A_26   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_27  ), WM_GETTEXT, 10, (LPARAM)A_27  ); matrixA[1 ][6  ] = atoi(A_27   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_28  ), WM_GETTEXT, 10, (LPARAM)A_28  ); matrixA[1 ][7  ] = atoi(A_28   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_29  ), WM_GETTEXT, 10, (LPARAM)A_29  ); matrixA[1 ][8  ] = atoi(A_29   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_210 ), WM_GETTEXT, 10, (LPARAM)A_210 ); matrixA[1 ][9  ] = atoi(A_210  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_31  ), WM_GETTEXT, 10, (LPARAM)A_31  ); matrixA[2 ][0  ] = atoi(A_31   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_32  ), WM_GETTEXT, 10, (LPARAM)A_32  ); matrixA[2 ][1  ] = atoi(A_32   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_33  ), WM_GETTEXT, 10, (LPARAM)A_33  ); matrixA[2 ][2  ] = atoi(A_33   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_34  ), WM_GETTEXT, 10, (LPARAM)A_34  ); matrixA[2 ][3  ] = atoi(A_34   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_35  ), WM_GETTEXT, 10, (LPARAM)A_35  ); matrixA[2 ][4  ] = atoi(A_35   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_36  ), WM_GETTEXT, 10, (LPARAM)A_36  ); matrixA[2 ][5  ] = atoi(A_36   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_37  ), WM_GETTEXT, 10, (LPARAM)A_37  ); matrixA[2 ][6  ] = atoi(A_37   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_38  ), WM_GETTEXT, 10, (LPARAM)A_38  ); matrixA[2 ][7  ] = atoi(A_38   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_39  ), WM_GETTEXT, 10, (LPARAM)A_39  ); matrixA[2 ][8  ] = atoi(A_39   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_310 ), WM_GETTEXT, 10, (LPARAM)A_310 ); matrixA[2 ][9  ] = atoi(A_310  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_41  ), WM_GETTEXT, 10, (LPARAM)A_41  ); matrixA[3 ][0  ] = atoi(A_41   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_42  ), WM_GETTEXT, 10, (LPARAM)A_42  ); matrixA[3 ][1  ] = atoi(A_42   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_43  ), WM_GETTEXT, 10, (LPARAM)A_43  ); matrixA[3 ][2  ] = atoi(A_43   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_44  ), WM_GETTEXT, 10, (LPARAM)A_44  ); matrixA[3 ][3  ] = atoi(A_44   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_45  ), WM_GETTEXT, 10, (LPARAM)A_45  ); matrixA[3 ][4  ] = atoi(A_45   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_46  ), WM_GETTEXT, 10, (LPARAM)A_46  ); matrixA[3 ][5  ] = atoi(A_46   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_47  ), WM_GETTEXT, 10, (LPARAM)A_47  ); matrixA[3 ][6  ] = atoi(A_47   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_48  ), WM_GETTEXT, 10, (LPARAM)A_48  ); matrixA[3 ][7  ] = atoi(A_48   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_49  ), WM_GETTEXT, 10, (LPARAM)A_49  ); matrixA[3 ][8  ] = atoi(A_49   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_410 ), WM_GETTEXT, 10, (LPARAM)A_410 ); matrixA[3 ][9  ] = atoi(A_410  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_51  ), WM_GETTEXT, 10, (LPARAM)A_51  ); matrixA[4 ][0  ] = atoi(A_51   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_52  ), WM_GETTEXT, 10, (LPARAM)A_52  ); matrixA[4 ][1  ] = atoi(A_52   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_53  ), WM_GETTEXT, 10, (LPARAM)A_53  ); matrixA[4 ][2  ] = atoi(A_53   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_54  ), WM_GETTEXT, 10, (LPARAM)A_54  ); matrixA[4 ][3  ] = atoi(A_54   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_55  ), WM_GETTEXT, 10, (LPARAM)A_55  ); matrixA[4 ][4  ] = atoi(A_55   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_56  ), WM_GETTEXT, 10, (LPARAM)A_56  ); matrixA[4 ][5  ] = atoi(A_56   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_57  ), WM_GETTEXT, 10, (LPARAM)A_57  ); matrixA[4 ][6  ] = atoi(A_57   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_58  ), WM_GETTEXT, 10, (LPARAM)A_58  ); matrixA[4 ][7  ] = atoi(A_58   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_59  ), WM_GETTEXT, 10, (LPARAM)A_59  ); matrixA[4 ][8  ] = atoi(A_59   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_510 ), WM_GETTEXT, 10, (LPARAM)A_510 ); matrixA[4 ][9  ] = atoi(A_510  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_61  ), WM_GETTEXT, 10, (LPARAM)A_61  ); matrixA[5 ][0  ] = atoi(A_61   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_62  ), WM_GETTEXT, 10, (LPARAM)A_62  ); matrixA[5 ][1  ] = atoi(A_62   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_63  ), WM_GETTEXT, 10, (LPARAM)A_63  ); matrixA[5 ][2  ] = atoi(A_63   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_64  ), WM_GETTEXT, 10, (LPARAM)A_64  ); matrixA[5 ][3  ] = atoi(A_64   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_65  ), WM_GETTEXT, 10, (LPARAM)A_65  ); matrixA[5 ][4  ] = atoi(A_65   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_66  ), WM_GETTEXT, 10, (LPARAM)A_66  ); matrixA[5 ][5  ] = atoi(A_66   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_67  ), WM_GETTEXT, 10, (LPARAM)A_67  ); matrixA[5 ][6  ] = atoi(A_67   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_68  ), WM_GETTEXT, 10, (LPARAM)A_68  ); matrixA[5 ][7  ] = atoi(A_68   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_69  ), WM_GETTEXT, 10, (LPARAM)A_69  ); matrixA[5 ][8  ] = atoi(A_69   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_610 ), WM_GETTEXT, 10, (LPARAM)A_610 ); matrixA[5 ][9  ] = atoi(A_610  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_71  ), WM_GETTEXT, 10, (LPARAM)A_71  ); matrixA[6 ][0  ] = atoi(A_71   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_72  ), WM_GETTEXT, 10, (LPARAM)A_72  ); matrixA[6 ][1  ] = atoi(A_72   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_73  ), WM_GETTEXT, 10, (LPARAM)A_73  ); matrixA[6 ][2  ] = atoi(A_73   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_74  ), WM_GETTEXT, 10, (LPARAM)A_74  ); matrixA[6 ][3  ] = atoi(A_74   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_75  ), WM_GETTEXT, 10, (LPARAM)A_75  ); matrixA[6 ][4  ] = atoi(A_75   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_76  ), WM_GETTEXT, 10, (LPARAM)A_76  ); matrixA[6 ][5  ] = atoi(A_76   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_77  ), WM_GETTEXT, 10, (LPARAM)A_77  ); matrixA[6 ][6  ] = atoi(A_77   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_78  ), WM_GETTEXT, 10, (LPARAM)A_78  ); matrixA[6 ][7  ] = atoi(A_78   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_79  ), WM_GETTEXT, 10, (LPARAM)A_79  ); matrixA[6 ][8  ] = atoi(A_79   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_710 ), WM_GETTEXT, 10, (LPARAM)A_710 ); matrixA[6 ][9  ] = atoi(A_710  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_81  ), WM_GETTEXT, 10, (LPARAM)A_81  ); matrixA[7 ][0  ] = atoi(A_81   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_82  ), WM_GETTEXT, 10, (LPARAM)A_82  ); matrixA[7 ][1  ] = atoi(A_82   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_83  ), WM_GETTEXT, 10, (LPARAM)A_83  ); matrixA[7 ][2  ] = atoi(A_83   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_84  ), WM_GETTEXT, 10, (LPARAM)A_84  ); matrixA[7 ][3  ] = atoi(A_84   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_85  ), WM_GETTEXT, 10, (LPARAM)A_85  ); matrixA[7 ][4  ] = atoi(A_85   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_86  ), WM_GETTEXT, 10, (LPARAM)A_86  ); matrixA[7 ][5  ] = atoi(A_86   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_87  ), WM_GETTEXT, 10, (LPARAM)A_87  ); matrixA[7 ][6  ] = atoi(A_87   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_88  ), WM_GETTEXT, 10, (LPARAM)A_88  ); matrixA[7 ][7  ] = atoi(A_88   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_89  ), WM_GETTEXT, 10, (LPARAM)A_89  ); matrixA[7 ][8  ] = atoi(A_89   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_810 ), WM_GETTEXT, 10, (LPARAM)A_810 ); matrixA[7 ][9  ] = atoi(A_810  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_91  ), WM_GETTEXT, 10, (LPARAM)A_91  ); matrixA[8 ][0  ] = atoi(A_91   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_92  ), WM_GETTEXT, 10, (LPARAM)A_92  ); matrixA[8 ][1  ] = atoi(A_92   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_93  ), WM_GETTEXT, 10, (LPARAM)A_93  ); matrixA[8 ][2  ] = atoi(A_93   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_94  ), WM_GETTEXT, 10, (LPARAM)A_94  ); matrixA[8 ][3  ] = atoi(A_94   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_95  ), WM_GETTEXT, 10, (LPARAM)A_95  ); matrixA[8 ][4  ] = atoi(A_95   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_96  ), WM_GETTEXT, 10, (LPARAM)A_96  ); matrixA[8 ][5  ] = atoi(A_96   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_97  ), WM_GETTEXT, 10, (LPARAM)A_97  ); matrixA[8 ][6  ] = atoi(A_97   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_98  ), WM_GETTEXT, 10, (LPARAM)A_98  ); matrixA[8 ][7  ] = atoi(A_98   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_99  ), WM_GETTEXT, 10, (LPARAM)A_99  ); matrixA[8 ][8  ] = atoi(A_99   );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_910 ), WM_GETTEXT, 10, (LPARAM)A_910 ); matrixA[8 ][9  ] = atoi(A_910  );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_101 ), WM_GETTEXT, 10, (LPARAM)A_101 ); matrixA[9 ][0  ] = atoi(A_101  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_102 ), WM_GETTEXT, 10, (LPARAM)A_102 ); matrixA[9 ][1  ] = atoi(A_102  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_103 ), WM_GETTEXT, 10, (LPARAM)A_103 ); matrixA[9 ][2  ] = atoi(A_103  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_104 ), WM_GETTEXT, 10, (LPARAM)A_104 ); matrixA[9 ][3  ] = atoi(A_104  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_105 ), WM_GETTEXT, 10, (LPARAM)A_105 ); matrixA[9 ][4  ] = atoi(A_105  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_106 ), WM_GETTEXT, 10, (LPARAM)A_106 ); matrixA[9 ][5  ] = atoi(A_106  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_107 ), WM_GETTEXT, 10, (LPARAM)A_107 ); matrixA[9 ][6  ] = atoi(A_107  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_108 ), WM_GETTEXT, 10, (LPARAM)A_108 ); matrixA[9 ][7  ] = atoi(A_108  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_109 ), WM_GETTEXT, 10, (LPARAM)A_109 ); matrixA[9 ][8  ] = atoi(A_109  );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_1010), WM_GETTEXT, 10, (LPARAM)A_1010); matrixA[9 ][9  ] = atoi(A_1010 );//


}

void leerB(HWND h) {
	    char B_11	 [10]="";
		char B_12	 [10]="";
		char B_13	 [10]="";
		char B_14	 [10]="";
		char B_15	 [10]="";
		char B_16	 [10]="";
		char B_17	 [10]="";
		char B_18	 [10]="";
		char B_19	 [10]="";
		char B_110	 [10]="";
		char B_21	 [10]="";
		char B_22	 [10]="";
		char B_23	 [10]="";
		char B_24	 [10]="";
		char B_25	 [10]="";
		char B_26	 [10]="";
		char B_27	 [10]="";
		char B_28	 [10]="";
		char B_29	 [10]="";
		char B_210	 [10]="";
		char B_31	 [10]="";
		char B_32	 [10]="";
		char B_33	 [10]="";
		char B_34	 [10]="";
		char B_35	 [10]="";
		char B_36	 [10]="";
		char B_37	 [10]="";
		char B_38	 [10]="";
		char B_39	 [10]="";
		char B_310	 [10]="";
		char B_41	 [10]="";
		char B_42	 [10]="";
		char B_43	 [10]="";
		char B_44	 [10]="";
		char B_45	 [10]="";
		char B_46	 [10]="";
		char B_47	 [10]="";
		char B_48	 [10]="";
		char B_49	 [10]="";
		char B_410	 [10]="";
		char B_51	 [10]="";
		char B_52	 [10]="";
		char B_53	 [10]="";
		char B_54	 [10]="";
		char B_55	 [10]="";
		char B_56	 [10]="";
		char B_57	 [10]="";
		char B_58	 [10]="";
		char B_59	 [10]="";
		char B_510	 [10]="";
		char B_61	 [10]="";
		char B_62	 [10]="";
		char B_63	 [10]="";
		char B_64	 [10]="";
		char B_65	 [10]="";
		char B_66	 [10]="";
		char B_67	 [10]="";
		char B_68	 [10]="";
		char B_69	 [10]="";
		char B_610	 [10]="";
		char B_71	 [10]="";
		char B_72	 [10]="";
		char B_73	 [10]="";
		char B_74	 [10]="";
		char B_75	 [10]="";
		char B_76	 [10]="";
		char B_77	 [10]="";
		char B_78	 [10]="";
		char B_79	 [10]="";
		char B_710	 [10]="";
		char B_81	 [10]="";
		char B_82	 [10]="";
		char B_83	 [10]="";
		char B_84	 [10]="";
		char B_85	 [10]="";
		char B_86	 [10]="";
		char B_87	 [10]="";
		char B_88	 [10]="";
		char B_89	 [10]="";
		char B_810	 [10]="";
		char B_91	 [10]="";
		char B_92	 [10]="";
		char B_93	 [10]="";
		char B_94	 [10]="";
		char B_95	 [10]="";
		char B_96	 [10]="";
		char B_97	 [10]="";
		char B_98	 [10]="";
		char B_99	 [10]="";
		char B_910	 [10]="";
		char B_101	 [10]="";
		char B_102	 [10]="";
		char B_103	 [10]="";
		char B_104	 [10]="";
		char B_105	 [10]="";
		char B_106	 [10]="";
		char B_107	 [10]="";
		char B_108	 [10]="";
		char B_109	 [10]="";
		char B_1010	 [10]="";



	SendMessage(GetDlgItem(h, IDC_EDIT_B_11  ), WM_GETTEXT, 10, (LPARAM)B_11  ); matrixB[0 ][0  ] = atoi(B_11   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_12  ), WM_GETTEXT, 10, (LPARAM)B_12  ); matrixB[0 ][1  ] = atoi(B_12   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_13  ), WM_GETTEXT, 10, (LPARAM)B_13  ); matrixB[0 ][2  ] = atoi(B_13   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_14  ), WM_GETTEXT, 10, (LPARAM)B_14  ); matrixB[0 ][3  ] = atoi(B_14   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_15  ), WM_GETTEXT, 10, (LPARAM)B_15  ); matrixB[0 ][4  ] = atoi(B_15   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_16  ), WM_GETTEXT, 10, (LPARAM)B_16  ); matrixB[0 ][5  ] = atoi(B_16   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_17  ), WM_GETTEXT, 10, (LPARAM)B_17  ); matrixB[0 ][6  ] = atoi(B_17   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_18  ), WM_GETTEXT, 10, (LPARAM)B_18  ); matrixB[0 ][7  ] = atoi(B_18   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_19  ), WM_GETTEXT, 10, (LPARAM)B_19  ); matrixB[0 ][8  ] = atoi(B_19   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_110 ), WM_GETTEXT, 10, (LPARAM)B_110 ); matrixB[0 ][9  ] = atoi(B_110  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_21  ), WM_GETTEXT, 10, (LPARAM)B_21  ); matrixB[1 ][0  ] = atoi(B_21   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_22  ), WM_GETTEXT, 10, (LPARAM)B_22  ); matrixB[1 ][1  ] = atoi(B_22   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_23  ), WM_GETTEXT, 10, (LPARAM)B_23  ); matrixB[1 ][2  ] = atoi(B_23   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_24  ), WM_GETTEXT, 10, (LPARAM)B_24  ); matrixB[1 ][3  ] = atoi(B_24   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_25  ), WM_GETTEXT, 10, (LPARAM)B_25  ); matrixB[1 ][4  ] = atoi(B_25   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_26  ), WM_GETTEXT, 10, (LPARAM)B_26  ); matrixB[1 ][5  ] = atoi(B_26   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_27  ), WM_GETTEXT, 10, (LPARAM)B_27  ); matrixB[1 ][6  ] = atoi(B_27   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_28  ), WM_GETTEXT, 10, (LPARAM)B_28  ); matrixB[1 ][7  ] = atoi(B_28   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_29  ), WM_GETTEXT, 10, (LPARAM)B_29  ); matrixB[1 ][8  ] = atoi(B_29   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_210 ), WM_GETTEXT, 10, (LPARAM)B_210 ); matrixB[1 ][9  ] = atoi(B_210  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_31  ), WM_GETTEXT, 10, (LPARAM)B_31  ); matrixB[2 ][0  ] = atoi(B_31   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_32  ), WM_GETTEXT, 10, (LPARAM)B_32  ); matrixB[2 ][1  ] = atoi(B_32   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_33  ), WM_GETTEXT, 10, (LPARAM)B_33  ); matrixB[2 ][2  ] = atoi(B_33   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_34  ), WM_GETTEXT, 10, (LPARAM)B_34  ); matrixB[2 ][3  ] = atoi(B_34   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_35  ), WM_GETTEXT, 10, (LPARAM)B_35  ); matrixB[2 ][4  ] = atoi(B_35   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_36  ), WM_GETTEXT, 10, (LPARAM)B_36  ); matrixB[2 ][5  ] = atoi(B_36   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_37  ), WM_GETTEXT, 10, (LPARAM)B_37  ); matrixB[2 ][6  ] = atoi(B_37   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_38  ), WM_GETTEXT, 10, (LPARAM)B_38  ); matrixB[2 ][7  ] = atoi(B_38   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_39  ), WM_GETTEXT, 10, (LPARAM)B_39  ); matrixB[2 ][8  ] = atoi(B_39   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_310 ), WM_GETTEXT, 10, (LPARAM)B_310 ); matrixB[2 ][9  ] = atoi(B_310  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_41  ), WM_GETTEXT, 10, (LPARAM)B_41  ); matrixB[3 ][0  ] = atoi(B_41   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_42  ), WM_GETTEXT, 10, (LPARAM)B_42  ); matrixB[3 ][1  ] = atoi(B_42   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_43  ), WM_GETTEXT, 10, (LPARAM)B_43  ); matrixB[3 ][2  ] = atoi(B_43   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_44  ), WM_GETTEXT, 10, (LPARAM)B_44  ); matrixB[3 ][3  ] = atoi(B_44   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_45  ), WM_GETTEXT, 10, (LPARAM)B_45  ); matrixB[3 ][4  ] = atoi(B_45   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_46  ), WM_GETTEXT, 10, (LPARAM)B_46  ); matrixB[3 ][5  ] = atoi(B_46   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_47  ), WM_GETTEXT, 10, (LPARAM)B_47  ); matrixB[3 ][6  ] = atoi(B_47   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_48  ), WM_GETTEXT, 10, (LPARAM)B_48  ); matrixB[3 ][7  ] = atoi(B_48   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_49  ), WM_GETTEXT, 10, (LPARAM)B_49  ); matrixB[3 ][8  ] = atoi(B_49   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_410 ), WM_GETTEXT, 10, (LPARAM)B_410 ); matrixB[3 ][9  ] = atoi(B_410  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_51  ), WM_GETTEXT, 10, (LPARAM)B_51  ); matrixB[4 ][0  ] = atoi(B_51   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_52  ), WM_GETTEXT, 10, (LPARAM)B_52  ); matrixB[4 ][1  ] = atoi(B_52   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_53  ), WM_GETTEXT, 10, (LPARAM)B_53  ); matrixB[4 ][2  ] = atoi(B_53   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_54  ), WM_GETTEXT, 10, (LPARAM)B_54  ); matrixB[4 ][3  ] = atoi(B_54   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_55  ), WM_GETTEXT, 10, (LPARAM)B_55  ); matrixB[4 ][4  ] = atoi(B_55   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_56  ), WM_GETTEXT, 10, (LPARAM)B_56  ); matrixB[4 ][5  ] = atoi(B_56   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_57  ), WM_GETTEXT, 10, (LPARAM)B_57  ); matrixB[4 ][6  ] = atoi(B_57   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_58  ), WM_GETTEXT, 10, (LPARAM)B_58  ); matrixB[4 ][7  ] = atoi(B_58   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_59  ), WM_GETTEXT, 10, (LPARAM)B_59  ); matrixB[4 ][8  ] = atoi(B_59   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_510 ), WM_GETTEXT, 10, (LPARAM)B_510 ); matrixB[4 ][9  ] = atoi(B_510  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_61  ), WM_GETTEXT, 10, (LPARAM)B_61  ); matrixB[5 ][0  ] = atoi(B_61   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_62  ), WM_GETTEXT, 10, (LPARAM)B_62  ); matrixB[5 ][1  ] = atoi(B_62   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_63  ), WM_GETTEXT, 10, (LPARAM)B_63  ); matrixB[5 ][2  ] = atoi(B_63   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_64  ), WM_GETTEXT, 10, (LPARAM)B_64  ); matrixB[5 ][3  ] = atoi(B_64   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_65  ), WM_GETTEXT, 10, (LPARAM)B_65  ); matrixB[5 ][4  ] = atoi(B_65   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_66  ), WM_GETTEXT, 10, (LPARAM)B_66  ); matrixB[5 ][5  ] = atoi(B_66   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_67  ), WM_GETTEXT, 10, (LPARAM)B_67  ); matrixB[5 ][6  ] = atoi(B_67   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_68  ), WM_GETTEXT, 10, (LPARAM)B_68  ); matrixB[5 ][7  ] = atoi(B_68   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_69  ), WM_GETTEXT, 10, (LPARAM)B_69  ); matrixB[5 ][8  ] = atoi(B_69   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_610 ), WM_GETTEXT, 10, (LPARAM)B_610 ); matrixB[5 ][9  ] = atoi(B_610  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_71  ), WM_GETTEXT, 10, (LPARAM)B_71  ); matrixB[6 ][0  ] = atoi(B_71   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_72  ), WM_GETTEXT, 10, (LPARAM)B_72  ); matrixB[6 ][1  ] = atoi(B_72   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_73  ), WM_GETTEXT, 10, (LPARAM)B_73  ); matrixB[6 ][2  ] = atoi(B_73   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_74  ), WM_GETTEXT, 10, (LPARAM)B_74  ); matrixB[6 ][3  ] = atoi(B_74   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_75  ), WM_GETTEXT, 10, (LPARAM)B_75  ); matrixB[6 ][4  ] = atoi(B_75   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_76  ), WM_GETTEXT, 10, (LPARAM)B_76  ); matrixB[6 ][5  ] = atoi(B_76   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_77  ), WM_GETTEXT, 10, (LPARAM)B_77  ); matrixB[6 ][6  ] = atoi(B_77   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_78  ), WM_GETTEXT, 10, (LPARAM)B_78  ); matrixB[6 ][7  ] = atoi(B_78   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_79  ), WM_GETTEXT, 10, (LPARAM)B_79  ); matrixB[6 ][8  ] = atoi(B_79   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_710 ), WM_GETTEXT, 10, (LPARAM)B_710 ); matrixB[6 ][9  ] = atoi(B_710  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_81  ), WM_GETTEXT, 10, (LPARAM)B_81  ); matrixB[7 ][0  ] = atoi(B_81   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_82  ), WM_GETTEXT, 10, (LPARAM)B_82  ); matrixB[7 ][1  ] = atoi(B_82   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_83  ), WM_GETTEXT, 10, (LPARAM)B_83  ); matrixB[7 ][2  ] = atoi(B_83   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_84  ), WM_GETTEXT, 10, (LPARAM)B_84  ); matrixB[7 ][3  ] = atoi(B_84   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_85  ), WM_GETTEXT, 10, (LPARAM)B_85  ); matrixB[7 ][4  ] = atoi(B_85   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_86  ), WM_GETTEXT, 10, (LPARAM)B_86  ); matrixB[7 ][5  ] = atoi(B_86   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_87  ), WM_GETTEXT, 10, (LPARAM)B_87  ); matrixB[7 ][6  ] = atoi(B_87   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_88  ), WM_GETTEXT, 10, (LPARAM)B_88  ); matrixB[7 ][7  ] = atoi(B_88   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_89  ), WM_GETTEXT, 10, (LPARAM)B_89  ); matrixB[7 ][8  ] = atoi(B_89   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_810 ), WM_GETTEXT, 10, (LPARAM)B_810 ); matrixB[7 ][9  ] = atoi(B_810  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_91  ), WM_GETTEXT, 10, (LPARAM)B_91  ); matrixB[8 ][0  ] = atoi(B_91   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_92  ), WM_GETTEXT, 10, (LPARAM)B_92  ); matrixB[8 ][1  ] = atoi(B_92   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_93  ), WM_GETTEXT, 10, (LPARAM)B_93  ); matrixB[8 ][2  ] = atoi(B_93   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_94  ), WM_GETTEXT, 10, (LPARAM)B_94  ); matrixB[8 ][3  ] = atoi(B_94   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_95  ), WM_GETTEXT, 10, (LPARAM)B_95  ); matrixB[8 ][4  ] = atoi(B_95   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_96  ), WM_GETTEXT, 10, (LPARAM)B_96  ); matrixB[8 ][5  ] = atoi(B_96   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_97  ), WM_GETTEXT, 10, (LPARAM)B_97  ); matrixB[8 ][6  ] = atoi(B_97   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_98  ), WM_GETTEXT, 10, (LPARAM)B_98  ); matrixB[8 ][7  ] = atoi(B_98   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_99  ), WM_GETTEXT, 10, (LPARAM)B_99  ); matrixB[8 ][8  ] = atoi(B_99   );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_910 ), WM_GETTEXT, 10, (LPARAM)B_910 ); matrixB[8 ][9  ] = atoi(B_910  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_101 ), WM_GETTEXT, 10, (LPARAM)B_101 ); matrixB[9 ][0  ] = atoi(B_101  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_102 ), WM_GETTEXT, 10, (LPARAM)B_102 ); matrixB[9 ][1  ] = atoi(B_102  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_103 ), WM_GETTEXT, 10, (LPARAM)B_103 ); matrixB[9 ][2  ] = atoi(B_103  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_104 ), WM_GETTEXT, 10, (LPARAM)B_104 ); matrixB[9 ][3  ] = atoi(B_104  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_105 ), WM_GETTEXT, 10, (LPARAM)B_105 ); matrixB[9 ][4  ] = atoi(B_105  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_106 ), WM_GETTEXT, 10, (LPARAM)B_106 ); matrixB[9 ][5  ] = atoi(B_106  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_107 ), WM_GETTEXT, 10, (LPARAM)B_107 ); matrixB[9 ][6  ] = atoi(B_107  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_108 ), WM_GETTEXT, 10, (LPARAM)B_108 ); matrixB[9 ][7  ] = atoi(B_108  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_109 ), WM_GETTEXT, 10, (LPARAM)B_109 ); matrixB[9 ][8  ] = atoi(B_109  );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_1010), WM_GETTEXT, 10, (LPARAM)B_1010); matrixB[9 ][9  ] = atoi(B_1010 );


}

void leerA_deci(HWND h) {
        char A_11	 [10]="";
		char A_12	 [10]="";
		char A_13	 [10]="";
		char A_14	 [10]="";
		char A_15	 [10]="";
		char A_16	 [10]="";
		char A_17	 [10]="";
		char A_18	 [10]="";
		char A_19	 [10]="";
		char A_110	 [10]="";
		char A_21	 [10]="";
		char A_22	 [10]="";
		char A_23	 [10]="";
		char A_24	 [10]="";
		char A_25	 [10]="";
		char A_26	 [10]="";
		char A_27	 [10]="";
		char A_28	 [10]="";
		char A_29	 [10]="";
		char A_210	 [10]="";
		char A_31	 [10]="";
		char A_32	 [10]="";
		char A_33	 [10]="";
		char A_34	 [10]="";
		char A_35	 [10]="";
		char A_36	 [10]="";
		char A_37	 [10]="";
		char A_38	 [10]="";
		char A_39	 [10]="";
		char A_310	 [10]="";
		char A_41	 [10]="";
		char A_42	 [10]="";
		char A_43	 [10]="";
		char A_44	 [10]="";
		char A_45	 [10]="";
		char A_46	 [10]="";
		char A_47	 [10]="";
		char A_48	 [10]="";
		char A_49	 [10]="";
		char A_410	 [10]="";
		char A_51	 [10]="";
		char A_52	 [10]="";
		char A_53	 [10]="";
		char A_54	 [10]="";
		char A_55	 [10]="";
		char A_56	 [10]="";
		char A_57	 [10]="";
		char A_58	 [10]="";
		char A_59	 [10]="";
		char A_510	 [10]="";
		char A_61	 [10]="";
		char A_62	 [10]="";
		char A_63	 [10]="";
		char A_64	 [10]="";
		char A_65	 [10]="";
		char A_66	 [10]="";
		char A_67	 [10]="";
		char A_68	 [10]="";
		char A_69	 [10]="";
		char A_610	 [10]="";
		char A_71	 [10]="";
		char A_72	 [10]="";
		char A_73	 [10]="";
		char A_74	 [10]="";
		char A_75	 [10]="";
		char A_76	 [10]="";
		char A_77	 [10]="";
		char A_78	 [10]="";
		char A_79	 [10]="";
		char A_710	 [10]="";
		char A_81	 [10]="";
		char A_82	 [10]="";
		char A_83	 [10]="";
		char A_84	 [10]="";
		char A_85	 [10]="";
		char A_86	 [10]="";
		char A_87	 [10]="";
		char A_88	 [10]="";
		char A_89	 [10]="";
		char A_810	 [10]="";
		char A_91	 [10]="";
		char A_92	 [10]="";
		char A_93	 [10]="";
		char A_94	 [10]="";
		char A_95	 [10]="";
		char A_96	 [10]="";
		char A_97	 [10]="";
		char A_98	 [10]="";
		char A_99	 [10]="";
		char A_910	 [10]="";
		char A_101	 [10]="";
		char A_102	 [10]="";
		char A_103	 [10]="";
		char A_104	 [10]="";
		char A_105	 [10]="";
		char A_106	 [10]="";
		char A_107	 [10]="";
		char A_108	 [10]="";
		char A_109	 [10]="";
		char A_1010	 [10]="";

    SendMessage(GetDlgItem(h, IDC_EDIT_A_11  ), WM_GETTEXT, 10, (LPARAM)A_11  ); matrixA[0 ][0  ] = strtod(A_11  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_12  ), WM_GETTEXT, 10, (LPARAM)A_12  ); matrixA[0 ][1  ] = strtod(A_12  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_13  ), WM_GETTEXT, 10, (LPARAM)A_13  ); matrixA[0 ][2  ] = strtod(A_13  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_14  ), WM_GETTEXT, 10, (LPARAM)A_14  ); matrixA[0 ][3  ] = strtod(A_14  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_15  ), WM_GETTEXT, 10, (LPARAM)A_15  ); matrixA[0 ][4  ] = strtod(A_15  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_16  ), WM_GETTEXT, 10, (LPARAM)A_16  ); matrixA[0 ][5  ] = strtod(A_16  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_17  ), WM_GETTEXT, 10, (LPARAM)A_17  ); matrixA[0 ][6  ] = strtod(A_17  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_18  ), WM_GETTEXT, 10, (LPARAM)A_18  ); matrixA[0 ][7  ] = strtod(A_18  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_19  ), WM_GETTEXT, 10, (LPARAM)A_19  ); matrixA[0 ][8  ] = strtod(A_19  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_110 ), WM_GETTEXT, 10, (LPARAM)A_110 ); matrixA[0 ][9  ] = strtod(A_110 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_21  ), WM_GETTEXT, 10, (LPARAM)A_21  ); matrixA[1 ][0  ] = strtod(A_21  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_22  ), WM_GETTEXT, 10, (LPARAM)A_22  ); matrixA[1 ][1  ] = strtod(A_22  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_23  ), WM_GETTEXT, 10, (LPARAM)A_23  ); matrixA[1 ][2  ] = strtod(A_23  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_24  ), WM_GETTEXT, 10, (LPARAM)A_24  ); matrixA[1 ][3  ] = strtod(A_24  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_25  ), WM_GETTEXT, 10, (LPARAM)A_25  ); matrixA[1 ][4  ] = strtod(A_25  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_26  ), WM_GETTEXT, 10, (LPARAM)A_26  ); matrixA[1 ][5  ] = strtod(A_26  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_27  ), WM_GETTEXT, 10, (LPARAM)A_27  ); matrixA[1 ][6  ] = strtod(A_27  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_28  ), WM_GETTEXT, 10, (LPARAM)A_28  ); matrixA[1 ][7  ] = strtod(A_28  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_29  ), WM_GETTEXT, 10, (LPARAM)A_29  ); matrixA[1 ][8  ] = strtod(A_29  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_210 ), WM_GETTEXT, 10, (LPARAM)A_210 ); matrixA[1 ][9  ] = strtod(A_210 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_31  ), WM_GETTEXT, 10, (LPARAM)A_31  ); matrixA[2 ][0  ] = strtod(A_31  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_32  ), WM_GETTEXT, 10, (LPARAM)A_32  ); matrixA[2 ][1  ] = strtod(A_32  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_33  ), WM_GETTEXT, 10, (LPARAM)A_33  ); matrixA[2 ][2  ] = strtod(A_33  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_34  ), WM_GETTEXT, 10, (LPARAM)A_34  ); matrixA[2 ][3  ] = strtod(A_34  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_35  ), WM_GETTEXT, 10, (LPARAM)A_35  ); matrixA[2 ][4  ] = strtod(A_35  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_36  ), WM_GETTEXT, 10, (LPARAM)A_36  ); matrixA[2 ][5  ] = strtod(A_36  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_37  ), WM_GETTEXT, 10, (LPARAM)A_37  ); matrixA[2 ][6  ] = strtod(A_37  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_38  ), WM_GETTEXT, 10, (LPARAM)A_38  ); matrixA[2 ][7  ] = strtod(A_38  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_39  ), WM_GETTEXT, 10, (LPARAM)A_39  ); matrixA[2 ][8  ] = strtod(A_39  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_310 ), WM_GETTEXT, 10, (LPARAM)A_310 ); matrixA[2 ][9  ] = strtod(A_310 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_41  ), WM_GETTEXT, 10, (LPARAM)A_41  ); matrixA[3 ][0  ] = strtod(A_41  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_42  ), WM_GETTEXT, 10, (LPARAM)A_42  ); matrixA[3 ][1  ] = strtod(A_42  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_43  ), WM_GETTEXT, 10, (LPARAM)A_43  ); matrixA[3 ][2  ] = strtod(A_43  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_44  ), WM_GETTEXT, 10, (LPARAM)A_44  ); matrixA[3 ][3  ] = strtod(A_44  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_45  ), WM_GETTEXT, 10, (LPARAM)A_45  ); matrixA[3 ][4  ] = strtod(A_45  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_46  ), WM_GETTEXT, 10, (LPARAM)A_46  ); matrixA[3 ][5  ] = strtod(A_46  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_47  ), WM_GETTEXT, 10, (LPARAM)A_47  ); matrixA[3 ][6  ] = strtod(A_47  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_48  ), WM_GETTEXT, 10, (LPARAM)A_48  ); matrixA[3 ][7  ] = strtod(A_48  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_49  ), WM_GETTEXT, 10, (LPARAM)A_49  ); matrixA[3 ][8  ] = strtod(A_49  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_410 ), WM_GETTEXT, 10, (LPARAM)A_410 ); matrixA[3 ][9  ] = strtod(A_410 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_51  ), WM_GETTEXT, 10, (LPARAM)A_51  ); matrixA[4 ][0  ] = strtod(A_51  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_52  ), WM_GETTEXT, 10, (LPARAM)A_52  ); matrixA[4 ][1  ] = strtod(A_52  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_53  ), WM_GETTEXT, 10, (LPARAM)A_53  ); matrixA[4 ][2  ] = strtod(A_53  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_54  ), WM_GETTEXT, 10, (LPARAM)A_54  ); matrixA[4 ][3  ] = strtod(A_54  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_55  ), WM_GETTEXT, 10, (LPARAM)A_55  ); matrixA[4 ][4  ] = strtod(A_55  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_56  ), WM_GETTEXT, 10, (LPARAM)A_56  ); matrixA[4 ][5  ] = strtod(A_56  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_57  ), WM_GETTEXT, 10, (LPARAM)A_57  ); matrixA[4 ][6  ] = strtod(A_57  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_58  ), WM_GETTEXT, 10, (LPARAM)A_58  ); matrixA[4 ][7  ] = strtod(A_58  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_59  ), WM_GETTEXT, 10, (LPARAM)A_59  ); matrixA[4 ][8  ] = strtod(A_59  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_510 ), WM_GETTEXT, 10, (LPARAM)A_510 ); matrixA[4 ][9  ] = strtod(A_510 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_61  ), WM_GETTEXT, 10, (LPARAM)A_61  ); matrixA[5 ][0  ] = strtod(A_61  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_62  ), WM_GETTEXT, 10, (LPARAM)A_62  ); matrixA[5 ][1  ] = strtod(A_62  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_63  ), WM_GETTEXT, 10, (LPARAM)A_63  ); matrixA[5 ][2  ] = strtod(A_63  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_64  ), WM_GETTEXT, 10, (LPARAM)A_64  ); matrixA[5 ][3  ] = strtod(A_64  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_65  ), WM_GETTEXT, 10, (LPARAM)A_65  ); matrixA[5 ][4  ] = strtod(A_65  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_66  ), WM_GETTEXT, 10, (LPARAM)A_66  ); matrixA[5 ][5  ] = strtod(A_66  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_67  ), WM_GETTEXT, 10, (LPARAM)A_67  ); matrixA[5 ][6  ] = strtod(A_67  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_68  ), WM_GETTEXT, 10, (LPARAM)A_68  ); matrixA[5 ][7  ] = strtod(A_68  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_69  ), WM_GETTEXT, 10, (LPARAM)A_69  ); matrixA[5 ][8  ] = strtod(A_69  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_610 ), WM_GETTEXT, 10, (LPARAM)A_610 ); matrixA[5 ][9  ] = strtod(A_610 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_71  ), WM_GETTEXT, 10, (LPARAM)A_71  ); matrixA[6 ][0  ] = strtod(A_71  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_72  ), WM_GETTEXT, 10, (LPARAM)A_72  ); matrixA[6 ][1  ] = strtod(A_72  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_73  ), WM_GETTEXT, 10, (LPARAM)A_73  ); matrixA[6 ][2  ] = strtod(A_73  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_74  ), WM_GETTEXT, 10, (LPARAM)A_74  ); matrixA[6 ][3  ] = strtod(A_74  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_75  ), WM_GETTEXT, 10, (LPARAM)A_75  ); matrixA[6 ][4  ] = strtod(A_75  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_76  ), WM_GETTEXT, 10, (LPARAM)A_76  ); matrixA[6 ][5  ] = strtod(A_76  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_77  ), WM_GETTEXT, 10, (LPARAM)A_77  ); matrixA[6 ][6  ] = strtod(A_77  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_78  ), WM_GETTEXT, 10, (LPARAM)A_78  ); matrixA[6 ][7  ] = strtod(A_78  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_79  ), WM_GETTEXT, 10, (LPARAM)A_79  ); matrixA[6 ][8  ] = strtod(A_79  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_710 ), WM_GETTEXT, 10, (LPARAM)A_710 ); matrixA[6 ][9  ] = strtod(A_710 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_81  ), WM_GETTEXT, 10, (LPARAM)A_81  ); matrixA[7 ][0  ] = strtod(A_81  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_82  ), WM_GETTEXT, 10, (LPARAM)A_82  ); matrixA[7 ][1  ] = strtod(A_82  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_83  ), WM_GETTEXT, 10, (LPARAM)A_83  ); matrixA[7 ][2  ] = strtod(A_83  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_84  ), WM_GETTEXT, 10, (LPARAM)A_84  ); matrixA[7 ][3  ] = strtod(A_84  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_85  ), WM_GETTEXT, 10, (LPARAM)A_85  ); matrixA[7 ][4  ] = strtod(A_85  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_86  ), WM_GETTEXT, 10, (LPARAM)A_86  ); matrixA[7 ][5  ] = strtod(A_86  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_87  ), WM_GETTEXT, 10, (LPARAM)A_87  ); matrixA[7 ][6  ] = strtod(A_87  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_88  ), WM_GETTEXT, 10, (LPARAM)A_88  ); matrixA[7 ][7  ] = strtod(A_88  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_89  ), WM_GETTEXT, 10, (LPARAM)A_89  ); matrixA[7 ][8  ] = strtod(A_89  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_810 ), WM_GETTEXT, 10, (LPARAM)A_810 ); matrixA[7 ][9  ] = strtod(A_810 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_91  ), WM_GETTEXT, 10, (LPARAM)A_91  ); matrixA[8 ][0  ] = strtod(A_91  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_92  ), WM_GETTEXT, 10, (LPARAM)A_92  ); matrixA[8 ][1  ] = strtod(A_92  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_93  ), WM_GETTEXT, 10, (LPARAM)A_93  ); matrixA[8 ][2  ] = strtod(A_93  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_94  ), WM_GETTEXT, 10, (LPARAM)A_94  ); matrixA[8 ][3  ] = strtod(A_94  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_95  ), WM_GETTEXT, 10, (LPARAM)A_95  ); matrixA[8 ][4  ] = strtod(A_95  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_96  ), WM_GETTEXT, 10, (LPARAM)A_96  ); matrixA[8 ][5  ] = strtod(A_96  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_97  ), WM_GETTEXT, 10, (LPARAM)A_97  ); matrixA[8 ][6  ] = strtod(A_97  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_98  ), WM_GETTEXT, 10, (LPARAM)A_98  ); matrixA[8 ][7  ] = strtod(A_98  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_99  ), WM_GETTEXT, 10, (LPARAM)A_99  ); matrixA[8 ][8  ] = strtod(A_99  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_910 ), WM_GETTEXT, 10, (LPARAM)A_910 ); matrixA[8 ][9  ] = strtod(A_910 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_A_101 ), WM_GETTEXT, 10, (LPARAM)A_101 ); matrixA[9 ][0  ] = strtod(A_101 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_102 ), WM_GETTEXT, 10, (LPARAM)A_102 ); matrixA[9 ][1  ] = strtod(A_102 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_103 ), WM_GETTEXT, 10, (LPARAM)A_103 ); matrixA[9 ][2  ] = strtod(A_103 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_104 ), WM_GETTEXT, 10, (LPARAM)A_104 ); matrixA[9 ][3  ] = strtod(A_104 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_105 ), WM_GETTEXT, 10, (LPARAM)A_105 ); matrixA[9 ][4  ] = strtod(A_105 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_106 ), WM_GETTEXT, 10, (LPARAM)A_106 ); matrixA[9 ][5  ] = strtod(A_106 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_107 ), WM_GETTEXT, 10, (LPARAM)A_107 ); matrixA[9 ][6  ] = strtod(A_107 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_108 ), WM_GETTEXT, 10, (LPARAM)A_108 ); matrixA[9 ][7  ] = strtod(A_108 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_109 ), WM_GETTEXT, 10, (LPARAM)A_109 ); matrixA[9 ][8  ] = strtod(A_109 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_A_1010), WM_GETTEXT, 10, (LPARAM)A_1010); matrixA[9 ][9  ] = strtod(A_1010,0 );//
}
void leerB_deci(HWND h) {
	    char B_11	 [10]="";
		char B_12	 [10]="";
		char B_13	 [10]="";
		char B_14	 [10]="";
		char B_15	 [10]="";
		char B_16	 [10]="";
		char B_17	 [10]="";
		char B_18	 [10]="";
		char B_19	 [10]="";
		char B_110	 [10]="";
		char B_21	 [10]="";
		char B_22	 [10]="";
		char B_23	 [10]="";
		char B_24	 [10]="";
		char B_25	 [10]="";
		char B_26	 [10]="";
		char B_27	 [10]="";
		char B_28	 [10]="";
		char B_29	 [10]="";
		char B_210	 [10]="";
		char B_31	 [10]="";
		char B_32	 [10]="";
		char B_33	 [10]="";
		char B_34	 [10]="";
		char B_35	 [10]="";
		char B_36	 [10]="";
		char B_37	 [10]="";
		char B_38	 [10]="";
		char B_39	 [10]="";
		char B_310	 [10]="";
		char B_41	 [10]="";
		char B_42	 [10]="";
		char B_43	 [10]="";
		char B_44	 [10]="";
		char B_45	 [10]="";
		char B_46	 [10]="";
		char B_47	 [10]="";
		char B_48	 [10]="";
		char B_49	 [10]="";
		char B_410	 [10]="";
		char B_51	 [10]="";
		char B_52	 [10]="";
		char B_53	 [10]="";
		char B_54	 [10]="";
		char B_55	 [10]="";
		char B_56	 [10]="";
		char B_57	 [10]="";
		char B_58	 [10]="";
		char B_59	 [10]="";
		char B_510	 [10]="";
		char B_61	 [10]="";
		char B_62	 [10]="";
		char B_63	 [10]="";
		char B_64	 [10]="";
		char B_65	 [10]="";
		char B_66	 [10]="";
		char B_67	 [10]="";
		char B_68	 [10]="";
		char B_69	 [10]="";
		char B_610	 [10]="";
		char B_71	 [10]="";
		char B_72	 [10]="";
		char B_73	 [10]="";
		char B_74	 [10]="";
		char B_75	 [10]="";
		char B_76	 [10]="";
		char B_77	 [10]="";
		char B_78	 [10]="";
		char B_79	 [10]="";
		char B_710	 [10]="";
		char B_81	 [10]="";
		char B_82	 [10]="";
		char B_83	 [10]="";
		char B_84	 [10]="";
		char B_85	 [10]="";
		char B_86	 [10]="";
		char B_87	 [10]="";
		char B_88	 [10]="";
		char B_89	 [10]="";
		char B_810	 [10]="";
		char B_91	 [10]="";
		char B_92	 [10]="";
		char B_93	 [10]="";
		char B_94	 [10]="";
		char B_95	 [10]="";
		char B_96	 [10]="";
		char B_97	 [10]="";
		char B_98	 [10]="";
		char B_99	 [10]="";
		char B_910	 [10]="";
		char B_101	 [10]="";
		char B_102	 [10]="";
		char B_103	 [10]="";
		char B_104	 [10]="";
		char B_105	 [10]="";
		char B_106	 [10]="";
		char B_107	 [10]="";
		char B_108	 [10]="";
		char B_109	 [10]="";
		char B_1010	 [10]="";



	SendMessage(GetDlgItem(h, IDC_EDIT_B_11  ), WM_GETTEXT, 10, (LPARAM)B_11  ); matrixB[0 ][0  ] = strtod(B_11  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_12  ), WM_GETTEXT, 10, (LPARAM)B_12  ); matrixB[0 ][1  ] = strtod(B_12  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_13  ), WM_GETTEXT, 10, (LPARAM)B_13  ); matrixB[0 ][2  ] = strtod(B_13  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_14  ), WM_GETTEXT, 10, (LPARAM)B_14  ); matrixB[0 ][3  ] = strtod(B_14  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_15  ), WM_GETTEXT, 10, (LPARAM)B_15  ); matrixB[0 ][4  ] = strtod(B_15  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_16  ), WM_GETTEXT, 10, (LPARAM)B_16  ); matrixB[0 ][5  ] = strtod(B_16  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_17  ), WM_GETTEXT, 10, (LPARAM)B_17  ); matrixB[0 ][6  ] = strtod(B_17  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_18  ), WM_GETTEXT, 10, (LPARAM)B_18  ); matrixB[0 ][7  ] = strtod(B_18  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_19  ), WM_GETTEXT, 10, (LPARAM)B_19  ); matrixB[0 ][8  ] = strtod(B_19  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_110 ), WM_GETTEXT, 10, (LPARAM)B_110 ); matrixB[0 ][9  ] = strtod(B_110 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_21  ), WM_GETTEXT, 10, (LPARAM)B_21  ); matrixB[1 ][0  ] = strtod(B_21  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_22  ), WM_GETTEXT, 10, (LPARAM)B_22  ); matrixB[1 ][1  ] = strtod(B_22  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_23  ), WM_GETTEXT, 10, (LPARAM)B_23  ); matrixB[1 ][2  ] = strtod(B_23  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_24  ), WM_GETTEXT, 10, (LPARAM)B_24  ); matrixB[1 ][3  ] = strtod(B_24  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_25  ), WM_GETTEXT, 10, (LPARAM)B_25  ); matrixB[1 ][4  ] = strtod(B_25  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_26  ), WM_GETTEXT, 10, (LPARAM)B_26  ); matrixB[1 ][5  ] = strtod(B_26  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_27  ), WM_GETTEXT, 10, (LPARAM)B_27  ); matrixB[1 ][6  ] = strtod(B_27  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_28  ), WM_GETTEXT, 10, (LPARAM)B_28  ); matrixB[1 ][7  ] = strtod(B_28  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_29  ), WM_GETTEXT, 10, (LPARAM)B_29  ); matrixB[1 ][8  ] = strtod(B_29  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_210 ), WM_GETTEXT, 10, (LPARAM)B_210 ); matrixB[1 ][9  ] = strtod(B_210 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_31  ), WM_GETTEXT, 10, (LPARAM)B_31  ); matrixB[2 ][0  ] = strtod(B_31  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_32  ), WM_GETTEXT, 10, (LPARAM)B_32  ); matrixB[2 ][1  ] = strtod(B_32  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_33  ), WM_GETTEXT, 10, (LPARAM)B_33  ); matrixB[2 ][2  ] = strtod(B_33  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_34  ), WM_GETTEXT, 10, (LPARAM)B_34  ); matrixB[2 ][3  ] = strtod(B_34  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_35  ), WM_GETTEXT, 10, (LPARAM)B_35  ); matrixB[2 ][4  ] = strtod(B_35  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_36  ), WM_GETTEXT, 10, (LPARAM)B_36  ); matrixB[2 ][5  ] = strtod(B_36  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_37  ), WM_GETTEXT, 10, (LPARAM)B_37  ); matrixB[2 ][6  ] = strtod(B_37  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_38  ), WM_GETTEXT, 10, (LPARAM)B_38  ); matrixB[2 ][7  ] = strtod(B_38  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_39  ), WM_GETTEXT, 10, (LPARAM)B_39  ); matrixB[2 ][8  ] = strtod(B_39  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_310 ), WM_GETTEXT, 10, (LPARAM)B_310 ); matrixB[2 ][9  ] = strtod(B_310 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_41  ), WM_GETTEXT, 10, (LPARAM)B_41  ); matrixB[3 ][0  ] = strtod(B_41  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_42  ), WM_GETTEXT, 10, (LPARAM)B_42  ); matrixB[3 ][1  ] = strtod(B_42  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_43  ), WM_GETTEXT, 10, (LPARAM)B_43  ); matrixB[3 ][2  ] = strtod(B_43  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_44  ), WM_GETTEXT, 10, (LPARAM)B_44  ); matrixB[3 ][3  ] = strtod(B_44  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_45  ), WM_GETTEXT, 10, (LPARAM)B_45  ); matrixB[3 ][4  ] = strtod(B_45  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_46  ), WM_GETTEXT, 10, (LPARAM)B_46  ); matrixB[3 ][5  ] = strtod(B_46  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_47  ), WM_GETTEXT, 10, (LPARAM)B_47  ); matrixB[3 ][6  ] = strtod(B_47  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_48  ), WM_GETTEXT, 10, (LPARAM)B_48  ); matrixB[3 ][7  ] = strtod(B_48  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_49  ), WM_GETTEXT, 10, (LPARAM)B_49  ); matrixB[3 ][8  ] = strtod(B_49  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_410 ), WM_GETTEXT, 10, (LPARAM)B_410 ); matrixB[3 ][9  ] = strtod(B_410 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_51  ), WM_GETTEXT, 10, (LPARAM)B_51  ); matrixB[4 ][0  ] = strtod(B_51  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_52  ), WM_GETTEXT, 10, (LPARAM)B_52  ); matrixB[4 ][1  ] = strtod(B_52  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_53  ), WM_GETTEXT, 10, (LPARAM)B_53  ); matrixB[4 ][2  ] = strtod(B_53  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_54  ), WM_GETTEXT, 10, (LPARAM)B_54  ); matrixB[4 ][3  ] = strtod(B_54  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_55  ), WM_GETTEXT, 10, (LPARAM)B_55  ); matrixB[4 ][4  ] = strtod(B_55  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_56  ), WM_GETTEXT, 10, (LPARAM)B_56  ); matrixB[4 ][5  ] = strtod(B_56  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_57  ), WM_GETTEXT, 10, (LPARAM)B_57  ); matrixB[4 ][6  ] = strtod(B_57  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_58  ), WM_GETTEXT, 10, (LPARAM)B_58  ); matrixB[4 ][7  ] = strtod(B_58  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_59  ), WM_GETTEXT, 10, (LPARAM)B_59  ); matrixB[4 ][8  ] = strtod(B_59  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_510 ), WM_GETTEXT, 10, (LPARAM)B_510 ); matrixB[4 ][9  ] = strtod(B_510 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_61  ), WM_GETTEXT, 10, (LPARAM)B_61  ); matrixB[5 ][0  ] = strtod(B_61  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_62  ), WM_GETTEXT, 10, (LPARAM)B_62  ); matrixB[5 ][1  ] = strtod(B_62  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_63  ), WM_GETTEXT, 10, (LPARAM)B_63  ); matrixB[5 ][2  ] = strtod(B_63  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_64  ), WM_GETTEXT, 10, (LPARAM)B_64  ); matrixB[5 ][3  ] = strtod(B_64  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_65  ), WM_GETTEXT, 10, (LPARAM)B_65  ); matrixB[5 ][4  ] = strtod(B_65  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_66  ), WM_GETTEXT, 10, (LPARAM)B_66  ); matrixB[5 ][5  ] = strtod(B_66  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_67  ), WM_GETTEXT, 10, (LPARAM)B_67  ); matrixB[5 ][6  ] = strtod(B_67  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_68  ), WM_GETTEXT, 10, (LPARAM)B_68  ); matrixB[5 ][7  ] = strtod(B_68  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_69  ), WM_GETTEXT, 10, (LPARAM)B_69  ); matrixB[5 ][8  ] = strtod(B_69  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_610 ), WM_GETTEXT, 10, (LPARAM)B_610 ); matrixB[5 ][9  ] = strtod(B_610 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_71  ), WM_GETTEXT, 10, (LPARAM)B_71  ); matrixB[6 ][0  ] = strtod(B_71  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_72  ), WM_GETTEXT, 10, (LPARAM)B_72  ); matrixB[6 ][1  ] = strtod(B_72  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_73  ), WM_GETTEXT, 10, (LPARAM)B_73  ); matrixB[6 ][2  ] = strtod(B_73  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_74  ), WM_GETTEXT, 10, (LPARAM)B_74  ); matrixB[6 ][3  ] = strtod(B_74  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_75  ), WM_GETTEXT, 10, (LPARAM)B_75  ); matrixB[6 ][4  ] = strtod(B_75  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_76  ), WM_GETTEXT, 10, (LPARAM)B_76  ); matrixB[6 ][5  ] = strtod(B_76  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_77  ), WM_GETTEXT, 10, (LPARAM)B_77  ); matrixB[6 ][6  ] = strtod(B_77  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_78  ), WM_GETTEXT, 10, (LPARAM)B_78  ); matrixB[6 ][7  ] = strtod(B_78  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_79  ), WM_GETTEXT, 10, (LPARAM)B_79  ); matrixB[6 ][8  ] = strtod(B_79  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_710 ), WM_GETTEXT, 10, (LPARAM)B_710 ); matrixB[6 ][9  ] = strtod(B_710 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_81  ), WM_GETTEXT, 10, (LPARAM)B_81  ); matrixB[7 ][0  ] = strtod(B_81  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_82  ), WM_GETTEXT, 10, (LPARAM)B_82  ); matrixB[7 ][1  ] = strtod(B_82  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_83  ), WM_GETTEXT, 10, (LPARAM)B_83  ); matrixB[7 ][2  ] = strtod(B_83  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_84  ), WM_GETTEXT, 10, (LPARAM)B_84  ); matrixB[7 ][3  ] = strtod(B_84  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_85  ), WM_GETTEXT, 10, (LPARAM)B_85  ); matrixB[7 ][4  ] = strtod(B_85  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_86  ), WM_GETTEXT, 10, (LPARAM)B_86  ); matrixB[7 ][5  ] = strtod(B_86  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_87  ), WM_GETTEXT, 10, (LPARAM)B_87  ); matrixB[7 ][6  ] = strtod(B_87  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_88  ), WM_GETTEXT, 10, (LPARAM)B_88  ); matrixB[7 ][7  ] = strtod(B_88  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_89  ), WM_GETTEXT, 10, (LPARAM)B_89  ); matrixB[7 ][8  ] = strtod(B_89  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_810 ), WM_GETTEXT, 10, (LPARAM)B_810 ); matrixB[7 ][9  ] = strtod(B_810 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_91  ), WM_GETTEXT, 10, (LPARAM)B_91  ); matrixB[8 ][0  ] = strtod(B_91  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_92  ), WM_GETTEXT, 10, (LPARAM)B_92  ); matrixB[8 ][1  ] = strtod(B_92  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_93  ), WM_GETTEXT, 10, (LPARAM)B_93  ); matrixB[8 ][2  ] = strtod(B_93  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_94  ), WM_GETTEXT, 10, (LPARAM)B_94  ); matrixB[8 ][3  ] = strtod(B_94  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_95  ), WM_GETTEXT, 10, (LPARAM)B_95  ); matrixB[8 ][4  ] = strtod(B_95  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_96  ), WM_GETTEXT, 10, (LPARAM)B_96  ); matrixB[8 ][5  ] = strtod(B_96  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_97  ), WM_GETTEXT, 10, (LPARAM)B_97  ); matrixB[8 ][6  ] = strtod(B_97  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_98  ), WM_GETTEXT, 10, (LPARAM)B_98  ); matrixB[8 ][7  ] = strtod(B_98  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_99  ), WM_GETTEXT, 10, (LPARAM)B_99  ); matrixB[8 ][8  ] = strtod(B_99  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_910 ), WM_GETTEXT, 10, (LPARAM)B_910 ); matrixB[8 ][9  ] = strtod(B_910 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_B_101 ), WM_GETTEXT, 10, (LPARAM)B_101 ); matrixB[9 ][0  ] = strtod(B_101 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_102 ), WM_GETTEXT, 10, (LPARAM)B_102 ); matrixB[9 ][1  ] = strtod(B_102 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_103 ), WM_GETTEXT, 10, (LPARAM)B_103 ); matrixB[9 ][2  ] = strtod(B_103 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_104 ), WM_GETTEXT, 10, (LPARAM)B_104 ); matrixB[9 ][3  ] = strtod(B_104 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_105 ), WM_GETTEXT, 10, (LPARAM)B_105 ); matrixB[9 ][4  ] = strtod(B_105 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_106 ), WM_GETTEXT, 10, (LPARAM)B_106 ); matrixB[9 ][5  ] = strtod(B_106 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_107 ), WM_GETTEXT, 10, (LPARAM)B_107 ); matrixB[9 ][6  ] = strtod(B_107 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_108 ), WM_GETTEXT, 10, (LPARAM)B_108 ); matrixB[9 ][7  ] = strtod(B_108 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_109 ), WM_GETTEXT, 10, (LPARAM)B_109 ); matrixB[9 ][8  ] = strtod(B_109 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_B_1010), WM_GETTEXT, 10, (LPARAM)B_1010); matrixB[9 ][9  ] = strtod(B_1010,0 );//


}
void R_TO_A_deci(HWND h) {
	    char R_11	 [10]="";
		char R_12	 [10]="";
		char R_13	 [10]="";
		char R_14	 [10]="";
		char R_15	 [10]="";
		char R_16	 [10]="";
		char R_17	 [10]="";
		char R_18	 [10]="";
		char R_19	 [10]="";
		char R_110	 [10]="";
		char R_21	 [10]="";
		char R_22	 [10]="";
		char R_23	 [10]="";
		char R_24	 [10]="";
		char R_25	 [10]="";
		char R_26	 [10]="";
		char R_27	 [10]="";
		char R_28	 [10]="";
		char R_29	 [10]="";
		char R_210	 [10]="";
		char R_31	 [10]="";
		char R_32	 [10]="";
		char R_33	 [10]="";
		char R_34	 [10]="";
		char R_35	 [10]="";
		char R_36	 [10]="";
		char R_37	 [10]="";
		char R_38	 [10]="";
		char R_39	 [10]="";
		char R_310	 [10]="";
		char R_41	 [10]="";
		char R_42	 [10]="";
		char R_43	 [10]="";
		char R_44	 [10]="";
		char R_45	 [10]="";
		char R_46	 [10]="";
		char R_47	 [10]="";
		char R_48	 [10]="";
		char R_49	 [10]="";
		char R_410	 [10]="";
		char R_51	 [10]="";
		char R_52	 [10]="";
		char R_53	 [10]="";
		char R_54	 [10]="";
		char R_55	 [10]="";
		char R_56	 [10]="";
		char R_57	 [10]="";
		char R_58	 [10]="";
		char R_59	 [10]="";
		char R_510	 [10]="";
		char R_61	 [10]="";
		char R_62	 [10]="";
		char R_63	 [10]="";
		char R_64	 [10]="";
		char R_65	 [10]="";
		char R_66	 [10]="";
		char R_67	 [10]="";
		char R_68	 [10]="";
		char R_69	 [10]="";
		char R_610	 [10]="";
		char R_71	 [10]="";
		char R_72	 [10]="";
		char R_73	 [10]="";
		char R_74	 [10]="";
		char R_75	 [10]="";
		char R_76	 [10]="";
		char R_77	 [10]="";
		char R_78	 [10]="";
		char R_79	 [10]="";
		char R_710	 [10]="";
		char R_81	 [10]="";
		char R_82	 [10]="";
		char R_83	 [10]="";
		char R_84	 [10]="";
		char R_85	 [10]="";
		char R_86	 [10]="";
		char R_87	 [10]="";
		char R_88	 [10]="";
		char R_89	 [10]="";
		char R_810	 [10]="";
		char R_91	 [10]="";
		char R_92	 [10]="";
		char R_93	 [10]="";
		char R_94	 [10]="";
		char R_95	 [10]="";
		char R_96	 [10]="";
		char R_97	 [10]="";
		char R_98	 [10]="";
		char R_99	 [10]="";
		char R_910	 [10]="";
		char R_101	 [10]="";
		char R_102	 [10]="";
		char R_103	 [10]="";
		char R_104	 [10]="";
		char R_105	 [10]="";
		char R_106	 [10]="";
		char R_107	 [10]="";
		char R_108	 [10]="";
		char R_109	 [10]="";
		char R_1010	 [10]="";



	SendMessage(GetDlgItem(h, IDC_EDIT_R_11  ), WM_GETTEXT, 10, (LPARAM)R_11  ); matrixA[0 ][0  ] = strtod(R_11  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_12  ), WM_GETTEXT, 10, (LPARAM)R_12  ); matrixA[0 ][1  ] = strtod(R_12  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_13  ), WM_GETTEXT, 10, (LPARAM)R_13  ); matrixA[0 ][2  ] = strtod(R_13  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_14  ), WM_GETTEXT, 10, (LPARAM)R_14  ); matrixA[0 ][3  ] = strtod(R_14  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_15  ), WM_GETTEXT, 10, (LPARAM)R_15  ); matrixA[0 ][4  ] = strtod(R_15  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_16  ), WM_GETTEXT, 10, (LPARAM)R_16  ); matrixA[0 ][5  ] = strtod(R_16  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_17  ), WM_GETTEXT, 10, (LPARAM)R_17  ); matrixA[0 ][6  ] = strtod(R_17  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_18  ), WM_GETTEXT, 10, (LPARAM)R_18  ); matrixA[0 ][7  ] = strtod(R_18  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_19  ), WM_GETTEXT, 10, (LPARAM)R_19  ); matrixA[0 ][8  ] = strtod(R_19  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_110 ), WM_GETTEXT, 10, (LPARAM)R_110 ); matrixA[0 ][9  ] = strtod(R_110 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_21  ), WM_GETTEXT, 10, (LPARAM)R_21  ); matrixA[1 ][0  ] = strtod(R_21  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_22  ), WM_GETTEXT, 10, (LPARAM)R_22  ); matrixA[1 ][1  ] = strtod(R_22  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_23  ), WM_GETTEXT, 10, (LPARAM)R_23  ); matrixA[1 ][2  ] = strtod(R_23  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_24  ), WM_GETTEXT, 10, (LPARAM)R_24  ); matrixA[1 ][3  ] = strtod(R_24  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_25  ), WM_GETTEXT, 10, (LPARAM)R_25  ); matrixA[1 ][4  ] = strtod(R_25  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_26  ), WM_GETTEXT, 10, (LPARAM)R_26  ); matrixA[1 ][5  ] = strtod(R_26  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_27  ), WM_GETTEXT, 10, (LPARAM)R_27  ); matrixA[1 ][6  ] = strtod(R_27  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_28  ), WM_GETTEXT, 10, (LPARAM)R_28  ); matrixA[1 ][7  ] = strtod(R_28  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_29  ), WM_GETTEXT, 10, (LPARAM)R_29  ); matrixA[1 ][8  ] = strtod(R_29  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_210 ), WM_GETTEXT, 10, (LPARAM)R_210 ); matrixA[1 ][9  ] = strtod(R_210 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_31  ), WM_GETTEXT, 10, (LPARAM)R_31  ); matrixA[2 ][0  ] = strtod(R_31  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_32  ), WM_GETTEXT, 10, (LPARAM)R_32  ); matrixA[2 ][1  ] = strtod(R_32  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_33  ), WM_GETTEXT, 10, (LPARAM)R_33  ); matrixA[2 ][2  ] = strtod(R_33  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_34  ), WM_GETTEXT, 10, (LPARAM)R_34  ); matrixA[2 ][3  ] = strtod(R_34  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_35  ), WM_GETTEXT, 10, (LPARAM)R_35  ); matrixA[2 ][4  ] = strtod(R_35  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_36  ), WM_GETTEXT, 10, (LPARAM)R_36  ); matrixA[2 ][5  ] = strtod(R_36  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_37  ), WM_GETTEXT, 10, (LPARAM)R_37  ); matrixA[2 ][6  ] = strtod(R_37  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_38  ), WM_GETTEXT, 10, (LPARAM)R_38  ); matrixA[2 ][7  ] = strtod(R_38  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_39  ), WM_GETTEXT, 10, (LPARAM)R_39  ); matrixA[2 ][8  ] = strtod(R_39  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_310 ), WM_GETTEXT, 10, (LPARAM)R_310 ); matrixA[2 ][9  ] = strtod(R_310 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_41  ), WM_GETTEXT, 10, (LPARAM)R_41  ); matrixA[3 ][0  ] = strtod(R_41  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_42  ), WM_GETTEXT, 10, (LPARAM)R_42  ); matrixA[3 ][1  ] = strtod(R_42  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_43  ), WM_GETTEXT, 10, (LPARAM)R_43  ); matrixA[3 ][2  ] = strtod(R_43  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_44  ), WM_GETTEXT, 10, (LPARAM)R_44  ); matrixA[3 ][3  ] = strtod(R_44  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_45  ), WM_GETTEXT, 10, (LPARAM)R_45  ); matrixA[3 ][4  ] = strtod(R_45  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_46  ), WM_GETTEXT, 10, (LPARAM)R_46  ); matrixA[3 ][5  ] = strtod(R_46  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_47  ), WM_GETTEXT, 10, (LPARAM)R_47  ); matrixA[3 ][6  ] = strtod(R_47  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_48  ), WM_GETTEXT, 10, (LPARAM)R_48  ); matrixA[3 ][7  ] = strtod(R_48  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_49  ), WM_GETTEXT, 10, (LPARAM)R_49  ); matrixA[3 ][8  ] = strtod(R_49  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_410 ), WM_GETTEXT, 10, (LPARAM)R_410 ); matrixA[3 ][9  ] = strtod(R_410 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_51  ), WM_GETTEXT, 10, (LPARAM)R_51  ); matrixA[4 ][0  ] = strtod(R_51  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_52  ), WM_GETTEXT, 10, (LPARAM)R_52  ); matrixA[4 ][1  ] = strtod(R_52  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_53  ), WM_GETTEXT, 10, (LPARAM)R_53  ); matrixA[4 ][2  ] = strtod(R_53  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_54  ), WM_GETTEXT, 10, (LPARAM)R_54  ); matrixA[4 ][3  ] = strtod(R_54  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_55  ), WM_GETTEXT, 10, (LPARAM)R_55  ); matrixA[4 ][4  ] = strtod(R_55  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_56  ), WM_GETTEXT, 10, (LPARAM)R_56  ); matrixA[4 ][5  ] = strtod(R_56  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_57  ), WM_GETTEXT, 10, (LPARAM)R_57  ); matrixA[4 ][6  ] = strtod(R_57  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_58  ), WM_GETTEXT, 10, (LPARAM)R_58  ); matrixA[4 ][7  ] = strtod(R_58  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_59  ), WM_GETTEXT, 10, (LPARAM)R_59  ); matrixA[4 ][8  ] = strtod(R_59  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_510 ), WM_GETTEXT, 10, (LPARAM)R_510 ); matrixA[4 ][9  ] = strtod(R_510 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_61  ), WM_GETTEXT, 10, (LPARAM)R_61  ); matrixA[5 ][0  ] = strtod(R_61  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_62  ), WM_GETTEXT, 10, (LPARAM)R_62  ); matrixA[5 ][1  ] = strtod(R_62  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_63  ), WM_GETTEXT, 10, (LPARAM)R_63  ); matrixA[5 ][2  ] = strtod(R_63  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_64  ), WM_GETTEXT, 10, (LPARAM)R_64  ); matrixA[5 ][3  ] = strtod(R_64  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_65  ), WM_GETTEXT, 10, (LPARAM)R_65  ); matrixA[5 ][4  ] = strtod(R_65  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_66  ), WM_GETTEXT, 10, (LPARAM)R_66  ); matrixA[5 ][5  ] = strtod(R_66  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_67  ), WM_GETTEXT, 10, (LPARAM)R_67  ); matrixA[5 ][6  ] = strtod(R_67  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_68  ), WM_GETTEXT, 10, (LPARAM)R_68  ); matrixA[5 ][7  ] = strtod(R_68  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_69  ), WM_GETTEXT, 10, (LPARAM)R_69  ); matrixA[5 ][8  ] = strtod(R_69  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_610 ), WM_GETTEXT, 10, (LPARAM)R_610 ); matrixA[5 ][9  ] = strtod(R_610 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_71  ), WM_GETTEXT, 10, (LPARAM)R_71  ); matrixA[6 ][0  ] = strtod(R_71  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_72  ), WM_GETTEXT, 10, (LPARAM)R_72  ); matrixA[6 ][1  ] = strtod(R_72  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_73  ), WM_GETTEXT, 10, (LPARAM)R_73  ); matrixA[6 ][2  ] = strtod(R_73  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_74  ), WM_GETTEXT, 10, (LPARAM)R_74  ); matrixA[6 ][3  ] = strtod(R_74  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_75  ), WM_GETTEXT, 10, (LPARAM)R_75  ); matrixA[6 ][4  ] = strtod(R_75  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_76  ), WM_GETTEXT, 10, (LPARAM)R_76  ); matrixA[6 ][5  ] = strtod(R_76  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_77  ), WM_GETTEXT, 10, (LPARAM)R_77  ); matrixA[6 ][6  ] = strtod(R_77  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_78  ), WM_GETTEXT, 10, (LPARAM)R_78  ); matrixA[6 ][7  ] = strtod(R_78  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_79  ), WM_GETTEXT, 10, (LPARAM)R_79  ); matrixA[6 ][8  ] = strtod(R_79  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_710 ), WM_GETTEXT, 10, (LPARAM)R_710 ); matrixA[6 ][9  ] = strtod(R_710 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_81  ), WM_GETTEXT, 10, (LPARAM)R_81  ); matrixA[7 ][0  ] = strtod(R_81  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_82  ), WM_GETTEXT, 10, (LPARAM)R_82  ); matrixA[7 ][1  ] = strtod(R_82  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_83  ), WM_GETTEXT, 10, (LPARAM)R_83  ); matrixA[7 ][2  ] = strtod(R_83  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_84  ), WM_GETTEXT, 10, (LPARAM)R_84  ); matrixA[7 ][3  ] = strtod(R_84  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_85  ), WM_GETTEXT, 10, (LPARAM)R_85  ); matrixA[7 ][4  ] = strtod(R_85  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_86  ), WM_GETTEXT, 10, (LPARAM)R_86  ); matrixA[7 ][5  ] = strtod(R_86  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_87  ), WM_GETTEXT, 10, (LPARAM)R_87  ); matrixA[7 ][6  ] = strtod(R_87  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_88  ), WM_GETTEXT, 10, (LPARAM)R_88  ); matrixA[7 ][7  ] = strtod(R_88  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_89  ), WM_GETTEXT, 10, (LPARAM)R_89  ); matrixA[7 ][8  ] = strtod(R_89  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_810 ), WM_GETTEXT, 10, (LPARAM)R_810 ); matrixA[7 ][9  ] = strtod(R_810 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_91  ), WM_GETTEXT, 10, (LPARAM)R_91  ); matrixA[8 ][0  ] = strtod(R_91  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_92  ), WM_GETTEXT, 10, (LPARAM)R_92  ); matrixA[8 ][1  ] = strtod(R_92  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_93  ), WM_GETTEXT, 10, (LPARAM)R_93  ); matrixA[8 ][2  ] = strtod(R_93  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_94  ), WM_GETTEXT, 10, (LPARAM)R_94  ); matrixA[8 ][3  ] = strtod(R_94  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_95  ), WM_GETTEXT, 10, (LPARAM)R_95  ); matrixA[8 ][4  ] = strtod(R_95  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_96  ), WM_GETTEXT, 10, (LPARAM)R_96  ); matrixA[8 ][5  ] = strtod(R_96  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_97  ), WM_GETTEXT, 10, (LPARAM)R_97  ); matrixA[8 ][6  ] = strtod(R_97  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_98  ), WM_GETTEXT, 10, (LPARAM)R_98  ); matrixA[8 ][7  ] = strtod(R_98  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_99  ), WM_GETTEXT, 10, (LPARAM)R_99  ); matrixA[8 ][8  ] = strtod(R_99  ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_910 ), WM_GETTEXT, 10, (LPARAM)R_910 ); matrixA[8 ][9  ] = strtod(R_910 ,0 );//
	SendMessage(GetDlgItem(h, IDC_EDIT_R_101 ), WM_GETTEXT, 10, (LPARAM)R_101 ); matrixA[9 ][0  ] = strtod(R_101 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_102 ), WM_GETTEXT, 10, (LPARAM)R_102 ); matrixA[9 ][1  ] = strtod(R_102 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_103 ), WM_GETTEXT, 10, (LPARAM)R_103 ); matrixA[9 ][2  ] = strtod(R_103 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_104 ), WM_GETTEXT, 10, (LPARAM)R_104 ); matrixA[9 ][3  ] = strtod(R_104 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_105 ), WM_GETTEXT, 10, (LPARAM)R_105 ); matrixA[9 ][4  ] = strtod(R_105 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_106 ), WM_GETTEXT, 10, (LPARAM)R_106 ); matrixA[9 ][5  ] = strtod(R_106 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_107 ), WM_GETTEXT, 10, (LPARAM)R_107 ); matrixA[9 ][6  ] = strtod(R_107 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_108 ), WM_GETTEXT, 10, (LPARAM)R_108 ); matrixA[9 ][7  ] = strtod(R_108 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_109 ), WM_GETTEXT, 10, (LPARAM)R_109 ); matrixA[9 ][8  ] = strtod(R_109 ,0 );
	SendMessage(GetDlgItem(h, IDC_EDIT_R_1010), WM_GETTEXT, 10, (LPARAM)R_1010); matrixA[9 ][9  ] = strtod(R_1010,0 );//


	SetWindowText(GetDlgItem(h, IDC_EDIT_A_11),   R_11  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_12),   R_12  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_13),   R_13  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_14),   R_14  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_15),   R_15  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_16),   R_16  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_17),   R_17  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_18),   R_18  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_19),   R_19  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_110),  R_110 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_21),   R_21  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_22),   R_22  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_23),   R_23  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_24),   R_24  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_25),   R_25  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_26),   R_26  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_27),   R_27  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_28),   R_28  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_29),   R_29  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_210),  R_210 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_31),   R_31  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_32),   R_32  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_33),   R_33  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_34),   R_34  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_35),   R_35  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_36),   R_36  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_37),   R_37  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_38),   R_38  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_39),   R_39  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_310),  R_310 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_41),   R_41  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_42),   R_42  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_43),   R_43  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_44),   R_44  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_45),   R_45  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_46),   R_46  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_47),   R_47  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_48),   R_48  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_49),   R_49  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_410),  R_410 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_51),   R_51  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_52),   R_52  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_53),   R_53  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_54),   R_54  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_55),   R_55  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_56),   R_56  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_57),   R_57  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_58),   R_58  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_59),   R_59  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_510),  R_510 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_61),   R_61  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_62),   R_62  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_63),   R_63  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_64),   R_64  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_65),   R_65  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_66),   R_66  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_67),   R_67  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_68),   R_68  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_69),   R_69  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_610),  R_610 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_71),   R_71  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_72),   R_72  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_73),   R_73  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_74),   R_74  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_75),   R_75  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_76),   R_76  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_77),   R_77  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_78),   R_78  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_79),   R_79  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_710),  R_710 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_81),   R_81  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_82),   R_82  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_83),   R_83  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_84),   R_84  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_85),   R_85  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_86),   R_86  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_87),   R_87  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_88),   R_88  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_89),   R_89  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_810),  R_810 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_91),   R_91  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_92),   R_92  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_93),   R_93  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_94),   R_94  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_95),   R_95  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_96),   R_96  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_97),   R_97  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_98),   R_98  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_99),   R_99  );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_910),  R_910 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_101),  R_101 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_102),  R_102 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_103),  R_103 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_104),  R_104 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_105),  R_105 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_106),  R_106 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_107),  R_107 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_108),  R_108 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_109),  R_109 );
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_1010), R_1010);





}

void EscribriResultado(HWND h) {
	    char R_11	 [10]="";
		char R_12	 [10]="";
		char R_13	 [10]="";
		char R_14	 [10]="";
		char R_15	 [10]="";
		char R_16	 [10]="";
		char R_17	 [10]="";
		char R_18	 [10]="";
		char R_19	 [10]="";
		char R_110	 [10]="";
		char R_21	 [10]="";
		char R_22	 [10]="";
		char R_23	 [10]="";
		char R_24	 [10]="";
		char R_25	 [10]="";
		char R_26	 [10]="";
		char R_27	 [10]="";
		char R_28	 [10]="";
		char R_29	 [10]="";
		char R_210	 [10]="";
		char R_31	 [10]="";
		char R_32	 [10]="";
		char R_33	 [10]="";
		char R_34	 [10]="";
		char R_35	 [10]="";
		char R_36	 [10]="";
		char R_37	 [10]="";
		char R_38	 [10]="";
		char R_39	 [10]="";
		char R_310	 [10]="";
		char R_41	 [10]="";
		char R_42	 [10]="";
		char R_43	 [10]="";
		char R_44	 [10]="";
		char R_45	 [10]="";
		char R_46	 [10]="";
		char R_47	 [10]="";
		char R_48	 [10]="";
		char R_49	 [10]="";
		char R_410	 [10]="";
		char R_51	 [10]="";
		char R_52	 [10]="";
		char R_53	 [10]="";
		char R_54	 [10]="";
		char R_55	 [10]="";
		char R_56	 [10]="";
		char R_57	 [10]="";
		char R_58	 [10]="";
		char R_59	 [10]="";
		char R_510	 [10]="";
		char R_61	 [10]="";
		char R_62	 [10]="";
		char R_63	 [10]="";
		char R_64	 [10]="";
		char R_65	 [10]="";
		char R_66	 [10]="";
		char R_67	 [10]="";
		char R_68	 [10]="";
		char R_69	 [10]="";
		char R_610	 [10]="";
		char R_71	 [10]="";
		char R_72	 [10]="";
		char R_73	 [10]="";
		char R_74	 [10]="";
		char R_75	 [10]="";
		char R_76	 [10]="";
		char R_77	 [10]="";
		char R_78	 [10]="";
		char R_79	 [10]="";
		char R_710	 [10]="";
		char R_81	 [10]="";
		char R_82	 [10]="";
		char R_83	 [10]="";
		char R_84	 [10]="";
		char R_85	 [10]="";
		char R_86	 [10]="";
		char R_87	 [10]="";
		char R_88	 [10]="";
		char R_89	 [10]="";
		char R_810	 [10]="";
		char R_91	 [10]="";
		char R_92	 [10]="";
		char R_93	 [10]="";
		char R_94	 [10]="";
		char R_95	 [10]="";
		char R_96	 [10]="";
		char R_97	 [10]="";
		char R_98	 [10]="";
		char R_99	 [10]="";
		char R_910	 [10]="";
		char R_101	 [10]="";
		char R_102	 [10]="";
		char R_103	 [10]="";
		char R_104	 [10]="";
		char R_105	 [10]="";
		char R_106	 [10]="";
		char R_107	 [10]="";
		char R_108	 [10]="";
		char R_109	 [10]="";
		char R_1010	 [10]="";



	_itoa (result[0 ][0  ] ,R_11  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_11),   R_11  );
	_itoa (result[0 ][1  ] ,R_12  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_12),   R_12  );
	_itoa (result[0 ][2  ] ,R_13  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_13),   R_13  );
	_itoa (result[0 ][3  ] ,R_14  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_14),   R_14  );
	_itoa (result[0 ][4  ] ,R_15  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_15),   R_15  );
	_itoa (result[0 ][5  ] ,R_16  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_16),   R_16  );
	_itoa (result[0 ][6  ] ,R_17  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_17),   R_17  );
	_itoa (result[0 ][7  ] ,R_18  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_18),   R_18  );
	_itoa (result[0 ][8  ] ,R_19  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_19),   R_19  );
	_itoa (result[0 ][9  ] ,R_110 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_110),  R_110 );
	_itoa (result[1 ][0  ] ,R_21  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_21),   R_21  );
	_itoa (result[1 ][1  ] ,R_22  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_22),   R_22  );
	_itoa (result[1 ][2  ] ,R_23  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_23),   R_23  );
	_itoa (result[1 ][3  ] ,R_24  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_24),   R_24  );
	_itoa (result[1 ][4  ] ,R_25  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_25),   R_25  );
	_itoa (result[1 ][5  ] ,R_26  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_26),   R_26  );
	_itoa (result[1 ][6  ] ,R_27  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_27),   R_27  );
	_itoa (result[1 ][7  ] ,R_28  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_28),   R_28  );
	_itoa (result[1 ][8  ] ,R_29  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_29),   R_29  );
	_itoa (result[1 ][9  ] ,R_210 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_210),  R_210 );
	_itoa (result[2 ][0  ] ,R_31  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_31),   R_31  );
	_itoa (result[2 ][1  ] ,R_32  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_32),   R_32  );
	_itoa (result[2 ][2  ] ,R_33  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_33),   R_33  );
	_itoa (result[2 ][3  ] ,R_34  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_34),   R_34  );
	_itoa (result[2 ][4  ] ,R_35  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_35),   R_35  );
	_itoa (result[2 ][5  ] ,R_36  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_36),   R_36  );
	_itoa (result[2 ][6  ] ,R_37  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_37),   R_37  );
	_itoa (result[2 ][7  ] ,R_38  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_38),   R_38  );
	_itoa (result[2 ][8  ] ,R_39  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_39),   R_39  );
	_itoa (result[2 ][9  ] ,R_310 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_310),  R_310 );
	_itoa (result[3 ][0  ] ,R_41  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_41),   R_41  );
	_itoa (result[3 ][1  ] ,R_42  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_42),   R_42  );
	_itoa (result[3 ][2  ] ,R_43  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_43),   R_43  );
	_itoa (result[3 ][3  ] ,R_44  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_44),   R_44  );
	_itoa (result[3 ][4  ] ,R_45  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_45),   R_45  );
	_itoa (result[3 ][5  ] ,R_46  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_46),   R_46  );
	_itoa (result[3 ][6  ] ,R_47  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_47),   R_47  );
	_itoa (result[3 ][7  ] ,R_48  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_48),   R_48  );
	_itoa (result[3 ][8  ] ,R_49  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_49),   R_49  );
	_itoa (result[3 ][9  ] ,R_410 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_410),  R_410 );
	_itoa (result[4 ][0  ] ,R_51  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_51),   R_51  );
	_itoa (result[4 ][1  ] ,R_52  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_52),   R_52  );
	_itoa (result[4 ][2  ] ,R_53  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_53),   R_53  );
	_itoa (result[4 ][3  ] ,R_54  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_54),   R_54  );
	_itoa (result[4 ][4  ] ,R_55  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_55),   R_55  );
	_itoa (result[4 ][5  ] ,R_56  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_56),   R_56  );
	_itoa (result[4 ][6  ] ,R_57  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_57),   R_57  );
	_itoa (result[4 ][7  ] ,R_58  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_58),   R_58  );
	_itoa (result[4 ][8  ] ,R_59  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_59),   R_59  );
	_itoa (result[4 ][9  ] ,R_510 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_510),  R_510 );
	_itoa (result[5 ][0  ] ,R_61  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_61),   R_61  );
	_itoa (result[5 ][1  ] ,R_62  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_62),   R_62  );
	_itoa (result[5 ][2  ] ,R_63  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_63),   R_63  );
	_itoa (result[5 ][3  ] ,R_64  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_64),   R_64  );
	_itoa (result[5 ][4  ] ,R_65  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_65),   R_65  );
	_itoa (result[5 ][5  ] ,R_66  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_66),   R_66  );
	_itoa (result[5 ][6  ] ,R_67  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_67),   R_67  );
	_itoa (result[5 ][7  ] ,R_68  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_68),   R_68  );
	_itoa (result[5 ][8  ] ,R_69  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_69),   R_69  );
	_itoa (result[5 ][9  ] ,R_610 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_610),  R_610 );
	_itoa (result[6 ][0  ] ,R_71  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_71),   R_71  );
	_itoa (result[6 ][1  ] ,R_72  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_72),   R_72  );
	_itoa (result[6 ][2  ] ,R_73  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_73),   R_73  );
	_itoa (result[6 ][3  ] ,R_74  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_74),   R_74  );
	_itoa (result[6 ][4  ] ,R_75  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_75),   R_75  );
	_itoa (result[6 ][5  ] ,R_76  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_76),   R_76  );
	_itoa (result[6 ][6  ] ,R_77  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_77),   R_77  );
	_itoa (result[6 ][7  ] ,R_78  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_78),   R_78  );
	_itoa (result[6 ][8  ] ,R_79  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_79),   R_79  );
	_itoa (result[6 ][9  ] ,R_710 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_710),  R_710 );
	_itoa (result[7 ][0  ] ,R_81  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_81),   R_81  );
	_itoa (result[7 ][1  ] ,R_82  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_82),   R_82  );
	_itoa (result[7 ][2  ] ,R_83  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_83),   R_83  );
	_itoa (result[7 ][3  ] ,R_84  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_84),   R_84  );
	_itoa (result[7 ][4  ] ,R_85  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_85),   R_85  );
	_itoa (result[7 ][5  ] ,R_86  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_86),   R_86  );
	_itoa (result[7 ][6  ] ,R_87  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_87),   R_87  );
	_itoa (result[7 ][7  ] ,R_88  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_88),   R_88  );
	_itoa (result[7 ][8  ] ,R_89  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_89),   R_89  );
	_itoa (result[7 ][9  ] ,R_810 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_810),  R_810 );
	_itoa (result[8 ][0  ] ,R_91  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_91),   R_91  );
	_itoa (result[8 ][1  ] ,R_92  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_92),   R_92  );
	_itoa (result[8 ][2  ] ,R_93  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_93),   R_93  );
	_itoa (result[8 ][3  ] ,R_94  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_94),   R_94  );
	_itoa (result[8 ][4  ] ,R_95  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_95),   R_95  );
	_itoa (result[8 ][5  ] ,R_96  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_96),   R_96  );
	_itoa (result[8 ][6  ] ,R_97  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_97),   R_97  );
	_itoa (result[8 ][7  ] ,R_98  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_98),   R_98  );
	_itoa (result[8 ][8  ] ,R_99  ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_99),   R_99  );
	_itoa (result[8 ][9  ] ,R_910 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_910),  R_910 );
	_itoa (result[9 ][0  ] ,R_101 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_101),  R_101 );
	_itoa (result[9 ][1  ] ,R_102 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_102),  R_102 );
	_itoa (result[9 ][2  ] ,R_103 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_103),  R_103 );
	_itoa (result[9 ][3  ] ,R_104 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_104),  R_104 );
	_itoa (result[9 ][4  ] ,R_105 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_105),  R_105 );
	_itoa (result[9 ][5  ] ,R_106 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_106),  R_106 );
	_itoa (result[9 ][6  ] ,R_107 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_107),  R_107 );
	_itoa (result[9 ][7  ] ,R_108 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_108),  R_108 );
	_itoa (result[9 ][8  ] ,R_109 ,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_109),  R_109 );
	_itoa (result[9 ][9  ] ,R_1010,10); SetWindowText(GetDlgItem(h, IDC_EDIT_R_1010), R_1010);






}
void EscribriResultado_con_decilames(HWND h) {
	   
	    





	    char R_11	 [10]="";
		char R_12	 [10]="";
		char R_13	 [10]="";
		char R_14	 [10]="";
		char R_15	 [10]="";
		char R_16	 [10]="";
		char R_17	 [10]="";
		char R_18	 [10]="";
		char R_19	 [10]="";
		char R_110	 [10]="";
		char R_21	 [10]="";
		char R_22	 [10]="";
		char R_23	 [10]="";
		char R_24	 [10]="";
		char R_25	 [10]="";
		char R_26	 [10]="";
		char R_27	 [10]="";
		char R_28	 [10]="";
		char R_29	 [10]="";
		char R_210	 [10]="";
		char R_31	 [10]="";
		char R_32	 [10]="";
		char R_33	 [10]="";
		char R_34	 [10]="";
		char R_35	 [10]="";
		char R_36	 [10]="";
		char R_37	 [10]="";
		char R_38	 [10]="";
		char R_39	 [10]="";
		char R_310	 [10]="";
		char R_41	 [10]="";
		char R_42	 [10]="";
		char R_43	 [10]="";
		char R_44	 [10]="";
		char R_45	 [10]="";
		char R_46	 [10]="";
		char R_47	 [10]="";
		char R_48	 [10]="";
		char R_49	 [10]="";
		char R_410	 [10]="";
		char R_51	 [10]="";
		char R_52	 [10]="";
		char R_53	 [10]="";
		char R_54	 [10]="";
		char R_55	 [10]="";
		char R_56	 [10]="";
		char R_57	 [10]="";
		char R_58	 [10]="";
		char R_59	 [10]="";
		char R_510	 [10]="";
		char R_61	 [10]="";
		char R_62	 [10]="";
		char R_63	 [10]="";
		char R_64	 [10]="";
		char R_65	 [10]="";
		char R_66	 [10]="";
		char R_67	 [10]="";
		char R_68	 [10]="";
		char R_69	 [10]="";
		char R_610	 [10]="";
		char R_71	 [10]="";
		char R_72	 [10]="";
		char R_73	 [10]="";
		char R_74	 [10]="";
		char R_75	 [10]="";
		char R_76	 [10]="";
		char R_77	 [10]="";
		char R_78	 [10]="";
		char R_79	 [10]="";
		char R_710	 [10]="";
		char R_81	 [10]="";
		char R_82	 [10]="";
		char R_83	 [10]="";
		char R_84	 [10]="";
		char R_85	 [10]="";
		char R_86	 [10]="";
		char R_87	 [10]="";
		char R_88	 [10]="";
		char R_89	 [10]="";
		char R_810	 [10]="";
		char R_91	 [10]="";
		char R_92	 [10]="";
		char R_93	 [10]="";
		char R_94	 [10]="";
		char R_95	 [10]="";
		char R_96	 [10]="";
		char R_97	 [10]="";
		char R_98	 [10]="";
		char R_99	 [10]="";
		char R_910	 [10]="";
		char R_101	 [10]="";
		char R_102	 [10]="";
		char R_103	 [10]="";
		char R_104	 [10]="";
		char R_105	 [10]="";
		char R_106	 [10]="";
		char R_107	 [10]="";
		char R_108	 [10]="";
		char R_109	 [10]="";
		char R_1010	 [10]="";


	  snprintf(R_11  , sizeof R_11  , "%f",result[0 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_11),   R_11  );
	  snprintf(R_12  , sizeof R_12  , "%f",result[0 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_12),   R_12  );
	  snprintf(R_13  , sizeof R_13  , "%f",result[0 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_13),   R_13  );
	  snprintf(R_14  , sizeof R_14  , "%f",result[0 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_14),   R_14  );
	  snprintf(R_15  , sizeof R_15  , "%f",result[0 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_15),   R_15  );
	  snprintf(R_16  , sizeof R_16  , "%f",result[0 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_16),   R_16  );
	  snprintf(R_17  , sizeof R_17  , "%f",result[0 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_17),   R_17  );
	  snprintf(R_18  , sizeof R_18  , "%f",result[0 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_18),   R_18  );
	  snprintf(R_19  , sizeof R_19  , "%f",result[0 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_19),   R_19  );
	  snprintf(R_110 , sizeof R_110 , "%f",result[0 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_110),  R_110 );
	  snprintf(R_21  , sizeof R_21  , "%f",result[1 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_21),   R_21  );
	  snprintf(R_22  , sizeof R_22  , "%f",result[1 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_22),   R_22  );
	  snprintf(R_23  , sizeof R_23  , "%f",result[1 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_23),   R_23  );
	  snprintf(R_24  , sizeof R_24  , "%f",result[1 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_24),   R_24  );
	  snprintf(R_25  , sizeof R_25  , "%f",result[1 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_25),   R_25  );
	  snprintf(R_26  , sizeof R_26  , "%f",result[1 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_26),   R_26  );
	  snprintf(R_27  , sizeof R_27  , "%f",result[1 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_27),   R_27  );
	  snprintf(R_28  , sizeof R_28  , "%f",result[1 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_28),   R_28  );
	  snprintf(R_29  , sizeof R_29  , "%f",result[1 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_29),   R_29  );
	  snprintf(R_210 , sizeof R_210 , "%f",result[1 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_210),  R_210 );
	  snprintf(R_31  , sizeof R_31  , "%f",result[2 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_31),   R_31  );
	  snprintf(R_32  , sizeof R_32  , "%f",result[2 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_32),   R_32  );
	  snprintf(R_33  , sizeof R_33  , "%f",result[2 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_33),   R_33  );
	  snprintf(R_34  , sizeof R_34  , "%f",result[2 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_34),   R_34  );
	  snprintf(R_35  , sizeof R_35  , "%f",result[2 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_35),   R_35  );
	  snprintf(R_36  , sizeof R_36  , "%f",result[2 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_36),   R_36  );
	  snprintf(R_37  , sizeof R_37  , "%f",result[2 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_37),   R_37  );
	  snprintf(R_38  , sizeof R_38  , "%f",result[2 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_38),   R_38  );
	  snprintf(R_39  , sizeof R_39  , "%f",result[2 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_39),   R_39  );
	  snprintf(R_310 , sizeof R_310 , "%f",result[2 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_310),  R_310 );
	  snprintf(R_41  , sizeof R_41  , "%f",result[3 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_41),   R_41  );
	  snprintf(R_42  , sizeof R_42  , "%f",result[3 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_42),   R_42  );
	  snprintf(R_43  , sizeof R_43  , "%f",result[3 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_43),   R_43  );
	  snprintf(R_44  , sizeof R_44  , "%f",result[3 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_44),   R_44  );
	  snprintf(R_45  , sizeof R_45  , "%f",result[3 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_45),   R_45  );
	  snprintf(R_46  , sizeof R_46  , "%f",result[3 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_46),   R_46  );
	  snprintf(R_47  , sizeof R_47  , "%f",result[3 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_47),   R_47  );
	  snprintf(R_48  , sizeof R_48  , "%f",result[3 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_48),   R_48  );
	  snprintf(R_49  , sizeof R_49  , "%f",result[3 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_49),   R_49  );
	  snprintf(R_410 , sizeof R_410 , "%f",result[3 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_410),  R_410 );
	  snprintf(R_51  , sizeof R_51  , "%f",result[4 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_51),   R_51  );
	  snprintf(R_52  , sizeof R_52  , "%f",result[4 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_52),   R_52  );
	  snprintf(R_53  , sizeof R_53  , "%f",result[4 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_53),   R_53  );
	  snprintf(R_54  , sizeof R_54  , "%f",result[4 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_54),   R_54  );
	  snprintf(R_55  , sizeof R_55  , "%f",result[4 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_55),   R_55  );
	  snprintf(R_56  , sizeof R_56  , "%f",result[4 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_56),   R_56  );
	  snprintf(R_57  , sizeof R_57  , "%f",result[4 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_57),   R_57  );
	  snprintf(R_58  , sizeof R_58  , "%f",result[4 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_58),   R_58  );
	  snprintf(R_59  , sizeof R_59  , "%f",result[4 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_59),   R_59  );
	  snprintf(R_510 , sizeof R_510 , "%f",result[4 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_510),  R_510 );
	  snprintf(R_61  , sizeof R_61  , "%f",result[5 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_61),   R_61  );
	  snprintf(R_62  , sizeof R_62  , "%f",result[5 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_62),   R_62  );
	  snprintf(R_63  , sizeof R_63  , "%f",result[5 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_63),   R_63  );
	  snprintf(R_64  , sizeof R_64  , "%f",result[5 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_64),   R_64  );
	  snprintf(R_65  , sizeof R_65  , "%f",result[5 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_65),   R_65  );
	  snprintf(R_66  , sizeof R_66  , "%f",result[5 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_66),   R_66  );
	  snprintf(R_67  , sizeof R_67  , "%f",result[5 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_67),   R_67  );
	  snprintf(R_68  , sizeof R_68  , "%f",result[5 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_68),   R_68  );
	  snprintf(R_69  , sizeof R_69  , "%f",result[5 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_69),   R_69  );
	  snprintf(R_610 , sizeof R_610 , "%f",result[5 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_610),  R_610 );
	  snprintf(R_71  , sizeof R_71  , "%f",result[6 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_71),   R_71  );
	  snprintf(R_72  , sizeof R_72  , "%f",result[6 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_72),   R_72  );
	  snprintf(R_73  , sizeof R_73  , "%f",result[6 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_73),   R_73  );
	  snprintf(R_74  , sizeof R_74  , "%f",result[6 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_74),   R_74  );
	  snprintf(R_75  , sizeof R_75  , "%f",result[6 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_75),   R_75  );
	  snprintf(R_76  , sizeof R_76  , "%f",result[6 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_76),   R_76  );
	  snprintf(R_77  , sizeof R_77  , "%f",result[6 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_77),   R_77  );
	  snprintf(R_78  , sizeof R_78  , "%f",result[6 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_78),   R_78  );
	  snprintf(R_79  , sizeof R_79  , "%f",result[6 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_79),   R_79  );
	  snprintf(R_710 , sizeof R_710 , "%f",result[6 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_710),  R_710 );
	  snprintf(R_81  , sizeof R_81  , "%f",result[7 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_81),   R_81  );
	  snprintf(R_82  , sizeof R_82  , "%f",result[7 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_82),   R_82  );
	  snprintf(R_83  , sizeof R_83  , "%f",result[7 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_83),   R_83  );
	  snprintf(R_84  , sizeof R_84  , "%f",result[7 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_84),   R_84  );
	  snprintf(R_85  , sizeof R_85  , "%f",result[7 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_85),   R_85  );
	  snprintf(R_86  , sizeof R_86  , "%f",result[7 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_86),   R_86  );
	  snprintf(R_87  , sizeof R_87  , "%f",result[7 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_87),   R_87  );
	  snprintf(R_88  , sizeof R_88  , "%f",result[7 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_88),   R_88  );
	  snprintf(R_89  , sizeof R_89  , "%f",result[7 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_89),   R_89  );
	  snprintf(R_810 , sizeof R_810 , "%f",result[7 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_810),  R_810 );
	  snprintf(R_91  , sizeof R_91  , "%f",result[8 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_91),   R_91  );
	  snprintf(R_92  , sizeof R_92  , "%f",result[8 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_92),   R_92  );
	  snprintf(R_93  , sizeof R_93  , "%f",result[8 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_93),   R_93  );
	  snprintf(R_94  , sizeof R_94  , "%f",result[8 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_94),   R_94  );
	  snprintf(R_95  , sizeof R_95  , "%f",result[8 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_95),   R_95  );
	  snprintf(R_96  , sizeof R_96  , "%f",result[8 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_96),   R_96  );
	  snprintf(R_97  , sizeof R_97  , "%f",result[8 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_97),   R_97  );
	  snprintf(R_98  , sizeof R_98  , "%f",result[8 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_98),   R_98  );
	  snprintf(R_99  , sizeof R_99  , "%f",result[8 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_99),   R_99  );
	  snprintf(R_910 , sizeof R_910 , "%f",result[8 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_910),  R_910 );
	  snprintf(R_101 , sizeof R_101 , "%f",result[9 ][0  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_101),  R_101 );
	  snprintf(R_102 , sizeof R_102 , "%f",result[9 ][1  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_102),  R_102 );
	  snprintf(R_103 , sizeof R_103 , "%f",result[9 ][2  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_103),  R_103 );
	  snprintf(R_104 , sizeof R_104 , "%f",result[9 ][3  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_104),  R_104 );
	  snprintf(R_105 , sizeof R_105 , "%f",result[9 ][4  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_105),  R_105 );
	  snprintf(R_106 , sizeof R_106 , "%f",result[9 ][5  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_106),  R_106 );
	  snprintf(R_107 , sizeof R_107 , "%f",result[9 ][6  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_107),  R_107 );
	  snprintf(R_108 , sizeof R_108 , "%f",result[9 ][7  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_108),  R_108 );
	  snprintf(R_109 , sizeof R_109 , "%f",result[9 ][8  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_109),  R_109 );
	  snprintf(R_1010, sizeof R_1010, "%f",result[9 ][9  ]); SetWindowText(GetDlgItem(h, IDC_EDIT_R_1010), R_1010);




}
void borrarA(HWND h) {
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_11  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_12  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_13  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_14  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_15  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_16  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_17  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_18  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_19  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_110 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_21  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_22  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_23  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_24  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_25  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_26  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_27  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_28  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_29  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_210 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_31  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_32  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_33  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_34  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_35  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_36  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_37  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_38  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_39  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_310 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_41  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_42  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_43  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_44  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_45  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_46  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_47  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_48  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_49  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_410 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_51  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_52  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_53  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_54  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_55  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_56  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_57  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_58  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_59  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_510 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_61  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_62  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_63  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_64  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_65  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_66  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_67  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_68  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_69  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_610 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_71  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_72  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_73  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_74  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_75  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_76  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_77  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_78  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_79  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_710 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_81  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_82  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_83  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_84  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_85  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_86  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_87  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_88  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_89  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_810 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_91  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_92  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_93  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_94  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_95  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_96  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_97  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_98  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_99  ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_910 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_101 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_102 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_103 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_104 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_105 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_106 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_107 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_108 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_109 ), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_A_1010), 0);
}
void borrarB(HWND h) {
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_11), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_12), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_13), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_14), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_15), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_16), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_17), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_18), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_19), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_110), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_21), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_22), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_23), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_24), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_25), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_26), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_27), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_28), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_29), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_210), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_31), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_32), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_33), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_34), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_35), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_36), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_37), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_38), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_39), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_310), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_41), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_42), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_43), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_44), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_45), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_46), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_47), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_48), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_49), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_410), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_51), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_52), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_53), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_54), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_55), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_56), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_57), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_58), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_59), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_510), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_61), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_62), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_63), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_64), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_65), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_66), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_67), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_68), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_69), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_610), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_71), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_72), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_73), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_74), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_75), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_76), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_77), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_78), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_79), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_710), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_81), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_82), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_83), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_84), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_85), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_86), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_87), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_88), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_89), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_810), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_91), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_92), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_93), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_94), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_95), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_96), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_97), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_98), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_99), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_910), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_101), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_102), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_103), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_104), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_105), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_106), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_107), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_108), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_109), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_B_1010), 0);

}
void borrarR(HWND h) {
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_11), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_12), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_13), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_14), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_15), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_16), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_17), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_18), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_19), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_110), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_21), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_22), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_23), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_24), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_25), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_26), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_27), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_28), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_29), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_210), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_31), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_32), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_33), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_34), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_35), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_36), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_37), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_38), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_39), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_310), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_41), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_42), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_43), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_44), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_45), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_46), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_47), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_48), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_49), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_410), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_51), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_52), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_53), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_54), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_55), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_56), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_57), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_58), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_59), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_510), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_61), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_62), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_63), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_64), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_65), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_66), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_67), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_68), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_69), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_610), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_71), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_72), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_73), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_74), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_75), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_76), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_77), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_78), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_79), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_710), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_81), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_82), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_83), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_84), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_85), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_86), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_87), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_88), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_89), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_810), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_91), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_92), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_93), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_94), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_95), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_96), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_97), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_98), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_99), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_910), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_101), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_102), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_103), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_104), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_105), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_106), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_107), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_108), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_109), 0);
	SetWindowText(GetDlgItem(h, IDC_EDIT_R_1010), 0);

	for (int t = 0; t < 10; t++) {
		for (int t2 = 0; t2 < 10; t2++) {
			result[t][t2] = 0;
		}
	}

}
void Multiplicar(HWND h) {

	


	if (a2 == b1) {
		for (int i = 0; i < a1; i++) {
			for (int j = 0; j < b2; j++) {
				for (int k = 0; k < b1; k++) {
					result[i][j] += matrixA[i][k] * matrixB[k][j];
				}
			}
		}

		if (flag_aux == 1) { EscribriResultado(h); }
		else { EscribriResultado_con_decilames(h); }
		
	}
	else {
		MessageBox(h, "No se puede completar la multiplicación de matrices con estas matrices.", "Advertencia", MB_ICONWARNING);
		
	}
	

}
void Suma(HWND h) {

	if (a1 == b1 && a2 == b2) {
		for (int i = 0; i < a1; i++) {
			for (int j = 0; j < a2; j++) {
				result[i][j] = matrixA[i][j] + matrixB[i][j];
			}
		}
		if (flag_aux == 1) { EscribriResultado(h); }
		else { EscribriResultado_con_decilames(h); }
	}
	else {
		MessageBox(h, "No se puede completar la multiplicación de matrices con estas matrices.", "Advertencia", MB_ICONWARNING);

	}





}
void Resta(HWND h) {

	if (a1 == b1 && a2 == b2) {
		for (int i = 0; i < a1; i++) {
			for (int j = 0; j < a2; j++) {
				result[i][j] = matrixA[i][j] - matrixB[i][j];
			}
		}
		if (flag_aux == 1) { EscribriResultado(h); }
		else { EscribriResultado_con_decilames(h); }
	}
	else {
		MessageBox(h, "No se puede completar la multiplicación de matrices con estas matrices.", "Advertencia", MB_ICONWARNING);

	}


}

void handels(HWND sh) {
	HA[0].A[0] = GetDlgItem(sh, IDC_EDIT_A_11	);   SHA[0].A[0] = GetDlgItem(sh, IDC_EDIT_B_11	 );   SHAR[0].A[0] = GetDlgItem(sh, IDC_EDIT_R_11	 );
	HA[0].A[1] = GetDlgItem(sh, IDC_EDIT_A_12	);   SHA[0].A[1] = GetDlgItem(sh, IDC_EDIT_B_12	 );   SHAR[0].A[1] = GetDlgItem(sh, IDC_EDIT_R_12	 );
	HA[0].A[2] = GetDlgItem(sh, IDC_EDIT_A_13	);   SHA[0].A[2] = GetDlgItem(sh, IDC_EDIT_B_13	 );   SHAR[0].A[2] = GetDlgItem(sh, IDC_EDIT_R_13	 );
	HA[0].A[3] = GetDlgItem(sh, IDC_EDIT_A_14	);   SHA[0].A[3] = GetDlgItem(sh, IDC_EDIT_B_14	 );   SHAR[0].A[3] = GetDlgItem(sh, IDC_EDIT_R_14	 );
	HA[0].A[4] = GetDlgItem(sh, IDC_EDIT_A_15	);   SHA[0].A[4] = GetDlgItem(sh, IDC_EDIT_B_15	 );   SHAR[0].A[4] = GetDlgItem(sh, IDC_EDIT_R_15	 );
	HA[0].A[5] = GetDlgItem(sh, IDC_EDIT_A_16	);   SHA[0].A[5] = GetDlgItem(sh, IDC_EDIT_B_16	 );   SHAR[0].A[5] = GetDlgItem(sh, IDC_EDIT_R_16	 );
	HA[0].A[6] = GetDlgItem(sh, IDC_EDIT_A_17	);   SHA[0].A[6] = GetDlgItem(sh, IDC_EDIT_B_17	 );   SHAR[0].A[6] = GetDlgItem(sh, IDC_EDIT_R_17	 );
	HA[0].A[7] = GetDlgItem(sh, IDC_EDIT_A_18	);   SHA[0].A[7] = GetDlgItem(sh, IDC_EDIT_B_18	 );   SHAR[0].A[7] = GetDlgItem(sh, IDC_EDIT_R_18	 );
	HA[0].A[8] = GetDlgItem(sh, IDC_EDIT_A_19	);   SHA[0].A[8] = GetDlgItem(sh, IDC_EDIT_B_19	 );   SHAR[0].A[8] = GetDlgItem(sh, IDC_EDIT_R_19	 );
	HA[0].A[9] = GetDlgItem(sh, IDC_EDIT_A_110  );   SHA[0].A[9] = GetDlgItem(sh, IDC_EDIT_B_110 );   SHAR[0].A[9] = GetDlgItem(sh, IDC_EDIT_R_110 );
	HA[1].A[0] = GetDlgItem(sh, IDC_EDIT_A_21	);   SHA[1].A[0] = GetDlgItem(sh, IDC_EDIT_B_21	 );   SHAR[1].A[0] = GetDlgItem(sh, IDC_EDIT_R_21	 );
	HA[1].A[1] = GetDlgItem(sh, IDC_EDIT_A_22	);   SHA[1].A[1] = GetDlgItem(sh, IDC_EDIT_B_22	 );   SHAR[1].A[1] = GetDlgItem(sh, IDC_EDIT_R_22	 );
	HA[1].A[2] = GetDlgItem(sh, IDC_EDIT_A_23	);   SHA[1].A[2] = GetDlgItem(sh, IDC_EDIT_B_23	 );   SHAR[1].A[2] = GetDlgItem(sh, IDC_EDIT_R_23	 );
	HA[1].A[3] = GetDlgItem(sh, IDC_EDIT_A_24	);   SHA[1].A[3] = GetDlgItem(sh, IDC_EDIT_B_24	 );   SHAR[1].A[3] = GetDlgItem(sh, IDC_EDIT_R_24	 );
	HA[1].A[4] = GetDlgItem(sh, IDC_EDIT_A_25	);   SHA[1].A[4] = GetDlgItem(sh, IDC_EDIT_B_25	 );   SHAR[1].A[4] = GetDlgItem(sh, IDC_EDIT_R_25	 );
	HA[1].A[5] = GetDlgItem(sh, IDC_EDIT_A_26	);   SHA[1].A[5] = GetDlgItem(sh, IDC_EDIT_B_26	 );   SHAR[1].A[5] = GetDlgItem(sh, IDC_EDIT_R_26	 );
	HA[1].A[6] = GetDlgItem(sh, IDC_EDIT_A_27	);   SHA[1].A[6] = GetDlgItem(sh, IDC_EDIT_B_27	 );   SHAR[1].A[6] = GetDlgItem(sh, IDC_EDIT_R_27	 );
	HA[1].A[7] = GetDlgItem(sh, IDC_EDIT_A_28	);   SHA[1].A[7] = GetDlgItem(sh, IDC_EDIT_B_28	 );   SHAR[1].A[7] = GetDlgItem(sh, IDC_EDIT_R_28	 );
	HA[1].A[8] = GetDlgItem(sh, IDC_EDIT_A_29	);   SHA[1].A[8] = GetDlgItem(sh, IDC_EDIT_B_29	 );   SHAR[1].A[8] = GetDlgItem(sh, IDC_EDIT_R_29	 );
	HA[1].A[9] = GetDlgItem(sh, IDC_EDIT_A_210  );   SHA[1].A[9] = GetDlgItem(sh, IDC_EDIT_B_210 );   SHAR[1].A[9] = GetDlgItem(sh, IDC_EDIT_R_210 );
	HA[2].A[0] = GetDlgItem(sh, IDC_EDIT_A_31	);   SHA[2].A[0] = GetDlgItem(sh, IDC_EDIT_B_31	 );   SHAR[2].A[0] = GetDlgItem(sh, IDC_EDIT_R_31	 );
	HA[2].A[1] = GetDlgItem(sh, IDC_EDIT_A_32	);   SHA[2].A[1] = GetDlgItem(sh, IDC_EDIT_B_32	 );   SHAR[2].A[1] = GetDlgItem(sh, IDC_EDIT_R_32	 );
	HA[2].A[2] = GetDlgItem(sh, IDC_EDIT_A_33	);   SHA[2].A[2] = GetDlgItem(sh, IDC_EDIT_B_33	 );   SHAR[2].A[2] = GetDlgItem(sh, IDC_EDIT_R_33	 );
	HA[2].A[3] = GetDlgItem(sh, IDC_EDIT_A_34	);   SHA[2].A[3] = GetDlgItem(sh, IDC_EDIT_B_34	 );   SHAR[2].A[3] = GetDlgItem(sh, IDC_EDIT_R_34	 );
	HA[2].A[4] = GetDlgItem(sh, IDC_EDIT_A_35	);   SHA[2].A[4] = GetDlgItem(sh, IDC_EDIT_B_35	 );   SHAR[2].A[4] = GetDlgItem(sh, IDC_EDIT_R_35	 );
	HA[2].A[5] = GetDlgItem(sh, IDC_EDIT_A_36	);   SHA[2].A[5] = GetDlgItem(sh, IDC_EDIT_B_36	 );   SHAR[2].A[5] = GetDlgItem(sh, IDC_EDIT_R_36	 );
	HA[2].A[6] = GetDlgItem(sh, IDC_EDIT_A_37	);   SHA[2].A[6] = GetDlgItem(sh, IDC_EDIT_B_37	 );   SHAR[2].A[6] = GetDlgItem(sh, IDC_EDIT_R_37	 );
	HA[2].A[7] = GetDlgItem(sh, IDC_EDIT_A_38	);   SHA[2].A[7] = GetDlgItem(sh, IDC_EDIT_B_38	 );   SHAR[2].A[7] = GetDlgItem(sh, IDC_EDIT_R_38	 );
	HA[2].A[8] = GetDlgItem(sh, IDC_EDIT_A_39	);   SHA[2].A[8] = GetDlgItem(sh, IDC_EDIT_B_39	 );   SHAR[2].A[8] = GetDlgItem(sh, IDC_EDIT_R_39	 );
	HA[2].A[9] = GetDlgItem(sh, IDC_EDIT_A_310  );   SHA[2].A[9] = GetDlgItem(sh, IDC_EDIT_B_310 );   SHAR[2].A[9] = GetDlgItem(sh, IDC_EDIT_R_310 );
	HA[3].A[0] = GetDlgItem(sh, IDC_EDIT_A_41	);   SHA[3].A[0] = GetDlgItem(sh, IDC_EDIT_B_41	 );   SHAR[3].A[0] = GetDlgItem(sh, IDC_EDIT_R_41	 );
	HA[3].A[1] = GetDlgItem(sh, IDC_EDIT_A_42	);   SHA[3].A[1] = GetDlgItem(sh, IDC_EDIT_B_42	 );   SHAR[3].A[1] = GetDlgItem(sh, IDC_EDIT_R_42	 );
	HA[3].A[2] = GetDlgItem(sh, IDC_EDIT_A_43	);   SHA[3].A[2] = GetDlgItem(sh, IDC_EDIT_B_43	 );   SHAR[3].A[2] = GetDlgItem(sh, IDC_EDIT_R_43	 );
	HA[3].A[3] = GetDlgItem(sh, IDC_EDIT_A_44	);   SHA[3].A[3] = GetDlgItem(sh, IDC_EDIT_B_44	 );   SHAR[3].A[3] = GetDlgItem(sh, IDC_EDIT_R_44	 );
	HA[3].A[4] = GetDlgItem(sh, IDC_EDIT_A_45	);   SHA[3].A[4] = GetDlgItem(sh, IDC_EDIT_B_45	 );   SHAR[3].A[4] = GetDlgItem(sh, IDC_EDIT_R_45	 );
	HA[3].A[5] = GetDlgItem(sh, IDC_EDIT_A_46	);   SHA[3].A[5] = GetDlgItem(sh, IDC_EDIT_B_46	 );   SHAR[3].A[5] = GetDlgItem(sh, IDC_EDIT_R_46	 );
	HA[3].A[6] = GetDlgItem(sh, IDC_EDIT_A_47	);   SHA[3].A[6] = GetDlgItem(sh, IDC_EDIT_B_47	 );   SHAR[3].A[6] = GetDlgItem(sh, IDC_EDIT_R_47	 );
	HA[3].A[7] = GetDlgItem(sh, IDC_EDIT_A_48	);   SHA[3].A[7] = GetDlgItem(sh, IDC_EDIT_B_48	 );   SHAR[3].A[7] = GetDlgItem(sh, IDC_EDIT_R_48	 );
	HA[3].A[8] = GetDlgItem(sh, IDC_EDIT_A_49	);   SHA[3].A[8] = GetDlgItem(sh, IDC_EDIT_B_49	 );   SHAR[3].A[8] = GetDlgItem(sh, IDC_EDIT_R_49	 );
	HA[3].A[9] = GetDlgItem(sh, IDC_EDIT_A_410  );   SHA[3].A[9] = GetDlgItem(sh, IDC_EDIT_B_410 );   SHAR[3].A[9] = GetDlgItem(sh, IDC_EDIT_R_410 );
	HA[4].A[0] = GetDlgItem(sh, IDC_EDIT_A_51	);   SHA[4].A[0] = GetDlgItem(sh, IDC_EDIT_B_51	 );   SHAR[4].A[0] = GetDlgItem(sh, IDC_EDIT_R_51	 );
	HA[4].A[1] = GetDlgItem(sh, IDC_EDIT_A_52	);   SHA[4].A[1] = GetDlgItem(sh, IDC_EDIT_B_52	 );   SHAR[4].A[1] = GetDlgItem(sh, IDC_EDIT_R_52	 );
	HA[4].A[2] = GetDlgItem(sh, IDC_EDIT_A_53	);   SHA[4].A[2] = GetDlgItem(sh, IDC_EDIT_B_53	 );   SHAR[4].A[2] = GetDlgItem(sh, IDC_EDIT_R_53	 );
	HA[4].A[3] = GetDlgItem(sh, IDC_EDIT_A_54	);   SHA[4].A[3] = GetDlgItem(sh, IDC_EDIT_B_54	 );   SHAR[4].A[3] = GetDlgItem(sh, IDC_EDIT_R_54	 );
	HA[4].A[4] = GetDlgItem(sh, IDC_EDIT_A_55	);   SHA[4].A[4] = GetDlgItem(sh, IDC_EDIT_B_55	 );   SHAR[4].A[4] = GetDlgItem(sh, IDC_EDIT_R_55	 );
	HA[4].A[5] = GetDlgItem(sh, IDC_EDIT_A_56	);   SHA[4].A[5] = GetDlgItem(sh, IDC_EDIT_B_56	 );   SHAR[4].A[5] = GetDlgItem(sh, IDC_EDIT_R_56	 );
	HA[4].A[6] = GetDlgItem(sh, IDC_EDIT_A_57	);   SHA[4].A[6] = GetDlgItem(sh, IDC_EDIT_B_57	 );   SHAR[4].A[6] = GetDlgItem(sh, IDC_EDIT_R_57	 );
	HA[4].A[7] = GetDlgItem(sh, IDC_EDIT_A_58	);   SHA[4].A[7] = GetDlgItem(sh, IDC_EDIT_B_58	 );   SHAR[4].A[7] = GetDlgItem(sh, IDC_EDIT_R_58	 );
	HA[4].A[8] = GetDlgItem(sh, IDC_EDIT_A_59	);   SHA[4].A[8] = GetDlgItem(sh, IDC_EDIT_B_59	 );   SHAR[4].A[8] = GetDlgItem(sh, IDC_EDIT_R_59	 );
	HA[4].A[9] = GetDlgItem(sh, IDC_EDIT_A_510  );   SHA[4].A[9] = GetDlgItem(sh, IDC_EDIT_B_510 );   SHAR[4].A[9] = GetDlgItem(sh, IDC_EDIT_R_510 );
	HA[5].A[0] = GetDlgItem(sh, IDC_EDIT_A_61	);   SHA[5].A[0] = GetDlgItem(sh, IDC_EDIT_B_61	 );   SHAR[5].A[0] = GetDlgItem(sh, IDC_EDIT_R_61	 );
	HA[5].A[1] = GetDlgItem(sh, IDC_EDIT_A_62	);   SHA[5].A[1] = GetDlgItem(sh, IDC_EDIT_B_62	 );   SHAR[5].A[1] = GetDlgItem(sh, IDC_EDIT_R_62	 );
	HA[5].A[2] = GetDlgItem(sh, IDC_EDIT_A_63	);   SHA[5].A[2] = GetDlgItem(sh, IDC_EDIT_B_63	 );   SHAR[5].A[2] = GetDlgItem(sh, IDC_EDIT_R_63	 );
	HA[5].A[3] = GetDlgItem(sh, IDC_EDIT_A_64	);   SHA[5].A[3] = GetDlgItem(sh, IDC_EDIT_B_64	 );   SHAR[5].A[3] = GetDlgItem(sh, IDC_EDIT_R_64	 );
	HA[5].A[4] = GetDlgItem(sh, IDC_EDIT_A_65	);   SHA[5].A[4] = GetDlgItem(sh, IDC_EDIT_B_65	 );   SHAR[5].A[4] = GetDlgItem(sh, IDC_EDIT_R_65	 );
	HA[5].A[5] = GetDlgItem(sh, IDC_EDIT_A_66	);   SHA[5].A[5] = GetDlgItem(sh, IDC_EDIT_B_66	 );   SHAR[5].A[5] = GetDlgItem(sh, IDC_EDIT_R_66	 );
	HA[5].A[6] = GetDlgItem(sh, IDC_EDIT_A_67	);   SHA[5].A[6] = GetDlgItem(sh, IDC_EDIT_B_67	 );   SHAR[5].A[6] = GetDlgItem(sh, IDC_EDIT_R_67	 );
	HA[5].A[7] = GetDlgItem(sh, IDC_EDIT_A_68	);   SHA[5].A[7] = GetDlgItem(sh, IDC_EDIT_B_68	 );   SHAR[5].A[7] = GetDlgItem(sh, IDC_EDIT_R_68	 );
	HA[5].A[8] = GetDlgItem(sh, IDC_EDIT_A_69	);   SHA[5].A[8] = GetDlgItem(sh, IDC_EDIT_B_69	 );   SHAR[5].A[8] = GetDlgItem(sh, IDC_EDIT_R_69	 );
	HA[5].A[9] = GetDlgItem(sh, IDC_EDIT_A_610  );   SHA[5].A[9] = GetDlgItem(sh, IDC_EDIT_B_610 );   SHAR[5].A[9] = GetDlgItem(sh, IDC_EDIT_R_610 );
	HA[6].A[0] = GetDlgItem(sh, IDC_EDIT_A_71	);   SHA[6].A[0] = GetDlgItem(sh, IDC_EDIT_B_71	 );   SHAR[6].A[0] = GetDlgItem(sh, IDC_EDIT_R_71	 );
	HA[6].A[1] = GetDlgItem(sh, IDC_EDIT_A_72	);   SHA[6].A[1] = GetDlgItem(sh, IDC_EDIT_B_72	 );   SHAR[6].A[1] = GetDlgItem(sh, IDC_EDIT_R_72	 );
	HA[6].A[2] = GetDlgItem(sh, IDC_EDIT_A_73	);   SHA[6].A[2] = GetDlgItem(sh, IDC_EDIT_B_73	 );   SHAR[6].A[2] = GetDlgItem(sh, IDC_EDIT_R_73	 );
	HA[6].A[3] = GetDlgItem(sh, IDC_EDIT_A_74	);   SHA[6].A[3] = GetDlgItem(sh, IDC_EDIT_B_74	 );   SHAR[6].A[3] = GetDlgItem(sh, IDC_EDIT_R_74	 );
	HA[6].A[4] = GetDlgItem(sh, IDC_EDIT_A_75	);   SHA[6].A[4] = GetDlgItem(sh, IDC_EDIT_B_75	 );   SHAR[6].A[4] = GetDlgItem(sh, IDC_EDIT_R_75	 );
	HA[6].A[5] = GetDlgItem(sh, IDC_EDIT_A_76	);   SHA[6].A[5] = GetDlgItem(sh, IDC_EDIT_B_76	 );   SHAR[6].A[5] = GetDlgItem(sh, IDC_EDIT_R_76	 );
	HA[6].A[6] = GetDlgItem(sh, IDC_EDIT_A_77	);   SHA[6].A[6] = GetDlgItem(sh, IDC_EDIT_B_77	 );   SHAR[6].A[6] = GetDlgItem(sh, IDC_EDIT_R_77	 );
	HA[6].A[7] = GetDlgItem(sh, IDC_EDIT_A_78	);   SHA[6].A[7] = GetDlgItem(sh, IDC_EDIT_B_78	 );   SHAR[6].A[7] = GetDlgItem(sh, IDC_EDIT_R_78	 );
	HA[6].A[8] = GetDlgItem(sh, IDC_EDIT_A_79	);   SHA[6].A[8] = GetDlgItem(sh, IDC_EDIT_B_79	 );   SHAR[6].A[8] = GetDlgItem(sh, IDC_EDIT_R_79	 );
	HA[6].A[9] = GetDlgItem(sh, IDC_EDIT_A_710  );   SHA[6].A[9] = GetDlgItem(sh, IDC_EDIT_B_710 );   SHAR[6].A[9] = GetDlgItem(sh, IDC_EDIT_R_710 );
	HA[7].A[0] = GetDlgItem(sh, IDC_EDIT_A_81	);   SHA[7].A[0] = GetDlgItem(sh, IDC_EDIT_B_81	 );   SHAR[7].A[0] = GetDlgItem(sh, IDC_EDIT_R_81	 );
	HA[7].A[1] = GetDlgItem(sh, IDC_EDIT_A_82	);   SHA[7].A[1] = GetDlgItem(sh, IDC_EDIT_B_82	 );   SHAR[7].A[1] = GetDlgItem(sh, IDC_EDIT_R_82	 );
	HA[7].A[2] = GetDlgItem(sh, IDC_EDIT_A_83	);   SHA[7].A[2] = GetDlgItem(sh, IDC_EDIT_B_83	 );   SHAR[7].A[2] = GetDlgItem(sh, IDC_EDIT_R_83	 );
	HA[7].A[3] = GetDlgItem(sh, IDC_EDIT_A_84	);   SHA[7].A[3] = GetDlgItem(sh, IDC_EDIT_B_84	 );   SHAR[7].A[3] = GetDlgItem(sh, IDC_EDIT_R_84	 );
	HA[7].A[4] = GetDlgItem(sh, IDC_EDIT_A_85	);   SHA[7].A[4] = GetDlgItem(sh, IDC_EDIT_B_85	 );   SHAR[7].A[4] = GetDlgItem(sh, IDC_EDIT_R_85	 );
	HA[7].A[5] = GetDlgItem(sh, IDC_EDIT_A_86	);   SHA[7].A[5] = GetDlgItem(sh, IDC_EDIT_B_86	 );   SHAR[7].A[5] = GetDlgItem(sh, IDC_EDIT_R_86	 );
	HA[7].A[6] = GetDlgItem(sh, IDC_EDIT_A_87	);   SHA[7].A[6] = GetDlgItem(sh, IDC_EDIT_B_87	 );   SHAR[7].A[6] = GetDlgItem(sh, IDC_EDIT_R_87	 );
	HA[7].A[7] = GetDlgItem(sh, IDC_EDIT_A_88	);   SHA[7].A[7] = GetDlgItem(sh, IDC_EDIT_B_88	 );   SHAR[7].A[7] = GetDlgItem(sh, IDC_EDIT_R_88	 );
	HA[7].A[8] = GetDlgItem(sh, IDC_EDIT_A_89	);   SHA[7].A[8] = GetDlgItem(sh, IDC_EDIT_B_89	 );   SHAR[7].A[8] = GetDlgItem(sh, IDC_EDIT_R_89	 );
	HA[7].A[9] = GetDlgItem(sh, IDC_EDIT_A_810  );   SHA[7].A[9] = GetDlgItem(sh, IDC_EDIT_B_810 );   SHAR[7].A[9] = GetDlgItem(sh, IDC_EDIT_R_810 );
	HA[8].A[0] = GetDlgItem(sh, IDC_EDIT_A_91	);   SHA[8].A[0] = GetDlgItem(sh, IDC_EDIT_B_91	 );   SHAR[8].A[0] = GetDlgItem(sh, IDC_EDIT_R_91	 );
	HA[8].A[1] = GetDlgItem(sh, IDC_EDIT_A_92	);   SHA[8].A[1] = GetDlgItem(sh, IDC_EDIT_B_92	 );   SHAR[8].A[1] = GetDlgItem(sh, IDC_EDIT_R_92	 );
	HA[8].A[2] = GetDlgItem(sh, IDC_EDIT_A_93	);   SHA[8].A[2] = GetDlgItem(sh, IDC_EDIT_B_93	 );   SHAR[8].A[2] = GetDlgItem(sh, IDC_EDIT_R_93	 );
	HA[8].A[3] = GetDlgItem(sh, IDC_EDIT_A_94	);   SHA[8].A[3] = GetDlgItem(sh, IDC_EDIT_B_94	 );   SHAR[8].A[3] = GetDlgItem(sh, IDC_EDIT_R_94	 );
	HA[8].A[4] = GetDlgItem(sh, IDC_EDIT_A_95	);   SHA[8].A[4] = GetDlgItem(sh, IDC_EDIT_B_95	 );   SHAR[8].A[4] = GetDlgItem(sh, IDC_EDIT_R_95	 );
	HA[8].A[5] = GetDlgItem(sh, IDC_EDIT_A_96	);   SHA[8].A[5] = GetDlgItem(sh, IDC_EDIT_B_96	 );   SHAR[8].A[5] = GetDlgItem(sh, IDC_EDIT_R_96	 );
	HA[8].A[6] = GetDlgItem(sh, IDC_EDIT_A_97	);   SHA[8].A[6] = GetDlgItem(sh, IDC_EDIT_B_97	 );   SHAR[8].A[6] = GetDlgItem(sh, IDC_EDIT_R_97	 );
	HA[8].A[7] = GetDlgItem(sh, IDC_EDIT_A_98	);   SHA[8].A[7] = GetDlgItem(sh, IDC_EDIT_B_98	 );   SHAR[8].A[7] = GetDlgItem(sh, IDC_EDIT_R_98	 );
	HA[8].A[8] = GetDlgItem(sh, IDC_EDIT_A_99	);   SHA[8].A[8] = GetDlgItem(sh, IDC_EDIT_B_99	 );   SHAR[8].A[8] = GetDlgItem(sh, IDC_EDIT_R_99	 );
	HA[8].A[9] = GetDlgItem(sh, IDC_EDIT_A_910  );   SHA[8].A[9] = GetDlgItem(sh, IDC_EDIT_B_910 );   SHAR[8].A[9] = GetDlgItem(sh, IDC_EDIT_R_910 );
	HA[9].A[0] = GetDlgItem(sh, IDC_EDIT_A_101  );   SHA[9].A[0] = GetDlgItem(sh, IDC_EDIT_B_101 );   SHAR[9].A[0] = GetDlgItem(sh, IDC_EDIT_R_101 );
	HA[9].A[1] = GetDlgItem(sh, IDC_EDIT_A_102  );   SHA[9].A[1] = GetDlgItem(sh, IDC_EDIT_B_102 );   SHAR[9].A[1] = GetDlgItem(sh, IDC_EDIT_R_102 );
	HA[9].A[2] = GetDlgItem(sh, IDC_EDIT_A_103  );   SHA[9].A[2] = GetDlgItem(sh, IDC_EDIT_B_103 );   SHAR[9].A[2] = GetDlgItem(sh, IDC_EDIT_R_103 );
	HA[9].A[3] = GetDlgItem(sh, IDC_EDIT_A_104  );   SHA[9].A[3] = GetDlgItem(sh, IDC_EDIT_B_104 );   SHAR[9].A[3] = GetDlgItem(sh, IDC_EDIT_R_104 );
	HA[9].A[4] = GetDlgItem(sh, IDC_EDIT_A_105  );   SHA[9].A[4] = GetDlgItem(sh, IDC_EDIT_B_105 );   SHAR[9].A[4] = GetDlgItem(sh, IDC_EDIT_R_105 );
	HA[9].A[5] = GetDlgItem(sh, IDC_EDIT_A_106  );   SHA[9].A[5] = GetDlgItem(sh, IDC_EDIT_B_106 );   SHAR[9].A[5] = GetDlgItem(sh, IDC_EDIT_R_106 );
	HA[9].A[6] = GetDlgItem(sh, IDC_EDIT_A_107  );   SHA[9].A[6] = GetDlgItem(sh, IDC_EDIT_B_107 );   SHAR[9].A[6] = GetDlgItem(sh, IDC_EDIT_R_107 );
	HA[9].A[7] = GetDlgItem(sh, IDC_EDIT_A_108  );   SHA[9].A[7] = GetDlgItem(sh, IDC_EDIT_B_108 );   SHAR[9].A[7] = GetDlgItem(sh, IDC_EDIT_R_108 );
	HA[9].A[8] = GetDlgItem(sh, IDC_EDIT_A_109  );   SHA[9].A[8] = GetDlgItem(sh, IDC_EDIT_B_109 );   SHAR[9].A[8] = GetDlgItem(sh, IDC_EDIT_R_109 );
	HA[9].A[9] = GetDlgItem(sh, IDC_EDIT_A_1010 );   SHA[9].A[9] = GetDlgItem(sh, IDC_EDIT_B_1010);   SHAR[9].A[9] = GetDlgItem(sh, IDC_EDIT_R_1010);
}

void desactivarA() {
	for (int s = 0; s < 10; s++) {
		for (int ss = 0; ss < 10; ss++) {
			ShowWindow(HA[s].A[ss], SW_HIDE);
		}
	}
}
void desactivarB() {
	for (int s = 0; s < 10; s++) {
		for (int ss = 0; ss < 10; ss++) {
			ShowWindow(SHA[s].A[ss], SW_HIDE);
		}
	}
}
void desactivarR() {
	for (int s = 0; s < 10; s++) {
		for (int ss = 0; ss < 10; ss++) {
			ShowWindow(SHAR[s].A[ss], SW_HIDE);
		}
	}
}
void activarA(string f, string g) {

	int a = stoi(f), b = stoi(g);

	for (int sa = 0; sa < a; sa++) {
		for (int es = 0; es < b; es = es++) {
			ShowWindow(HA[sa].A[es], SW_RESTORE);
		}
	}
}
void activarB(string f, string g) {
	int a = stoi(f), b = stoi(g);
	for (int sa = 0; sa < a; sa++) {
		for (int es = 0; es < b; es = es++) {
			ShowWindow(SHA[sa].A[es], SW_RESTORE);
		}
	}
}
void activarR(string f, string g) {
	int a = stoi(f), b = stoi(g);
	for (int sa = 0; sa < a; sa++) {
		for (int es = 0; es < b; es = es++) {
			ShowWindow(SHAR[sa].A[es], SW_RESTORE);
		}
	}
}
