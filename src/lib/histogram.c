/* Source for the library that will be used by the Common Lisp script
   through the sbcl's FFI.  */

#define NONCHAR_INDEX 26
#define HISTOGRAM_LEN 27

typedef struct Histogram
{
  int char_count[HISTOGRAM_LEN];
} Histogram;

/* All accessible functions in this library */
Histogram histogram_init (void);
Histogram histogram_from_str (char const *);
Histogram histogram_difference (Histogram, Histogram);
int histogram_reduce (Histogram);
int string_similarity_score (char const *, char const *);

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
  int index = NONCHAR_INDEX;
  while (*str)
    {
      c = *str;
      if ((c >= 'a') && (c <= 'z'))
        {
          index = c - 97;
        }
      else if ((c >= 'A') && (c <= 'Z'))
        {
          index = c - 65;
        }
      else
        {
          index = NONCHAR_INDEX;
        }
      ++str;
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

/* Evaluates the reduced histogram difference between the two arg strings */
int
string_similarity_score (char const *str1, char const *str2)
{
  Histogram h1 = histogram_from_str (str1);
  Histogram h2 = histogram_from_str (str2);
  Histogram diff = histogram_difference (h1, h2);
  int score = histogram_reduce (diff);
  return score;
}
