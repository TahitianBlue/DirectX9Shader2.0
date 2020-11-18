
// �ڂ����t�B���^ 4 texture filter vertex shader

//	4 texture * 4 sample = 16 texel filter
//	��������}�P�h�b�g���炵���S�̃e�N�X�`�����W���o��

vs_2_0

// ���̓��W�X�^
dcl_position0			v0				// ���W�ϊ�������PS�֏o��
dcl_texcoord0			v8				// �e�N�X�`�����W�O

// �萔���W�X�^
//	c0		texture offset 1.0f / �� ( +X, +Y, -X, -Y )

//----------------------------------------------------------------
//----------------------------------------------------------------

// ���W

mov			oPos,		v0							// �ϊ������ɍ��W�o��

// �e�N�X�`��

// ���� ( -X, -Y )
add			oT0.xy,	v8.xy,	c0.zw

// ���� ( -X, +Y )
add			oT1.xy,	v8.xy,	c0.zy

// �E�� ( +X, -Y )
add			oT2.xy,	v8.xy,	c0.xw

// �E�� ( +X, +Y )
add			oT3.xy,	v8.xy,	c0.xy

