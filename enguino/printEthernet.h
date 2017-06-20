// Performance 'print' functions to ethernet 'client' (includes flush)

char buffer[64];
int bfree = 64;
char *bufp = buffer;

void flush() {
  client.write(buffer, 64-bfree);
  bfree = 64;
  bufp = buffer;
}

void print(string cp, int len) {
  while (len) {
    int n = len;
    if (n > bfree)
      n = bfree;
    memcpy(bufp, cp, n);
    bufp += n;
    bfree -= n;
    if (bfree == 0)
      flush();
    cp += n;
    len -= n;     
  }
}

void print_P(const __FlashStringHelper * cp, int len) {
  PGM_P pp = reinterpret_cast<PGM_P>(cp);
  while (len) {
    int n = len;
    if (n > bfree)
      n = bfree;
    memcpy_P(bufp, pp, n);
    bufp += n;
    bfree -= n;
    if (bfree == 0)
      flush();
    pp += n;
    len -= n;     
  }
}

void print(string cp) {
  print(cp, strlen(cp));
}

void print_P(const __FlashStringHelper * cp) {
  PGM_P pp = reinterpret_cast<PGM_P>(cp);
  print_P(cp, strlen_P(pp));
}

void print(char c) {
  print(&c,1);
}

void print(int n, int decimal) {
  char buf[7];
  buf[6] = 0;
  char *cp = buf + 6;
  if (n < 0) {
    if (n == OPEN) {
      print("open");
      return;
    }
   if (n == SHORT) {
      print("shrt");
      return;
    }
      
    print('-');
    n = -n;
  }
  do {
    *--cp = n % 10 + '0';
    n /= 10;
    if (decimal-- == 1)
      *--cp = '.';
  } while (n > 0 || decimal >= 0);
  print(cp);
}

void print(int n) {
  print(n,0);
}

void print_n_close() {
  print_P(F("'/>\n"));
}

void print_n_close(int n) {
  print(n);
  print_n_close();
}

void print_g_close() {
  print_P(F("</g>\n"));
}

void print_text_close() {
  print_P(F("</text>\n"));
}

void print_text_close(string cp) {
  print(cp);
  print_text_close();
}
