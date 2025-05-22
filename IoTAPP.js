// Tu configuración de Firebase aquí
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

$('#manualForm').submit(function(e) {
  e.preventDefault();
  var valor = $('#manualInput').val();
  db.ref('/display/modo').set('manual');
  db.ref('/display/numero').set(valor);
});

function activarAutomatico() {
  db.ref('/display/modo').set('automatico');
}
