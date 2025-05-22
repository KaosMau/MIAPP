#include "FirebaseManager.h"
#include <FirebaseESP32.h>

FirebaseManager::FirebaseManager(const String& host, const String& auth)
    : firebaseHost(host), firebaseAuth(auth) {}

void FirebaseManager::begin() {
    Firebase.begin(firebaseHost, firebaseAuth);
    Firebase.reconnectWiFi(true);
}

String FirebaseManager::getModo() {
    if (Firebase.getString(firebaseData, "/display/modo")) {
        return firebaseData.stringData();
    }
    return "manual";
}

String FirebaseManager::getNumero() {
    if (Firebase.getString(firebaseData, "/display/numero")) {
        return firebaseData.stringData();
    }
    return "00000000";
}
