
#ifndef	__dsAction_h__
#define	__dsAction_h__

#include	"ddJacket.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

enum	DA_ACTOR
{
	DA_ACTOR_SYSTEM0,
	
	DA_ACTOR_PLAYER,
	DA_ACTOR_ENEMY,
	DA_ACTOR_EFFECT,
	
	DA_ACTOR_SYSTEM1,
	
	DA_ACTOR_TOTAL
};

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	DSAction
{
	public:
						 DSAction( DA_ACTOR actor );
		virtual	~DSAction( DDvoid );
	
	// copy protect
	protected:
		DSAction( DSAction& ){ ddASSERT( true ); }
	
	// over load
	public:
		virtual	DDbool	daAction( DDvoid ) = 0;
	
	//-----------------------------------------------
	
		private:
			DSAction*		daGetNext( DDvoid ){ return damNext; }
			DSAction*		daGetPrev( DDvoid ){ return damPrev; }
		
		private:
			DA_ACTOR		damActor;
			DSAction*		damNext;
			DSAction*		damPrev;
	
	//-----------------------------------------------
	
	public:
		static	DDvoid	daActionInitial( DDvoid );
		static	DDvoid	daActionDispose( DDvoid );
		static	DDvoid	daActionProcess( DA_ACTOR actor );
	
	//-----------------------------------------------
	
		private:
			static	DSAction*		daGetBase( DA_ACTOR actor ){ return damBase[ actor ]; }
			static	DSAction*		daGetLast( DA_ACTOR actor ){ return damBase[ actor ]; }
		
		private:
			static	DSAction*		damBase[ DA_ACTOR_TOTAL ];
			static	DSAction*		damLast[ DA_ACTOR_TOTAL ];
			static	DSAction*		damSave;
};

#endif
