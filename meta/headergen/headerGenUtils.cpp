//=---------------------------------------------------------------------=
//
// $Id$ $Name$
//
// The contents of this file are subject to the AAF SDK Public Source
// License Agreement Version 2.0 (the "License"); You may not use this
// file except in compliance with the License.  The License is available
// in AAFSDKPSL.TXT, or you may obtain a copy of the License from the
// Advanced Media Workflow Association, Inc., or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.  Refer to Section 3.3 of the License for proper use
// of this Exhibit.
//
// WARNING:  Please contact the Advanced Media Workflow Association,
// Inc., for more information about any additional licenses to
// intellectual property covering the AAF Standard that may be required
// to create and distribute AAF compliant products.
// (http://www.amwa.tv/policies).
//
// Copyright Notices:
// The Original Code of this file is Copyright 1998-2009, licensor of the
// Advanced Media Workflow Association.  All rights reserved.
//
// The Initial Developer of the Original Code of this file and the
// licensor of the Advanced Media Workflow Association is
// Avid Technology.
// All rights reserved.
//
//=---------------------------------------------------------------------=

// Author : Tim Bingham (Tim_Bingham@avid.com) - after an initial
// implementation by Bob Tillman.

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "headerGenUtils.h"

void printBeginGuard(const char* moduleName, ostream& s)
{
  assert (moduleName);
  s << "#ifndef __" << moduleName << "_h__" << endl;
  s << "#define __" << moduleName << "_h__" << endl;
  s << endl;
}

void printEndGuard(const char* moduleName, ostream& s)
{
  assert(moduleName);
  s << endl;
  s << "#endif // ! __" << moduleName << "_h__" << endl;
}

void printCopyright (ostream & s) { printCopyright("Avid Technology", s); }

void printCopyright (const char* originator, ostream & s)
{
  s <<
"//=---------------------------------------------------------------------=\n"
"//\n"
"// This file was GENERATED for the AAF SDK\n"
"//\n"
"// $""Id$ $""Name$\n"
"//\n"
"// The contents of this file are subject to the AAF SDK Public Source\n"
"// License Agreement Version 2.0 (the \"License\"); You may not use this\n"
"// file except in compliance with the License.  The License is available\n"
"// in AAFSDKPSL.TXT, or you may obtain a copy of the License from the\n"
"// Advanced Media Workflow Association, Inc., or its successor.\n"
"//\n"
"// Software distributed under the License is distributed on an \"AS IS\"\n"
"// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See\n"
"// the License for the specific language governing rights and limitations\n"
"// under the License.  Refer to Section 3.3 of the License for proper use\n"
"// of this Exhibit.\n"
"//\n"
"// WARNING:  Please contact the Advanced Media Workflow Association,\n"
"// Inc., for more information about any additional licenses to\n"
"// intellectual property covering the AAF Standard that may be required\n"
"// to create and distribute AAF compliant products.\n"
"// (http://www.amwa.tv/policies).\n"
"//\n"
"// Copyright Notices:\n"
"// The Original Code of this file is Copyright 1998-2009, licensor of the\n"
"// Advanced Media Workflow Association.  All rights reserved.\n"
"//\n"
"// The Initial Developer of the Original Code of this file and the\n"
"// licensor of the Advanced Media Workflow Association is\n" 
"// " << originator << ".\n"
"// All rights reserved.\n"
"//\n"
"//=---------------------------------------------------------------------=\n";
  s << endl;
}


static void usage (const char * progname)
{
  assert (progname);

  cerr << "usage: " << progname << "moduleName [prefix]" << endl;
}


void validateArgs (int argc, char** argv, char*& moduleName)
{
  const char * progname = argv[0];

  if (argc < 2) {
    usage (progname);
    exit (1);
  }

  moduleName = argv[1];
}

void validateArgs(int argc, char** argv, char*& moduleName, char*& prefix)
{
  const char * progname = argv[0];

  if (argc < 2) {
    usage (progname);
    exit (1);
  }

  moduleName = argv[1];

  if( argc < 3 ) prefix = const_cast<char*>("");
  else prefix = argv[2];
}


