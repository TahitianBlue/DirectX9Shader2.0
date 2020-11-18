
#ifndef	__s99ddStroke_h__
#define	__s99ddStroke_h__

#include	"ddStroke.h"

//---------------------------------------------------------------
//---------------------------------------------------------------

class	S99DDStroke : public DDStroke
{
	public:
						 S99DDStroke( DDvoid );
		virtual	~S99DDStroke( DDvoid );
	
	protected:
		virtual	DDvoid	dsCreateObject( DDvoid );
		virtual	DDvoid	dsDeleteObject( DDvoid );
};


#endif
