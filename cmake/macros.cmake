macro(llvm_config output lcargs)
  execute_process(
    COMMAND ${LLVM_CONFIG} ${lcargs}
    OUTPUT_VARIABLE ${output}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endmacro()

macro(prepend_dir output p_dir files)
  set(${output} "")
  foreach(f ${files})
    list(APPEND ${output} "${p_dir}/${f}")
  endforeach(f)
endmacro()