// print a GUID like this -
//{0x0D010101, 0x0101, 0x0100,
//{0x06, 0x0E, 0x2B, 0x34, 0x02, 0x06, 0x01, 0x01}}
void print(const uid& id, ostream& s)
{
  s.setf(ios::uppercase);
  s.flags(ios::right);
  s << hex << setfill('0')
    << "{"
    << "0x" << setw(8) << id.Data1 << ", "
    << "0x" << setw(4) << id.Data2 << ", "
    << "0x" << setw(4) << id.Data3 << ", "
    << "{"
    << "0x" << setw(2) << (int)id.Data4[0] << ", "
    << "0x" << setw(2) << (int)id.Data4[1] << ", "
    << "0x" << setw(2) << (int)id.Data4[2] << ", "
    << "0x" << setw(2) << (int)id.Data4[3] << ", "
    << "0x" << setw(2) << (int)id.Data4[4] << ", "
    << "0x" << setw(2) << (int)id.Data4[5] << ", "
    << "0x" << setw(2) << (int)id.Data4[6] << ", "
    << "0x" << setw(2) << (int)id.Data4[7]
    << "}"
    << "}";
}

// print a GUID like this -
//{0101010D-0101-0100-060E-2B3402060101}
void printReg(const uid& id, ostream& s)
{
  s.setf(ios::uppercase);
  s.flags(ios::right);
  s << hex << setfill('0')
    << "{"
    << setw(8) << id.Data1 << "-"
    << setw(4) << id.Data2 << "-"
    << setw(4) << id.Data3 << "-"
    << setw(2) << (int)id.Data4[0] << setw(2) << (int)id.Data4[1] << "-"
    << setw(2) << (int)id.Data4[2]
    << setw(2) << (int)id.Data4[3]
    << setw(2) << (int)id.Data4[4]
    << setw(2) << (int)id.Data4[5]
    << setw(2) << (int)id.Data4[6]
    << setw(2) << (int)id.Data4[7]
    << "}";
}

// Convert a GUID to a label
//{0101010D-0101-0100-060E-2B3402060101} =>
//06.0E.2B.34.02.53.01.01.0D.01.01.01.01.01.01.00
// Note 06 -> 53 in octet 6
void convert(label& lid, const uid& auid)
{
  // Bottom half of label <- top half of auid
  //
  lid.octet0  = auid.Data4[0];
  lid.octet1  = auid.Data4[1];
  lid.octet2  = auid.Data4[2];
  lid.octet3  = auid.Data4[3];
  lid.octet4  = auid.Data4[4];
  lid.octet5  = auid.Data4[5];
  lid.octet6  = auid.Data4[6];
  lid.octet7  = auid.Data4[7];

  // Top half of label <- bottom half of auid
  //
  lid.octet8  = (aafUInt8)((auid.Data1 & 0xff000000) >> 24);
  lid.octet9  = (aafUInt8)((auid.Data1 & 0x00ff0000) >> 16);
  lid.octet10 = (aafUInt8)((auid.Data1 & 0x0000ff00) >>  8);
  lid.octet11 = (aafUInt8)((auid.Data1 & 0x000000ff));

  lid.octet12 = (aafUInt8)((auid.Data2 & 0xff00) >> 8);
  lid.octet13 = (aafUInt8)((auid.Data2 & 0x00ff));

  lid.octet14 = (aafUInt8)((auid.Data3 & 0xff00) >> 8);
  lid.octet15 = (aafUInt8)((auid.Data3 & 0x00ff));

  // If auid is an AAF class AUID, map it to a SMPTE 336M local set key
  //
  aafUInt8 classIdPrefix[] = {0x06, 0x0e, 0x2b, 0x34, 0x02, 0x06};
  if (memcmp(&lid, &classIdPrefix, sizeof(classIdPrefix)) == 0) {
    lid.octet5  = 0x53;
  }
}
 
