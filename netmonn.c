#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "format_bytes.h"

FILE *pNetDev() {
  FILE *pNet = fopen("/proc/net/dev", "r");
  if (pNet == NULL) {
    perror("fopen");
    return NULL;
  }
  return pNet;
}

void read_network_data(FILE *pNet) {
  char buffer[512];
  fgets(buffer, sizeof(buffer), pNet);
  fgets(buffer, sizeof(buffer), pNet);

  while (fgets(buffer, sizeof(buffer), pNet)) {
    char iface[32], rx_formatted[20], tx_formatted[20];
    unsigned long rx_bytes, tx_bytes;

    sscanf(buffer, " %31[^:]: %lu %*s %*s %*s %*s %*s %*s %*s %lu", iface,
           &rx_bytes, &tx_bytes);

    format_bytes(rx_bytes, rx_formatted);
    format_bytes(tx_bytes, tx_formatted);

    printf("%-8s | %-12s | %-12s\n", iface, rx_formatted, tx_formatted);
  }
}

void display_network_usage() {
  while (1) {
    FILE *pNet = pNetDev();
    if (pNet == NULL) {
      return;
    }

    system("clear");
    printf("%-8s | %-12s | %-12s\n", "Iface", "Rx Bytes", "Tx Bytes");
    printf("--------------------------------------\n");

    read_network_data(pNet);

    fclose(pNet);
    sleep(1);
  }
}

int main() {
  display_network_usage();
  return 0;
}
