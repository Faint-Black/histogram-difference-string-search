;;-----------------------------------------------------------------------------
;;  Dictionary file loading and parsing functions.
;;-----------------------------------------------------------------------------

(defun normalize-character(CHARACTER)
  "Takes in a character and outputs a normalized-form character, any lowercase gets converted to uppercase, any non-character gets converted to whitespace"
  (cond
    ((<= (char-code #\a) (char-code CHARACTER) (char-code #\z)) (char-upcase CHARACTER))
    ((<= (char-code #\A) (char-code CHARACTER) (char-code #\Z)) CHARACTER)
    (t #\Space)))

(defun normalize-word(STRING)
  "Takes in a raw unparsed dictionary string and normalizes it"
  (map 'string #'normalize-character STRING))

(defun parse-dictionary(FILEPATH)
  "Parses the input dictionary file into a list of normalized and usable strings. Words are separated by newline characters, and not whitespace"
  (mapcar #'normalize-word (cl-ppcre:split "\\r?\\n" (uiop:read-file-string FILEPATH))))
