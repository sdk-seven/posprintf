# posprintf Documentation

## What is it?

`posprintf` is a function to call in your Gameboy Advance programs to generate strings. It is
basically a somewhat amputated version of the standard C library function, `sprintf`.

---

## Why use it?

Probably the most significant use of it is to print out and format numbers for display on the
screen. In order to do this, the numbers need to be converted from their internal representation
(base 2) to decimal (base 10). `posprintf` uses an [extremely efficient algorithm scammed off of
the 'net](https://www.cs.uiowa.edu/~jones/bcd/decimal.html) to do this, and it is written entirely
in Thumb assembler to run very quickly (without consuming the internal memory needed to run
efficiently in ARM mode).

Other reasons to use it include that it's fast, extremely flexible for most GBA applications, and
absolutely free. [I wouldn't say no to a credit](#credit) if it used in an application, though,
commercial or otherwise.

---

## How do I use it?

1. Include the file `posprintf.h` in your C source code that you want to call the function. (ie.
   `#include "posprintf.h"`)
2. Call it the same way you would call `sprintf`, keeping in mind the differences between the two
   (see the next section).
3. Make sure to link the file `posprintf.o` with your project. Generally this just means including
   `posprintf.o` on the command line when you call gcc.

That's all there is to it.

---

## How do I call the function?

The syntax is as follows:

```c
posprintf(char *dest, const char *src[, param1[, param2[, ... paramN]]]);
```

- *`dest`* is the address of the string to be printed out to. **IMPORTANT:** There must be
  sufficient memory allocated to the buffer to hold the string, including the terminating zero.
- *`src`* is the address of the source string to print. This absolutely **must** be a valid,
  zero-terminated C string.
- The optional parameters accompany any format specifiers used in the source string.

### Format Specifiers

The following are valid format specifiers for use with `posprintf`:

- `%%` - print `%` character
- `%s` - print a string. The accompanying parameter must be a valid, zero-terminated C string.
- `%d` - print an integer. **Important**: unlike `sprintf`, this is only accurate for 16 bits of
  data, or numbers ranging from -65,535 to 65,535.
- `%l` - print a long integer. **Important**: unlike `sprintf`, this is only accurate for
  approximately 29 bits of data, or numbers ranging from about -500 million to 500 million.
- `%x` - print in hexadecimal format. Provided mostly as a programming tool, since few user
  applications would probably ever want to print hexadecimal numbers.
- `%X` - same as `%x`, but printf capital letters for the digits 'a' through 'f'.

### Output Control

The output of `%d`, `%l`, `%x` and `%X` tags may be optionally influenced by the following
prefixes:

- **Digits 1 through 9**: Indicate how many leading spaces to include. Examples:
  - `%5d` would print the number 123 as `"  123"`
  - `%3d` would print the number 12345 as `"12345"` (no leading spaces)
- **Digit 0**: When prefixing the above number, indicates to print leading zeros instead of
  leading spaces. Examples:
  - `%05d` would print the number 123 as `"00123"`
  - `%03d` would print the number 12345 as `"12345"` (no leading zeros)

**Note**: If the number printed is negative, then the negative sign will consume a leading
space/zero, if there are any.

---

## Other Notes

### Optimized for GBA development

One of the big realizations in understanding this code is that few GBA games need to display
numbers larger than 65,535, and when they do these are the minority of numbers, not the majority.
The `%d` specifier is highly optimized to work with 16 bits, and you should use it whenever
possible.

For the minority of occassions when you need to display more than 16 bits worth of numerical data,
`%l` works fine to numbers well beyond the plus-or-minus 500 million mark. (The actual limit is +/-
655,539,999.) It takes about twice as long to run as `%d`, though, and includes a slow SWI call to
split the number into two chunks, so you should still use `%d` instead whenever you can.

If you need to display numbers larger than 500 million, then you will either have to heavily alter
the code, use a different utility, or break your number up into sizeable chunks. If you need to
display larger numbers than 500 million for a GBA game, though, you may want to rethink your game
design.

### What about other ARM machines?

Although `posprintf` is mostly written as generic Thumn code, the %l (29-bit print) specifier code
currently uses a software interrupt (SWI) specific to the Gameboy Advance to perform a division.
If you wish to port this to other ARM machines, you may need to alter this code. I believe that
most ARM machines support SWI 7 as an alternative software divide, although you will have to swap
the numerator/denominator registers (r0 and r1).

### Can't you optimize out the SWI call? Use inverse multiplication, register shifting, or somesuch?

Not easily. Not in Thumb mode, anyway, which doesn't have the 64-bit multiply instruction. The
number has many significant digits, and is being divided by 10,000, which requires two registers
to keep things accurate. My best advice is to avoid it in the first place by keeping your numbers
small and using `%d` instead, but also not to fret over using `%l` as the SWI is only issued once
in the entire routine, and everything else is still quite zippy. It is not like you will have to
call it a bazillion times per frame, and it's still a helluva lot faster than what the standard
lirbary `sprintf` does. If anyone does feel like optimizing this, though, please [send me the
results](#credit).

### If it's displaying 16-bit numbers and they are signed, shouldn't they be only in the range +/- 32767?

The conversion to base 10 is actually done on the number unsigned, so you get a full range up to
65,535. The sign is taken from the extension of the number to 32 bits, which happens automatically
regardless of whether you pass a short or not. The same applies to `%l`.

### What are the terms and restrictions to using posprintf?

`posprintf` is part of the [public domain](https://creativecommons.org/licenses/publicdomain/),
with no licenses attached.

### Why "posprintf"

I think the "po" stood for something originally, but now the "pos" is just a play on my last name.
Please, no P.O.S. jokes. :)

---

<a id="credit"></a>

# Contacting the Author

Please submit all bug reports, queries, suggested improvements, etc. to Dan Posluns at
[dan@danposluns.com](mailto:dan@danposluns.com).

---

<center><b>F I N</b></center>
