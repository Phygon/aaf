#! C:/mksnt/sh.exe
# Terry Skotz

CHECK_DEBUG=0
CHECK_RELEASE=0
ESSENCETEST=0
MODULETEST=0
TIMDUMP=0
CLIENTTEST=0
CUTSTEST=0
PROPDIRECTDUMP=0
PROPDIRECTACCESS=0
CREATESEQUENCE=0
ESSENCEACCESS=0
AAFINFO=0
AAFOMFTEST=0
ALL=0
PRINTPATH=0
AAFWATCHDOG=0


PrintHelp ()
{
	echo "\nTo run module test and all examples for specified target, use either:"
	echo "-r  = Release"
	echo "-d  = Debug"
	echo "\nTo specify which tests to run, add any of the following:"
	echo "-a  = Run ALL Tests"
	echo "-ao = AafOmf"
	echo "-i  = ComAAFInfo"
	echo "-cl = ComClientTest"
	echo "-cu = ComCutsTest"
	echo "-e  = ComEssenceDataTest"
	echo "-m  = ComModAAF"
	echo "-pd = ComPropDirectDump"
	echo "-pa = ComPropDirectAccess" 
	echo "-ea = EssenceAccess"
	echo "-cs = CreateSequence"
	echo "-t  = dump\n\n"
	echo "-s  = update AAFWatchDog.log with exit code results"
	echo "-pp = Print PATH variable\n\n"
}


#####################
# Parse Command Line
#####################
if [ $# -eq 0 ]; then
	PrintHelp
	exit 1
elif [ $# -eq 1 ]; then
	if [ $1 = "-d" ] || [ $1 = "-r" ]; then
		ALL=1;
	fi
fi

until [ $# = 0 ]
do
	case $1 in
		-a ) ALL=1;;
		-r ) CHECK_RELEASE=1 ;;
		-d ) CHECK_DEBUG=1 ;;
		-e ) ESSENCETEST=1;;
		-m ) MODULETEST=1;;
		-t ) TIMDUMP=1;;
		-cl ) CLIENTTEST=1;;
		-cu ) CUTSTEST=1;;
		-pd ) PROPDIRECTDUMP=1;;
		-pa ) PROPDIRECTACCESS=1;;
		-ea) ESSENCEACCESS=1;;
		-cs ) CREATESEQUENCE=1;;
		-i ) AAFINFO=1;;
		-ao ) AAFOMFTEST=1;;
		-pp ) PRINTPATH=1;;
		-s ) AAFWATCHDOG=1;;
		-h ) PrintHelp
			 exit 1 ;;
	esac
	shift
done


DEBUG="AAFWinSDK/Debug"
RELEASE="AAFWinSDK/Release"

OLD_PATH=""

STATUS=0

RESULTS=""

CheckExitCode ()
{
	ExitCode=$1
	PROGRAM=$2

	#Generate list of all the results
	RESULTS="${RESULTS}$ExitCode  $PROGRAM\n"

	if [ $ExitCode -ne 0 ]; then
		STATUS=1
	fi
}


SetPath ()
{
	Target=$1

	print "\nSetting PATH $Target \n"
	OLD_PATH=$PATH
	PATH="`PWD`/AAFWINSDK/${Target}/RefImpl;$PATH"
}


ResetPath ()
{
	print "\nResetting PATH\n"
	PATH=$OLD_PATH
}


PrintSeparator ()
{
	TEXT=$1
	print "\n\n"
	print "****************************************************************************"
	print "$TEXT"
	print "****************************************************************************\n\n"
}


VerifyFiles ()
{
	FileList=$1

	RemoveIfExists ()
	{
		FileToBeRemove=$1

		if [ -a FileToBeRemove ]; then
			rm FileToBeRemove
		fi
	}

	for File in $FileList; do
	print -n "running ${File} thru dump.exe...  "
		RemoveIfExists ${File}Dump.log
		${DumpDir}/dump -s -p "$File" > tempdump.log
		Stat=$?
		print $Stat
		if [ $Stat -ne 0 ]; then
			CheckExitCode $Stat   "     $File <- This File flunked the dump.exe validation test"
			mv tempdump.log ${File}Dump.log
		fi
			
		print -n "running ${File} thru ComPropDirectDump.exe...  "
		RemoveIfExists ${File}CPDDump.log
		${ExamplesDir}/ComPropDirectDump "$File" > tempdump.log
		Stat=$?
		print $Stat
		if [ $Stat -ne 0 ]; then
			CheckExitCode $Stat   "     $File <- This File flunked the ComPropDirectDump.exe validation test"
			mv tempdump.log ${File}CPDDump.log
		fi
	done
	
	RemoveIfExists tempdump.log
}


