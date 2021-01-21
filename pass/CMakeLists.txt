if(NOT FUNC_DIR)
    set( FUNC_DIR /home/user/study/llvm/llvmPass/pass/FuncBlockCount)
endif()

if( IS_DIRECTORY ${FUNC_DIR} )
    # .out参数用于指定外部文件夹在输出文件夹中的位置
    add_subdirectory( ${FUNC_DIR} FuncBlockCount.dir)
else()
    message(FATAL_ERROR   "INVALID FOLDER 'FUNC_DIR'=${FUNC_DIR}" )
endif()

