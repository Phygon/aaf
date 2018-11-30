macro(EXEC_CHECK CMD)
    execute_process(COMMAND ${CMD} ${ARGN} RESULT_VARIABLE CMD_RESULT)
    if(CMD_RESULT)
        message(FATAL_ERROR "Error running ${CMD} ${ARGN}")
    endif()
endmacro()

if(EXISTS basic.aaf)
    file(REMOVE basic.aaf)
endif()

EXEC_CHECK(${EXECUTABLE} -r LoadLib ${LIBRARY} -r FileOp write ${FILEKIND} basic.aaf -r MasterMobAdd A -r FileOp save_and_close -r UnloadLib)
EXEC_CHECK(${EXECUTABLE} -r LoadLib ${LIBRARY} -r FileOp read ${FILEKIND} basic.aaf -r FindMasterMob A -r FileOp close -r UnloadLib)
