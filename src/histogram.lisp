;;-----------------------------------------------------------------------------
;;  Defines the FFI for integrating the pre-compiled C functions
;;-----------------------------------------------------------------------------

(sb-alien:load-shared-object "./lib/libhistogram.so")

;; similarity score function
(sb-alien:define-alien-routine
    ("string_similarity_score" c-similarity-score)
    sb-alien:int
  (str1 sb-alien:c-string)
  (str2 sb-alien:c-string))
