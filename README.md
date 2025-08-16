# Histogram Difference String Search
An algorithm that recommends the closest auto-completion to a string with a histogram difference of each individual character. Implemented in Common Lisp.

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

After that, open a REPL, load the main.lisp file, then run any function you wish.
