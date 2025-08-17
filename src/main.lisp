;;-----------------------------------------------------------------------------
;;  Includes all dependencies needed for the main function.
;;-----------------------------------------------------------------------------

;; regex matching library
(ql:quickload :cl-ppcre)
;; system utilities library
(ql:quickload :uiop)

;; Turns the input dictionary file into a list of usable strings
(load "dictionary.lisp")
;; Defines the string similarity score function
(load "histogram.lisp")

(defun sort-tuples(TUPLE-LIST)
  "Sorts the (str score) tuple list based on its score in ascending order"
  (sort TUPLE-LIST #'< :key #'second))

(defun make-tuple(INPUT-WORD DICT-WORD)
  "Given the dictionary string and the input string, evaluate a (str score) tuple"
  (list DICT-WORD (c-similarity-score DICT-WORD INPUT-WORD)))

(defun make-tuple-list(INPUT-WORD DICT-WORD-LIST)
  "Given a list of dictionary words and a predicate input word, build the score tuple list"
  (mapcar (lambda(x) (make-tuple INPUT-WORD x)) DICT-WORD-LIST))

(defun main(DICT-FILEPATH INPUT-WORD)
  "Given a dictionary, check which word is the most similar to the input string"
  (sort-tuples
   (make-tuple-list
    INPUT-WORD (parse-dictionary DICT-FILEPATH))))
