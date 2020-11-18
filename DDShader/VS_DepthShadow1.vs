
// depth shadow vertex shader pass 1

//	���W�ϊ�
//	���f���e�N�X�`����������( XZ���� )
//	�e�e�N�X�`�����W�o��
//	���˕t�����C�e�B���O

vs_2_0

// ���̓��W�X�^
dcl_position0			v0
dcl_normal0				v4

// �萔���W�X�^
// c0_c3		�ϊ��s��
// c4				�����x�N�g��
// c5.x			���ʔ��˗� * 0.5f
// c8_c11		�e�e�N�X�`�����W�ւ̕ϊ��s��

// �萔			c31		0.5f,		-,			-, 			-
def					c31,	0.5f,		0.0f,		0.0f,		0.0f

// c32			diffuse color
// c33			ambient color

//----------------------------------------------------------------
//----------------------------------------------------------------

// transform

m4x4		oPos,		v0,			c0			// vertex transform

// texture

// model texture uv
add			oT0.xy,	v0.xz,	c31.xx	// local XZ + 0.5f => tex UV

// shadow texture xyzw
m4x4		oT1,		v0,			c8			// ���Wv0�� �e�s��c8_c11�ŕϊ�

// lighting

// ���x
dp3			r0.x,		v4,			c4			// ���]���x = dot( �@��v4, ����c4 )
mov			r0.x,		-r0.x						// �����x = -���]���x
abs			r0.y,		r0.x						// ��Βl���x

// ���ʌ��x
add			r0.z,		r0.x,		r0.y		// ���x + ��Βl���x = ���x*2 : 0
mul			r0.z,		r0.z,		c31.x		// ���x*2 * 0.5f = ���x : 0

// ���ʌ��x
add			r0.w,		r0.x,		-r0.y		// ���x - ��Βl���x = 0 : -���x*2
mul			r0.w,		-r0.w,	c5.x		// ���x*2 * RefCo*0.5f = 0 : ���ʌ��x

// ���v���x
add			r0.y,		r0.z,		r0.w		// ���ʌ��x + ���ʌ��x ( �ǂ��炩���� )

// output diffuse
mul			r1.rgb,	r0.y,		c32.rgb	// ���v���x x dif.RGB
mul			r1.a,		r0.x,		c32.a		// ���ʌ��x x dif.A
add			oD0,		r1,			c33			// ���_�FoD0 = DIF + AMB


