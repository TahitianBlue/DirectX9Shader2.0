
// Deal dominator Option Collision

#ifndef	__doCollision_h__
#define	__doCollision_h__

#include	"ddJacket.h"
#include	"ddComputer.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

enum	DOCproperty
{
	DOC_TABLE_SIZE = 256
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------

class	DOCollision;

struct	DOCTable
{
	DOCollision*	Con;
	f32						Key;
};

class	DOCollision
{
	// constructor / destructor
	public:
						 DOCollision( DDvoid );
		virtual	~DOCollision( DDvoid );
	
	public:
		virtual	DDvoid	docIntro( DDvoid ) = 0;
		virtual	DDvoid	docOutro( DDvoid ) = 0;
	
	// this pointer
	public:
		DOCollision*	docThis( DDvoid ){ return this; }
	
	// enabler / disabler
	public:
		DDvoid		docEnable ( DDvoid );
		DDvoid		docDisable( DDvoid );
	
	// accessor
	public:
		DDenum		docGetOwner( DDvoid       ){ return  docmOwner; }
		DDvoid		docSetOwner( DDenum Owner ){ docmOwner = Owner; }
	
	public:
		DCvec&		docP     ( DDvoid ){ return docmP; }
		DCvec&		docV     ( DDvoid ){ return docmV; }
		f32&			docMass  ( DDvoid ){ return docmMass;   }
		f32&			docRadius( DDvoid ){ return docmRadius; }
	
	public:
		DDbool		docCollided( DDvoid ){ return docmCollided; }
	
	//---------------------------------------------
	public:
		static	DDvoid	docCollisionInitial( DDvoid );
		static	DDvoid	docCollisionDispose( DDvoid );
		
		static	DDvoid	docCollisionProcess( DDvoid );
		static	DDvoid	docCollisionIntro  ( DDvoid );
		static	DDvoid	docCollisionOutro  ( DDvoid );
	
	public:
		static	DDvoid	docSetAxis( DCvec& axis ){ docmAXIS = axis; }
	
	//---------------------------------------------
	private:
		// enables sort table
		DDvoid	docEntry( DDvoid );
		DDvoid	docErase( DDvoid );
		
		// disables link list
		DDvoid 	docAppend( DDvoid );
		DDvoid 	docRemove( DDvoid );
	
	//---------------------------------------------
	protected:
		DCvec		docmP;
		DCvec		docmV;
		f32			docmMass;
		f32			docmRadius;
	
	//---------------------------------------------
	private:
		DDbool	docmCollided;
	
	private:
		DDenum	docmOwner;
	
	private:
		// sort table
		s32						docmIndex;		// DISABLE = -1 : ENABLE = 0Å`
		// link list
		DOCollision*	docmNext;
		DOCollision*	docmPrev;
	
	private:
		static	DCvec					docmAXIS;
		static	s32						docmINDEX;										// óLå¯êî
		static	DOCTable			docmTABLE[ DOC_TABLE_SIZE ];	// Enable sort table
		static	DOCollision*	docmDisBASE;									// Disable link list
};

#endif
