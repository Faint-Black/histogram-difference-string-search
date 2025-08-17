;;-----------------------------------------------------------------------------
;;  Main function resides here.
;;-----------------------------------------------------------------------------

;; regex matching library
(ql:quickload :cl-ppcre)
;; system utilities library
(ql:quickload :uiop)

;; Turns the input dictionary file into a list of usable strings
(load "dictionary.lisp")
;; Defines the string similarity score function
(load "histogram.lisp")

(defun main(DICT-FILEPATH WORD)
  "Given a dictionary, check which word is the most similar to the input string"
  (sort
   (mapcar
    (lambda(x) (list x (c-similarity-score WORD x)))
    (parse-dictionary DICT-FILEPATH))
   #'< :key #'second))
