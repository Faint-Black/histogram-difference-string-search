# Histogram Difference String Search
An algorithm that quickly determines the similarity score between two strings, 
meant as a mostly conceptual demonstration of a fast user search-bar auto-completion suggestion algorithm by just counting the number of instances of each character of a string and seeing how many of them match by calculating the difference.

Implemented in Common Lisp + C.

---

## Possible Dependencies:
The following setup may be required for you to run the code:
* **Editor:** Emacs
* **Repl:** SLIME
* **Implementation:** sbcl
* **Package manager:** quicklisp

---

## Instructions:
First, you need to compile the C code to generate a shared object library that the Lisp code depends on:
```sh
cd src/lib/
chmod +x buildlib.sh
./buildlib.sh
```

After that, open a REPL, load the `main.lisp` file, then run the main function, like so:
```
REPL> (main "./path/to/dictionary" "foobar")
```
This should return a list of tuples that correspond to the dictionary words and their respective similarity scores with your provided string.
The closer to 0, the more similar the two strings are.
