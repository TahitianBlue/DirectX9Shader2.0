
#include	"ddInput.h"

#include	"DealDominator.h"

//--------------------------------------------------------------
//--------------------------------------------------------------

#define		DI_DXID_BUFFER_SIZE		( 0 )			// device buffer size
#define		DI_DXID_AXIS_RANGE		( 1024 )	// device axis range

//--------------------------------------------------------------
//--------------------------------------------------------------

LPDIRECTINPUT8				DDInput::dimDXI;
LPDIRECTINPUTDEVICE8	DDInput::dimDXID;
DIDEVCAPS							DDInput::dimDXIDCaps;

DDbits	DDInput::dimBits;
DDbits	DDInput::dimPrev;
DDbits	DDInput::dimPush;

//--------------------------------------------------------------
//--------------------------------------------------------------

DDbool	DDInput::diInputInitial( DDvoid )
{
	HRESULT			res;
	
	dimDXI  = NULL;
	dimDXID = NULL;
	
	// create direct input
	res = DirectInput8Create(
		ddgThis() -> ddGetHInst(),
		DIRECTINPUT_VERSION, 
		IID_IDirectInput8,
		(DDvoid**)&dimDXI,
		NULL );
	
	if( FAILED( res ) )
	{
		DXTRACE_ERR( "DirectInput8�I�u�W�F�N�g�̍쐬�Ɏ��s", res );
		return	true;
	}
	
	// device listing and create
	res = dimDXI -> EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		diEnumJoysticksCallback,
		NULL,
		DIEDFL_ATTACHEDONLY );
	
	if( FAILED( res ) || dimDXI == NULL )
	{
		DXTRACE_ERR( "DirectInputDevice8�I�u�W�F�N�g�̍쐬�Ɏ��s", res );
		return	true;
	}
	
	// setup data format
	res = dimDXID -> SetDataFormat( &c_dfDIJoystick2 );
	
	if( FAILED( res ) )
	{
		DXTRACE_ERR( "c_dfDIJoystick2�`���̐ݒ�Ɏ��s", res );
		return	true;
	}
	
	// setup mode �i�t�H�A�O���E���h����r�����[�h�j
	res = dimDXID -> SetCooperativeLevel(
		ddgThis() -> ddGetH_wnd(),
		( DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) );
	
	if( FAILED( res ) )
	{
		DXTRACE_ERR( "�t�H�A�O���E���h����r�����[�h�̐ݒ�Ɏ��s", res );
		return	true;
	}
	
	// setup axis mode
	res = dimDXID -> EnumObjects( diEnumAxesCallback, NULL, DIDFT_AXIS );
	
	if( FAILED( res ) )
	{
		DXTRACE_ERR( "�����[�h�̐ݒ�Ɏ��s", res );
		return	true;
	}
	
	// set up axiz mode�i��Βl���[�h�ɐݒ�B�f�t�H���g�Ȃ̂ŕK�������ݒ�͕K�v�Ȃ��j
	DIPROPDWORD		diprop;
	
	diprop.diph.dwSize       = sizeof( diprop ); 
	diprop.diph.dwHeaderSize = sizeof( diprop.diph ); 
	diprop.diph.dwObj        = 0;
	diprop.diph.dwHow        = DIPH_DEVICE;
	diprop.dwData            = DIPROPAXISMODE_ABS;
//diprop.dwData            = DIPROPAXISMODE_REL;	// ���Βl���[�h�̏ꍇ
	
	res = dimDXID -> SetProperty( DIPROP_AXISMODE, &diprop.diph );
	
	if( FAILED( res ) )
	{
		DXTRACE_ERR( "�����[�h�̐ݒ�Ɏ��s", res );
		return	true;
	}
	
	// setup buffer size
	diprop.dwData = DI_DXID_BUFFER_SIZE;
	
	res = dimDXID -> SetProperty( DIPROP_BUFFERSIZE, &diprop.diph );
	
	if( FAILED( res ) )
	{
		DXTRACE_ERR( "�o�b�t�@�E�T�C�Y�̐ݒ�Ɏ��s", res );
		return	true;
	}
	
	// start the device input
	dimDXID -> Acquire();
	
	return	false;
}

//--------------------------------------------------------------

