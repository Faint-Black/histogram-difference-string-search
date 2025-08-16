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

(defun main(FILEPATH)
  "Execute me!"
  (parse-dictionary FILEPATH))
