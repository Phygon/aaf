// @doc INTERNAL
// @com This file implements the OMF exception handling utility. 
/***********************************************************************
 *
 *              Copyright (c) 1998-1999 Avid Technology, Inc.
 *
 * Permission to use, copy and modify this software and accompanying 
 * documentation, and to distribute and sublicense application software
 * incorporating this software for any purpose is hereby granted, 
 * provided that (i) the above copyright notice and this permission
 * notice appear in all copies of the software and related documentation,
 * and (ii) the name Avid Technology, Inc. may not be used in any
 * advertising or publicity relating to the software without the specific,
 *  prior written permission of Avid Technology, Inc.
 *
 * THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL AVID TECHNOLOGY, INC. BE LIABLE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, PUNITIVE, INDIRECT, ECONOMIC, CONSEQUENTIAL OR
 * OTHER DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE AND
 * ACCOMPANYING DOCUMENTATION, INCLUDING, WITHOUT LIMITATION, DAMAGES
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, AND WHETHER OR NOT
 * ADVISED OF THE POSSIBILITY OF DAMAGE, REGARDLESS OF THE THEORY OF
 * LIABILITY.
 *
 ************************************************************************/

#ifndef OMFEXCEPT_H_DEFINED
#define OMFEXCEPT_H_DEFINED (1)

#include "ExceptionBase.h"
namespace OMF2
{
	#include "omErr.h"
}
using	OMF2::omfErr_t;
using	OMF2::OM_ERR_NONE;

/*******************************************************************
Name: 
	 class OMFException
Description:
	OMF exception handling class.

********************************************************************/

class OMFException : public ExceptionBase
{
public:
	OMFException( omfErr_t errCode );
	virtual ~OMFException( void );
	virtual	const char *Type( void );

	// Does a status check on the the error code and throws an
	// exception on failure. 
	static void Check( omfErr_t errCode, const char *fmt = 0, ... ); 
};

inline OMFException::OMFException( omfErr_t errCode ) : ExceptionBase( errCode ) 
{
}	

inline OMFException::~OMFException( void ) 
{
} 

/********************************************************************
Name: 
	OMFException::Type
Description:
Returns:
	A string which IDs this exception type as "OMF."
********************************************************************/

inline const char *OMFException::Type( void )
{ 
	return "OMF"; 
}

/*******************************************************************
Name: 
	 class OMFCheck
Description:
	OMF return status checker. 
	Used to check the return values of OMF calls.
********************************************************************/

class OMFCheck
{
private:
	// These things are not meant to get copied around. They are meant
	// to check the status of function calls. They are private because
	// they are not meant to be used.
	OMFCheck & operator= (OMFCheck &status ); // N/A
	OMFCheck(OMFCheck &status);// N/A
public:
	OMFCheck & operator= ( omfErr_t status );
	OMFCheck( omfErr_t status = OM_ERR_NONE );
};


inline OMFCheck & OMFCheck::operator= ( OMFCheck &status )
{ 
	return *this; 
}

inline OMFCheck::OMFCheck( OMFCheck &status )
{
}

inline OMFCheck & OMFCheck::operator= ( omfErr_t status )
{ 
	OMFException::Check( status ); 
	return *this;
}
	
inline OMFCheck::OMFCheck( omfErr_t status )
{ 
	OMFException::Check( status ); 
}

#endif // EXCEPTION_H_DEFINED 