RunMainScript ()
{
	Target=$1
	print "\n\nTarget:  $Target"
	SetPath "$Target"


	if [ PRINTPATH -eq 1 ]; then 
		print "PATH = $PATH" 
		print "\n\n"
	fi

	START_DIR="`PWD`"

	cd AAFWinSDK/$Target
	
	TargetDir="`PWD`"
	DumpDir="`PWD`/DevUtils"
	ExamplesDir="`PWD`/Examples/Com"


	if [ MODULETEST -eq 1 ] || [ ALL -eq 1 ]; then
		cd Test
		cp ../../Test/Com/ComModTestAAF/Laser.wav .
		ComModAAF
		CheckExitCode $? "ComModAAF"

		VerifyFiles "`ls *.aaf`"

		cd $TargetDir
	fi

	if [ AAFOMFTEST -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "AafOmf Convertor Test 1 -  AAF -> OMF"
		cd Utilities
		cp ../Test/AAFSequenceTest.aaf .
		AafOmf -omf AAFSequenceTest.aaf
		CheckExitCode $? "AafOmf Convertor Test 1 -  AAF -> OMF"

		VerifyFiles "AAFSequenceTest.aaf"

		PrintSeparator "AafOmf Convertor Test 2 -  OMF -> AAF"
		cp D:/views/Complx2x.omf .
		AafOmf Complx2x.omf
		CheckExitCode $? "AafOmf Convertor Test 2 -  OMF -> AAF"

		cd $TargetDir
	fi

	if [ CLIENTTEST -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running COMClientAAF"
		cd Examples/com
		COMClientAAF
		CheckExitCode $? "COMClientAAF"

		VerifyFiles "`ls *.aaf`"

		cd $TargetDir
	fi

	if [ CUTSTEST -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running ComCutsTestAAF"
		cd Examples/com
		ComCutsTestAAF
		CheckExitCode $? "ComCutsTestAAF"

		VerifyFiles "CutsOnly.aaf"

		cd $TargetDir
	fi

	if [ ESSENCETEST -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running ComEssenceDataTest"
		cd Examples/com
		cp ../../../examples/com-api/ComEssenceDataTest/Laser.wav .
		ComEssenceDataTest
		CheckExitCode $? "ComEssenceDataTest"

		VerifyFiles "EssenceTest.aaf"
		VerifyFiles "ExternalAAFEssence.aaf"

		cd $TargetDir
	fi

	if [ AAFINFO -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running ComAAFInfo on EssenceTest.aaf"
		cd Examples/com
		ComAAFInfo EssenceTest.aaf
		CheckExitCode $? "ComAAFInfo"

		cd $TargetDir
	fi
	
	if [ PROPDIRECTDUMP -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running ComPropDirectDump on EssenceTest.aaf"
		cd Examples/com
		ComPropDirectDump EssenceTest.aaf
		CheckExitCode $? "ComPropDirectDump" 

		cd $TargetDir
	fi

	if [ PROPDIRECTACCESS -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running ComPropDirectAccess on EssenceTest.aaf"
		cd Examples/com
		ComPropDirectAccess EssenceTest.aaf
		CheckExitCode $? "ComPropDirectAccess" 

		cd $TargetDir
	fi

	if [ CREATESEQUENCE -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running CreateSequence"
		cd Test
		CreateSequence 10 CreateSequence10
		CheckExitCode $? "CreateSequence" 

		VerifyFiles "CreateSequence10.aaf"

		cd $TargetDir
	fi

	if [ ESSENCEACCESS -eq 1 ] || [ ALL -eq 1 ]; then
		PrintSeparator "Running EssenceAccess"
		cd Test
		EssenceAccess 10
		CheckExitCode $? "EssenceAccess" 

		VerifyFiles "ExternalAAFEssence.aaf"
		VerifyFiles "ExternalStandardAAF.aaf"
		VerifyFiles "ExternalStandardRaw.aaf"
		VerifyFiles "InternalFractional.aaf"
		VerifyFiles "InternalMulti.aaf"
		VerifyFiles "InternalStandard.aaf"
		VerifyFiles "InternalRaw.aaf"

		cd $TargetDir
	fi

	cd $START_DIR

	ResetPath
}


PrintExitCodes ()
{
	ExTarget=$1

	print "\nPrinting $ExTarget Test Exit Codes:\n$RESULTS"

	if [ AAFWATCHDOG -eq 1 ]; then
		print "\nPrinting $ExTarget Test Exit Codes:\n$RESULTS" >> D:/AAFWatchDog/AAFWatchDog.log
	fi
}



if [ CHECK_DEBUG -eq 1 ]; then
	RunMainScript "Debug"
	PrintExitCodes "Debug"
fi


if [ CHECK_RELEASE -eq 1 ]; then
	RunMainScript "Release"
	PrintExitCodes "Release"
fi



exit $STATUS
