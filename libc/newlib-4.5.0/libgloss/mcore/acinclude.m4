MCORE_BUILD_ELF=false
MCORE_BUILD_PE=false
AS_CASE([${target}],
  [mcore-*-elf], [MCORE_BUILD_ELF=true],
  [mcore-*-pe], [MCORE_BUILD_PE=true])
AM_CONDITIONAL([MCORE_BUILD_ELF], [$MCORE_BUILD_ELF])
AM_CONDITIONAL([MCORE_BUILD_PE], [$MCORE_BUILD_PE])