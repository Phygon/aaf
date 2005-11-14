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

//Edit Protocol Test files
#include "EPContainedTrackVisitor.h"
#include "EPContainedTrackTest.h"

//Test/Result files
#include <DetailLevelTestResult.h>
#include <TestRegistry.h>

//Ax files
#include <AxMob.h>
#include <AxMetaDef.h>
#include <AxMobSlot.h>
#include <AxIterator.h>
#include <AxComponent.h>

//AAF files
#include <AAFResult.h>

//STL files
#include <sstream>

namespace {

} // end of namespace

//======================================================================

namespace aafanalyzer {

using namespace boost;
 
EPContainedTrackVisitor::EPContainedTrackVisitor( wostream& log, shared_ptr<EdgeMap> spEdgeMap )
    : _log(log),
      _spEdgeMap( spEdgeMap ),
      _spResult( new DetailLevelTestResult( L"Edit Protocol Contained Track Visitor",
                                            L"Visit derivation chain mateiral and ensure they contain the required tracks.",
                                            L"", // explain
                                            L"", // DOCREF REQUIRED
                                            TestResult::PASS,
                                            TestRegistry::GetInstance().GetRequirementsForTest( EPContainedTrackTest::GetTestInfo().GetName() )
               )                          )
{}
    
EPContainedTrackVisitor::~EPContainedTrackVisitor()
{}

bool EPContainedTrackVisitor::PreOrderVisit( EPTypedObjNode<IAAFCompositionMob, EPTopLevelComposition>& node )
{
  
    AxCompositionMob axCompMob( node.GetAAFObjectOfType() );
    
    //Get the name of the mob
    AxString nodeName = this->GetMobName( axCompMob, EPTopLevelComposition::GetName() );
    
    unsigned int unnumberedtracks;
    shared_ptr<TrackNumberMap> spTrackNumMap( CountTrackCodes( this->GetTimecodeTracks( _spEdgeMap, node ), unnumberedtracks ) );
    
    TrackNumberMap::const_iterator mapIter;
    bool testPassed = true;
    
    //Ensure all tracks have a physical track number
    if (unnumberedtracks != 0)
    {
        wstringstream ss;
        ss << nodeName << L" has " << unnumberedtracks << " Timecode tracks with no MobSlot::PhysicalTrackNumber property.";
        AxString explain( ss.str().c_str() );
        _spResult->AddInformationResult( L"REQ_EP_028", explain, TestResult::FAIL );
        testPassed = false;
    }    
    
    for ( mapIter = spTrackNumMap->begin(); mapIter != spTrackNumMap->end(); mapIter++ )
    {
    
        switch (mapIter->first)
        {
            case 1:
                //1. Ensure that there are <=1 primary timecode tracks
                if ( mapIter->second > 1 )
                {
                    _spResult->AddInformationResult( L"REQ_EP_028", nodeName + L" has more than one Primary Timecode track.", TestResult::FAIL );
                    testPassed = false;
                }
                break;
            case 2:
                //2. Ensure that there are <=1 alternative timecode tracks
                if ( mapIter->second > 1 )
                {
                    _spResult->AddInformationResult( L"REQ_EP_028", nodeName + L" has more than one Alternative Timecode track.", TestResult::FAIL );
                    testPassed = false;
                }
                break;
            case 3: case 4: case 5: case 6:
                //3. Ensure there are no reserved timecode tracks
                {
                    wstringstream ss;
                    ss << nodeName << L" has a Reserved Timecode track (MobSlot::PhysicalTrackNumber = " << mapIter->first << L").";
                    AxString explain( ss.str().c_str() );
                    _spResult->AddInformationResult( L"REQ_EP_028", explain, TestResult::FAIL );
                    testPassed = false;
                }
                break;
            default:
                //4. Ensure there are no other timecode tracks
                {
                    wstringstream ss;
                    ss << nodeName << L" has a illegal Timecode track (MobSlot::PhysicalTrackNumber = " << mapIter->first << L").";
                    AxString explain( ss.str().c_str() );
                    _spResult->AddInformationResult( L"REQ_EP_028", explain, TestResult::FAIL );
                    testPassed = false;
                }
                break;
        }
    
    }
    
    //5. Ensure there are >= 1 primary timecode tracks
    if ( spTrackNumMap->find( 1 ) == spTrackNumMap->end() )
    {
        _spResult->AddInformationResult( L"REQ_EP_028", nodeName + L" does not have a Primary Timecode track.", TestResult::FAIL );
        testPassed = false;
    }
    
    return testPassed;
    
}

bool EPContainedTrackVisitor::PreOrderVisit( EPTypedObjNode<IAAFCompositionMob, EPSubClipComposition>& node )
{
    bool testPassed = true;

    AxCompositionMob axCompMob( node.GetAAFObjectOfType() );
    shared_ptr<MobSlotSet> spEssenceTrack = this->GetEssenceTracks( _spEdgeMap, node );

    MobSlotSet::const_iterator iter;
    for ( iter = spEssenceTrack->begin(); iter != spEssenceTrack->end(); iter++ )
    {
        if ( CountSegments( **iter, kAAFClassID_SourceClip ) != 1 )
        {
            AxString mobName = this->GetMobName( axCompMob, EPSubClipComposition::GetName() );

            wstringstream ss;
            ss << L"Slot with ID ";
            ss << (*iter)->GetSlotID();
            ss << L" in " << mobName << L" does not have exactly one SourceClip.";

            AxString explain( ss.str().c_str() );
            _spResult->AddInformationResult( L"REQ_EP_037", explain, TestResult::FAIL );
            testPassed = false;
        }
    }
          
    return testPassed;
}

bool EPContainedTrackVisitor::PreOrderVisit( EPTypedObjNode<IAAFCompositionMob, EPAdjustedClipComposition>& node )
{
    bool testPassed = true;

    AxCompositionMob axCompMob( node.GetAAFObjectOfType() );
    shared_ptr<MobSlotSet> spEssenceTrack = this->GetEssenceTracks( _spEdgeMap, node );

    MobSlotSet::const_iterator iter;
    for ( iter = spEssenceTrack->begin(); iter != spEssenceTrack->end(); iter++ )
    {
        if ( CountSegments( **iter, kAAFClassID_OperationGroup ) != 1 )
        {
            AxString mobName = this->GetMobName( axCompMob, EPAdjustedClipComposition::GetName() );

            wstringstream ss;
            ss << L"Slot with ID ";
            ss << (*iter)->GetSlotID();
            ss << L" in " << mobName << L" does not have exactly one OperationGroup.";

            AxString explain( ss.str().c_str() );
            _spResult->AddInformationResult( L"REQ_EP_046", explain, TestResult::FAIL );
            testPassed = false;
        }
    }
        
    return testPassed;
}

bool EPContainedTrackVisitor::PreOrderVisit( EPTypedObjNode<IAAFSourceMob, EPTapeSource>& node )
{
  
    AxSourceMob axSrcMob( node.GetAAFObjectOfType() );
    
    //Get the name of the mob
    AxString nodeName = this->GetMobName( axSrcMob, EPTapeSource::GetName() );
    
    unsigned int unnumberedtracks;
    shared_ptr<TrackNumberMap> spTrackNumMap( CountTrackCodes( this->GetTimecodeTracks( _spEdgeMap, node ), unnumberedtracks ) );
    
    TrackNumberMap::const_iterator mapIter;
    bool testPassed = true;

    //Ensure all tracks have a physical track number
    if (unnumberedtracks != 0)
    {
        wstringstream ss;
        ss << nodeName << L" has " << unnumberedtracks << " Timecode tracks with no MobSlot::PhysicalTrackNumber property.";
        AxString explain( ss.str().c_str() );
        _spResult->AddInformationResult( L"REQ_EP_082", explain, TestResult::FAIL );
        testPassed = false;
    }
    
    for ( mapIter = spTrackNumMap->begin(); mapIter != spTrackNumMap->end(); mapIter++ )
    {
    
        switch (mapIter->first)
        {
            case 1:
                //1. Ensure that there are <=1 primary timecode tracks
                if ( mapIter->second > 1 )
                {
                    _spResult->AddInformationResult( L"REQ_EP_082", nodeName + L" has more than one Primary timecode track.", TestResult::FAIL );
                    testPassed = false;
                }
                break;
            case 3: case 4: case 5: case 6: case 7:
                //2. Ensure that there are <=1 AuxN tracks
                if ( mapIter->second > 1 )
                {
                    wstringstream ss;
                    ss << nodeName << L" has more than one Aux" << (mapIter->first - 2) << L" Timecode track.";
                    AxString explain( ss.str().c_str() );
                    _spResult->AddInformationResult( L"REQ_EP_082", explain, TestResult::FAIL );
                    testPassed = false;
                }
                break;
            case 2: case 8: case 9: case 10: case 11: case 12:
                //3. Ensure there are no reserved timecode tracks
                {
                    wstringstream ss;
                    ss << nodeName << L" has a Reserved Timecode track (MobSlot::PhysicalTrackNumber = " << mapIter->first << L").";
                    AxString explain( ss.str().c_str() );
                    _spResult->AddInformationResult( L"REQ_EP_082", explain, TestResult::FAIL );
                    testPassed = false;
                }
                break;
            default:
                //4. Ensure there are no other timecode tracks
                {
                    wstringstream ss;
                    ss << nodeName << L" has a illegal Timecode track (MobSlot::PhysicalTrackNumber = " << mapIter->first << L").";
                    AxString explain( ss.str().c_str() );
                    _spResult->AddInformationResult( L"REQ_EP_082", explain, TestResult::FAIL );
                    testPassed = false;
                }
                break;
        }
    
    }
    
    return testPassed;
}

bool EPContainedTrackVisitor::PreOrderVisit( EPTypedObjNode<IAAFSourceMob, EPFilmSource>& node )
{
  
    AxSourceMob axSrcMob( node.GetAAFObjectOfType() );
    
    //Get the name of the mob
    AxString nodeName = this->GetMobName( axSrcMob, L"Film Source" );
    
    unsigned int unnumberedtracks;
    shared_ptr<TrackNumberMap> spTrackNumMap( CountTrackCodes( this->GetEdgecodeTracks( _spEdgeMap, node ), unnumberedtracks ) );
    
    TrackNumberMap::const_iterator mapIter;
    bool testPassed = true;

    //Ensure all tracks have a physical track number
    if (unnumberedtracks != 0)
    {
        wstringstream ss;
        ss << nodeName << L" has " << unnumberedtracks << " Edgecode tracks with no MobSlot::PhysicalTrackNumber property.";
        AxString explain( ss.str().c_str() );
        _spResult->AddInformationResult( L"REQ_EP_087", explain, TestResult::FAIL );
        testPassed = false;
    }
    
    for ( mapIter = spTrackNumMap->begin(); mapIter != spTrackNumMap->end(); mapIter++ )
    {
    
        switch (mapIter->first)
        {
            case 1:
                //1. Ensure that there are <=1 Keycode Number Edgecode tracks
                if ( mapIter->second > 1 )
                {
                    _spResult->AddInformationResult( L"REQ_EP_087", nodeName + L" has more than one Keycode Number Edgecode track.", TestResult::FAIL );
                    testPassed = false;
                }
                break;
            case 2:
                //2. Ensure that there are <=1 Ink Number Edgecode tracks
                if ( mapIter->second > 1 )
                {
                    _spResult->AddInformationResult( L"REQ_EP_087", nodeName + L" has more than one Ink Number Edgecode track.", TestResult::FAIL );
                    testPassed = false;
                }
                break;
            case 3:
                //3. Ensure that there are <=1 Aux. Ink Number Edgecode tracks
                if ( mapIter->second > 1 )
                {
                    _spResult->AddInformationResult( L"REQ_EP_087", nodeName + L" has more than one Aux. Ink Number Edgecode track.", TestResult::FAIL );
                    testPassed = false;
                }
                break;
            default:
                //4. Ensure there are no other Edgecode tracks
                {
                    wstringstream ss;
                    ss << nodeName << L" has a illegal Edgecode track (MobSlot::PhysicalTrackNumber = " << mapIter->first << L").";
                    AxString explain( ss.str().c_str() );
                    _spResult->AddInformationResult( L"REQ_EP_087", explain, TestResult::FAIL );                    
                    testPassed = false;
                }
                break;
        }
    
    }
    
    return testPassed;

}

shared_ptr<DetailLevelTestResult> EPContainedTrackVisitor::GetResult()
{
    return _spResult;
}

shared_ptr<EPContainedTrackVisitor::TrackNumberMap> EPContainedTrackVisitor::CountTrackCodes( shared_ptr<EPTypedVisitor::MobSlotSet> tracks, unsigned int& unnumberedTracks )
{
    shared_ptr<TrackNumberMap> spTrackMap( new TrackNumberMap );
    unnumberedTracks = 0;
    
    EPTypedVisitor::MobSlotSet::const_iterator iter;
    
    for ( iter = tracks->begin(); iter != tracks->end(); iter++ )
    {
        try {
            aafUInt32 physicalTrackNumber = (*iter)->GetPhysicalNum();
            if ( spTrackMap->find( physicalTrackNumber ) == spTrackMap->end() )
            {
                (*spTrackMap)[physicalTrackNumber] = 1;
            }
            else
            {
                (*spTrackMap)[physicalTrackNumber] = (*spTrackMap)[physicalTrackNumber] + 1;
            }
        }
        catch ( const AxExHResult& ex )
        {
            if ( ex.getHResult() == AAFRESULT_PROP_NOT_PRESENT )
            {
                unnumberedTracks++;
            }
            else
            {
                throw ex;
            }
        }
    }
    
    return spTrackMap;
    
}

unsigned int EPContainedTrackVisitor::CountSegments( AxMobSlot& track, aafUID_t segmentType )
{

    //TODO: Once the requirements are clarified, it may be useful to rewrite
    //      this method using a visitor to allow sequences to be accessed.

    AxSegment axSegment( track.GetSegment() );
    AxClassDef clsDef( axSegment.GetDefinition() );
    if ( this->IsType( clsDef, segmentType, kAAFClassID_Segment ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
    
} // end of namespace aafanalyzer
