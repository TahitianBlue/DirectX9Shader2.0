
#ifndef	__doRestriction_h__
#define	__doRestriction_h__

#include	"ddJacket.h"
#include	"dsOption.h"
#include	"doRorDomain.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

enum	DORtype
{
	DOR_TYPE_EARTH,					// 地形
	DOR_TYPE_LIMPID,				// 見えない壁
	DOR_TYPE_FALL,					// 転落判定
	DOR_TYPE_WATER,					// 水面判定
	DOR_TYPE_DISABLE,				// 無効
	DOR_TYPE_TOTAL
};

enum	DORbit
{
	DOR_BIT_EARTH    = BIT( DOR_TYPE_EARTH ),
	DOR_BIT_LIMPID   = BIT( DOR_TYPE_LIMPID ),
	DOR_BIT_FALL     = BIT( DOR_TYPE_FALL ),
	DOR_BIT_WATER    = BIT( DOR_TYPE_WATER ),
//DOR_BIT_DISABLE  = BIT( DOR_TYPE_DISABLE ),							bit 不要
	DOR_BIT_ALL      = ( DOR_BIT_EARTH | DOR_BIT_LIMPID )
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------

// forward declare
class	DORestrictor;
class	DORestricted;


class	DORestriction
{
	// constructor / destructor
	private:
						 DORestriction( DDvoid ){}
		virtual	~DORestriction( DDvoid ){}
	
	public:
		static	DDvoid		dorRestrictionInitial( DDvoid );
		static	DDvoid		dorRestrictionDispose( DDvoid );
		static	DDvoid		dorRestrictionIntro  ( DDvoid );
		static	DDvoid		dorRestrictionProcess( DDvoid );
		static	DDvoid		dorRestrictionOutro  ( DDvoid );
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------

class	DORestricted
{
	friend class	DORestriction;
	
	// constructor / destructor
	public:
						 DORestricted( DDvoid );
		virtual	~DORestricted( DDvoid );
	
	// this pointer
	public:
		DORestricted*	doredThis( DDvoid ){ return this; }
	
	// enabler / disabler
	public:
		DDvoid		doredEnable ( DDvoid );
		DDvoid		doredDisable( DDvoid );
	
	// OVER LOAD THIS
	public:
		virtual	DDvoid	doredIntro  ( DDvoid ) = 0;
		virtual	DDvoid	doredProcess( DDvoid ) = 0;
		virtual	DDvoid	doredOutro  ( DDvoid ) = 0;
	
	// accessor
	public:
		DDenum	doredGetOwner( DDvoid       ){ return  doredmOwner; }
		DDvoid	doredSetOwner( DDenum owner ){ doredmOwner = owner; }
		
		DDbits	doredGetRBit( DDvoid      ){ return  doredmRBit; }
		DDvoid	doredSetRBit( DDbits rBit ){ doredmRBit = rBit;  }
	
	// evaluate
	protected:
		DDbool	doredEvaluateArrow ( DCvec& P, DCvec& A, f32 Length, DORDresult& Result );
		DDbool	doredEvaluateArrow ( DCvec& P, DCvec& A, f32 Length, DORDresult& Result, DCvec& DP, DCvec& DR );
		DDbool	doredEvaluateSphere( DCvec& P,           f32 Radius, DORDresult& Result );
		DDbool	doredEvaluateSphere( DCvec& P,           f32 Radius, DORDresult& Result, DCvec& DP, DCvec& DR );
	
		//------------------------------
		
		private:
			static	DDvoid	doredRestrictedInitial( DDvoid );
			static	DDvoid	doredRestrictedDispose( DDvoid );
			static	DDvoid	doredRestrictedIntro  ( DDvoid );
			static	DDvoid	doredRestrictedOutro  ( DDvoid );
		
		private:
			static	DORestricted*	doredGetBase( DOentry restriction ){ return doredmBASE[ restriction ]; }
							DORestricted*	doredGetNext( DDvoid ){ return doredmNext; }
							DORestricted*	doredGetPrev( DDvoid ){ return doredmPrev; }
			
			//------------------------------
			
			private:
				DDvoid 	doredAppend( DOentry Base )
				{
					ddASSERT( doredmBase != Base );
					
					doredmNext = doredmBASE[ Base ];
					doredmPrev = NULL;
					doredmBASE[ Base ] = this;
					
					if( doredmNext ){ doredmNext -> doredmPrev = this; }
				}
				
				DDvoid	doredRemove( DDvoid )
				{
					if( doredmSAVE == this ){ doredmSAVE = doredmNext; }
					
					if( doredmNext ){ doredmNext -> doredmPrev = doredmPrev; }
					if( doredmPrev ){ doredmPrev -> doredmNext = doredmNext; } else { doredmBASE[ doredmBase ] = doredmNext; }
				}
				
				//------------------------------
				private:
					DDbits				doredmRBit;
					DDenum				doredmOwner;
				
				private:
					DOentry				doredmBase;
					DORestricted*	doredmNext;
					DORestricted*	doredmPrev;
				
