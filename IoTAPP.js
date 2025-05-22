document.addEventListener("DOMContentLoaded", function () {
  // Configuración de Firebase
  var firebaseConfig = {
    apiKey: "AIzaSyD6MWwFlkKigBkog4xJzryUWpqPlO_dc4g",
    authDomain: "pia1-4739e.firebaseapp.com",
    databaseURL: "https://pia1-4739e-default-rtdb.firebaseio.com",
    projectId: "pia1-4739e",
    storageBucket: "pia1-4739e.appspot.com",
    messagingSenderId: "1234567890",
    appId: "1:1234567890:web:abcdefg12345"
  };

  firebase.initializeApp(firebaseConfig);
  var db = firebase.database();

  // Modo Manual
  $('#manualForm').submit(function (e) {
    e.preventDefault();
    var valor = $('#manualInput').val();

    console.log("📤 Enviando número manual: " + valor);

    db.ref('/display/modo').set('manual')
      .then(() => console.log("✅ Modo manual activado"))
      .catch((error) => console.error("❌ Error al cambiar el modo:", error));

    db.ref('/display/numero').set(valor)
      .then(() => console.log("✅ Número enviado: " + valor))
      .catch((error) => console.error("❌ Error al enviar número:", error));
  });

  // Modo Automático
  window.activarAutomatico = function () {
    console.log("📤 Activando modo automático...");

    db.ref('/display/modo').set('automatico')
      .then(() => console.log("✅ Modo automático activado"))
      .catch((error) => console.error("❌ Error al activar automático:", error));
  };
});
