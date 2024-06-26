/*

posprintf - a condensed version of sprintf for Thumb, esp. GBA
Copyright (C) 2003 Dan Posluns

The person or persons who have associated work with this document (the "Dedicator" or "Certifier") hereby either (a) certifies that, to the best of his knowledge, the work of authorship identified is in the public domain of the country from which the work is published, or (b) hereby dedicates whatever copyright the dedicators holds in the work of authorship identified below (the "Work") to the public domain. A certifier, moreover, dedicates any copyright interest he may have in the associated work, and for these purposes, is described as a "dedicator" below.

A certifier has taken reasonable steps to verify the copyright status of this work. Certifier recognizes that his good faith efforts may not shield him from liability if in fact the work certified is not in the public domain.

Dedicator makes this dedication for the benefit of the public at large and to the detriment of the Dedicator's heirs and successors. Dedicator intends this dedication to be an overt act of relinquishment in perpetuity of all present and future rights under copyright law, whether vested or contingent, in the Work. Dedicator understands that such relinquishment of all rights includes the relinquishment of all rights to enforce (by lawsuit or otherwise) those copyrights in the Work.

Dedicator recognizes that, once placed in the public domain, the Work may be freely reproduced, distributed, transmitted, used, modified, built upon, or otherwise exploited by anyone for any purpose, commercial or non-commercial, and in any way, including by methods that have not yet been invented or conceived.

Author contact e-mail: dan at danposluns dot com


INSTRUCTIONS:

To call: posprintf(char *dest, const char *src[, param1[, param2[, ... paramN]]]);

- src must be a valid zero-terminated C string.
- dest must point to a sufficiently large block of memory to contain the result string.

The following format specifiers are valid:

%% - print a '%' symbol
%s - print a string; parameter must point to a valid zero-terminated C string
%d - print a 16-bit (short) integer; must be within [-65,535 .. 65,535]
%l - print a 29-bit integer; approximate range [-500,000,000 .. 500,000,000]
%x - print a hexadecimal number (lowercase digits)
%X - print a hexadecimal number (uppercase digits)

The specifiers %d, %l, %x and %X may be modified as follows:

- Digits 1 through 9 indicate number of leading spaces to print, eg.
	%5d would print the number 123 as "  123"
	%5d would print the number 123456 as "123456" (no leading spaces)
- When above digit is prefixed with 0, leading zeros are printed instead of spaces
	%05d would print the number 123 as "00123"
	%04d would print the number 12345 as "12345" (no leading zeros)
- Negative sign consumes a leading space, eg.
	%05d would print the number -123 as "-0123"
	(Hexadecimal numbers are considered unsigned)

IF YOU WANT MORE FUNCTIONALITY THAN THIS, YOU CAN FEEL FREE TO MODIFY THE CODE,
BUT THEN I WOULD SUGGEST MOVING TO A MORE SOPHISTICATED LIBRARY ANYWAY.

*** CAUTION IF NOT USED ON GAMEBOY ADVANCE ***
Although this is mostly written as general Thumb code, the %l (29-bit print)
specifier code currently uses a software interrupt (SWI) specific to the
Gameboy Advance to perform a division. If you wish to port this to other ARM
machines, you may need to alter this code. I believe that most ARM machines
support SWI 7 as an alternative software divide, although you will have to
swap the numerator/denominator registers (r0 and r1).
*** END CAUTION ***

My contact e-mail is: dan at danposluns dot com

*/

#ifndef _PSPRINTF_HEADER_
#define _PSPRINTF_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

extern void posprintf(char *, const char *, ...);

#ifdef __cplusplus
}
#endif

#endif
