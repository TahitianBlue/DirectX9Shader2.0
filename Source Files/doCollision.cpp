
#include	"doCollision.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DCvec					DOCollision::docmAXIS;
s32						DOCollision::docmINDEX;
DOCTable			DOCollision::docmTABLE[ DOC_TABLE_SIZE ];
DOCollision*	DOCollision::docmDisBASE;

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DOCollision::docCollisionInitial( DDvoid )
{
	docmAXIS  = dcXp();
	docmINDEX = 0;
	
	for( s32 i=0 ; i!=DOC_TABLE_SIZE ; i++ )
	{
		docmTABLE[ i ].Con = NULL;
		docmTABLE[ i ].Key = 0.0f;
	}
	
	docmDisBASE = NULL;
}

DDvoid		DOCollision::docCollisionDispose( DDvoid )
{
	while( docmTABLE[ 0 ].Con ){ delete docmTABLE[ 0 ].Con; }
	
	while( docmDisBASE ){ delete docmDisBASE; }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DOCollision::docCollisionProcess( DDvoid )
{
	s32					i;
	s32					j;
	
	DDenum			owner;
	
	f32					maxRadius;
	
	f32					v1;
	f32					v2;

	f32					r1;
	f32					r2;

	f32					m1;
	f32					m2;

	f32					md;
	f32					mi;
	f32					cr;
	
	f32					k1;
	
	f32					r12;
	f32					c12;
	f32					work;

	DCvec				Delta;
	
	DOCTable		save;
	
	
	// �O�����@�\�[�g�L�[�Z�o�@�ő唼�a�擾
	maxRadius = 0.0f;
	
	for( i = 0 ; i < docmINDEX ; i++ )
	{
		docmTABLE[ i ].Con -> docmCollided = false;
		
		docmTABLE[ i ].Key = dcDot( docmAXIS, docmTABLE[ i ].Con -> docmP );
		
		if( maxRadius < docmTABLE[ i ].Con -> docmRadius )
		{
			maxRadius = docmTABLE[ i ].Con -> docmRadius;
		}
	}
	
	// ���ǃo�u���\�[�g
	{
		s32		fg;		// final	�����L�����Ō�Ɍ��������z��ԍ�
		s32		st;		// start	�O
		s32		en;		// end		�z��
		s32		sp;		// step		�i�s����
		
		fg = 1;
		st = 0;
		en = docmINDEX;
		sp = 1;
		i  = 1;
		
		while( fg )
		{
			fg = 0;
			
			while( st < i && i < en )
			{
				if( docmTABLE[ i ].Key < docmTABLE[ i - 1 ].Key )
				{
					save = docmTABLE[ i ];
					
					docmTABLE[ i ]     = docmTABLE[ i - 1 ];
					docmTABLE[ i - 1 ] = save;
					
					fg = i;
				}
				i += sp;
			}
			
			if( sp == 1 )
			{
				en = fg;
				sp = -1;
			}
			else
			{
				st = fg;
				sp = +1;
			}
			i = fg + sp;
		}
	}
	
	// �C���f�b�N�X�ăZ�b�g
	for( i = 0 ; i < docmINDEX ; i++ )
	{
		docmTABLE[ i ].Con -> docmIndex = i;
	}
	
	// ����
	for( i = 0 ; i < docmINDEX - 1 ; i++ )
	{
		r1 = docmTABLE[ i ].Con -> docmRadius;
		k1 = docmTABLE[ i ].Key;
		
		owner = docmTABLE[ i ].Con -> docmOwner;
		
		for( j = i + 1 ; j < docmINDEX ; j++ )
		{
			if( owner != docmTABLE[ j ].Con -> docmOwner )
			{
				r2  = docmTABLE[ j ].Con -> docmRadius;
				r12 = r1 + r2;
				
				// �K�p�͈̓`�F�b�N
				if( docmTABLE[ j ].Key - k1 > maxRadius + r1 )
					break;
				
				// �Փˌ��o
				dcVSub( docmTABLE[ i ].Con -> docmP, docmTABLE[ j ].Con -> docmP, Delta );
				
				work = dcNormSqr( Delta );
				
				if( work > 0.0f  &&  work <= r12 * r12 )
				{
					// set collided
					docmTABLE[ i ].Con -> docmCollided = true;
					docmTABLE[ j ].Con -> docmCollided = true;
					
					// preparetion
					work = dcSqrt( work );
					
					dcVScale( 1.0f / work, Delta );
					
					c12 = r12 - work;
					
					m1 = docmTABLE[ i ].Con -> docmMass;
					m2 = docmTABLE[ j ].Con -> docmMass;
					
					md =    ( m1 - m2 );
					mi = RPC( m1 + m2 );
					
					cr = c12 * m1 * mi;
					
					// ���W�␳
					dcVAdd( docmTABLE[ i ].Con -> docmP, c12 - cr + _256, Delta, docmTABLE[ i ].Con -> docmP );
					dcVSub( docmTABLE[ j ].Con -> docmP,       cr + _256, Delta, docmTABLE[ j ].Con -> docmP );
					
					// ����
					v1 = dcDot( docmTABLE[ i ].Con -> docmV, Delta );
					v2 = dcDot( docmTABLE[ j ].Con -> docmV, Delta );
					
					dcVAdd( docmTABLE[ i ].Con -> docmV, m2 * ( v1 - v2 ) * -2.0f * mi, Delta, docmTABLE[ i ].Con -> docmV );
					dcVAdd( docmTABLE[ j ].Con -> docmV, m1 * ( v2 - v1 ) * -2.0f * mi, Delta, docmTABLE[ j ].Con -> docmV );
				}
			}
		}
	}
}

DDvoid	DOCollision::docCollisionIntro( DDvoid )
{
	s32			i;
	
	for( i = 0 ; i < docmINDEX ; i++ )
		docmTABLE[ i ].Con -> docIntro();
}

DDvoid	DOCollision::docCollisionOutro( DDvoid )
{
	s32			i;
	
	for( i = 0 ; i < docmINDEX ; i++ )
		docmTABLE[ i ].Con -> docOutro();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DOCollision::DOCollision( DDvoid )
{
	#ifdef	DD_DEBUG
	dcVLoad( docmP, dcNan(), dcNan(), dcNan() );		// �񐔏�����
	#endif	DD_DEBUG
	
	docmOwner = (DDenum)this;
	docmIndex = -1;						// DISABLE
	
	docAppend();
}

DOCollision::~DOCollision( DDvoid ) 
{
	if( docmIndex >= 0 )	docErase();
	else									docRemove();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DOCollision::docEnable( DDvoid )
{
	if( docmIndex < 0 )
	{
		docRemove();
		docEntry();			// docmIndex = ENABLE = 0_
	}
}

DDvoid		DOCollision::docDisable( DDvoid )
{
	if( docmIndex >= 0 )
	{
		docErase();			// docmIndex = DISABLE = -1
		docAppend();
	}
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

// ���������N���X�g�ւ̒ǉ�
DDvoid 	DOCollision::docAppend( DDvoid )
{
	this -> docmNext = docmDisBASE;
	this -> docmPrev = NULL;
	docmDisBASE      = this;
	
	if( this -> docmNext )
		this -> docmNext -> docmPrev = this;
}

// ���������N���X�g����̍폜
DDvoid 	DOCollision::docRemove( DDvoid )
{
	if( this -> docmNext )
		this -> docmNext -> docmPrev = this -> docmPrev;
	
	if( this -> docmPrev )
		this -> docmPrev -> docmNext = this -> docmNext;
	else
		docmDisBASE = this -> docmNext;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

// �L���\�[�g�e�[�u���ւ̓o�^
DDvoid	DOCollision::docEntry( DDvoid )
{
	s32			i;
	f32			key;
	
	i   = 0;
	key = dcDot( docmAXIS, docmP );
	
	// �ő吔�m�F
	ddASSERT( docmINDEX == DOC_TABLE_SIZE );
	
	// Position�ݒ�m�F
	ddNAN( key );
	
	// �����ʒu�̌��o
	while( docmTABLE[ i ].Key < key  &&  i != docmINDEX )		i++;
	
	// ENABLE
	docmIndex = i;
	
	// ��납��P�Âړ������č������݈ʒu���󂯂�
	for( i = docmINDEX ; i != docmIndex ; i-- )
	{
		docmTABLE[ i ] = docmTABLE[ i - 1 ];
		docmTABLE[ i ].Con -> docmIndex = i;
	}
	
	// ����
	docmTABLE[ docmIndex ].Con = this;
	docmTABLE[ docmIndex ].Key = key;
	
	// �����{�P
	docmINDEX++;
}

// �L���\�[�g�e�[�u������̖���
DDvoid	DOCollision::docErase( DDvoid )
{
	s32		i;
	
	--docmINDEX;
	
	for( i = docmIndex ; i < docmINDEX ; i++ )
	{
		docmTABLE[ i ] = docmTABLE[ i + 1 ];
		docmTABLE[ i ].Con -> docmIndex = i;
	}
	
	docmTABLE[ i ].Con = NULL;
	docmTABLE[ i ].Key = 0.0f;
	
	docmIndex = -1;			// DISABLE
}

