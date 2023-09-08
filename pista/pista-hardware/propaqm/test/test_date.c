#define _XOPEN_SOURCE
#include <time.h>
#include <stdio.h>
#include <string.h>

/*
 * curl -k -H Accept:application/json -H Content-Type:application/json -H Client-Id:12345 -u "zolldata:MDARK2018" "https://192.168.50.55/Numerics/current?now"
 *
 */

struct tm a_tm;

int main( int argc, char *argv[] ) {

  char input[] = "2019-01-16T10:32:06";

  /* First clear the result structure.  */
  memset (&a_tm, '\0', sizeof (a_tm));

  /* Try the ISO format first.  */
  char *cp = strptime (input, "%Y-%m-%dT%H:%M:%S", &a_tm);

  if (cp == NULL) { /* Does not match.  Try the US form.  */
      printf("DOES NOT MATCH\n" );
      return 0;
  } else {
      char buf[60];
      strftime( buf, sizeof( buf ), "%c", &a_tm);
      printf("DT=%s\n", buf );
  }

}


