
#ifndef	__dvCoaster_h__
#define	__dvCoaster_h__

#include	"ddJacket.h"
#include	"ddComputer.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

// coaster card		ÉQÅ[ÉÄì‡àÍà”(è¨ãKñÕ) or äeñ (ëÂãKñÕ)
enum	DVCcard
{
	// object model
	DVC_CARD_OBJECT_TOP,
	DVC_CARD_OBJECT_MODEL_BOX,
	DVC_CARD_OBJECT_MODEL_SPHERE,
	DVC_CARD_OBJECT_END,
	
	// terrain model
	DVC_CARD_TERRAIN_TOP = DVC_CARD_OBJECT_END,
	DVC_CARD_TERRAIN_MODEL_INNER_BOX,
	DVC_CARD_TERRAIN_MODEL_TERRA_BOX,
	DVC_CARD_TERRAIN_END,
	
	// effect model
	DVC_CARD_EFFECT_MODEL_TOP = DVC_CARD_TERRAIN_END,
	DVC_CARD_EFFECT_MODEL_00,
	DVC_CARD_EFFECT_MODEL_END,
	
	// effect primitive
	DVC_CARD_EFFECT_TEX_TOP = DVC_CARD_EFFECT_MODEL_END,
	DVC_CARD_EFFECT_TEX_00,
	DVC_CARD_EFFECT_TEX_END,
	
	// informations
	DVC_CARD_INFO_TOP = DVC_CARD_EFFECT_TEX_END,
	DVC_CARD_INFO_00,
	DVC_CARD_INFO_END,
	
	DVC_CARD_TOTAL
};

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	DVPlot;		// forward declare

class	DVCoaster
{
	public:
						 DVCoaster( DDvoid );
		virtual	~DVCoaster( DDvoid );
	
	// copy protect
	protected:
		DVCoaster( DVCoaster& ){ ddASSERT( true ); }
	
	// over load
	protected:
		virtual	DDvoid	dvcIntro( DDvoid ) = 0;
		virtual	DDvoid	dvcOutro( DDvoid ) = 0;
	
	// access
	public:
		DVPlot*		dvcGetPlotBase( DDvoid )      { return dvcmPlotBase; }
		DDvoid		dvcSetPlotBase( DVPlot* plot ){ dvcmPlotBase = plot; }
	
	//--------------------------------------------
	private:
		DDvoid		dvcProcess( DDvoid );
		DDvoid			dvcPlot( DDvoid );
	
	private:
		DVPlot*		dvcmPlotBase;
	
	//--------------------------------------------
		public:
			static	DDvoid			dvcCoasterInitial( DDvoid );
			static	DDvoid			dvcCoasterDispose( DDvoid );
			static	DDvoid			dvcCoasterProcess( DDvoid );
			static	DDvoid			dvcCoasterProcess( DVCcard top, DVCcard end );
			
			static	DVCoaster*	dvcList( DVCcard card ){ return dvcmList[ card ]; }
		
		protected:
			static	DVCoaster*	dvcmList[ DVC_CARD_TOTAL ];
};


#endif
