#include "Boot.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "You forgot to insert port number!" << endl;
    return 0;
  }
  int port = atoi(argv[1]);

  auto* main = new boot::Main();
  main->main(port);
  return 0;
}
