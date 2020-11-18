
#ifndef	__s98ddStroke_h__
#define	__s98ddStroke_h__

#include	"ddStroke.h"

//---------------------------------------------------------------
//---------------------------------------------------------------

class	S98DDStroke : public DDStroke
{
	public:
						 S98DDStroke( DDvoid );
		virtual	~S98DDStroke( DDvoid );
	
	protected:
		virtual	DDvoid	dsCreateObject( DDvoid );
		virtual	DDvoid	dsDeleteObject( DDvoid );
};


#endif
