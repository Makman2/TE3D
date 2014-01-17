#include "ascii_converter.h"

#include <stdlib.h>


// Converts vectors to an ASCII-art-representation and writes them to the target TE3D_Surface.
bool TE3D_ASCII_Convert(struct TE3D_Vector4f vectors[], int count, struct TE3D_Surface* target, void* indices, enum TE3D_VectorFormat format, float* zBuffer)
{
	// If z-Buffer is NULL, create own one.
	if (!zBuffer)
		zBuffer = (float*)malloc(target->Width * target->Height);
		
	// -- Fragt ab, welches Format für die Verbindung der Vektoren gewählt wurde.
	switch (format)
	{
		// -- Wir wollen keine Linien oder Dreiecke zeichnen, nur Punkte:
		case TE3D_VECTORFORMAT_POINTS:
			// No connections, just draw the vector points.
			// But if indices is not NULL, something may went not right, so exit function.
			if (indices != NULL)
				return false;
			
			// -- Hier gehts weiter mit dem Zeichnen. Die if-Bedingung von davor ist nur dazu da, um zu überprüfen ob indices nicht gesetzt wurde,
			// -- ansonsten ist wohl im Funktionsaufruf was schiefgegangen. Aber falls nicht, sind wir eben an dieser Stelle.
			// -- Hier werden die Vektoren in Zeichen umgewandelt, und in diesem fall (also case ...POINTS) werden sie in Punkte umgezeichnet.
			// -- Gezeichnet wird in 'target'. Die Definition der Struktur TE3D_Surface ist in graphics.h zu finden.
			// -- TE3D_Surface enthält Breite (Width) und Höhe (Height) und ein Array von TE3D_ColorChar's, die eben die Farbe und den jeweiligen Char enthalten.
			// -- Also im Prinzip ein Pixel vom Terminalbild. Dieses Array gilt es zu bauen aus den eingegebenen Vektoren (vectors).
			// -- Den Speicher für das TE3D_ColorChar Array von der Surface brauchst du nicht mit malloc zu initialisieren, das sollte der Benutzer der Funktion
			// -- vorher selber machen.
			// -- Zur Erinnerung: Die umzuwandelnden Vektoren nimmst du aus dem Parameter vectors[].
			
			break;
			
		// -- Hier wollen wir Linien zwischen den Vektoren zeichnen. Dazu sollte sich ein Array vom Typ TE3D_VectorIndex2 in 'indices' befinden.
		case TE3D_VECTORFORMAT_LINES:
			// Line connections.
			// If indices is NULL the function must exit.
			if (!indices)
				return false;
			
			// -- Also hier dasselbe mit dem Zeichnen, nur eben keine Punkte sondern Linien. Jetzt ist 'indices' nicht mehr NULL, sondern ein Zeiger auf
			// -- ein Array von integern (also Ganzzahlen), die die Indexe beschreiben. D.h. Die Indexe sagen dir, welche Linien aus dem vectors-Array
			// -- verbunden werden sollen.
			
			break;
			
		case TE3D_VECTORFORMAT_TRIANGLES:
			// Triangle connections.
			// If indices is again NULL the function must also exit.
			if (!indices)
				return false;
				
			// -- Dasselbe hier wie oben nur jetzt mit Dreiecken malen und indices ist vom Typ Array von TE3D_VectorIndex3.
				
			break;
	}
	
	// -- Wenn alles geklappt hat, 'true' zurückgeben.
	// -- PS: Alle deutschen Kommentare (mit -- nach jedem //) werden am Ende gelöscht wenn die Funktion fertig ist.
	return true;
}