# Computer Vision

Computer Vision Challenge

Gruppe: G10
Mitglieder:
Johann Brenner (ga78zan@mytum.de)
Michael Maas (ga96vur@mytum.de)
Daniel Milz (ga58huv@mytum.de)
Alexander Schmaus (ga96fin@mytum.de)

Das Programm um die Disparity-Map zu erhalten kann in den folgenden Wegen ausgeführt werden:

Man kann im Skript challenge.m in Zeile 21 eine Ordnerpfad übergeben, in welchem die Datein 'Im0.png', 'Im1.png' und 'disp0.pfm' liegen sollten.
Wenn dieser Pfad gesetzt ist, kann man das Skript challenge.m ausführen.
Sobald alle Funktionen abgearbeitet sind, werden in der Konsole die Werte für die Rotationsmatrix R und die Translationsmatrix T sowie das Peak Signal-To-Noise Ratio p in dB und die vergangene Zeit in elapsed_time angegeben.
Zudem wird die Disparity-Map in einem Plot dargestellt.

Alternativ kann man das Skript start_gui ausführen. Dadurch wird eine GUI gestartet.
Klickt man nun auf den Button "Select Folder", so startet ein UI mit der aktuellen Matlab Ordnerstruktur.
Nun ist es die Aufgabe des Nutzers, zu einem Ordner zu manövrieren, in welchem die Datein 'Im0.png', 'Im1.png' und 'disp0.pfm' liegen sollten.
Ist dies nicht der Fall, so wird der Nutzer gebeten, einen anderen Ordner auszuwählen.
Ist dies jedoch der Fall, dann werden die beiden Bilder angezeigt und es erscheint der Button "Compute Disparity-Map".
Klickt der Nutzer auf diesen Button, so wird, nachdem alle Funktionen abgearbeitet wurden, die Disparity-Map in die GUI geplottet sowie die Rotationsmatrix R, die Translationsmatrix T und das Peak Signal-To-Noise Ratio p in dB angezeigt.
