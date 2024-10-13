-CSV dosyasını json türüne çevirmek amacıyla üretilmiştir.
-Terminalde exe dosyasını açtıktan sonra dosya konumlarını belirtip
girdi ve çıktı dosyalarını, header durumunu belirtip çalıştırabilirsiniz.
-Aşağıda örnek kullanım vardır. 

   C:\Users\berkea\Documents ./untitled.exe abc.csv def.json

Kullanılan Değişkenler:
1.ch  : ch karakter karakter okumak için
2.dizi  : virgüle kadar okuma sağlıyor
3.csvHeader: header-on için headerları tutan char pointer arrayi
4.k :  headerların ismi için index değişkeni
5.yeniObjeEklenmeKontrol :her obje başladığında { kullanımı için kontrol değişkeni
6.headerOFFDurumu : csv dosyasında header ın olup olmadığını kontrol ediyor
7.isint: integer olup olmadığını kontrol eden değişken
8.kolonSayi: kaç tane header tag olacağını belirler
