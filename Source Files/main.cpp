
// main.cpp

#include	<windows.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"ddHeapMonitor.h"

#include	"DealDominator.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

// �v���g�^�C�v
int PASCAL				WinMain( HINSTANCE hInst, HINSTANCE hPrev, char *CmdLine, int CmdShow );

//------------------------------------------------------------------
//------------------------------------------------------------------

// WinMain - Windows �A�v���P�[�V�����͂�������n�܂�
int PASCAL	WinMain( HINSTANCE hInst, HINSTANCE hPrev, char *CmdLine, int CmdShow )
{
	(DDvoid)hPrev;
	(DDvoid)CmdLine;
	(DDvoid)CmdShow;
	
	// �E�B���h�E�쐬
	DealDominator::ddCreateWindow( hInst );
	
	
	// �q�[�v���j�^�[������
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
	
	// �q�[�v���j�^�[����
	dhgHeapMonitorDispose();
	
	
	// �I����̃��������[�N�`�F�b�N�\��
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	return	0;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

// ���C���E�C���h�E�v���V�[�W��
LRESULT CALLBACK	procMain( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		// �I���t���O
		case	WM_CLOSE:
			
			if( ddgThis() )
			{
				ddgThis() -> ddSetEnd();
			}
			return	1;
		
		// �L�[����
		case	WM_KEYDOWN:
			
			switch( wParam )
			{
				// �I���L�[
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

