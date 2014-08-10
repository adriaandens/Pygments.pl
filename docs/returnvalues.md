# Return values

If anything went wrong, you'll receive a negative number as response. Here's the meaning behind every number:

* **-1**. Python and/or Pygments modules could not be imported. Do you have Pygments installed?
* **-10**. You're providing invalid input. Check your argument(s).
* **-20**. Something went wrong when converting your code to a Python object. (Should never happen)
* **-30**. The lexer does not exist.
* **-40**. The formatter does not exist.
* **-50**. There was an error trying to open the file for writing.
