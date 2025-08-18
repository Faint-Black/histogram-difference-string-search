# Histogram Difference String Search
An algorithm that quickly determines the similarity score between two strings, 
meant as a mostly conceptual demonstration of a fast user search-bar auto-completion suggestion algorithm by just counting the number of instances of each character of a string and seeing how many of them match by calculating the difference, along with some complimentary steps.

User Input/Output implemented in **Common Lisp**.
Main algorithm functions implemented in **C**.

Bridge between these two languages is made possible by SBCL's alien routine FFI.

---

## The Algorithm:
1. Consider the input strings, sanitized to only include letters and whitespaces:
```
let str1 = normalize_string("aB1cd");
   => "AB CD"
let str2 = normalize_string("ab&CcD");
   => "AB CCD"
```

2. The first step of the algorithms would involve turning these strings into histograms based on the frequency of their letters:
```
let hist1 = histogram_from_str(str1);
   => [A:1, B:1, C:1, D:1, E:0, F:0, [...], Y:0, Z:0, NonLetter:1]
let hist2 = histogram_from_str(str2);
   => [A:1, B:1, C:2, D:1, E:0, F:0, [...], Y:0, Z:0, NonLetter:1]
```

3. Then, the difference of each slot is calculated individually into a new histogram, since negative values can cancel out positive values on the next step, only the absolute of the difference is extracted.
```
let hist_diff = histogram_difference(hist1, hist2);
   => [A:0, B:0, C:1, D:0, E:0, F:0, [...], Y:0, Z:0, NonLetter:0]
```

4. Afterwards, the entire histogram is collapsed into a single integer scalar by summing each slot.
```
let score = histogram_reduce(hist_diff);
   => 1
```

The closer to zero this score is, the more similar the 2 strings are.
In this case, 1 is a very similar match score, but the strings "Aardvark" and "Zebra" generate a score of 9, indicating a stark difference.

The histogram part of the algorithm stops here, however, the results remain somewhat innacurate, the scores are heavily skewed towards anagrams rather than any smart auto-completion.
For example: the word "REAC" returns the matches "CARE"(0), "RACE"(0), "CAR"(1), "CLEAR"(1), "CREAM"(1) and "EAR"(1) before it ever reaches the logical options of "REACH"(1) or "REACT"(1).

5. This next step of the algorithm subtracts from the score the amount of identical consecutive characters of the two strings.
```
score = score - consecutive_identical_letters(str1, str2);
```

With this tweak, inputting the input "REAC" returns the top matches "REACH"(-3), "REACT"(-3), "RACE"(-1), "READ"(-1), "REAL"(-1) and "REAR"(-1), these being much more intuitive results than the previous step of the algorithm.

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
REPL> (main "./path/to/dictionary.txt" "foobar")
```
This should return a list of tuples that correspond to the dictionary words and their respective similarity scores with your provided string.
