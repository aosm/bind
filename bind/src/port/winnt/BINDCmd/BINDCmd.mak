# Microsoft Developer Studio Generated NMAKE File, Based on BINDCmd.dsp
!IF "$(CFG)" == ""
CFG=BINDCmd - Win32 Debug
!MESSAGE No configuration specified. Defaulting to BINDCmd - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "BINDCmd - Win32 Release" && "$(CFG)" != "BINDCmd - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BINDCmd.mak" CFG="BINDCmd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BINDCmd - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "BINDCmd - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "BINDCmd - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\bin\Release\BINDCmd.exe"


CLEAN :
	-@erase "$(INTDIR)\BINDCmd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\bin\Release\BINDCmd.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\..\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "i386" /Fp"$(INTDIR)\BINDCmd.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BINDCmd.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Advapi32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\BINDCmd.pdb" /machine:I386 /out:"..\bin\Release\BINDCmd.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BINDCmd.obj"

"..\bin\Release\BINDCmd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BINDCmd - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "..\bin\Debug\BINDCmd.exe" "$(OUTDIR)\BINDCmd.bsc"


CLEAN :
	-@erase "$(INTDIR)\BINDCmd.obj"
	-@erase "$(INTDIR)\BINDCmd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BINDCmd.bsc"
	-@erase "..\bin\Debug\BINDCmd.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\..\include" /D "_DEBUG" /D "i386" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BINDCmd.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BINDCmd.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BINDCmd.sbr"

"$(OUTDIR)\BINDCmd.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Advapi32.lib /nologo /subsystem:console /pdb:none /debug /machine:I386 /out:"..\bin\Debug\BINDCmd.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BINDCmd.obj"

"..\bin\Debug\BINDCmd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("BINDCmd.dep")
!INCLUDE "BINDCmd.dep"
!ELSE 
!MESSAGE Warning: cannot find "BINDCmd.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "BINDCmd - Win32 Release" || "$(CFG)" == "BINDCmd - Win32 Debug"
SOURCE=.\BINDCmd.cpp

!IF  "$(CFG)" == "BINDCmd - Win32 Release"


"$(INTDIR)\BINDCmd.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "BINDCmd - Win32 Debug"


"$(INTDIR)\BINDCmd.obj"	"$(INTDIR)\BINDCmd.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

