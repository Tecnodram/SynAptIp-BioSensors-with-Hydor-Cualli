/* ============================================================
   HYDOR-CUALLI — Firmware del dispositivo embajador (BASE)
   Autoría original del proyecto y del código: Emily Acosta.
   ------------------------------------------------------------
   Versión "tal cual nos la dieron". Lee UN sensor a la vez desde
   A0 (agua o aire), según cuál cable de datos esté conectado
   físicamente. Un jumper en el pin D7 le dice al código cuál es.

   Jumper de modo:
     - D7 conectado a G  -> modo AGUA
     - D7 sin conectar   -> modo AIRE (usa resistencia interna)

   IMPORTANTE: mueve el cable de datos Y el jumper de modo juntos.
   Si mides agua, el cable de datos del TDS va en A0 y el jumper
   de modo va en G. Si mides aire, el cable de datos del MQ-135
   va en A0 y el jumper de modo se deja suelto.

   >> Esta versión publica a Firebase la ÚLTIMA lectura (la pisa
      cada vez). No guarda historial. Si quieres que el "Historial"
      del tablero se llene, usa la carpeta hermana:
      firmware/esp8266-oficial-historial
   ============================================================ */

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <time.h>

// ============================================================
//  ===== CONFIGURA ESTO (lo único que tienes que tocar) =====
// ============================================================

// ---------- WIFI: pon aquí tus redes reales ----------
#define WIFI_SSID1     "TU_RED_1"
#define WIFI_PASSWORD1 "TU_PASSWORD_1"
#define WIFI_SSID2     "TU_RED_2"
#define WIFI_PASSWORD2 "TU_PASSWORD_2"

// ---------- FIREBASE: pon aquí los datos de TU proyecto ----------
// Por ahora cada quien usa su propio Firebase: crea un proyecto gratis,
// activa la Realtime Database y pega aquí su host y su token.
#define FIREBASE_HOST  "tu-proyecto.firebaseio.com"
#define FIREBASE_AUTH  "TU_TOKEN_AQUI"

// ============================================================
//  fin de "CONFIGURA ESTO"
// ============================================================

// ---------- PINES ----------
const int PIN_DATO  = A0;  // señal del sensor que esté conectado
const int PIN_MODO  = D7;  // jumper: G = agua, suelto = aire

// ---------- CALIBRACIÓN (ajusta con tus propias pruebas) ----------
// TDS: agua limpia ≈ 10 ppm, agua salada ≈ 1000 ppm
const float TDS_MIN_LECTURA = 0;
const float TDS_MAX_LECTURA = 1023;
const float TDS_MIN_PPM     = 10;
const float TDS_MAX_PPM     = 1000;

// MQ-135: valor de referencia en aire normal ≈ 100, con fuente de gas ≈ 214
// A 3.3V estos números son relativos, no ppm reales. Sirven para comparar,
// no para dar una concentración exacta.

FirebaseData   fbData;
FirebaseAuth   fbAuth;
FirebaseConfig fbConfig;

unsigned long ultimaLectura = 0;
const unsigned long INTERVALO = 30000; // 30 segundos

// ---------- Promedio con filtro de valores raros ----------
float leerPromedio(int pin, int muestras = 15) {
  float suma = 0;
  float valores[muestras];
  for (int i = 0; i < muestras; i++) {
    valores[i] = analogRead(pin);
    suma += valores[i];
    delay(20);
  }
  float promedio = suma / muestras;

  // descarta muestras que se alejan más de 30% del promedio y vuelve a promediar
  float sumaFiltrada = 0;
  int contadas = 0;
  for (int i = 0; i < muestras; i++) {
    if (abs(valores[i] - promedio) <= promedio * 0.30) {
      sumaFiltrada += valores[i];
      contadas++;
    }
  }
  return contadas > 0 ? sumaFiltrada / contadas : promedio;
}

String obtenerTimestamp() {
  time_t ahora = time(nullptr);
  struct tm* t = localtime(&ahora);
  char buf[25];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
  return String(buf);
}

void conectarWiFi() {
  Serial.print("Conectando a red 1");
  WiFi.begin(WIFI_SSID1, WIFI_PASSWORD1);
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nIntentando red 2...");
    WiFi.begin(WIFI_SSID2, WIFI_PASSWORD2);
    intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 20) {
      delay(500);
      Serial.print(".");
      intentos++;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado.");
  } else {
    Serial.println("\nNo se pudo conectar a ninguna red. Revisa tus credenciales.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(PIN_MODO, INPUT_PULLUP); // sin jumper = HIGH = modo aire

  conectarWiFi();

  // Hora real (zona horaria de México Central, UTC-6)
  configTime(-6 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Sincronizando hora");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" listo!");

  fbConfig.host = FIREBASE_HOST;
  fbConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&fbConfig, &fbAuth);
  Firebase.reconnectWiFi(true);

  Firebase.setString(fbData, "/sensor/estadoConexion", "conectado");
  Serial.println("Listo. Esperando ciclo de lectura...");
}

void loop() {
  if (millis() - ultimaLectura >= INTERVALO) {
    ultimaLectura = millis();

    bool modoAgua = (digitalRead(PIN_MODO) == LOW); // jumper puesto a G
    float lecturaCruda = leerPromedio(PIN_DATO);
    String timestamp = obtenerTimestamp();

    if (modoAgua) {
      float ppm = TDS_MIN_PPM + (lecturaCruda - TDS_MIN_LECTURA) *
                  (TDS_MAX_PPM - TDS_MIN_PPM) / (TDS_MAX_LECTURA - TDS_MIN_LECTURA);
      Firebase.setFloat(fbData, "/sensor/agua", ppm);
      Serial.print("[" + timestamp + "] MODO AGUA | ppm: ");
      Serial.println(ppm);
    } else {
      Firebase.setFloat(fbData, "/sensor/aire", lecturaCruda);
      Serial.print("[" + timestamp + "] MODO AIRE | valor relativo: ");
      Serial.println(lecturaCruda);
    }

    Firebase.setString(fbData, "/sensor/timestamp", timestamp);
    Firebase.setString(fbData, "/sensor/uptime", String(millis() / 1000));
  }
}
