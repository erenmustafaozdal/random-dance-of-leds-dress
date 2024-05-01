/* Arduino Lilypad ile elbise üzerindeki ledleri rastgele yakma projesi

MALZEMELER
- Arduino Lilypad Atmega32U4 Geliştirme Kartı
- LilyPad RGB - Üç Renk - LED (istenilen sayıda)

Yazar: Eren Mustafa Özdal [eren.060737@gmail.com] 
Tarih: 19/04/24
Lisans: (MIT Lisansı) - Bu kodu kullanmaktan ve bakımını yapmaktan çekinmeyin.
Eğer duygularınızı içtenlikle ifade ederseniz minnettar olurum.
*/

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 4  // led sayısı
#define LED_PIN 9    // ledlere verinin aktarılacağı dijital pin  numarası

// Burası görünecek favori renklerinizi koyabileceğiniz yer!
// sadece yeni {nnn, nnn, nnn}, çizgileri ekleyin. Rastgele seçilecekler
uint8_t myFavoriteColors[][3] = {
  // R   G   B
  { 255, 49, 49 },    // parlak kırmızı
  { 255, 102, 196 },  // pembe
  { 140, 82, 255 },   // mor
  { 93, 226, 231 },   // turkuaz
  { 0, 128, 255 },    // mavi
  { 0, 191, 99 },     // yeşil
  { 255, 222, 89 },   // sarı
  { 255, 145, 77 },   // turuncu
  { 255, 255, 255 },  // beyaz
};

// favori renklerin sayısını belirleyelim
#define FAVCOLORS sizeof(myFavoriteColors) / 3

// Parametre 1 = şeritteki piksel led sayısı
// Parametre 2 = pin numarası (çoğu geçerlidir)
// Parametre 3 = piksel tipi bayrakları, gerektiği gibi toplayın:
// NEO_RGB Pikseller RGB bit akışı için kablolanmıştır
// NEO_GRB Pikseller GRB bit akışı için kablolanmıştır
// NEO_KHZ400 400 KHz bit akışı (örn. FLORA pikselleri)
// NEO_KHZ800 800 KHz bit akışı (örn. Yüksek Yoğunluklu LED şerit)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);  // 9600 seri port (boud rate) ile Arduino’nun haberleşmesi başlatılıyor

  strip.begin();            // NeoPixel şerit nesnesini başlatalım (GEREKLİ)
  strip.show();             // Tüm pikselleri en kısa sürede KAPATALIM
  strip.setBrightness(50);  // PARLAKLIĞI ayarlayalım (maks = 255)
}

void loop() {

  // Biraz bekleyelim
  delay(100);
  
  flashRandom(5, 1);
  flashRandom(5, 3);
  flashRandom(5, 2);
}

void flashRandom(int wait, uint8_t howmany) {
  // 'wait' parametresi: Her bir adımda ne kadar beklenmesi gerektiğini belirtir (milisaniye cinsinden)
  // 'howmany' parametresi: Aynı anda yanacak LED sayısını belirtir

  for (uint16_t i = 0; i < howmany; i++) {
    // Belirtilen sayıda LED için döngü başlatılır

    // Rastgele bir favori renk seçilir
    int c = random(FAVCOLORS);
    int red = myFavoriteColors[c][0];
    int green = myFavoriteColors[c][1];
    int blue = myFavoriteColors[c][2];

    // Favori renkten rastgele bir piksel seçilir
    int j = random(strip.numPixels());
    // Seçilen piksel seri porta yazdırılır (gerekirse hata ayıklama için)
    Serial.print("Yanan Led Numarası: ");
    Serial.println(j);

    // Seçilen pikselin belirli bir sürede belirtilen renge 'fade in' (belirginleştirme) işlemi yapılır
    for (int x = 0; x < 5; x++) {
      int r = red * (x + 1);
      r /= 5;
      int g = green * (x + 1);
      g /= 5;
      int b = blue * (x + 1);
      b /= 5;

      strip.setPixelColor(j, strip.Color(r, g, b));  // Seçilen pikselin rengi ayarlanır
      strip.show();                                  // Ayarlanan rengi LED'lere gönderir
      delay(wait);                                   // Belirtilen süre boyunca bekler
    }

    // Seçilen pikselin belirli bir sürede belirtilen renge 'fade out' (karanlıklaştırma) işlemi yapılır
    for (int x = 5; x >= 0; x--) {
      int r = red * x;
      r /= 5;
      int g = green * x;
      g /= 5;
      int b = blue * x;
      b /= 5;

      strip.setPixelColor(j, strip.Color(r, g, b));  // Seçilen pikselin rengi ayarlanır
      strip.show();                                  // Ayarlanan rengi LED'lere gönderir
      delay(wait);                                   // Belirtilen süre boyunca bekler
    }
  }
  // İşlem tamamlandığında LED'ler kapalı olur (0'a karartılır)
}
