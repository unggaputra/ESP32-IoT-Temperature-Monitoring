# UAP-PirantiCerdas
An Internet of Things (IoT)-based temperature monitoring and control system for a chick brooder, utilizing an ESP32 microcontroller and a DHT22 sensor. The system is integrated with the Blynk application for remote monitoring and the configuration of temperature thresholds, while InfluxDB Cloud is used for storing sensor data.
--
Sistem pemantauan dan pengendalian suhu kandang anak ayam berbasis Internet of Things (IoT) menggunakan ESP32 dan sensor DHT22. Sistem ini terintegrasi dengan aplikasi Blynk untuk pemantauan jarak jauh dan pengaturan ambang batas suhu, serta InfluxDB Cloud untuk penyimpanan data sensor.

## Deskripsi
Proyek ini merupakan pengembangan alat penghangat kandang anak ayam (chick brooder) yang memanfaatkan ESP32 sebagai mikrokontroler, DHT22 sebagai sensor suhu dan kelembapan, serta modul relay untuk mengendalikan penghangat secara otomatis.

Sistem dilengkapi dengan aplikasi Blynk yang memungkinkan peternak memantau kondisi kandang dan mengatur batas bawah serta batas atas suhu melalui perangkat yang terhubung ke internet. InfluxDB Cloud digunakan sebagai media penyimpanan data sensor untuk mendukung pemantauan kondisi kandang.

## Permasalahan
Anak ayam berumur di bawah 14 hari masih memiliki kemampuan termoregulasi yang belum berkembang secara optimal sehingga membutuhkan suhu lingkungan yang sesuai selama masa brooding.

Kondisi kandang yang terlalu dingin dapat menyebabkan anak ayam bergerombol dan mengurangi aktivitas makan serta minum. Sebaliknya, suhu yang terlalu tinggi juga dapat mengganggu kenyamanan dan pertumbuhan anak ayam. Oleh karena itu, pemantauan dan pengendalian suhu kandang menjadi salah satu aspek penting dalam pemeliharaan anak ayam.

Sebagai acuan awal, kebutuhan suhu dan kelembapan selama masa brooding dapat disesuaikan dengan umur ayam, kondisi lingkungan, dan pedoman pemeliharaan yang digunakan.

| Umur anak ayam | Acuan suhu |
| :--- | :---: | ---: |
| 0–7 hari | 30–33 °C |
| 8–14 hari | 27–29 °C |

Kelembapan relatif yang digunakan sebagai acuan dalam proyek ini adalah 60–70%. Nilai tersebut perlu disesuaikan dengan kondisi aktual kandang dan panduan pemeliharaan ayam yang relevan

## Komponen dan Teknologi
- ESP32: Mikrokontroler untuk menjalankan logika sistem dan konektivitas Wi-Fi.
- DHT22: Sensor untuk mengukur suhu dan kelembapan kandang.
- Modul relay: Sakelar elektronik untuk mengendalikan penghangat berdasarkan ambang batas suhu.
- Blynk: Platform untuk pemantauan jarak jauh dan pengaturan ambang batas suhu.
- InfluxDB Cloud: Database untuk menyimpan data sensor dan mendukung analisis historis.

## Alur Kerja Sistem

![Alt text](https://github.com/unggaputra/UAP-PirantiCerdas/blob/main/uploads/Flowchart%20sistem%20IoT.jpg) 

Sistem membaca suhu dan kelembapan kandang menggunakan sensor DHT22. Data sensor digunakan oleh ESP32 untuk memperbarui informasi monitoring pada aplikasi Blynk dan, sesuai implementasi program, dikirimkan ke InfluxDB Cloud.

Pengendalian penghangat dilakukan berdasarkan ambang batas suhu yang dapat diatur melalui aplikasi Blynk. Relay digunakan untuk mengendalikan aliran listrik ke perangkat penghangat sesuai logika kontrol yang diprogram.

[![Alt_](https://github.com/unggaputra/ESP32-IoT-Temperature-Monitoring/blob/main/uploads/Alur%20kerja%20sistem.jpg)

## Tampilan Aplikasi Blynk
Aplikasi Blynk menyediakan antarmuka untuk memantau suhu dan kelembapan kandang dari jarak jauh. Pengguna juga dapat mengatur batas bawah dan batas atas suhu untuk menyesuaikan pengendalian penghangat dengan kebutuhan anak ayam.

<img src="https://github.com/unggaputra/UAP-PirantiCerdas/blob/main/uploads/Tampilan%20Blynk.jpg" width="300" />

## Perangkat IOT
Berikut merupakan dokumentasi perangkat keras yang digunakan dalam proyek ini.


[![Alt_](https://github.com/unggaputra/ESP32-IoT-Temperature-Monitoring/blob/main/uploads/Perangkat%20IOT.jpg)

## Teknologi yang Digunakan

C++ · ESP32 · DHT22 · Blynk IoT · InfluxDB Cloud · Wi-Fi