DDbool	DDInput::diInputDispose( DDvoid )
{
	// DirectInput�̃f�o�C�X�����
	if( dimDXID )
		dimDXID -> Unacquire(); 
	
	ddRELEASE( dimDXID );
	ddRELEASE( dimDXI );
	
	return	false;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	DDInput::diInputProcess( DDvoid )
{
	HRESULT				res;
	DIJOYSTATE2		dijs;
	
	// intro
	dimPrev = dimBits;
	dimBits = 0;
	dimPush = 0;
	
	// check device pointer
	if( dimDXID == NULL )
		return;
	
	// device poll
	res = dimDXID -> Poll();
	
	if( FAILED( res ) )
	{
		res = dimDXID -> Acquire();
		
		while( res == DIERR_INPUTLOST )
		{
			res = dimDXID -> Acquire();
		}
	}
	
	// get device data to dijs structure
	res = dimDXID -> GetDeviceState( sizeof( DIJOYSTATE2 ), &dijs );
	
	if( SUCCEEDED( res ) )
	{
		// get axis bit
		if( dijs.lX > ( +DI_DXID_AXIS_RANGE / 2 ) ){ dimBits |= DI_BIT_XR; }
		if( dijs.lX < ( -DI_DXID_AXIS_RANGE / 2 ) ){ dimBits |= DI_BIT_XL; }
		if( dijs.lY > ( +DI_DXID_AXIS_RANGE / 2 ) ){ dimBits |= DI_BIT_YD; }
		if( dijs.lY < ( -DI_DXID_AXIS_RANGE / 2 ) ){ dimBits |= DI_BIT_YU; }
		
		// get buttons
		if( dijs.rgbButtons[ 8 ] & 0x80 ){ dimBits |= DI_BIT_BST; }
		if( dijs.rgbButtons[ 9 ] & 0x80 ){ dimBits |= DI_BIT_BSL; }
		
		if( dijs.rgbButtons[ 7 ] & 0x80 ){ dimBits |= DI_BIT_BR; }
		if( dijs.rgbButtons[ 6 ] & 0x80 ){ dimBits |= DI_BIT_BL; }
		
		if( dijs.rgbButtons[ 1 ] & 0x80 ){ dimBits |= DI_BIT_BA; }
		if( dijs.rgbButtons[ 2 ] & 0x80 ){ dimBits |= DI_BIT_BB; }
		if( dijs.rgbButtons[ 0 ] & 0x80 ){ dimBits |= DI_BIT_BC; }
		if( dijs.rgbButtons[ 3 ] & 0x80 ){ dimBits |= DI_BIT_BD; }
		
		// make push bits
		dimPush = ( dimBits ^ dimPrev ) & dimBits;
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------

// joystick listing call back
BOOL	CALLBACK	DDInput::diEnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext )
{
	(DDvoid)pContext;
	
	HRESULT		res;
	
	// create interface for listed joystick
	res = dimDXI -> CreateDevice( pdidInstance -> guidInstance, &dimDXID, NULL );
	
	if( FAILED( res ) )
		return	DIENUM_CONTINUE;
	
	// evaluate joystick spec
	dimDXIDCaps.dwSize = sizeof( DIDEVCAPS );
	
	res = dimDXID -> GetCapabilities( &dimDXIDCaps );
	
	if( FAILED( res ) )
	{
		// �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		ddRELEASE( dimDXID );
		return	DIENUM_CONTINUE;
	}
	
	return	DIENUM_STOP;
}

//--------------------------------------------------------------

// joystick axis listing call back
BOOL	CALLBACK	DDInput::diEnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
{
	(DDvoid)pvRef;
	
	HRESULT		res;
	
	// setup axis range ( -DI_DXID_AXIS_RANGE _ +DI_DXID_AXIS_RANGE )
	DIPROPRANGE diprg;
	
	ZeroMemory( &diprg, sizeof( diprg ) );
	
	diprg.diph.dwSize       = sizeof(diprg); 
	diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
	diprg.diph.dwObj        = lpddoi -> dwType;
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.lMin              = -DI_DXID_AXIS_RANGE;
	diprg.lMax              = +DI_DXID_AXIS_RANGE;
	
	res = dimDXID -> SetProperty( DIPROP_RANGE, &diprg.diph );
	
	if( FAILED( res ) )
		return	DIENUM_STOP;
	
	return	DIENUM_CONTINUE;
}