// print a label like this -
// 06.0E.2B.34.02.53.01.01.0D.01.01.01.01.01.01.00
void printLabel(const label& id, ostream& s)
{
  s.setf(ios::uppercase);
  s.flags(ios::right);
  s << hex << setfill('0')
    << setw(2) << (int)id.octet0  << "."
    << setw(2) << (int)id.octet1  << "."
    << setw(2) << (int)id.octet2  << "."
    << setw(2) << (int)id.octet3  << "."
    << setw(2) << (int)id.octet4  << "."
    << setw(2) << (int)id.octet5  << "."
    << setw(2) << (int)id.octet6  << "."
    << setw(2) << (int)id.octet7  << "."
    << setw(2) << (int)id.octet8  << "."
    << setw(2) << (int)id.octet9  << "."
    << setw(2) << (int)id.octet10 << "."
    << setw(2) << (int)id.octet11 << "."
    << setw(2) << (int)id.octet12 << "."
    << setw(2) << (int)id.octet13 << "."
    << setw(2) << (int)id.octet14 << "."
    << setw(2) << (int)id.octet15;
}

void printDefinition(const char* type,
                     const char* prefix,
                     const char* name,
                     size_t width,
                     const uid& identifier,
                     ostream& s)
{
  s << "//";
  printReg(identifier, s);
  s << endl;
  s << "//";
  label lab;
  convert(lab, identifier);
  printLabel(lab, s);
  s << endl;
  s << type;
  s << " ";
  s << prefix;
  printName(name, width, s);
  s << " =" << endl;
  print(identifier, cout);
  s << ";" << endl << endl;
}

void printDefinition(const char* type,
                     const char* prefix,
                     const char* name,
                     size_t width,
                     int identifier,
                     const char* comment,
                     ostream& s)
{
  s << type;
  s << " ";
  s << prefix;
  printName(name, width, s);
  s << " = ";
  s.flags(ios::right);
  s.fill('0');
  s << "0x" << hex;
  s.setf(ios::uppercase);
  s << setw(4) << identifier << ";" << comment << endl;
}

void printDefinition(const char* type,
                     const char* prefix,
                     const char* name,
                     const char* suffix,
                     const char* string,
                     ostream& s)
{
  s << type;
  s << " ";
  s << prefix;
  s << name;
  s << suffix;
  s << " = L\"";
  s << string << "\";" << endl;
}

void printAlias(	 const char* type,
					 const char* alias,
                     const char* prefix,
                     const char* name,
                     const char* suffix,
                     ostream& s)
{
  s << type;
  s << " ";
  s << alias;
  s << " = ";
  s << prefix;
  s << name;
  s << suffix;
  s << ";" << endl;
}


// print a macro invocation like this -
// DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8);
void printMacroInvocation(const char* prefix,
                          const char* macro,
                          const char* name,
                          const uid& identifier,
                          ostream& s)
{
  s << "//";
  printReg(identifier, s);
  s << endl;
  s << "//";
  label lab;
  convert(lab, identifier);
  printLabel(lab, s);
  s << endl;

  s << macro << "(" << prefix << name << "," << endl;

  s.setf(ios::uppercase);
  s.flags(ios::right);
  s << hex << setfill('0')
    << "0x" << setw(8) << identifier.Data1 << ", "
    << "0x" << setw(4) << identifier.Data2 << ", "
    << "0x" << setw(4) << identifier.Data3 << ", "
    << "0x" << setw(2) << (int)identifier.Data4[0] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[1] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[2] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[3] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[4] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[5] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[6] << ", "
    << "0x" << setw(2) << (int)identifier.Data4[7];

  s << ");" << endl;
}

void printName(const char* name,
               size_t width,
               ostream& s)
{
  s << name;
  size_t actualWidth = strlen(name);
  for (size_t i = actualWidth; i < width; i++) {
    s << " ";
  }
}
