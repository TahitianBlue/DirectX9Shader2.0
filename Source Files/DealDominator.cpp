
//------------------------------------------------------------------
//------------------------------------------------------------------
//	Deal Dominator
//		2002-04-19		tahei katagai
//------------------------------------------------------------------
//------------------------------------------------------------------

#include	"DealDominator.h"

#include	"ddGraphic.h"
#include	"ddInput.h"
#include	"ddStroke.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

HINSTANCE								DealDominator::ddmHInst;
HWND										DealDominator::ddmH_wnd;
DealDominator*					DealDominator::ddmThis = NULL;

//------------------------------------------------------------------
//------------------------------------------------------------------

// �E�B���h�E�쐬
DDvoid	DealDominator::ddCreateWindow( HINSTANCE hInst )
{
	WNDCLASS		wc;
	s32					width;
	s32					height;
	
	// ���C���E�C���h�E���쐬����
	ZeroMemory( &wc, sizeof( WNDCLASS ) );
	
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.hCursor				= LoadCursor( NULL, IDC_ARROW );
	wc.hInstance			= hInst;
	wc.lpfnWndProc		= procMain;
	wc.lpszClassName	= "BASE";
	
	RegisterClass( &wc );
	
	// �E�C���h�E�̑傫�����v�Z
	#if  FULLSCREEN
	{
		// �t���X�N���[�����͂��̂܂܂� OK
		width  = (u32)WIDTH;
		height = (u32)HEIGHT;
	}
	#else
	{
		// �E�C���h�E���̓E�C���h�E�̊O�g�̃T�C�Y���l������
		width  = (u32)WIDTH  + GetSystemMetrics( SM_CXDLGFRAME ) * 2;
		height = (u32)HEIGHT + GetSystemMetrics( SM_CYDLGFRAME ) * 2 + GetSystemMetrics( SM_CYCAPTION );
	}
	#endif
	
	// �E�C���h�E���쐬
	ddmH_wnd = CreateWindow( "BASE", CAPTION, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInst, NULL );
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DealDominator::DealDominator( HINSTANCE hInst )
{
	ddASSERT( ddmThis != NULL );
	
	ddmThis = this;
	
	ddmHInst = hInst;
	
	ddmError = false;
	ddmEnd   = false;
	
	ddmStage		 = DS_STAGE_NULL;
	ddmNextStage = DS_STAGE_NULL;
	
	// direct X initial
	if( ddInitialGraphic() ){ ddASSERT( true );	}
	if( ddInitialSound  () ){	ddASSERT( true );	}
	if( ddInitialInput  () ){	ddASSERT( true );	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DealDominator::~DealDominator( DDvoid )
{
	// direct X dispose
	if( ddDisposeInput  () ){	ddASSERT( true );	}
	if( ddDisposeSound  () ){	ddASSERT( true );	}
	if( ddDisposeGraphic() ){ ddASSERT( true );	}
	
	ddASSERT( ddmStage != DS_STAGE_NULL );
	ddASSERT( ddmThis  != this );
	ddmThis = NULL;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	DealDominator::ddInitialGraphic( DDvoid )
{
	return	DDGraphic::dgGraphicInitial();
}

DDbool	DealDominator::ddDisposeGraphic( DDvoid )
{
	return	DDGraphic::dgGraphicDispose();
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	DealDominator::ddInitialSound( DDvoid )
{
	return	false;
}

DDbool	DealDominator::ddDisposeSound( DDvoid )
{
	return	false;
}


//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	DealDominator::ddInitialInput( DDvoid )
{
	return	DDInput::diInputInitial();
}

DDbool	DealDominator::ddDisposeInput( DDvoid )
{
	return	DDInput::diInputDispose();
}


//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	DealDominator::ddMain( DDvoid )
{
	MSG				msg;
	DDbool		continuation = true;
	
	// start stage
	ddmStage     = DS_STAGE_97;
	ddmNextStage = DS_STAGE_NULL;
	
	
	while( continuation )
	{
		continuation = false;
		
		// stroke construction
		DDStroke::dsStrokeInitial( ddmStage );
		
		// main stroke loop
		while( ddmEnd == false )
		{
			// ���b�Z�[�W�����Ă��邩?
			if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
			{
				// ���b�Z�[�W�̏���
				TranslateMessage( &msg );
				DispatchMessage ( &msg );
			}
			
			// system stroke
			ddStroke();
			
			// soft reset ( START + R + L )
			if( ddmEnd == false )
			{
			//if( digBits() == ( DI_BIT_BST | DI_BIT_BR | DI_BIT_BL )  &&  digPush() == DI_BIT_BS )
				if( digPush() == DI_BIT_BSL )
				{
					ddmEnd = true;
					
					ddmNextStage = (DSstage)( ddmStage + 1 );
					
					if( ddmNextStage == DS_STAGE_TOTAL ){  ddmNextStage = DS_STAGE_97;  }
				}
			}
		}
		
		// dispose stroke
		ddmEnd = false;
		
		DDStroke::dsStrokeDispose();
		
		ddmStage = DS_STAGE_NULL;
		
		// next stroke
		if( ddmNextStage != DS_STAGE_NULL )
		{
			ddmStage     = ddmNextStage;
			ddmNextStage = DS_STAGE_NULL;
			
			continuation = true;
		}
	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------
// stroke entrance 1 frame 1 time

DDbool	DealDominator::ddStroke( DDvoid )
{
	// main stroke
	DDStroke::dsStrokeProcess();
	
	// buffer swap ( back buffer to primary buffer )
	if( FAILED( dggD()->Present( NULL, NULL, NULL, NULL ) ) )
	{
		dggD()->Reset( &DDGraphic::dgParam() );
	}
	
	return	true;
}