				private:
					static	DORestricted*		doredmSAVE;
					static	DORestricted*		doredmBASE[ DO_ENTRY_TOTAL ];
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------

class	DORestrictor
{
	friend	class		DORestriction;
	
	friend	DDbool	DORestricted::doredEvaluateArrow ( DCvec& P, DCvec& A, f32 Length, DORDresult& Result );
	friend	DDbool	DORestricted::doredEvaluateArrow ( DCvec& P, DCvec& A, f32 Length, DORDresult& Result, DCvec& DP, DCvec& DR );
	friend	DDbool	DORestricted::doredEvaluateSphere( DCvec& P,           f32 Radius, DORDresult& Result );
	friend	DDbool	DORestricted::doredEvaluateSphere( DCvec& P,           f32 Radius, DORDresult& Result, DCvec& DP, DCvec& DR );
	
	// constructor / destructor
	public:
						 DORestrictor( DDvoid );
		virtual	~DORestrictor( DDvoid );
	
	public:
		virtual	DDvoid	dororIntro( DDvoid ) = 0;
		virtual	DDvoid	dororOutro( DDvoid ) = 0;
	
	// this pointer
	public:
		DORestrictor*	dororThis( DDvoid ){ return this; }
	
	// enabler / disabler
	public:
		DDvoid		dororEnable ( DORtype Rtype );
		DDvoid		dororDisable( DDvoid );
	
	// accessor
	public:
		DDenum		dororGetOwner( DDvoid       ){ return  dorormOwner; }
		DDvoid		dororSetOwner( DDenum owner ){ dorormOwner = owner; }
	
	protected:
		DORorDomain&	dororDomain( DDvoid ){ return *dorormDomain; }
	
	protected:
		DDenum		dororGetID( DDvoid ){ return dorormID; }
	
		//------------------------------
		
		// evaluate
		protected:
			static	DDbool	dororEvaluateArrow ( DDbits Bit, DDenum Owner, DCvec& P, DCvec& A, f32 Length, DORDresult& Result );
			static	DDbool	dororEvaluateArrow ( DDbits Bit, DDenum Owner, DCvec& P, DCvec& A, f32 Length, DORDresult& Result, DCvec& DP, DCvec& DR );
			static	DDbool	dororEvaluateSphere( DDbits Bit, DDenum Owner, DCvec& P,           f32 Radius, DORDresult& Result );
			static	DDbool	dororEvaluateSphere( DDbits Bit, DDenum Owner, DCvec& P,           f32 Radius, DORDresult& Result, DCvec& DP, DCvec& DR );
		
		private:
			static	DORestrictor*	dororEvaluateA( DDbits Bit, DDenum Owner, DCvec& P, DCvec& A, f32 Length, DORDresult& Result );
			static	DORestrictor*	dororEvaluateS( DDbits Bit, DDenum Owner, DCvec& P,           f32 Radius, DORDresult& Result );
		
		private:
			virtual	DDbool	dororEvaA( DCvec P, DCvec A, DORDresult& Result ) = 0;
			virtual	DDbool	dororEvaS( DCvec P,          DORDresult& Result ) = 0;
			
			virtual	DDbool	dororCalculateVelocity( DCvec& HitP, DCvec& DP, DCvec& DR ) = 0;
		
		//------------------------------

		private:
			static	DDvoid	dororRestrictorInitial( DDvoid );
			static	DDvoid	dororRestrictorDispose( DDvoid );
			static	DDvoid	dororRestrictorIntro  ( DDvoid );
			static	DDvoid	dororRestrictorOutro  ( DDvoid );
		
		private:
			static	DORestrictor*	dororGetBase( DORtype Rtype ){ return dorormBASE[ Rtype ]; }
			
							DORestrictor*	dororGetNext( DDvoid ){ return dorormNext; }
							DORestrictor*	dororGetPrev( DDvoid ){ return dorormPrev; }
		
			//------------------------------
			
			private:
				DDvoid 	dororAppend( DORtype Type )
				{
					ddASSERT( dorormType != Type );
					
					dorormNext = dorormBASE[ dorormType ];
					dorormPrev = NULL;
					dorormBASE[ dorormType ] = this;
					
					if( dorormNext ){ dorormNext -> dorormPrev = this; }
				}
				
				DDvoid 	dororRemove( DDvoid )
				{
					if( dorormSAVE == this ){ dorormSAVE = dorormNext; }
					
					if( dorormNext ){ dorormNext -> dorormPrev = dorormPrev; }
					if( dorormPrev ){ dorormPrev -> dorormNext = dorormNext; } else { dorormBASE[ dorormType ] = dorormNext; }
				}
				
				
				//------------------------------
				protected:
					DORorDomain*			dorormDomain;
				
				private:
					DDenum						dorormOwner;
					DDenum						dorormID;
				
				private:
					DORtype						dorormType;
					DORestrictor*			dorormNext;
					DORestrictor*			dorormPrev;
				
				private:
					static	DORestrictor*		dorormSAVE;
					static	DORestrictor*		dorormBASE[ DOR_TYPE_TOTAL ];
					static	DDenum					dorormBaseID;
};

#endif
