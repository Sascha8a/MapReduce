
#include <iostream>

#include "dummy.pb.h"

using namespace std;

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Dummy *d = new Dummy;
    d->set_text("Hello World");
    cout << d->text() << endl;
    delete d;
    google::protobuf::ShutdownProtobufLibrary();
}
