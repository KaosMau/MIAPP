#ifndef FIREBASEMANAGER_H
#define FIREBASEMANAGER_H

#include <Arduino.h>
#include <FirebaseESP32.h>

class FirebaseManager {
public:
    FirebaseManager(const String& host, const String& auth);
    void begin();
    String getModo();
    String getNumero();

private:
    FirebaseData firebaseData;
    String firebaseHost;
    String firebaseAuth;
};

#endif
