#include "Server.h"

int main(int argc, char* argv[]) {
  boot::Main<string, string> main;
  return main.main(argc, argv);
}
