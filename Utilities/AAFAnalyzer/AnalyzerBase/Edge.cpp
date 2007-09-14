//=---------------------------------------------------------------------=
//
// $Id$
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
//
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
//
// The Original Code of this file is Copyright 1998-2004, Licensor of the
// AAF Association.
//
//=---------------------------------------------------------------------=

//Analyzer Base files
#include "Edge.h"
#include "Node.h"
#include "Visitor.h"

namespace {

using namespace aafanalyzer;

} // end of namespace


//======================================================================
//======================================================================
//======================================================================

namespace aafanalyzer {

using namespace boost;

Edge::Edge(shared_ptr<Node> spParent, shared_ptr<Node> spChild )
  : _spParentNode( spParent ),
    _spChildNode( spChild ),
    _kind( EDGE_KIND_CONTAINMENT ),
    _tag( spParent->GetLID() )
{}

Edge::Edge(shared_ptr<Node> spParent, shared_ptr<Node> spChild,
	   EdgeKind_e kind, Node::LID tag)
  : _spParentNode( spParent ),
    _spChildNode( spChild ),
    _kind( kind ),
    _tag( tag )
{}

Edge::~Edge()
{}

bool Edge::Visit(shared_ptr<Visitor> spVisitor)
{
  return spVisitor->EdgeVisit(*this);
}

shared_ptr<Node> Edge::GetParentNode() const
{
  return _spParentNode;
}

shared_ptr<Node> Edge::GetChildNode() const
{
  return _spChildNode;
}

shared_ptr<Edge> Edge::CreateNewEdge( shared_ptr<Node> spParent, shared_ptr<Node> spChild ) const
{
  shared_ptr<Edge> spNewEdge( new Edge( spParent, spChild, _kind, _tag ) );
  return spNewEdge;
}

const std::wstring& Edge::GetTypeName() const
{
  static std::wstring name( L"edge" );
  return name;
}

Edge::EdgeKind_e Edge::GetKind() const
{
  return _kind;
}

Node::LID Edge::GetTag() const
{
  return _tag;
}

} // end of namespace diskstream


