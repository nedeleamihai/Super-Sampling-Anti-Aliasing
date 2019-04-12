Part 1. Super Sampling Anti Aliasing

In homework.h am definit structura image cu campurile culoare, lungime, latime, maxval si un buffer care reprezinta pixeli imaginii.

In homework.c :

	Functia readInput va citi din fisierul de intrare culoarea(P5 sau P6), lungimea, latimea imaginii si bufferul de pixeli.
	Dupa citire toate acestea vor fi adaugate in structura image.
	Buferul cu pixeli va fi alocat cu LungimeImagine = width * height * numcolors.
	Numcolors initial este 1. Daca imaginea este color numcolors se va face 3.
	
	Functia writeData va crea o imagine redimensionata cu datele din structura image data ca parametru.
	
	Functia resize va calcula mai intai care este noua lungime si latime a imaginii redimensionate.
	Daca imaginea este color vom impartii buferul initial in trei bufere pentru cele 3 culori (red, green, blue).
	Apoi va fi apelata functia threadFunction de num_threads ori care va calcula noul buffer redimensionat.
	
	In threadFunction primele doua for-uri vor parcurge fiecare pozitie din bufferul final. Paralelizarea se va face pe linii.
	Dupa aceea vom folosi inca doua for uri (fiecare facand resize_factor pasi) care vor transforma resize_factor * resize_factor pixeli in unul singur.
	Daca imaginea este greyscale se vor aduna toti cei resize_factor * resize_factor pixeli si se va impartii rezultatul la resize_factor * resize_factor.
	Daca imaginea este color se vor aduna pixeli din cele trei bufere separat, iar cele trei rezultate se vor impartii la 16.
	Rezultatul/Rezultatele se va pune in buferul final.
	Pentru resize_factor = 3 se va inmultii fiecare pixel din buffer cu o valoare din GaussianKernel.
	Pentru a afla valoarea respectiva din GaussianKernel cu care trebuie inmultit pixelul luam coordonatele pixelului si facem modulo 3.
	In final threadFunction va forma buferul cu pixeli redimensionati.
	
	
Part 2. Micro renderer

	Functia initialize va pune in structura image datele pentru a forma imagine alba patratica.
	Fiecare valoare din buffer va avea valoarea 255(pixel alb).
	
	In functia render va vi apelate functia threadFunction de num_threads ori.
	threadFunction va desena o linie neagra in imagine conform ecuatiei −1∗x + 2∗y+ 0 = 0.
	Daca in imagine rezolutia este de 100 cm, atunci un pixel va avea 100 / rezolution.
	Coordonatele pixelului in imagine vor fi x = (float)j * LungimeBloc + LungimeBloc / 2, respectiv
						 y = 100 - (float)i * LungimeBloc - LungimeBloc / 2.
	Distanta de la pixel la dreapta se va calcula cu formula matematica abs((-1) * x + 2 * y) / sqrt(5).
	Daca distanta este mai mica de 3 centimetri, valoarea pixelul se va face 0 (pixel negru).
	
	Functia writeData va lua datele din structura image data ca parametru si va crea imaginea.
	
