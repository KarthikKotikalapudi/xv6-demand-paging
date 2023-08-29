#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[])
{
  struct rtcdate r;

  if (date(&r)) {
    printf(2, "date failed\n");
    exit();
  }

  printf(1, "Year: %d\n", r.year);
  printf(1, "Month: %d\n", r.month);
  printf(1, "Date: %d\n", r.day);
  printf(1, "Hour: %d\n", r.hour);
  printf(1, "Minute: %d\n", r.minute);
  printf(1, "Second: %d\n", r.second);

  exit();
}