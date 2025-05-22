self.addEventListener("install", (event) => {
  event.waitUntil(
    caches.open("iot-cache").then((cache) => {
      return cache.addAll([
        "./",
        "./index.html",
        "./js/IoTAPP.js",
        "./manifest.json",
        "./icon-192.png",
        "./icon-512.png",
        "https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css",
        "https://code.jquery.com/jquery-3.6.4.min.js",
        "https://www.gstatic.com/firebasejs/6.5.0/firebase-app.js",
        "https://www.gstatic.com/firebasejs/6.5.0/firebase-database.js"
      ]);
    })
  );
});

self.addEventListener("fetch", (event) => {
  event.respondWith(
    caches.match(event.request).then((response) => {
      return response || fetch(event.request);
    })
  );
});