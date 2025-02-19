#include "format_bytes.h"

#include <stdio.h>

// B, KB, MB, GB, TB
char *format_bytes(unsigned long bytes, char *output) {
  const char *units[] = {"B", "KB", "MB", "GB", "TB"};
  int i = 0;
  double size = bytes;

  while (size >= 1024 && i < 4) {
    size /= 1024;
    i++;
  }

  sprintf(output, "%.2f %s", size, units[i]);
  return output;
}
