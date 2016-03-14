#include <ovlnet/crypto.hh>
#include <iostream>


int main(int argc, char *argv[]) {
  if (3 != argc) {
    std::cout << "Usage: ovlgenid PREFIX OUTPUT_DIRECTORY" << std::endl;
    return -1;
  }

  Identity *id = Identity::newIdentity();
  while (! id->id().toBase32().startsWith(argv[1])) {
    delete id;
    id = Identity::newIdentity();
  }

  if (! id->save(QString(argv[2])+"/identity.pem")) {
    std::cout << "Failed to store identity at " << argv[2] << "/identity.pem";
    return -1;
  }

  return 0;
}
