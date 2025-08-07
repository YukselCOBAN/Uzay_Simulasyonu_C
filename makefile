hepsi: derle calistir

derle:
	gcc -I ./include/ -c ./src/GlobalDegiskenler.c -o ./lib/GlobalDegiskenler.o
	gcc -I ./include/ -c ./src/DosyaOkuma.c -o ./lib/DosyaOkuma.o
	gcc -I ./include/ -c ./src/Kisi.c -o ./lib/Kisi.o
	gcc -I ./include/ -c ./src/UzayAraci.c -o ./lib/UzayAraci.o
	gcc -I ./include/ -c ./src/Gezegen.c -o ./lib/Gezegen.o
	gcc -I ./include/ -c ./src/Zaman.c -o ./lib/Zaman.o
	gcc -I ./include/ -c ./src/KayacGezegen.c -o ./lib/KayacGezegen.o
	gcc -I ./include/ -c ./src/CuceGezegen.c -o ./lib/CuceGezegen.o
	gcc -I ./include/ -c ./src/GazDeviGezegen.c -o ./lib/GazDeviGezegen.o
	gcc -I ./include/ -c ./src/BuzDeviGezegen.c -o ./lib/BuzDeviGezegen.o
	gcc -I ./include/ ./lib/DosyaOkuma.o ./lib/Kisi.o ./lib/UzayAraci.o ./lib/Gezegen.o ./lib/Zaman.o ./lib/KayacGezegen.o ./lib/CuceGezegen.o ./lib/GazDeviGezegen.o ./lib/BuzDeviGezegen.o ./lib/GlobalDegiskenler.o ./src/Simulasyon.c -o ./bin/Simulasyon

calistir:
	./bin/Simulasyon
