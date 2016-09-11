extern int printf(const char* format, ...);

void logDebug(char c) {
  printf("%c", c);
}
