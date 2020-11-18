
// main.cpp

#include	<windows.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"ddHeapMonitor.h"

#include	"DealDominator.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

// プロトタイプ
int PASCAL				WinMain( HINSTANCE hInst, HINSTANCE hPrev, char *CmdLine, int CmdShow );

//------------------------------------------------------------------
//------------------------------------------------------------------

// WinMain - Windows アプリケーションはここから始まる
int PASCAL	WinMain( HINSTANCE hInst, HINSTANCE hPrev, char *CmdLine, int CmdShow )
{
	(DDvoid)hPrev;
	(DDvoid)CmdLine;
	(DDvoid)CmdShow;
	
	// ウィンドウ作成
	DealDominator::ddCreateWindow( hInst );
	
	
	// ヒープモニター初期化
	dhgHeapMonitorInitial();
	
		dhgHeapMonitorSaveStatus();
		{
			DealDominator*		deal;
			
			// system entry
			deal = new DealDominator( hInst );
			
			// system process
			deal -> ddMain();
			
			// system erase
			delete	deal;
		}
		dhgHeapMonitorLeakDetect();
	
	// ヒープモニター抹消
	dhgHeapMonitorDispose();
	
	
	// 終了後のメモリリークチェック予約
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	return	0;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

// メインウインドウプロシージャ
LRESULT CALLBACK	procMain( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		// 終了フラグ
		case	WM_CLOSE:
			
			if( ddgThis() )
			{
				ddgThis() -> ddSetEnd();
			}
			return	1;
		
		// キー入力
		case	WM_KEYDOWN:
			
			switch( wParam )
			{
				// 終了キー
				case VK_ESCAPE:
				case VK_F12:
					PostMessage( hWnd, WM_CLOSE, 0, 0 );
					break;
				
				default:
					break;
			}
			break;
	}
	return	DefWindowProc( hWnd, msg, wParam, lParam );
}

