
#ifndef	__doRorDomain_h__
#define	__doRorDomain_h__

#include	"ddComputer.h"

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// �h���C�����
enum	DORDtype
{
	DORD_TYPE_SPHERE,					// ��
	DORD_TYPE_TRIANGLES,			// �����O�p
	DORD_TYPE_TOTAL
};


// SENS�@�}�e���A��
enum	DORDsensMaterial
{
	DORD_SENS_MATERIAL_00,					// �f�t�H���g
	DORD_SENS_MATERIAL_01_SAND,			// ��
	
	DORD_SENS_MATERIAL_TOTAL
};


// SENS�@�r�w�C�r�A
enum	DORDsensBehavior
{
	DORD_SENS_BEHAVIOR_00_NONE,			// ��������
	DORD_SENS_BEHAVIOR_01_SLIDE,		// ���ׂ鏰
	
	DORD_SENS_BEHAVIOR_TOTAL
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

struct	DORDsens
{
	u8			Material;			// DORDsensMaterial
	u8			Behavior;			// DORDsensBehavior
};


struct	DORDvertex
{
	f32			X;
	f32			Y;
	f32			Z;
};


struct	DORDtriangle
{
	f32			W;						// �@�� W
	s16			N[ 3 ];				// �@���x�N�g�� ( S1D14 )
	u16			V[ 3 ];				// ���_�C���f�b�N�X �@�����ʂɎ��v���
};


struct	DORDtriangles
{
	u16							TNumber;				// �O�p�|���S����
	u16							VNumber;				// ���_���X�g���̒��_��
	DORDtriangle*		TriangleList;		// �g���C�A���O�����X�g�擪�A�h���X
	DORDvertex*			VertexList;			// �Q�Ƃ��钸�_���X�g�擪�A�h���X
	DORDsens				Sens;						// �}�e���A�����
};


struct	DORDsphere
{
	DORDvertex	C;						// ���S���W
	f32					R;						// ���a
};


struct	DORDresult
{
	DCvec				Normal;				// �n�`�̖@��
	f32					Length;				// �c��̒����A�܂��͔��a
	DORDsens		Sens;					// �}�e���A�����
	DDenum			RorID;				// �n�`RorID�i���o�[
};


struct	DORDdomain
{
	DORDsphere*			S;
	DORDtriangles*	T;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// �h���C���@���N���X

class	DORorDomain
{
	public:
						 DORorDomain( DDvoid );
		virtual	~DORorDomain( DDvoid );
	
	public:
		virtual	DDbool		dordEvaArrow ( DCvec& P, DCvec& A, DORDresult& Result ) = 0;
		virtual	DDbool		dordEvaSphere( DCvec& P,           DORDresult& Result ) = 0;
	
	public:
		DORorDomain*			dordGetChild( DDvoid ){ return dordmChild; }
		DORorDomain*			dordGetNext ( DDvoid ){ return dordmNext;  }
	
	protected:
		DORorDomain*			dordmChild;
		DORorDomain*			dordmNext;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// �h���C���@��

class	DORDSphere : public DORorDomain
{
	public:
						 DORDSphere( DORDsphere& Sphere,        DORorDomain* Child, DORorDomain* Next );
						 DORDSphere( DCvec& Center, f32 Radius, DORorDomain* Child, DORorDomain* Next );
		virtual	~DORDSphere( DDvoid );
	
	public:
		virtual	DDbool		dordEvaArrow ( DCvec& P, DCvec& A, DORDresult& Result );
		virtual	DDbool		dordEvaSphere( DCvec& P,           DORDresult& Result );
	
	protected:
						DDbool		dordEvaA     ( DCvec& P, DCvec& A, DORDresult& Result );
						DDbool		dordEvaS     ( DCvec& P,           DORDresult& Result );
	
	private:
		DORDsphere				dordsmSphere;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// �h���C���@�O�p

class	DORDTriangles : public DORorDomain
{
	public:
						 DORDTriangles( DORDtriangles& Triangles, DORorDomain* Next );
		virtual	~DORDTriangles( DDvoid ){}
	
	public:
		virtual	DDbool		dordEvaArrow ( DCvec& P, DCvec& A, DORDresult& Result );
		virtual	DDbool		dordEvaSphere( DCvec& P,           DORDresult& Result );
	
	protected:
		DDbool						dordEvaA   ( DCvec& P, DCvec& A, DORDresult& Result );
		DDbool						dordEvaS   ( DCvec& P,           DORDresult& Result );
		DDbool						dordEvaAOne( DCvec& CP,                    DCvec& V0, DCvec& V1, DCvec& N );
		DDbool						dordEvaSOne( DCvec& P, DORDresult& Result, DCvec& V0, DCvec& V1, DCvec& N );
	
	private:
		DORDtriangles*		dordtmTriangles;
};


#endif
