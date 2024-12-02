// DefaultWindow.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DefaultWindow.h"
#include "MainGame.h"
#include "Object.h"
#include "SelectScene.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                          
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];         
HWND g_hWnd;

ATOM                MyRegisterClass(HINSTANCE hInstance);   
BOOL                InitInstance(HINSTANCE, int);           
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,        
                     _In_opt_ HINSTANCE hPrevInstance,  
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)           
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));
    MSG msg;
    msg.message = WM_NULL;

    ULONG64 ullTime = GetTickCount64();


    /*----------------
       SelectPlayer
   -----------------*/
    CObject* pPlayer(nullptr);
    SelectScene select;
    select.Initilaize();

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {

                TranslateMessage(&msg);


                DispatchMessage(&msg);
            }
        }
        else
        {
            if (ullTime + 10 < GetTickCount64())
            {
                if (pPlayer != nullptr) break;
                select.Update();
                pPlayer = select.Late_Update();
                select.Render();

                ullTime = GetTickCount64();
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE))
            PostQuitMessage(0);
    }

    /*----------------
        MainGame
    -----------------*/
    CMainGame MainGame;
    MainGame.Initialize(pPlayer);

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                
                TranslateMessage(&msg);

 
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (ullTime + 10 < GetTickCount64())
            {
                MainGame.Update();
                MainGame.Late_Update();
                MainGame.Render();

                ullTime = GetTickCount64();
            }
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);


    wcex.style          = CS_HREDRAW | CS_VREDRAW;

    wcex.lpfnWndProc    = WndProc;

    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;

    wcex.hInstance      = hInstance;

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    wcex.lpszMenuName = NULL;
   
    wcex.lpszClassName  = szWindowClass;

    
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   RECT rc{ 0, 0, WINCX, WINCY };

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass,        
                             szTitle,               
                             WS_OVERLAPPEDWINDOW,   
                             CW_USEDEFAULT, 0,      
                             rc.right - rc.left,
                             rc.bottom - rc.top,   
                             nullptr,               
                             nullptr,             
                             hInstance,            
                             nullptr);             

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


RECT        rc{ 100, 100, 200, 200 };
list<RECT>  BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
  
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
        }
        break;
    case WM_KEYDOWN:

        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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


