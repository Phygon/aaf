//@doc
//@class    EnumAAFClassDefs | Implementation class for EnumAAFClassDefs
#ifndef __ImplEnumAAFClassDefs_h__
#define __ImplEnumAAFClassDefs_h__
/***********************************************\
*                                               *
* Advanced Authoring Format                     *
*                                               *
* Copyright (c) 1998-1999 Avid Technology, Inc. *
* Copyright (c) 1998-1999 Microsoft Corporation *
*                                               *
\***********************************************/

class ImplAAFClassDef;

#ifndef __ImplAAFObject_h__
#include "ImplAAFObject.h"
#endif


typedef OMVariableSizeProperty<aafUID_t> classDefWeakRefArrayProp_t;
typedef OMStrongReferenceVectorProperty<ImplAAFClassDef> classDefStrongRefArrayProp_t;


class ImplEnumAAFClassDefs : public ImplAAFRoot
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplEnumAAFClassDefs ();

protected:
  virtual ~ImplEnumAAFClassDefs ();

public:

  //****************
  // NextOne()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    NextOne
        // @parm [out,retval] The Next ClassDefinition
        (ImplAAFClassDef ** ppClassDef);

  //****************
  // Next()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Next
        (// @parm [in] number of class definitions requested
         aafUInt32  count,

         // @parm [out, size_is(count), length_is(*pFetched)] array to receive class definitions
         ImplAAFClassDef ** ppClassDefs,

         // @parm [out,ref] number of actual ClassDefinitions fetched into ppClassDefs array
         aafUInt32 *  pFetched);

  //****************
  // Skip()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Skip
        // @parm [in] Number of elements to skip
        (aafUInt32  count);

  //****************
  // Reset()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Reset ();


  //****************
  // Clone()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Clone
        // @parm [out,retval] new enumeration
        (ImplEnumAAFClassDefs ** ppEnum);


public:
  // SDK Internal 
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEnumProperty( ImplAAFObject *pObj, classDefWeakRefArrayProp_t *pProp);
  virtual AAFRESULT STDMETHODCALLTYPE
    SetEnumStrongProperty( ImplAAFObject *pObj, classDefStrongRefArrayProp_t *pProp);

private:
	aafUInt32                      _current;
	ImplAAFObject                * _enumObj;
	classDefWeakRefArrayProp_t   * _enumProp;
	classDefStrongRefArrayProp_t * _enumStrongProp;
};

#endif // ! __ImplEnumAAFClassDefs_h__
