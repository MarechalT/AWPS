#ifndef MCP3008READING_H
#define MCP3008READING_H

#define BASE 100
#define SPI_CHAN 1

int initMCP3008();
int readMCP3008(int channel);

#endif
