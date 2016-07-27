// executer.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "executer.h"

using namespace System::ServiceModel;
using namespace System::ServiceModel::Channels;
using namespace System::ServiceModel::Description;
#include <typeinfo>

using namespace NMWSiWcfLib;
using namespace NMWSiWcfData;


#define MAX_LOADSTRING 100

CExecuterModule _Module;
Mystack stk;  //class 내부로 넣어서 선언한 class에서만 사용할수 있게 한다.

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EXECUTER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXECUTER));

	_Module.Run();
	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXECUTER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_EXECUTER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
 

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//수학함수 정의부분
double _POW(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1, parameter2;
	int pretype;

	pretype = _Module.FunctionParameter(code, parameter1, objid);
	if (pretype == 0x80)
	{
		// 이전 타입이 변수 이므로 +3
		for (int i = 0; i < size - 3; i++)
		{
			code[i] = code[i + 3];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	else if (pretype == 0x10)
	{
		//이전 타입이 object 이므로 +9
		for (int i = 0; i < size - 8; i++)
		{
			code[i] = code[i + 8];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	else
	{
		//이전 타입이 상수 이므로 +10
		for (int i = 0; i < size - 9; i++)
		{
			code[i] = code[i + 9];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	//pow 함수 AssignType에 맞춰서 stk에 push
	
	return pow(parameter1, parameter2);
}
double _ABS(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _COS(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1;
	int pretype;

	_Module.FunctionParameter(code, parameter1, objid);
	
	return cos(parameter1);
}
double _SIN(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1;
	int pretype;

	_Module.FunctionParameter(code, parameter1, objid);

	return sin(parameter1);
}
double _TAN(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _EXP(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1;
	int pretype;

	_Module.FunctionParameter(code, parameter1, objid);

	return exp(parameter1);
}
double _LOG(BYTE code[MAX_CODE], UNSIGNED objid, int size)  //자연로그
{
	double parameter1;
	int pretype;

	_Module.FunctionParameter(code, parameter1, objid);

	return log(parameter1);
}
double _SQRT(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _LOG10(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1;
	int pretype;

	_Module.FunctionParameter(code, parameter1, objid);

	return log10(parameter1);
}

double _ACOS(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _ASIN(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _ATAN(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _COSH(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _SINH(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _TANH(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _TRUNC(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _FACT(BYTE code[MAX_CODE], UNSIGNED objid, int size);

double _ATAN2(BYTE code[MAX_CODE], UNSIGNED objid, int size);
double _MAX(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1, parameter2;
	int pretype;

	pretype = _Module.FunctionParameter(code, parameter1, objid);
	if (pretype == 0x80)
	{
		// 이전 타입이 변수 이므로 +3
		for (int i = 0; i < size - 3; i++)
		{
			code[i] = code[i + 3];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	else if (pretype == 0x10)
	{
		//이전 타입이 object 이므로 +9
		for (int i = 0; i < size - 8; i++)
		{
			code[i] = code[i + 8];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	else
	{
		//이전 타입이 상수 이므로 +10
		for (int i = 0; i < size - 9; i++)
		{
			code[i] = code[i + 9];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	//max 함수 AssignType에 맞춰서 stk에 push

	return max(parameter1, parameter2);
}
double _MIN(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double parameter1, parameter2;
	int pretype;

	pretype = _Module.FunctionParameter(code, parameter1, objid);
	if (pretype == 0x80)
	{
		// 이전 타입이 변수 이므로 +3
		for (int i = 0; i < size - 3; i++)
		{
			code[i] = code[i + 3];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	else if (pretype == 0x10)
	{
		//이전 타입이 object 이므로 +9
		for (int i = 0; i < size - 8; i++)
		{
			code[i] = code[i + 8];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	else
	{
		//이전 타입이 상수 이므로 +10
		for (int i = 0; i < size - 9; i++)
		{
			code[i] = code[i + 9];
		}
		_Module.FunctionParameter(code, parameter2, objid);
	}
	//max 함수 AssignType에 맞춰서 stk에 push

	return min(parameter1, parameter2);
}
double _ABS_H(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double c2, d2, e2, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, g2, h2, i2;
	double absh;

	double a2, b2;
	int pretype;

	pretype = _Module.FunctionParameter(code, a2, objid);
	if (pretype == 0x80)
	{
		// 이전 타입이 변수 이므로 +3
		for (int i = 0; i < size - 3; i++)
		{
			code[i] = code[i + 3];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	else if (pretype == 0x10)
	{
		//이전 타입이 object 이므로 +9
		for (int i = 0; i < size - 8; i++)
		{
			code[i] = code[i + 8];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	else
	{
		//이전 타입이 상수 이므로 +10
		for (int i = 0; i < size - 9; i++)
		{
			code[i] = code[i + 9];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	//절대습도 구하기 stk에 push

	c2 = 1;
	d2 = a2 + 273.15;
	e2 = b2 / 100;  //**
	f1 = -5674.359; f2 = 6.3925247; f3 = -0.009677843; f4 = 0.00000062215701; f5 = 0.0000000020747825, f6 = -0.0000000000009484024;
	f7 = 4.1635019; f8 = -5800.2206; f9 = 1.3914993; f10 = -0.048640239; f11 = 0.000041764768; f12 = -0.000000014452093; f13 = 6.5459673;

	g2 = exp(f1 / d2 + f2 + f3*d2 + f4*pow(d2, 2) + f5*pow(d2, 3) + f6*pow(d2, 4) + f7*log(d2));

	h2 = exp(f8 / d2 + f9 + f10*d2 + f11*pow(d2, 2) + f12*pow(d2, 3) + f13*log(d2));

	if (d2 < 273.15)
		i2 = g2 / 101325;
	else
		i2 = h2 / 101325;

	absh = 0.62198*i2*e2 / (c2 - i2*e2);

	return absh;
}
double _ENT(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double c2, d2, e2, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, g2, h2, i2;
	double j2, ent;

	double a2, b2;
	int pretype;

	pretype = _Module.FunctionParameter(code, a2, objid);
	if (pretype == 0x80)
	{
		// 이전 타입이 변수 이므로 +3
		for (int i = 0; i < size - 3; i++)
		{
			code[i] = code[i + 3];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	else if (pretype == 0x10)
	{
		//이전 타입이 object 이므로 +9
		for (int i = 0; i < size - 8; i++)
		{
			code[i] = code[i + 8];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	else
	{
		//이전 타입이 상수 이므로 +10
		for (int i = 0; i < size - 9; i++)
		{
			code[i] = code[i + 9];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	//절대습도 구하기 stk에 push

	c2 = 1;
	d2 = a2 + 273.15;
	e2 = b2 / 100;  //**
	f1 = -5674.359; f2 = 6.3925247; f3 = -0.009677843; f4 = 0.00000062215701; f5 = 0.0000000020747825, f6 = -0.0000000000009484024;
	f7 = 4.1635019; f8 = -5800.2206; f9 = 1.3914993; f10 = -0.048640239; f11 = 0.000041764768; f12 = -0.000000014452093; f13 = 6.5459673;

	g2 = exp(f1 / d2 + f2 + f3*d2 + f4*pow(d2, 2) + f5*pow(d2, 3) + f6*pow(d2, 4) + f7*log(d2));

	h2 = exp(f8 / d2 + f9 + f10*d2 + f11*pow(d2, 2) + f12*pow(d2, 3) + f13*log(d2));

	if (d2 < 273.15)
		i2 = g2 / 101325;
	else
		i2 = h2 / 101325;

	j2 = 0.62198*i2*e2 / (c2 - i2*e2);

	ent = (a2 + j2*(2501 + 1.805*a2)) / 4.19;

	return ent;
}
double _WBT(BYTE code[MAX_CODE], UNSIGNED objid, int size)
{
	double c2, d2, e2, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, g2, h2, i2;
	double j2, k2, l2, m2, n2, wbt;

	double a2, b2;
	int pretype;

	pretype = _Module.FunctionParameter(code, a2, objid);
	if (pretype == 0x80)
	{
		// 이전 타입이 변수 이므로 +3
		for (int i = 0; i < size - 3; i++)
		{
			code[i] = code[i + 3];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	else if (pretype == 0x10)
	{
		//이전 타입이 object 이므로 +9
		for (int i = 0; i < size - 8; i++)
		{
			code[i] = code[i + 8];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	else
	{
		//이전 타입이 상수 이므로 +10
		for (int i = 0; i < size - 9; i++)
		{
			code[i] = code[i + 9];
		}
		_Module.FunctionParameter(code, b2, objid);
	}
	//절대습도 구하기 stk에 push

	c2 = 1;
	d2 = a2 + 273.15;
	e2 = b2 / 100;  //**
	f1 = -5674.359; f2 = 6.3925247; f3 = -0.009677843; f4 = 0.00000062215701; f5 = 0.0000000020747825, f6 = -0.0000000000009484024;
	f7 = 4.1635019; f8 = -5800.2206; f9 = 1.3914993; f10 = -0.048640239; f11 = 0.000041764768; f12 = -0.000000014452093; f13 = 6.5459673;

	g2 = exp(f1 / d2 + f2 + f3*d2 + f4*pow(d2, 2) + f5*pow(d2, 3) + f6*pow(d2, 4) + f7*log(d2));

	h2 = exp(f8 / d2 + f9 + f10*d2 + f11*pow(d2, 2) + f12*pow(d2, 3) + f13*log(d2));

	if (d2 < 273.15)
		i2 = g2 / 101325;
	else
		i2 = h2 / 101325;

	j2 = 0.62198*i2*e2 / (c2 - i2*e2);

	k2 = (a2 + j2*(2501 + 1.805*a2)) / 4.19;

	l2 = log(k2*4.19*0.43002 + 7.687);
	m2 = -17.4422 + 1.9356*l2 + 0.7556*pow(l2, 2) + 0.5403*pow(l2, 3);
	n2 = -0.6008 - 22.04556*l2 + 11.4356*pow(l2, 2) - 0.97667*pow(l2, 3);

	if (k2 <= 9.473)
		wbt = m2;
	else
		wbt = n2;

	return wbt;
}
//<--


void MarshalString(String^ s, string& os){
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void CExecuterModule::InitailizeSettings()
{
	String^ str;
	ExeConfigurationFileMap^ configFileMap = gcnew ExeConfigurationFileMap();
	configFileMap->ExeConfigFilename = gcnew String("C:\\nara\\NMWS\\bin\\NMWS.config");
	System::Configuration::Configuration^ config = ConfigurationManager::OpenMappedExeConfiguration(configFileMap, ConfigurationUserLevel::None);

	str = config->AppSettings->Settings["system.common.path"]->Value;
	MarshalString(str, m_sPath);

	// core 네트워크 정보
	str = config->AppSettings->Settings["si.common.ipaddr"]->Value;
	MarshalString(str, m_addrCore);
	str = config->AppSettings->Settings["si.common.ipport"]->Value;
	m_portCore = Convert::ToUInt16(str);
	str = config->AppSettings->Settings["system.common.interval_s"]->Value;
	m_nInterval_s = Convert::ToInt32(str);
}

void CExecuterModule::Run()
{	
	m_declarecount = 0;
	m_codecount = 0;
	m_SIConnect = FALSE;
	ACK_Button = FALSE;
	ReadObjtList = FALSE;

	InitailizeSettings();
	NMWSocketIntialize();
	NMWSIIntialize(const_cast<char*>(m_addrCore.c_str()), m_portCore, 10);

	string strParam;
	stServiceConnectData* pConnData = new stServiceConnectData;
	stCharacterString rVersion;	

	strParam = "LOGICSVR";
	strcpy_s(pConnData->name.cs, strParam.c_str());
	pConnData->name.ncs = strlen(pConnData->name.cs) + 1;

	strParam = "1.0";
	strcpy_s(pConnData->rx_version.cs, strParam.c_str());
	pConnData->rx_version.ncs = strlen(pConnData->rx_version.cs) + 1;
	
	if (NMWSIConnectService(pConnData, rVersion) >= 0)
	{
		m_SIConnect = TRUE;
	}
	else
		MessageBox(NULL, "연결실패", " ", MB_OK);
	
	delete pConnData;
	

	stServiceLoginClientReqData* pLogin = new stServiceLoginClientReqData;
	strParam = "LOGICSVR";
	strcpy_s(pLogin->name.cs, strParam.c_str());
	pLogin->name.ncs = strlen(pLogin->name.cs) + 1;

	strParam = "1234";
	strcpy_s(pLogin->password.cs, strParam.c_str());
	pLogin->password.ncs = strlen(pLogin->password.cs) + 1;
	
	clientid = NMWSILoginClient(pLogin);
	
	m_hpmThread = ::CreateThread(NULL, 0, ProcessManagementThread, NULL, 0, NULL);
	if(m_hpmThread == NULL)
	{
		return;
	}

	m_htSIRecvThread = ::CreateThread(NULL, 0, SIRecvThread, NULL, 0, NULL);
	if (m_htSIRecvThread == NULL)
	{
		return;	
	}
	
	_Module.InitLogicServer();	
	
	
	// 실행 후 쓰레드 실행으로 변경
	m_htExecuterThread = ::CreateThread(NULL, 0, ExecuterThread, NULL, 0, NULL);
	if (m_htExecuterThread == NULL)
	{
		return;
	}
	
//	m_codePath = "C:\\nara\\nmws\\logic\\TCPL.hex";
	
	//Recv Thread 필요
	
	//LoadHexFile(m_codePath);
	
}

// Load hex file to map
BOOL CExecuterModule::LoadHexFile(CString strcodePath)
{
	string os;
	char output[100];
	CString tstr_OneLineCode;
	// path 위치는 따로 받아야 한다. 2014-07-09

	ifstream myReadFile;
	myReadFile.open(strcodePath);

	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> output;
			os = output;
			tstr_OneLineCode = os.c_str();
			// : 주소 instruction 자르기 함수 수행
			// insert map 함수 수행

			TokenFirstStep(tstr_OneLineCode);				
		}
		m_codecount = 0;  //object id .seungdo 수정 필요
		m_mapGlobalCodeLine.insert(map<int, MAP_CODE_LINE>::value_type(m_codecount, m_mapCodeLine));
		m_mapCodeLine.clear();
	}
	return TRUE;
}

// 자르고 insert
BOOL CExecuterModule::TokenFirstStep(CString OneLineCode)
{
	int nComma;
	int OPsize;
	int OPAddr;
	int Instruction;
	int Line;

	stLineInfo stOneLineCode;	
	string tstr_strtohextoint;

	if (OneLineCode == ":00000001FF" || OneLineCode == "")
		return TRUE;

	// Delete :
	nComma = OneLineCode.Find(':', 0);
	OneLineCode.Delete(0, nComma + 1);
	
	// Input Code Size
	tstr_strtohextoint = OneLineCode.Left(2);	
	OPsize = string2hex2dec(tstr_strtohextoint) - 2;
	OneLineCode.Delete(0, 2);

	// addr
	tstr_strtohextoint = OneLineCode.Left(3);
	OPAddr = string2hex2dec(tstr_strtohextoint);
	OneLineCode.Delete(0, 4);

	OneLineCode.Delete(0, 2);
	
	// Instruction
	tstr_strtohextoint = OneLineCode.Left(2);
	Instruction = string2hex2dec(tstr_strtohextoint);
	OneLineCode.Delete(0, 2);

	// Line Size
	tstr_strtohextoint = OneLineCode.Left(2);
	Line = string2hex2dec(tstr_strtohextoint);
	OneLineCode.Delete(0, 2);

	for (int i = 0; i < OPsize; i++)
	{
		tstr_strtohextoint = OneLineCode.Left(2);
		stOneLineCode.Others[i] = string2hex2dec(tstr_strtohextoint);
		OneLineCode.Delete(0, 2);
	}

	stOneLineCode.status = FALSE; 
	stOneLineCode.Size = OPsize;
	stOneLineCode.Instruction = Instruction;
	stOneLineCode.Line = Line;
	
	//if (OPsize != -2)
	m_mapCodeLine.insert(map<int, stLineInfo >::value_type(OPAddr, stOneLineCode));

	return true;
}

int CExecuterModule::string2hex2dec(string sthexdata)
{
	int rethexdec;
	stringstream s1;
	s1 << sthexdata;
	s1 >> std::hex >> rethexdec;

	return rethexdec;
}

string CExecuterModule::hex2string(BYTE hex)
{
	string returnstr;
	stringstream s1;
	s1 << std::hex << hex;
	s1 >> returnstr;

	return returnstr;
}

BOOL CExecuterModule::AssignOP_Object(stLineInfo stLine, UNSIGNED objid_t)
{
	//저장변수 타입
	// 아날로그, 바이너리, 멀티스테이트
	BYTE code[7];
	int devid, objid, AssignType;
	stObjectID t_objid;
	ENUMERATED method, type;
	type = (ENUMERATED)NMWServiceConfirmedType::writeProperty;
	int rp, i;
	short invokeid;
	UNSIGNED8 flags;
	stServiceWritePropertyReqData* WPRdata = new stServiceWritePropertyReqData;
	stCharacterString* pstemp = new stCharacterString;
	string stemp = to_string(objid_t);
	pstemp->ncs = stemp.size() + 1;
	memcpy((void*)pstemp->cs, (void*)stemp.c_str(), pstemp->ncs);
	WPRdata->message = *pstemp;
	WPRdata->ccmsid.ncs = 1;
	WPRdata->ccmsid.cs[0] = '\0';
	delete pstemp;

	void* prdata;
	for (int i = 1; i < 8; i++)
	{
		code[i - 1] = stLine.Others[i];
	}
	_Module.Readcodetodevobjid(code, devid, objid);
	WPRdata->objid.nID = (UNSIGNED)objid;
	WPRdata->propValue.priority = (UNSIGNED16)16;

	switch (WPRdata->objid.s.Type)
	{
	case NMWObjectType::AnalogInputObject:
	case NMWObjectType::AnalogOutputObject:
	case NMWObjectType::AnalogValueObject:
		AssignType = 4;
		WPRdata->propValue.tValue = (UNSIGNED16)NMWDataTypeID::dtReal;
		break;
	case NMWObjectType::BinaryInputObject:
	case NMWObjectType::BinaryOutputObject:
	case NMWObjectType::BinaryValueObject:
		AssignType = 1;
		WPRdata->propValue.tValue = (UNSIGNED16)NMWDataTypeID::dtEnumerated;
		break;
	case NMWObjectType::MultistateInputObject:
	case NMWObjectType::MultistateOutputObject:
	case NMWObjectType::MultistateValueObject:
		AssignType = 2;
		WPRdata->propValue.tValue = (UNSIGNED16)NMWDataTypeID::dtUnsigned;
		break;
	default:
		AssignType = 5;
		break;
	}

	int size = stLine.Others[8];
	BYTE others[MAX_CODE] = { 0 };
	//expression 부분만 잘라주는for문
	for (int i = 0; i < size; i++)
	{
		others[i] = stLine.Others[9 + i];
	}

	//sdlee 2016-05-23 함수 추가
	//others[0] 이 함수
	BYTE parameters[MAX_CODE] = { 0 };

	if (is_function(others[0]))
	{
		//parameter 추출 함수 
		int pretype;  // 이전 변수의 type;
		double retvalue;

		for (int i = 0; i < (size - 1); i++)
		{
			parameters[i] = others[i + 1];
		}

		switch (others[0])
		{
		case POW: //POW
		{
			retvalue = _POW(parameters, objid, size);
			//pow 함수 AssignType에 맞춰서 stk에 push
			push_stk_type(AssignType, retvalue);
		}
		break;
		case LOG: //LOG
		{
			retvalue = _LOG(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case LOG10:
		{
			retvalue = _LOG10(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case SIN:
		{
			retvalue = _SIN(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case COS:
		{
			retvalue = _COS(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case MIN:
		{
			retvalue = _MIN(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case MAX:
		{
			retvalue = _MAX(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case EXP:
		{
			retvalue = _EXP(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case ABS_H: //ABS_H
		{
			retvalue = _ABS_H(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case ENT: //ENT
		{
			retvalue = _ENT(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case WBT: //WBT
		{
			retvalue = _WBT(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		default:
			break;
		}
	}
	else//<--
		_Module.Expression(others, size, AssignType, objid_t);

	WPRdata->propValue.nValue = 0;
	WPRdata->propValue.propertyArrayIndex = -1;
	WPRdata->propValue.propertyIdentifier = (ENUMERATED)NMWPropID::PRESENT_VALUE;

	//type 별로 스택에 있는 결과물을 WriteProperty Assign 하면 됨
	CString temp;
	switch (AssignType)
	{
	case 0x00: break; // NULL
	case 0x01:
		//BOOL	
		*(ENUMERATED*)&WPRdata->propValue.pValue = stk.bool_pop();
		break;
	case 0x02:
		//UNSIGN	
		*(UNSIGNED*)&WPRdata->propValue.pValue = stk.unsigned_pop();
		break;
	case 0x03:
		//INT	
		*(int*)&WPRdata->propValue.pValue = stk.int_pop();
		break;
	case 0x04:
		//REAL		
		*(REAL*)&WPRdata->propValue.pValue = stk.real_pop();
		break;
	case 0x05:
		//DOUBLE	
		*(double*)&WPRdata->propValue.pValue = stk.double_pop();
		break;
	case 0x06:
		//OCTETS	
		break;
	case 0x07:
		//STRING		
		break;
	case 0x08:
		//BITS		
		break;
	case 0x09:
		//ENUM				
		*(ENUMERATED*)&WPRdata->propValue.pValue = stk.enum_pop();
		break;
	case 0x0A:
		//DATE		
		break;
	case 0x0B:
		//TIME		
		break;
	case 0x0C:
		//OBJID	
		break;
	case 0x0D:
		//DATETIME		
		break;
	}
	if (devid == 0)
		flags = 0x00;
	else
		flags = 0x01;

	flags = true;

	UNSIGNED devid_un = (UNSIGNED)devid;
	int ret;
	void* prdataack;
	NMWSISendConfirmedReq(_Module.clientid, devid_un, type, invokeid, (void*)WPRdata, flags, rp);
	Sleep(100);
	//for (i = 0; i < 30; i++)
	//{
	//	Sleep(100);
	//	method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
	//	ret = NMWSIRecvConfirmedAck(_Module.clientid,	// clientid, 값이 '0'이면 system command
	//		devid_un,
	//		type,
	//		invokeid,
	//		prdataack,
	//		flags,
	//		rp);
	//	if (ret >= 0)
	//		break;
	//}
	//if (i >= 30)
	//	return FALSE;
	//sdlee 2016-05-12
	// WriteProperty ACK 를 기다릴 필요가 없다.

	delete WPRdata;	

	return true;
}


BOOL CExecuterModule::AssignOP(stLineInfo stLine, UNSIGNED objid)
{
	// 저장 변수 확인 (Variable | Object)
	int AssignType = stLine.Others[0] & 0x0F;	
	int Varcheck = stLine.Others[0] & 0xF0;
	// 저장 변수 주소 확인  -> 주소 확인 확장 1byte -> 2byte
	int addr = stLine.Others[2];
	// size 확인 
	int size = stLine.Others[3];
	// stack 으로 push 함수 
	// expression으로 넘김
	BYTE others[MAX_CODE] = { 0 };
	MAP_Memory::iterator iterPos;
	iterPos = _Module.m_memory.find(objid);
	//expression 부분만 잘라주는 for 문
	for (int i = 0; i < size; i++)
	{
		others[i] = stLine.Others[4 + i];
	}

	//sdlee 2016-05-18 함수 추가
	//others[0]이 함수
	BYTE parameters[MAX_CODE] = { 0 };
	if (is_function(others[0]))  // 함수 여부를 판단
	{
		//parameter 추출 함수 
		int pretype;  // 이전 변수의 type;
		double retvalue;

		for (int i = 0; i < (size - 1); i++)
		{
			parameters[i] = others[i + 1];
		}

		switch (others[0])
		{
		case POW: //POW
		{		
			retvalue = _POW(parameters, objid, size);
			//pow 함수 AssignType에 맞춰서 stk에 push
			push_stk_type(AssignType, retvalue);
		}
		break;
		case LOG: //LOG
		{
			retvalue = _LOG(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case LOG10:
		{
			retvalue = _LOG10(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case SIN:
		{
			retvalue = _SIN(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case COS:
		{
			retvalue = _COS(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case MIN:
		{
			retvalue = _MIN(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case MAX:
		{
			retvalue = _MAX(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case EXP:
		{
			retvalue = _EXP(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case ABS_H: //ABS_H
		{
			retvalue = _ABS_H(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case ENT: //ENT
		{
			retvalue = _ENT(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		case WBT: //WBT
		{
			retvalue = _WBT(parameters, objid, size);
			push_stk_type(AssignType, retvalue);
		}
		break;
		default:
			break;
		}
	}
	else  //<--
		_Module.Expression(others, size, AssignType, objid);
	
	//type 별로 스택에 있는 결과물을 Assign 하면 됨
	switch (AssignType)
	{
	case 0x00: break; // NULL
	case 0x01: 
		//BOOL	
		iterPos->second.bool_set(addr, stk.bool_pop());
		break;
	case 0x02:
		//UNSIGN		
		iterPos->second.unsigned_set(addr, stk.unsigned_pop());
		break;
	case 0x03:
		//INT		
		iterPos->second.int_set(addr, stk.int_pop());
		break;
	case 0x04:
		//REAL	
		iterPos->second.real_set(addr, stk.real_pop());
		break;
	case 0x05:
		//DOUBLE	
		iterPos->second.double_set(addr, stk.double_pop());
		break;
	case 0x06:
		//OCTETS		
		iterPos->second.octets_set(addr, stk.octets_pop());
		break;
	case 0x07:
		//STRING		
		iterPos->second.string_set(addr, stk.string_pop());
		break;
	case 0x08:
		//BITS		
		iterPos->second.bit_set(addr, stk.bits_pop());
		break;
	case 0x09:
		//ENUM		
		iterPos->second.enum_set(addr, stk.enum_pop());
		break;
	case 0x0A:
		//DATE	
		iterPos->second.date_set(addr, stk.date_pop());
		break;
	case 0x0B:
		//TIME		
		iterPos->second.time_set(addr, stk.time_pop());
		break;
	case 0x0C:
		//OBJID		
		iterPos->second.objid_set(addr, stk.objid_pop());
		break;
	case 0x0D:
		//DATETIME		
		iterPos->second.datetime_set(addr, stk.datetime_pop());
		break;	
	}
	return TRUE;
}

void CExecuterModule::binaryExpr_int(TknKind op)
{
	int d = 0, d2 = stk.int_pop(), d1 = stk.int_pop();

	if ((op == Divi || op == Mod) && d2 == 0)
		return;
	// 0으로 나눔
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	case Minus: d = d1 - d2;    break;
	case Multi: d = d1 * d2;    break;
	case Divi: d = d1 / d2;		break;
	case Mod: d = d1 % d2;		break;
	case Assign: d = d2;		break;
	case And: d = d1 && d2;		break;
	case Or: d = d1 || d2;		break;
	case Xor: d = d1 ^ d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.int_push(d);
}

void CExecuterModule::binaryExpr_bool(TknKind op)
{
	bool d = 0, d2 = stk.bool_pop(), d1 = stk.bool_pop();

	if ((op == Divi || op == Mod) && d2 == 0)
		return;
	// 0으로 나눔
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	case Minus: d = d1 - d2;    break;
	case Multi: d = d1 * d2;    break;
	case Divi: d = d1 / d2;		break;
	case Mod: d = d1 % d2;		break;
	case Assign: d = d2;		break;
	case And: d = d1 && d2;		break;
	case Or: d = d1 || d2;		break;
	case Xor: d = d1 ^ d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.bool_push(d);
}

void CExecuterModule::binaryExpr_unsign(TknKind op)
{
	unsigned d = 0, d2 = stk.unsigned_pop(), d1 = stk.unsigned_pop();

	if ((op == Divi || op == Mod) && d2 == 0)
		return;
	// 0으로 나눔
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	case Minus: d = d1 - d2;    break;
	case Multi: d = d1 * d2;    break;
	case Divi: d = d1 / d2;		break;
	case Mod: d = d1 % d2;		break;
	case Assign: d = d2;		break;
	case And: d = d1 && d2;		break;
	case Or: d = d1 || d2;		break;
	case Xor: d = d1 ^ d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.unsigned_push(d);
}

void CExecuterModule::binaryExpr_real(TknKind op)
{
	REAL d = 0, d2 = stk.real_pop(), d1 = stk.real_pop();

	if ((op == Divi || op == Mod) && d2 == 0)
		return;
	// 0으로 나눔
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	case Minus: d = d1 - d2;    break;
	case Multi: d = d1 * d2;    break;
	case Divi: d = d1 / d2;		break;
	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
	case And: d = d1 && d2;		break;
	case Or: d = d1 || d2;		break;
	case Xor: d = (int)d1 ^ (int)d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.real_push(d);
}

void CExecuterModule::binaryExpr_double(TknKind op)
{
	double d = 0, d2 = stk.double_pop(), d1 = stk.double_pop();

	if ((op == Divi || op == Mod) && d2 == 0)
		return;
	// 0으로 나눔
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	case Minus: d = d1 - d2;    break;
	case Multi: d = d1 * d2;    break;
	case Divi: d = d1 / d2;		break;
	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
	case And: d = d1 && d2;		break;
	case Or: d = d1 || d2;		break;
	case Xor: d = (int)d1 ^ (int)d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.double_push(d);
}

void CExecuterModule::binaryExpr_octets(TknKind op)
{
	stOctetString d , d2 = stk.octets_pop(), d1 = stk.octets_pop();
		
	// 0으로 나눔
	switch (op)
	{
	//case Plus: d = d1 + d2;		break;
	//case Minus: d = d1 - d2;    break;
	//case Multi: d = d1 * d2;    break;
	//case Divi: d = d1 / d2;		break;
	//case Mod: d = d1 % d2;		break;
	case Assign: d = d2;		break;
	//case And: d = d1 && d2;		break;
	//case Or: d = d1 || d2;		break;
//	case Xor: d = d1 ^ d2;		break;
	//case Less: d = d1 < d2;		break;
	//case Great: d = d1 > d2; 	break;
//	case Equal: d = d1 == d2;	break;
	}
	stk.octets_push(d);
}

void CExecuterModule::binaryExpr_string(TknKind op)
{
	string d , d2 = stk.string_pop(), d1 = stk.string_pop();
	
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	//case Minus: d = d1 - d2;    break;
	//case Multi: d = d1 * d2;    break;
	//case Divi: d = d1 / d2;		break;
	//case Mod: d = d1 % d2;		break;
	case Assign: d = d2;		break;
	//case And: d = d1 && d2;		break;
	//case Or: d = d1 || d2;		break;
	//case Xor: d = d1 ^ d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.string_push(d);
}

void CExecuterModule::binaryExpr_bits(TknKind op)
{
	stBitString d, d2 = stk.bits_pop(), d1 = stk.bits_pop();

	switch (op)
	{
	//case Plus: d = d1 + d2;		break;
	//case Minus: d = d1 - d2;    break;
	//case Multi: d = d1 * d2;    break;
	//case Divi: d = d1 / d2;		break;
	//case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
	//case And: d = d1 && d2;		break;
	//case Or: d = d1 || d2;		break;
//	case Xor: d = (int)d1 ^ (int)d2;		break;
//	case Less: d = d1 < d2;		break;
//	case Great: d = d1 > d2; 	break;
//	case Equal: d = d1 == d2;	break;
	}
	stk.bits_push(d);
}

void CExecuterModule::binaryExpr_enum(TknKind op)
{
	ENUMERATED d = 0, d2 = stk.enum_pop(), d1 = stk.enum_pop();

	if ((op == Divi || op == Mod) && d2 == 0)
		return;
	// 0으로 나눔
	switch (op)
	{
	case Plus: d = d1 + d2;		break;
	case Minus: d = d1 - d2;    break;
	case Multi: d = d1 * d2;    break;
	case Divi: d = d1 / d2;		break;
	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
	case And: d = d1 && d2;		break;
	case Or: d = d1 || d2;		break;
	case Xor: d = (int)d1 ^ (int)d2;		break;
	case Less: d = d1 < d2;		break;
	case Great: d = d1 > d2; 	break;
	case Equal: d = d1 == d2;	break;
	case Not: d = d1 != d2;		break;
	}
	stk.enum_push(d);
}

void CExecuterModule::binaryExpr_date(TknKind op)
{
	stDate d , d2 = stk.date_pop(), d1 = stk.date_pop();
	
	switch (op)
	{
	//case Plus: d = d1 + d2;		break;
	//case Minus: d = d1 - d2;    break;
	//case Multi: d = d1 * d2;    break;
//	case Divi: d = d1 / d2;		break;
//	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
//	case And: d = d1 && d2;		break;
//	case Or: d = d1 || d2;		break;
//	case Xor: d = (int)d1 ^ (int)d2;		break;
//	case Less: d = d1 < d2;		break;
//	case Great: d = d1 > d2; 	break;
//	case Equal: d = d1 == d2;	break;
	}
	stk.date_push(d);
}

void CExecuterModule::binaryExpr_time(TknKind op)
{
	stTime d, d2 = stk.time_pop(), d1 = stk.time_pop();
	
	switch (op)
	{
	//case Plus: d = d1 + d2;		break;
//	case Minus: d = d1 - d2;    break;
//	case Multi: d = d1 * d2;    break;
//	case Divi: d = d1 / d2;		break;
//	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
//	case And: d = d1 && d2;		break;
//	case Or: d = d1 || d2;		break;
//	case Xor: d = (int)d1 ^ (int)d2;		break;
	case Less:
	{
		if (d1.hour < d2.hour)
		{
			d = d1;
			stk.timebool_push(true);
			return;
		}
		else if (d1.hour > d2.hour){
			d = d2;
			stk.timebool_push(false);
			return;
		}
		else
		{
			if (d1.minute < d2.minute)
			{
				d = d1;
				stk.timebool_push(true);
				return;
			}
			else if (d1.minute > d2.minute)
			{
				d = d2;
				stk.timebool_push(false);
				return;
			}
			else
			{
				if (d1.second < d2.second)
				{
					d = d1;
					stk.timebool_push(true);
					return;
				}
				else if (d1.second > d2.second)
				{
					d = d2;
					stk.timebool_push(false);
					return;
				}
				else
				{
					if (d1.hundredths < d2.hundredths)
					{
						d = d1;
						stk.timebool_push(true);
						return;
					}
					else 					
					{
						d = d1;
						stk.timebool_push(false);
						return;
					}
				}
			}

		}
	}
	break;
	case Great: 	
	{
		if (d1.hour < d2.hour)
		{
			d = d1;
			stk.timebool_push(false);
			return;
		}
		else if (d1.hour > d2.hour){
			d = d2;
			stk.timebool_push(true);
			return;
		}
		else
		{
			if (d1.minute < d2.minute)
			{
				d = d1;
				stk.timebool_push(false);
				return;
			}
			else if (d1.minute > d2.minute)
			{
				d = d2;
				stk.timebool_push(true);
				return;
			}
			else
			{
				if (d1.second < d2.second)
				{
					d = d1;
					stk.timebool_push(false);
					return;
				}
				else if (d1.second > d2.second)
				{
					d = d2;
					stk.timebool_push(true);
					return;
				}
				else
				{
					if (d1.hundredths > d2.hundredths)
					{
						d = d1;
						stk.timebool_push(true);
						return;
					}
					else
					{
						d = d1;
						stk.timebool_push(false);
						return;
					}
				}
			}

		}
	}
	break;
	//case Equal: d = d1 == d2;	break;
	}
	
	stk.time_push(d);
}

void CExecuterModule::binaryExpr_objid(TknKind op)
{
	stObjectID d , d2 = stk.objid_pop(), d1 = stk.objid_pop();

	switch (op)
	{
//	case Plus: d = d1 + d2;		break;
//	case Minus: d = d1 - d2;    break;
//	case Multi: d = d1 * d2;    break;
//	case Divi: d = d1 / d2;		break;
//	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
//	case And: d = d1 && d2;		break;
//	case Or: d = d1 || d2;		break;
//	case Xor: d = (int)d1 ^ (int)d2;		break;
//	case Less: d = d1 < d2;		break;
//	case Great: d = d1 > d2; 	break;
//	case Equal: d = d1 == d2;	break;
	}
	stk.objid_push(d);
}

void CExecuterModule::binaryExpr_datetime(TknKind op)
{
	stDateTime d, d2 = stk.datetime_pop(), d1 = stk.datetime_pop();

	switch (op)
	{
	//case Plus: d = d1 + d2;		break;
//	case Minus: d = d1 - d2;    break;
//	case Multi: d = d1 * d2;    break;
//	case Divi: d = d1 / d2;		break;
//	case Mod: d = (int)d1 % (int)d2;		break;
	case Assign: d = d2;		break;
//	case And: d = d1 && d2;		break;
//	case Or: d = d1 || d2;		break;
//	case Xor: d = (int)d1 ^ (int)d2;		break;
//	case Less: d = d1 < d2;		break;
//	case Great: d = d1 > d2; 	break;
//	case Equal: d = d1 == d2;	break;
	}
	stk.datetime_push(d);
}

BOOL CExecuterModule::CreateUPG(byte clientId, int deviceId, int objectId)
{
	stServiceReadPropertyMultipleReqData* pRPMReqData = new stServiceReadPropertyMultipleReqData;
	MAP_OBJECT_TABLE::iterator iterPos;
	stObjectstate t_objectinfo;
	stPCDECinfo pcdecinfo;
	stObjectID addobject;
	addobject.nID = objectId;
	Mymemory memory;
	Mystack mystack;
	ENUMERATED type;
	short invokeid;
	UNSIGNED8 flags = 0x00;  //Middle Ware 내의 값만 수신
	ENUMERATED method;
	UNSIGNED32 devid;
	int i = 0;

	t_objectinfo.program_change = 0;
	t_objectinfo.program_state = 0;
	t_objectinfo.file_size = 0;
	pcdecinfo.dec = false;
	pcdecinfo.PC = 0;


	iterPos = _Module.m_mapobjectTable.find(addobject.s.ID);
	if (iterPos == _Module.m_mapobjectTable.end())
	{
		// 없음 추가
		_Module.m_mapobjectTable.insert(map<UNSIGNED, stObjectstate>::value_type(addobject.s.ID, t_objectinfo));
		_Module.m_mapExecuteInfoTable.insert(map<UNSIGNED, stPCDECinfo>::value_type(addobject.s.ID, pcdecinfo));
		_Module.m_memory.insert(map<UNSIGNED, Mymemory>::value_type(addobject.s.ID, memory));
		_Module.m_opstack.insert(map<UNSIGNED, Mystack>::value_type(addobject.s.ID, mystack));
	}
	else
	{
		return false;
	}

	stServiceReadPropertyMultipleACKData* pRPMAdata = NULL;

	//readproperty multiple 요청

	pRPMReqData->nListOfReadAccessSpecs = 1;
	pRPMReqData->pListOfReadAccessSpecs = new stReadAccessSpec;
	pRPMReqData->pListOfReadAccessSpecs->nListOfPropertyReferences = 2;
	pRPMReqData->pListOfReadAccessSpecs->objid = addobject;
	pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences = new stPropertyReference[2];
	pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences[0].arrayindex = 0xffff;
	pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences[0].propid = (ENUMERATED)NMWPropID::PROGRAM_CHANGE;
	pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences[1].arrayindex = 0xffff;
	pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences[1].propid = (ENUMERATED)NMWPropID::PROGRAM_STATE;

	type = (ENUMERATED)NMWServiceConfirmedType::readPropertyMultiple;

	if (NMWSISendConfirmedReq(clientId,
		deviceId,
		type,
		invokeid,
		(void*)pRPMReqData,
		flags,
		rp) >= 0)
	{
		for (i = 0; i < 30; i++)
		{
			Sleep(100);
			method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
			if (NMWSIRecvServiceCheck(devid, method, type, invokeid, (void*&)pRPMAdata, flags, clientId, rp))
				break;

		}
		if (i >= 30){
			delete[] pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences;
			delete pRPMReqData->pListOfReadAccessSpecs;
			delete pRPMReqData;
			return FALSE;
		}

		//풀어서 map에 insert
		for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++){
			iterPos = _Module.m_mapobjectTable.find(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);
			if (iterPos == _Module.m_mapobjectTable.end())
			{
				continue;
			}
			else
			{
				iterPos->second.program_change = *(ENUMERATED*)&pRPMAdata->pListOfReadAccessResults[i].pListOfResult[0].pValue;
				iterPos->second.program_state = *(ENUMERATED*)&pRPMAdata->pListOfReadAccessResults[i].pListOfResult[1].pValue;
			}

		}
	}
	//read file size(objid)
	for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++)
	{
		ReadFileSize(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);
	}

	for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++)
	{
		ReadFile(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);
	}

	delete[] pRPMReqData->pListOfReadAccessSpecs->pListOfPropertyReferences;
	delete pRPMReqData->pListOfReadAccessSpecs;
	delete pRPMReqData;
	delete[] pRPMAdata->pListOfReadAccessResults->pListOfResult;
	delete pRPMAdata->pListOfReadAccessResults;
	delete pRPMAdata;

	return true;
}

BOOL CExecuterModule::SendGetObject(byte clientId, int networkId, int deviceId)
{
	UNSIGNED32 devid = 0;
	stObjectPropertyReference* pRPReqData = new stObjectPropertyReference;
	pRPReqData->objid.s.Type = (ENUMERATED)NMWObjectType::DeviceObject;
	pRPReqData->objid.s.ID = (UNSIGNED)devid;
	pRPReqData->propid = (ENUMERATED)NMWPropID::OBJECT_LIST;
	pRPReqData->arrayindex = 0xffff;
	Mymemory memory;
	Mystack mystack;
	
	int i, ret;
	short invokeid;
	int rp;
	void* prdata;
	stObjectstate t_objectinfo;
	stPCDECinfo pcdecinfo;
	ENUMERATED method;
	ENUMERATED type = (ENUMERATED)NMWServiceConfirmedType::readProperty;
	UNSIGNED8 flags = 0x00;  //Middle Ware 내의 값만 수신
	stServiceReadPropertyACKData* pAckData = NULL;
	b_isProgramobject = FALSE;
	MAP_OBJECT_TABLE::iterator iterPos;
	stServiceReadPropertyMultipleReqData* pRPMReqData = new stServiceReadPropertyMultipleReqData;
	int program_count = 0;
	NMWSISendConfirmedReq(clientId,
		devid,
		type,
		invokeid,
		(void*)pRPReqData,
		flags,
		rp);

		ReadObjtList = TRUE;
		m_invokeid = invokeid;
		_Module.rp = rp;
		// ACK 수신 확인용
		
		for (i = 0; i < 30; i++)
		{
			Sleep(100);
			method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
			if (NMWSIRecvServiceCheck(devid, method, type, invokeid, (void*&)pAckData, flags, clientId, rp))
				break;
		}
		if (i >= 30){
			delete pRPReqData;
			return FALSE;
		}
		delete pRPReqData;
		unsigned long checktype;
		for (i = 0; i < pAckData->propValue.nValue; i++)
		{

			if (((stObjectID*)pAckData->propValue.pValue)[i].s.Type == 16)
			{
				program_count++;
				t_objectinfo.program_change = 0;
				t_objectinfo.program_state = 0;				
				t_objectinfo.file_size = 0;
				pcdecinfo.dec = false;
				pcdecinfo.PC = 0;
				//readproperty mulitple 상태 얻어오기
				//insert map 모든 정보 map에 업데이트
				_Module.m_mapobjectTable.insert(map<UNSIGNED, stObjectstate>::value_type(((stObjectID*)pAckData->propValue.pValue)[i].s.ID, t_objectinfo));
				_Module.m_mapExecuteInfoTable.insert(map<UNSIGNED, stPCDECinfo>::value_type(((stObjectID*)pAckData->propValue.pValue)[i].s.ID, pcdecinfo));
				_Module.m_memory.insert(map<UNSIGNED, Mymemory>::value_type(((stObjectID*)pAckData->propValue.pValue)[i].s.ID, memory));
				_Module.m_opstack.insert(map<UNSIGNED, Mystack>::value_type(((stObjectID*)pAckData->propValue.pValue)[i].s.ID, mystack));
				b_isProgramobject = TRUE;
			}
			else
			{
				//program object 없음
			}
		}
		int count = 0;
		stServiceReadPropertyMultipleACKData* pRPMAdata = NULL;
		if (b_isProgramobject)
		{
			//readproperty multiple 요청
			pRPMReqData->nListOfReadAccessSpecs = program_count;
			pRPMReqData->pListOfReadAccessSpecs = new stReadAccessSpec[program_count];
			for (iterPos = _Module.m_mapobjectTable.begin(); iterPos != _Module.m_mapobjectTable.end();)
			{
				pRPMReqData->pListOfReadAccessSpecs[count].objid.s.ID = iterPos->first;
				pRPMReqData->pListOfReadAccessSpecs[count].objid.s.Type = (ENUMERATED)NMWObjectType::ProgramObject;
				pRPMReqData->pListOfReadAccessSpecs[count].nListOfPropertyReferences = 2;
				pRPMReqData->pListOfReadAccessSpecs[count].pListOfPropertyReferences = new stPropertyReference[2];
				pRPMReqData->pListOfReadAccessSpecs[count].pListOfPropertyReferences[0].arrayindex = 0xffff;
				pRPMReqData->pListOfReadAccessSpecs[count].pListOfPropertyReferences[0].propid = (ENUMERATED)NMWPropID::PROGRAM_CHANGE;
				pRPMReqData->pListOfReadAccessSpecs[count].pListOfPropertyReferences[1].arrayindex = 0xffff;
				pRPMReqData->pListOfReadAccessSpecs[count].pListOfPropertyReferences[1].propid = (ENUMERATED)NMWPropID::PROGRAM_STATE;
				count++;
				iterPos++;
			}
			type = (ENUMERATED)NMWServiceConfirmedType::readPropertyMultiple;
			if (NMWSISendConfirmedReq(clientId,
				devid,
				type,
				invokeid,
				(void*)pRPMReqData,
				flags,
				rp) >= 0)
			{
				for (i = 0; i < 30; i++)
				{
					Sleep(100);
					method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
					if (NMWSIRecvServiceCheck(devid, method, type, invokeid, (void*&)pRPMAdata, flags, clientId, rp))
						break;

				}				
				if (i >= 30)
					return FALSE;
				// 풀어서 map에 insert
				for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++){
					iterPos = _Module.m_mapobjectTable.find(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);
					if (iterPos == _Module.m_mapobjectTable.end())
					{
						continue;
					}
					else
					{
						iterPos->second.program_change = *(ENUMERATED*)&pRPMAdata->pListOfReadAccessResults[i].pListOfResult[0].pValue;
						iterPos->second.program_state = *(ENUMERATED*)&pRPMAdata->pListOfReadAccessResults[i].pListOfResult[0].pValue;
					}

				}
			}
			//read file size(objid)
			for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++)
			{
				ReadFileSize(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);
			}
			//send Atomicfile Read
			//ReadFile();
			//object id 개수 대로 
			for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++)
			{
				ReadFile(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);				
			}


			//start 기능 필요
			for (iterPos = _Module.m_mapobjectTable.begin(); iterPos != _Module.m_mapobjectTable.end(); iterPos++)
			{
				if (iterPos->second.program_change == 2)
				{
					MAP_Global_CODE_LINE::iterator itGlobalPos;
					MAP_CODE_LINE::iterator itCLPos;
					for (int kk = 0; kk < program_count; kk++)
					{
						itGlobalPos = _Module.m_mapGlobalCodeLine.find(pRPMAdata->pListOfReadAccessResults[kk].objid.s.ID);
						if (itGlobalPos != _Module.m_mapGlobalCodeLine.end())
						{
							for (itCLPos = itGlobalPos->second.begin(); itCLPos != itGlobalPos->second.end();)
							{
								itCLPos->second.status = TRUE;
								itCLPos++;
							}
						}
						
					}
					
				}
			}
		}
		else
		{
			return FALSE;
		}
		return TRUE;	

}

void CExecuterModule::InitLogicServer()
{
	int networkid = 0; // network id 얻어오기 , virtual networkid, devid == 0?  테스트용
	int devid = 0;
	
	if (!SendGetObject(clientid, networkid, devid))
		return;

}

void CExecuterModule::RecvWritePropertyREQ(int devid, short invokeid, stServiceWritePropertyReqData WPData)
{
	ENUMERATED program_change_value;
	UNSIGNED objid;
	MAP_OBJECT_TABLE::iterator itPos;
	MAP_Global_CODE_LINE::iterator itGlobalPos;
	MAP_Memory::iterator iterPosMem;
	MAP_OPStack::iterator iterPosStack;
	MAP_EXECUTEINFO_TABLE::iterator iterPosEXE;
	MAP_CODE_LINE::iterator itCLPos;
	switch (WPData.objid.s.Type)
	{
	case (int)NMWObjectType::ProgramObject:
		switch (WPData.propValue.propertyIdentifier)
		{
		case(int)NMWPropID::PROGRAM_CHANGE:
			program_change_value = *(ENUMERATED*)&WPData.propValue.pValue;
			objid = WPData.objid.s.ID;
			itPos = _Module.m_mapobjectTable.find(objid);
			if (itPos == _Module.m_mapobjectTable.end())
			{
				// object 없음
			}
			else
			{
				itPos->second.program_change = program_change_value;
				itPos->second.program_state = program_change_value;

				if (program_change_value == 3)
				{
					//halt
					itGlobalPos = _Module.m_mapGlobalCodeLine.find(objid);

					for (itCLPos = itGlobalPos->second.begin(); itCLPos != itGlobalPos->second.end();)
					{
						itCLPos->second.status = FALSE;
						itCLPos++;
					}
				}
				else if (program_change_value == 2)
				{
					//on
					itGlobalPos = _Module.m_mapGlobalCodeLine.find(objid);

					for (itCLPos = itGlobalPos->second.begin(); itCLPos != itGlobalPos->second.end();)
					{
						itCLPos->second.status = TRUE;
						itCLPos++;
					}

				}
				else if (program_change_value == 4)
				{
					//restart 는 FALSE로 만든후 PC도 0으로 바꿔준다.
					// mem, stack 모두 초기화
					itGlobalPos = _Module.m_mapGlobalCodeLine.find(objid);
					iterPosEXE = _Module.m_mapExecuteInfoTable.find(objid);
					iterPosStack = _Module.m_opstack.find(objid);
					for (itCLPos = itGlobalPos->second.begin(); itCLPos != itGlobalPos->second.end();)
					{
						itCLPos->second.status = FALSE;
						itCLPos++;
					}
					iterPosEXE->second.dec = FALSE;
					iterPosEXE->second.PC = 0;
					//stack clear 필요함
					//meme clear 필요한
				}

			}
			break;
		}
		break;
	}
	
	// send simple ack
	ENUMERATED type;
	type = (ENUMERATED)NMWServiceConfirmedType::writeProperty;
	int rp;
	NMWSIConfirmedACKSend(_Module.clientid, devid, type, invokeid, NULL, 0x00, rp);	
}

void CExecuterModule::ReadFileSize(UNSIGNED objid)
{
	UNSIGNED devid = 0;
	stObjectPropertyReference* pRPReqData = new stObjectPropertyReference;
	int i, ret;
	short invokeid;
	int rp;
	ENUMERATED method;
	ENUMERATED type;
	UNSIGNED8 flags = 0x00; //Middle Ware 내의 값만 수신
	stServiceReadPropertyACKData* pAckData = NULL;

	// readproperty file size prop
	//target search map key: objid
	MAP_OBJECT_TABLE::iterator iterPos;
	iterPos = m_mapobjectTable.find(objid);

	if (iterPos == m_mapobjectTable.end())
	{
		// 없는 object id
		return;
	}
	else
	{
		// readproperty send filesize
		pRPReqData->objid.s.ID = objid;
		pRPReqData->objid.s.Type = (ENUMERATED)NMWObjectType::FileObject;
		pRPReqData->propid = (ENUMERATED)NMWPropID::FILE_SIZE;
		pRPReqData->arrayindex = 0xffff;
		type = (ENUMERATED)NMWServiceConfirmedType::readProperty;
		NMWSISendConfirmedReq(_Module.clientid,
			devid,
			type,
			invokeid,
			(void*)pRPReqData,
			flags,
			rp);

		for (i = 0; i < 30; ++i)
		{
			Sleep(100);
			method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
			if (NMWSIRecvServiceCheck(devid, method, type, invokeid, (void*&)pAckData, flags, _Module.clientid, rp))
				break;
		}
		if (i >= 30)
			return;
		// map에 적제
		if (method == (ENUMERATED)NMWServiceMethod::ConfirmedACK)
			iterPos->second.file_size = *(UNSIGNED*)&pAckData->propValue.pValue;
		else
			iterPos->second.file_size = 0;
	}
	
	delete pRPReqData;

}

void CExecuterModule::ReadFile(UNSIGNED objid)
{
	//atomic read file
	int count = 200, startpos = 0;
	int reqCount = 0;
	int rp;
	short invokeid;
	ENUMERATED type;
	ENUMERATED method;
	UNSIGNED8 flags = 0x00;
	UNSIGNED32 devid = 0;
	int ret;
	int retry;
	CString oneLineCode;
	string os;
	string ooo = "";
	char temp_ch[256];	

	stServiceAtomicReadFileReqData* pARFReq = new stServiceAtomicReadFileReqData;
	stServiceAtomicReadFileAckData* pARFAck = NULL;

	MAP_OBJECT_TABLE::iterator iterPos;
	iterPos = _Module.m_mapobjectTable.find(objid);	
	
	//req횟수 구하는 함수
	reqCount = _Module.ReadFileCount(iterPos->first, count);

	for (int i = 0; i < reqCount; i++)
	{
		pARFReq->objid.s.ID = iterPos->first;
		pARFReq->objid.s.Type = (UNSIGNED)NMWObjectType::FileObject;
		pARFReq->accessMethod = (UNSIGNED8)1; //stream_access;
		pARFReq->nFileStartPosition = (UNSIGNED)startpos;
		pARFReq->nCount = (UNSIGNED)count;

		NMWSISendConfirmedReq(_Module.clientid, devid, (ENUMERATED)NMWServiceConfirmedType::atomicReadFile, invokeid, (void*)pARFReq, flags, rp);			
		for (retry = 0; retry < 30; retry++)
		{
			Sleep(100);
			method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
			type = (ENUMERATED)NMWServiceConfirmedType::atomicReadFile;
			if (NMWSIRecvServiceCheck(devid, method, type, invokeid, (void*&)pARFAck, flags, _Module.clientid, rp))
				break;
		}
		//if (i >= 30)
		//	return;
		// file 모으기
		startpos += count;		
		for (int j = 0; j < pARFAck->nCount; j++)
		{
			temp_ch[j] = pARFAck->fileData[j];
			os += temp_ch[j];
			ooo += temp_ch[j];
			/*
			if (temp_ch[j] == 10 && temp_ch[j - 1] == 13)
			{
				oneLineCode = os.c_str();
				TokenFirstStep(oneLineCode);
				os.clear();
				oneLineCode = "";
				for (int init = 0; init < 256; init++)
					temp_ch[init] = 0;
			}
			*/
		}	
	}
	int cutAt = 0, cutAt2 = 0;
	for (int j = 0; j < ooo.length(); j++)
	{	
		if (ooo[j] == 10 && ooo[j - 1] == 13)
		{
			cutAt2 = j - cutAt;
			oneLineCode = ooo.substr(cutAt, cutAt2).c_str();
			TokenFirstStep(oneLineCode);
			os.clear();
			oneLineCode = "";
			for (int init = 0; init < 256; init++)
				temp_ch[init] = 0;
			cutAt = j+1;
		}
	}

	m_mapGlobalCodeLine.insert(map<int, MAP_CODE_LINE>::value_type(objid, m_mapCodeLine));
	m_mapCodeLine.clear();

	delete pARFReq;
	delete pARFAck;
}
void CExecuterModule::DeleteObject(int objectId)
{
	// 1. 우선 정지... 후 삭제
	MAP_OBJECT_TABLE::iterator itPos;
	MAP_Global_CODE_LINE::iterator itGlobalPos;
	MAP_CODE_LINE::iterator itCLPos;

	ENUMERATED program_change_value;
	program_change_value = 3;

	itPos = _Module.m_mapobjectTable.find(objectId);
	if (itPos == _Module.m_mapobjectTable.end())
	{
		//object 없음
	}
	else
	{
		itPos->second.program_change = program_change_value;
		itPos->second.program_state = program_change_value;

		//halt
		itGlobalPos = _Module.m_mapGlobalCodeLine.find(objectId);
		for (itCLPos = itGlobalPos->second.begin(); itCLPos != itGlobalPos->second.end();)
		{
			itCLPos->second.status = FALSE;
			itCLPos++;
		}
		Sleep(500);
		//delete map에서 삭제
		_Module.m_mapobjectTable.erase(objectId);
		_Module.m_mapExecuteInfoTable.erase(objectId);
		_Module.m_memory.erase(objectId);
		_Module.m_opstack.erase(objectId);
		_Module.m_mapGlobalCodeLine.erase(objectId);
	}
}

void CExecuterModule::CreateObject(int objectId, UNSIGNED devid)
{
	//  map에 update
	stObjectstate t_objectinfo;
	stPCDECinfo pcdecinfo;
	Mymemory mymemory;
	Mystack mystack;
	MAP_OBJECT_TABLE::iterator iterPos;
	stServiceReadPropertyMultipleReqData* pRPMReqData = new stServiceReadPropertyMultipleReqData;
	ENUMERATED type;
	ENUMERATED method;

	t_objectinfo.program_change = 0;
	t_objectinfo.program_state = 0;
	t_objectinfo.file_size = 0;
	pcdecinfo.dec = false;
	pcdecinfo.PC = 0;
	_Module.m_mapobjectTable.insert(map<UNSIGNED, stObjectstate>::value_type(objectId, t_objectinfo));
	_Module.m_mapExecuteInfoTable.insert(map<UNSIGNED, stPCDECinfo>::value_type(objectId, pcdecinfo));
	_Module.m_memory.insert(map<UNSIGNED, Mymemory>::value_type(objectId, mymemory));
	_Module.m_opstack.insert(map<UNSIGNED, Mystack>::value_type(objectId, mystack));

	//readproperty multiple 요청
	pRPMReqData->nListOfReadAccessSpecs = 1;
	pRPMReqData->pListOfReadAccessSpecs = new stReadAccessSpec[1];
	pRPMReqData->pListOfReadAccessSpecs[0].objid.s.ID = objectId;
	pRPMReqData->pListOfReadAccessSpecs[0].objid.s.Type = (ENUMERATED)NMWObjectType::ProgramObject;
	pRPMReqData->pListOfReadAccessSpecs[0].nListOfPropertyReferences = 2;
	pRPMReqData->pListOfReadAccessSpecs[0].pListOfPropertyReferences = new stPropertyReference[2];
	pRPMReqData->pListOfReadAccessSpecs[0].pListOfPropertyReferences[0].arrayindex = 0xffff;
	pRPMReqData->pListOfReadAccessSpecs[0].pListOfPropertyReferences[0].propid = (ENUMERATED)NMWPropID::PROGRAM_CHANGE;
	pRPMReqData->pListOfReadAccessSpecs[0].pListOfPropertyReferences[1].arrayindex = 0xffff;
	pRPMReqData->pListOfReadAccessSpecs[0].pListOfPropertyReferences[1].propid = (ENUMERATED)NMWPropID::PROGRAM_STATE;

	type = (ENUMERATED)NMWServiceConfirmedType::readPropertyMultiple;

	int ret, i;
	short invokeid;
	UNSIGNED8 flags = 0x00;  //Middle Ware 내의 값만 수신
	stServiceReadPropertyMultipleACKData* pRPMAdata = NULL;

	if (NMWSISendConfirmedReq(_Module.clientid,
		devid,
		type,
		invokeid,
		(void*)pRPMReqData,
		flags,
		rp) >= 0)
	{
		for (i = 0; i < 30; i++)
		{
			Sleep(100);
			method = (ENUMERATED)NMWServiceMethod::ConfirmedACK;
			if (NMWSIRecvServiceCheck(devid, method, type, invokeid, (void*&)pRPMAdata, flags, _Module.clientid, rp))
				break;
			
		}
		if (i >= 30)
			return;
		// 풀어서 map에 insert
		for (i = 0; i < pRPMAdata->nListOfReadAccessResults; i++){
			iterPos = _Module.m_mapobjectTable.find(pRPMAdata->pListOfReadAccessResults[i].objid.s.ID);
			if (iterPos == _Module.m_mapobjectTable.end())
			{
				continue;
			}
			else
			{
				iterPos->second.program_change = *(ENUMERATED*)&pRPMAdata->pListOfReadAccessResults[i].pListOfResult[0].pValue;
				iterPos->second.program_state = *(ENUMERATED*)&pRPMAdata->pListOfReadAccessResults[i].pListOfResult[1].pValue;
			}
		}
	}
	//read file size
	ReadFileSize(objectId);
	ReadFile(objectId);
	delete pRPMAdata;
	delete pRPMReqData;
}

void CExecuterModule::RecvReadPropertyMultipleReq(int devid, short invokeid, stServiceReadPropertyMultipleReqData RPMData)
{
	//readpropertymultiple ack
	int size = 	RPMData.nListOfReadAccessSpecs;
	MAP_OBJECT_TABLE::iterator itPos;
	
	stServiceReadPropertyMultipleACKData* RPMAdata = new stServiceReadPropertyMultipleACKData;
	RPMAdata->nListOfReadAccessResults = RPMData.nListOfReadAccessSpecs;
	RPMAdata->pListOfReadAccessResults = new stReadAccessResult[RPMAdata->nListOfReadAccessResults];

	for (int i = 0; i < size; i++)
	{
		itPos = _Module.m_mapobjectTable.find(RPMData.pListOfReadAccessSpecs[i].objid.s.ID);
		if (itPos == _Module.m_mapobjectTable.end())
		{
			//object 없음
			RPMAdata->pListOfReadAccessResults[i].message.ncs = 1;
			RPMAdata->pListOfReadAccessResults[i].message.cs[0] = '\0';
			RPMAdata->pListOfReadAccessResults[i].ccmsid.ncs = 1;
			RPMAdata->pListOfReadAccessResults[i].ccmsid.cs[0] = '\0';
			RPMAdata->pListOfReadAccessResults[i].nListOfResult = 1;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult = new stPropertyValue[1];
			RPMAdata->pListOfReadAccessResults[i].objid.s.ID = RPMData.pListOfReadAccessSpecs[i].objid.s.ID;
			RPMAdata->pListOfReadAccessResults[i].objid.s.Type = (ENUMERATED)NMWObjectType::ProgramObject;

			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].nValue = 0;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].propertyIdentifier = (ENUMERATED)NMWPropID::PROGRAM_STATE;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].propertyArrayIndex = RPMData.pListOfReadAccessSpecs[i].pListOfPropertyReferences[0].arrayindex;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].tValue = (UNSIGNED16)NMWDataTypeID::dtEnumerated;
			*(ENUMERATED*)&RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].pValue = 0;
		}
		else
		{
			// state 넣기
			RPMAdata->pListOfReadAccessResults[i].message.ncs = 1;
			RPMAdata->pListOfReadAccessResults[i].message.cs[0] = '\0';
			RPMAdata->pListOfReadAccessResults[i].ccmsid.ncs = 1;
			RPMAdata->pListOfReadAccessResults[i].ccmsid.cs[0] = '\0';
			RPMAdata->pListOfReadAccessResults[i].nListOfResult = 1;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult = new stPropertyValue[1];
			RPMAdata->pListOfReadAccessResults[i].objid.s.ID = RPMData.pListOfReadAccessSpecs[i].objid.s.ID;
			RPMAdata->pListOfReadAccessResults[i].objid.s.Type = (ENUMERATED)NMWObjectType::ProgramObject;

			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].nValue =0;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].propertyIdentifier = (ENUMERATED)NMWPropID::PROGRAM_STATE;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].propertyArrayIndex = RPMData.pListOfReadAccessSpecs[i].pListOfPropertyReferences[0].arrayindex;
			RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].tValue = (UNSIGNED16)NMWDataTypeID::dtEnumerated;
			*(ENUMERATED*)&RPMAdata->pListOfReadAccessResults[i].pListOfResult[0].pValue = itPos->second.program_state;
		}
	}
	ENUMERATED type;
	type = (ENUMERATED)NMWServiceConfirmedType::readPropertyMultiple;
	int rp;
	NMWSIConfirmedACKSend(_Module.clientid, devid, type, invokeid, (void*)RPMAdata, 0x00, rp);
	delete []RPMAdata->pListOfReadAccessResults->pListOfResult;
	delete []RPMAdata->pListOfReadAccessResults;
	delete RPMAdata;
}

void CExecuterModule::Readcodetodevobjid(BYTE code[7], int& devid, int& objid)
{
	string hextostringdev, hextostringobjid;
	CString t_sthex;

	for (int i = 0; i < 3; i++)
	{
		t_sthex.Format("%02x", code[i]);
		hextostringdev += t_sthex;
	}
	devid = _Module.string2hex2dec(hextostringdev);

	for (int i = 3; i < 7; i++)
	{
		t_sthex.Format("%02x", code[i]);
		hextostringobjid += t_sthex;
	}
	objid = _Module.string2hex2dec(hextostringobjid);
}

void CExecuterModule::RecvCreateObjectREQ(int devid, short invokeid, stReadAccessResult* COData)
{
	//object map 에 생성 
	// 각종 map 추가
	// 코드 리딩 atomic file
}

void CExecuterModule::RecvDeleteObjectREQ(int devid, short invokeid, stObjectID DOData)
{
	//코드 및 각종 맵 삭제 
	
}

int CExecuterModule::ReadFileCount(UNSIGNED objid, UNSIGNED splitSize)
{
	int ReqCount = 0;
	int Reqnamerge;
	MAP_OBJECT_TABLE::iterator iterPos;
	iterPos = _Module.m_mapobjectTable.find(objid);
	Reqnamerge = iterPos->second.file_size % splitSize;
	if (Reqnamerge != 0)
		ReqCount = iterPos->second.file_size / splitSize + 1;
	else
		ReqCount = iterPos->second.file_size;

	return ReqCount;
}