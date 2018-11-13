set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyMicrosoftModule
  MicrosoftTidyModule.cpp

  LINK_LIBS
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  clangTooling
  )
