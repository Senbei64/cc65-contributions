/* Test of the scanning of floating point constants: their value must be
** exact (correctly rounded), also with an integer part over 32 bits or an
** exponent with more than three digits. The constants are converted to
** integers at compile time.
*/

#include <stdio.h>

static const int Ints[] = {
    2.01e2,
    2.30e2,
    2.41e2,
    1.0e0002,                           /* Exponent with four digits */
    0x1.8p1,                            /* Hexadecimal */
    1234.5e1,
};

static const int Expected[] = {
    201,
    230,
    241,
    100,
    3,
    12345,
};

/* The integer part has more than 32 bits */
static const long Big = 21474836470e-1;

int main (void)
/* Run the test, return 0 if it passes */
{
    unsigned I;
    unsigned Failures = 0;

    for (I = 0; I < sizeof (Ints) / sizeof (Ints[0]); ++I) {
        if (Ints[I] != Expected[I]) {
            printf ("constant %u: %d, expected %d\n", I, Ints[I], Expected[I]);
            ++Failures;
        }
    }
    if (Big != 2147483647L) {
        printf ("Big: %ld\n", Big);
        ++Failures;
    }
    printf ("float-const-scan: %u failures\n", Failures);
    return Failures != 0;
}
