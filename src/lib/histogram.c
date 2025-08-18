/* Source for the library that will be used by the Common Lisp script
 * through the sbcl's alien-routine FFI.
 */

#define HISTOGRAM_LEN 27
#define NOT_A_LETTER_INDEX 26

typedef struct Histogram
{
  int char_count[HISTOGRAM_LEN];
} Histogram;

typedef enum CharacterType
{
  CT_UPPERCASE_LETTER,
  CT_LOWERCASE_LETTER,
  CT_NOT_A_LETTER
} CharacterType;

/* All externally accessible functions in this library */
Histogram histogram_init (void);
Histogram histogram_from_str (char const *);
Histogram histogram_difference (Histogram, Histogram);
int histogram_reduce (Histogram);
int consecutive_identical_letters (char const *, char const *);
int string_similarity_score (char const *, char const *);

/* All privately accessible functions in this library */
static int abs (int);
static CharacterType get_char_type (char);
static char normalized_char (char);

/* Returns the absolute value of an integer */
static int
abs (int n)
{
  if (n < 0)
    {
      return -n;
    }
  return n;
}

/* Determines if a char is [a-z], [A-Z] or anything else */
static CharacterType
get_char_type (char c)
{
  if ((c >= 'a') && (c <= 'z'))
    {
      return CT_LOWERCASE_LETTER;
    }
  if ((c >= 'A') && (c <= 'Z'))
    {
      return CT_UPPERCASE_LETTER;
    }
  return CT_NOT_A_LETTER;
}

/* returns the input as a uppercase letter, or whitespace if not a letter */
static char
normalized_char (char c)
{
  switch (get_char_type (c))
    {
    case CT_UPPERCASE_LETTER:
      return c;
    case CT_LOWERCASE_LETTER:
      return c - ('a' - 'A');
    default:
      return ' ';
    }
}

/* Init with zeroes */
Histogram
histogram_init (void)
{
  Histogram histogram;
  int i;
  for (i = 0; i < HISTOGRAM_LEN; i++)
    {
      histogram.char_count[i] = 0;
    }
  return histogram;
}

/* Creates a histogram from a string */
Histogram
histogram_from_str (char const *str)
{
  Histogram histogram = histogram_init ();
  char c;
  int index = NOT_A_LETTER_INDEX;
  while (*str)
    {
      c = *str;
      switch (get_char_type (c))
        {
        case CT_UPPERCASE_LETTER:
          index = c - 'A';
          break;
        case CT_LOWERCASE_LETTER:
          index = c - 'a';
          break;
        case CT_NOT_A_LETTER:
          index = NOT_A_LETTER_INDEX;
          break;
        }
      str++;
      histogram.char_count[index] += 1;
    }
  return histogram;
}

/* Evaluates another histogram with the difference of all entries */
Histogram
histogram_difference (Histogram h1, Histogram h2)
{
  Histogram histogram_diff;
  int diff;
  int i;
  for (i = 0; i < HISTOGRAM_LEN; i++)
    {
      diff = h1.char_count[i] - h2.char_count[i];
      histogram_diff.char_count[i] = abs (diff);
    }
  return histogram_diff;
}

/* Reduces all the values into a single integer by summming */
int
histogram_reduce (Histogram histogram)
{
  int reduce = 0;
  int i;
  for (i = 0; i < HISTOGRAM_LEN; i++)
    {
      reduce += histogram.char_count[i];
    }
  return reduce;
}

/* Aborts when a non-identical letter is found */
int
consecutive_identical_letters (char const *str1, char const *str2)
{
  int n = 0;
  while (*str1 && *str2)
    {
      if (normalized_char (*str1) != normalized_char (*str2))
        {
          break;
        }
      n++;
      str1++;
      str2++;
    }
  return n;
}

/* Evaluates the reduced histogram difference between the two arg strings */
int
string_similarity_score (char const *str1, char const *str2)
{
  int score;
  Histogram h1 = histogram_from_str (str1);
  Histogram h2 = histogram_from_str (str2);
  Histogram diff = histogram_difference (h1, h2);
  score = histogram_reduce (diff);
  score -= consecutive_identical_letters (str1, str2);
  return score;
}
