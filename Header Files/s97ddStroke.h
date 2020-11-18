
#ifndef	__s97ddStroke_h__
#define	__s97ddStroke_h__

#include	"ddStroke.h"

//---------------------------------------------------------------
//---------------------------------------------------------------

class	S97DDStroke : public DDStroke
{
	public:
						 S97DDStroke( DDvoid );
		virtual	~S97DDStroke( DDvoid );
	
	protected:
		virtual	DDvoid	dsCreateObject( DDvoid );
		virtual	DDvoid	dsDeleteObject( DDvoid );
};


#endif
