;;-----------------------------------------------------------------------------
;;  Defines the FFI responsible for integrating the pre-compiled C functions
;;-----------------------------------------------------------------------------

(sb-alien:load-shared-object "./lib/libhistogram.so")

(sb-alien:define-alien-routine ("string_similarity_score" c-string-score) sb-alien:int
  (str1 sb-alien:c-string)
  (str2 sb-alien:c-string))
