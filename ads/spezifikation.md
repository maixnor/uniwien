Container ADS_set (up)
template <
  typename Key,
  size_t N = /* implementation-defined */
> class ADS_set;
 
ADS_set ist ein Container, der Elemente speichert, die über einen Schlüssel identifiziert werden. Key ist der Typ des Schlüssels und zugleich auch der Typ des Elements. D.h., das gesamte gespeicherte Element dient als Schlüssel. ADS_set stellt eine Vereinfachung und Verallgemeinerung der STL-Typen «std::set» und «std::unordered_set» dar. 
 
Jeder Schlüssel kann in einem Container höchstens ein Mal auftreten (Mengeneigenschaft). Es kann also in keinem Container zwei Elemente mit demselben Schlüssel geben. Soweit nicht bei einzelnen Methoden/Funktionen anders festgelegt, wird das versuchte Einfügen von bereits vorhandenen Werten stillschweigend ignoriert. Dasselbe gilt, wenn versucht wird, nicht vorhandene Werte zu löschen. 
 
Im Container werden grundsätzlich immer Kopien der an die entsprechenden Methoden übergebenen Elemente gespeichert. Der Container ist in der Folge für die ordnungsgemäße Zerstörung dieser Elemente verantwortlich. 
 
Zur Realisierung ist eine der folgenden Datenstrukturen heranzuziehen: 

    Linear Hashing (50 Punkte) 

Die Datenstrukturen sind entsprechend den Spezifikationen aus dem Vortrag (siehe Folien) zu implementieren. Abweichungen bitte vorab mit der LV-Leitung (im Forum) klären. 
 
Der Vollständigkeit halber wird darauf hingewiesen, dass die Datenstrukturen und Algorithmen selbst zu implementieren sind und nicht auf vorhandene Implementierungen (auch nicht in Standard-Bibliotheken) zurückgegriffen werden darf. Für die Realisierung der Datenstruktur sind auch keine Datentypen aus der STL zulässig. Wenn Sie verfügbare Datenstrukturen aus der STL als temporäre Hilfsdatenstrukturen einsetzen wollen, dann fragen Sie bitte im Zweifelsfall vorher bei der LV-Leitung nach (im Forum).  
 
Die Datenstrukturen müssen - von Systembeschränkungen abgesehen - prinzipiell beliebig viele Werte aufnehmen können. Wenn bei Datenstrukturen mit fixer Größe (zB. statische Hashverfahren) kein Platz mehr vorhanden ist oder die vordefinierte maximale Belegung überschritten wird, so ist die Datenstruktur entsprechend zu vergrößern. Bei statischen Hashverfahren also zB.: neue (größere) Tabelle anlegen und Werte neu hashen. Die Datenstruktur soll mit der Anzahl der gespeicherten Werte "wachsen".  
 
Damit Elemente des Typs Key in einem ADS_set gespeichert werden können, muss Key die folgenden Eigenschaften haben: 

    Erzeugung von Objekten ohne Initialisierung ist möglich (bei Klassen: Default-Konstruktor). Achtung: Wenn der Elementdatentyp ein primitiver Datentyp (keine Klasse) ist, dann sind nicht initialisierte Elemente unter Umständen in einem nicht definierten Zustand. Die Verwendung nicht initialisierter Elemente (zB in Vergleichen) ist daher verboten.[16] 
    Erzeugung von Objekten mit Initialisierung und Übergabe by value ist möglich (bei Klassen: Kopier-Konstruktor) 
    Zuweisung ist möglich (bei Klassen: Kopierzuweisungsoperator) 
    Vergleich mittels std::less<Key> (siehe «std::less») ist möglich (Ordnungsrelation für B+-Baum).  
    Vergleich mittels std::equal_to<Key> (siehe «std::equal_to») ist möglich (Äquivalenzrelation für Hashverfahren)[3].  
    Berechnung eines Hashwertes mittels std::hash<Key> (siehe «std::hash») ist möglich (für Hashverfahren). 

Darüber hinausgehende Eigenschaften von Key dürfen nicht vorausgesetzt werden. Andere als die oben genannten Operationen sind für die im Container gespeicherten Elemente vom Typ Key daher nicht zulässig! 
 
N ist ein datenstrukturspezifischer Templateparameter[1][4], konkret 

    k (Ordnung) beim B+-Baum 
    die Anfangsgröße der Hashtabelle bei statischen Hashverfahren (Separate Chaining, Coalesced Chaining). 
    die Bucketgröße bei dynamischen Hashverfahren (Extendible Hashing, Linear Hashing) 

Weitere datenstrukturspezifische Parameter können bei Bedarf als Template-Parameter oder als Konstruktor-Parameter realisiert werden. Es muss für alle Template-Parameter (mit Ausnahme von Key) Defaultwerte geben, die für alle Parameter sinnvolle Werte vorgeben. Es empfiehlt sich unbedingt, die Datenstruktur mit unterschiedlichen Parameterwerten zu testen. Die Datenstruktur muss mit allen (prinzipiell sinnvollen) Parameterwerten funktionieren!  
 
Die im Container gespeicherten Elemente dürfen nicht verändert werden (zB über Iteratoren), da dadurch die Konsistenz des Containers zerstört werden kann. 
 
Die gesamte Implementierung muss sich in einer Datei namens ADS_set.h befinden. Implementierungssprache ist C++17. 
Member types (up)
using value_type = Key;
using key_type = Key;
using reference = value_type &;
using const_reference = const value_type &;
using size_type = size_t;
using difference_type = std::ptrdiff_t;
using const_iterator = /* constant ForwardIterator */
using iterator = const_iterator;
using key_compare = std::less<key_type>;   // B+-Tree
using key_equal = std::equal_to<key_type>; // Hashing
using hasher = std::hash<key_type>;        // Hashing
Member functions (up)
Konstruktoren (up)
ADS_set();
 
[Phase 1] Default-Konstruktor. Erzeugt einen leeren Container. 
Komplexität: O(1) 
 
ADS_set(std::initializer_list<key_type> ilist);
 
[Phase 1] Initializer-List-Konstruktor. Erzeugt einen Container, der die Elemente aus ilist enthält. Die Elemente werden in der in ilist vorgegebenen Reihenfolge eingefügt. 
Komplexität: B+-Baum: O(ilist_size * log ilist_size), Hashing: O(ilist_size) 
 
template<typename InputIt> ADS_set(InputIt first, InputIt last);
 
[Phase 1] Range-Konstruktor. Erzeugt einen Container, der die Elemente aus dem Bereich [first, last[ enthält. Die Elemente werden in der vorgegebenen Reihenfolge (beginnend mit first) eingefügt. 
Komplexität: B+-Baum: O(range_size * log range_size), Hashing: O(range_size) 
 
ADS_set(const ADS_set &other);
 
Kopierkonstruktor. Erzeugt einen Container, der dieselben Elemente wie der Container other enthält. 
Komplexität: B+-Baum: O(other_size * log other_size)[2], Hashing: O(other_size) 
Destruktor (up)
~ADS_set();
 
Die Destruktoren der gespeicherten Elemente werden aufgerufen und der benützte Speicherplatz vollständig freigegeben. 
Komplexität: O(size) 
Zuweisungsoperatoren (up)
ADS_set &operator=(const ADS_set &other);
 
Kopierzuweisungsoperator. Der Inhalt des Containers wird durch den Inhalt von other ersetzt. 
Rückgabewert: Referenz auf *this 
Komplexität: B+-Baum O(size + other_size * log other_size)[2], Hashing: O(size + other_size) 
 
ADS_set &operator=(std::initializer_list<key_type> ilist)
 
Initializer-List-Zuweisungsoperator. Der Inhalt des Containers wird durch die Elemente aus ilist ersetzt. Die Elemente werden in der in ilist vorgegebenen Reihenfolge eingefügt. 
Rückgabewert: Referenz auf *this 
Komplexität: B+-Baum O(size + ilist_size * log ilist_size), Hashing: O(size + ilist_size) 
Größe (up)
size_type size() const;
 
[Phase 1]  
Rückgabewert: Anzahl der im Container gespeicherten Elemente 
Komplexität: O(1) 
 
bool empty() const;
 
[Phase 1]  
Rückgabewert: true, wenn size()==0, false sonst. 
Komplexität: O(1) 
Einfügen (up)
void insert(std::initializer_list<key_type> ilist);
 
[Phase 1] Fügt die Elemente aus ilist ein. Die Elemente werden in der in ilist vorgegebenen Reihenfolge eingefügt. 
Komplexität: B+-Baum: O(ilist_size * log (ilist_size + size)), Hashing: O(ilist_size) 
 
std::pair<iterator,bool> insert(const key_type &key);
 
Fügt key ein. 
Rückgabewert: Ein std::pair, bestehend aus einem iterator und einem bool.  
iterator: zeigt auf das eingefügte Element, falls ein Element eingefügt wurde, bzw. auf das bereits vorhandene Element mit demselben key, falls kein Element eingefügt wurde.  
bool: true, falls eine Element eingefügt wurde, false sonst. 
Komplexität: B+-Baum: O(log size), Hashing O(1) 
 
template<typename InputIt> void insert(InputIt first, InputIt last);
 
[Phase 1] Fügt die Elemente aus dem Bereich [first, last[ in der vorgegebenen Reihenfolge (beginnend mit first) ein. 
Komplexität: B+-Baum: O(range_size * log (range_size + size)), Hashing: O(range_size) 
Löschen (up)
void clear();
 
Entfernt alle Elemente aus dem Container. 
Komplexität: O(size) 
 
size_type erase(const key_type &key);
 
Entfernt das Element key. 
Rückgabewert: Anzahl der gelöschten Elemente (0 oder 1). 
Komplexität: B+-Baum: O(log size), Hashing: O(1) 
 
Bei den dynamischen Hashverfahren ist es zur Vereinfachung zulässig, nur die jeweils betroffenen Werte aus den Buckets zu entfernen (kein Verschmelzen etc. nötig). Die Datenstruktur muss natürlich funktionsfähig bleiben. Bei den statischen Hashverfahren ist es nicht nötig, eine vergrößerte Tabelle wieder zu verkleinern. 
Sonstige Modifikationen (up)
void swap(ADS_set &other);
 
Vertauscht die Elemente des Containers mit den Elementen des Containers other. 
Komplexität: O(1) 
Suchen (up)
size_type count(const key_type &key) const;
 
[Phase 1]  
Rückgabewert: Die Anzahl der Elemente im Container mit Schlüssel key (0 oder 1). 
Komplexität: B+-Baum O(log size)), Hashing O(1) 
 
iterator find(const key_type &key) const;
 
Rückgabewert: ein Iterator auf das Element mit dem Schlüssel key bzw. der End-Iterator (siehe end()), falls kein solches Element vorhanden ist. 
Komplexität: B+-Baum O(log size), Hashing O(1) 
Iteratoren (up)
const_iterator begin() const;
 
Liefert einen Iterator auf das erste Element im Container. 
Rückgabewert: Iterator auf des erste Element bzw. der End-Iterator, falls der Container leer ist. 
 
const_iterator end() const;
 
Liefert einen Iterator auf das (virtuelle) Element nach dem letzten Element im Container ("End-Iterator"). 
Rückgabewert: End-Iterator 
Debugging (up)
void dump(std::ostream &o = std::cerr) const;
 
[Phase 1][4] Ausgabe des Containerinhalts auf den Stream o. Es gibt keine Vorgabe zur Funktionalität von dump(), d.h. es ist nicht vorgeschrieben, was die Methode in den Stream schreibt. Es ist auch zulässig, dass die Methode nichts ausgibt. Es empfiehlt sich aber, zumindest alle enthaltenen Elemente auszugeben. Beim Testen kann es darüber hinaus hilfreich sein, wenn die Ausgabe in irgendeiner Form auch den Zustand der Datenstruktur darstellt.  
 
Der Unit-Test gibt bei Fehlern den Inhalt des Containers mit Hilfe dieser Methode aus, um die Fehlersuche zu erleichtern. Wenn die Ausgabe allzu umfangreich ist, kann diese beim Unit-Test allerdings gekürzt werden. Es darf davon ausgegangen werden, dass der Container beim Unit-Test nur mit Elementdatentypen (key_type) instanziert wird, die den Ausgabeoperator (<<) unterstützen. 
Non-member functions (up)
template <typename Key, size_t N>
bool operator==(const ADS_set<Key,N> &lhs, const ADS_set<Key,N> &rhs);
 
Überprüft, ob die Inhalte zweier Container gleich sind. Die Inhalte sind genau dann gleich, wenn die Container gleich groß sind und es zu jedem Element in lhs ein Element in rhs mit demseben Schlüssel gibt.[5] 
Rückgabewert: true, wenn die Containerinhalte gleich sind, false sonst. 
Komplexität: O(size). 
 
template <typename Key, size_t N>
bool operator!=(const ADS_set<Key,N> &lhs, const ADS_set<Key,N> &rhs);
 
Überprüft, ob die Inhalte zweier Container ungleich sind. Die Inhalte sind genau dann ungleich, wenn sie nicht gleich sind.[5] 
Rückgabewert: false, wenn die Containerinhalte gleich sind, true sonst. 
Komplexität: O(size). 
 
template <typename Key, size_t N>
void swap(ADS_set<Key,N> &lhs, ADS_set<Key,N> &rhs);
 
Non-member-swap() zur Erfüllung des «Swappable»-Konzepts. Ruft lhs.swap(rhs) auf (siehe oben). 
Komplexität: O(1) 
 
Iterator für ADS_set (up)
Für ADS_set ist eine Iterator-Klasse zu implementieren, die die Spezifikation eines konstanten «ForwardIterator»s erfüllt. 
 
Zur Vereinfachung ist es zulässig, dass jede Modifikation des Containers alle existierenden Iteratoren invalidiert. 
Es ist nicht erforderlich, die Iterator-Methoden/Funktionen gegen unzulässige Verwendung abzusichern. 
 
Die im Container gespeicherten Elemente müssen vom Iterator in keiner bestimmten Reihenfolge besucht werden. Die Elemente desselben Containers werden aber von allen Iteratoren in derselben Reihenfolge besucht, solange der Inhalt des Containers nicht modifiziert wird. 
 
Sonstiges (up)
Speicherverwaltung (up)
Für die Verwaltung des dynamischen Speichers sind die entsprechenden C++-Mechanismen (new, delete) einzusetzen. Die Verwendung einschlägiger C-Funktionen (malloc() etc), system calls (sbrk() etc) oder sonstiger Mechanismen ist nicht zulässig. 
Fehlersuche mit "Kontrollausgaben" (Instrumentierung) (up)
Damit für ein Programm, das die Container-Klasse benutzt, keine unerwarteten bzw. unkontrollierbaren Effekte auftreten, dürfen die Methoden von ADS_set neben dem definierten Verhalten keine Seiteneffekte produzieren. Daher ist auch jede Form von Ausgaben auf (vordefinierte) Streams (zB cout, cerr, etc) verboten (dies wird zb auch vom Unit-Test überprüft; eine Ausnahme ist natürlich die Methode dump(), die in den als Parameter übergebenen ostream - und nur in diesen - schreiben darf). 
 
Allerdings werden als einfache Form der Fehlersuche gerne Kontrollausgaben ("tracing") in Funktionen eingebaut, um bei Problemen die Funktionsweise eines bestimmten Programmstücks anhand der Ausgaben nachvollziehen zu können. Falls in Methoden der implementierten Klasse tracing-Ausgaben benötigt werden, dann verwenden Sie einen "Schalter" zum Ein- und Ausschalten der Ausgaben. 
 
Zwei simple Möglichkeiten werden im folgenden beschrieben. 
Variante 1 - Präprozessor-Schalter (up)
#if defined(DEBUG)
  std::cerr << "jetzt bin ich hier\n";
#endif
 
Beim Compileraufruf kann die Ausgabe dann mittels -DDEBUG aktiviert werden, zB: 
 
g++ -DDEBUG -Wall -O3 --std=C++17 --pedantic-errors MeinTestprogramm.cpp ...
 
Ist DEBUG hingegen nicht definiert (zB beim Unit Test), so entfernt der Präprozessor die Zeilen von #if defined(DEBUG) bis zum zugehörigen #endif, der eigentliche C++-Compiler bekommt diesen Code gar nicht mehr zu Gesicht und er ist daher auch im erzeugten exekutierbaren Programm nicht enthalten.  
 
Achtung: Es ist daher darauf zu achten, dass das Programm sowohl mit als auch ohne die jeweiligen Zeilen syntaktisch richtig ist und durch das Ein- oder Ausblenden der Zeilen die sonstige Funktionalität des Programms nicht verändert wird. 
 
Schlechtes Beispiel (nicht nachmachen): 
 
das folgende Programmstück kommt uns verdächtig vor 
 
int sum {0}, i {1};
for (; i < 10; ++i)
  sum += i;
 
und wir bauen daher eine Kontroll-Ausgabe ein: 
 
int sum {0}, i {1};
for (; i < 10; ++i)
#if defined(DEBUG)
  std::cerr << "jetzt bin ich in der Schleife, die Stimmung ist gut und i = " << i << std::endl;
#endif
  sum += i;
 
Was geht hier schief? Was müssen wir ändern? 
 
Speziell für tracing-Ausgaben kann auch ein eigenes Makro definiert werden 
 
#if defined(DEBUG)
#  define TRACE(x) std::cerr << x << std::endl;
#else
#  define TRACE(x)
#endif
 
das dann so verwendet werden kann: 
 
TRACE( "jetzt bin ich in der Schleife, die Stimmung ist gut und i = " << i )
 
Der Ausdruck innerhalb der Klammer wird - je nachdem ob DEBUG definiert ist - durch das Makro zu einer Anweisung (inklusive Strichpunkt) ergänzt oder restlos entfernt (die Warnung von oben gilt also auch hier). 
Variante 2 - Instanzvariable als Schalter (up)
In der Klasse wird eine Instanzvariable bool debug definiert, die Verwendung in den Methoden der Klasse sieht dann recht ähnlich aus (funktioniert aber völlig anders):  
 
if (debug) std::cout << "jetzt bin ich weg\n";
 
Wenn die Instanzvariable debug auf true gesetzt wird (zb durch einen speziellen Konstruktor oder eine eigene set-Methode), dann erscheinen die Ausgaben, andernfalls (zb beim Unit Test) nicht. Denkbar wäre auch eine eigene Methode für Kontrollausgaben, die vor der Ausgabe debug überprüft, oder sogar ein eigener Stream, der ein- oder ausgeschaltet werden kann. 
 
Da aber in jedem Fall zumindest der Zustand des Schalters debug überprüft werden muss, hat diese Variante leichte Nachteile bei der Laufzeit. 
Kontrollausgaben im Unit-Test (up)
Der Unit-Test ist keine Entwicklungsumgebung und daher auch nicht für Debugging/Fehlersuche gedacht, auch nicht mittels Kontrollausgaben. Im begrenzten(!) Umfang kann diese Methode aber, wenn alles andere nicht klappen will, auch hier eingesetzt werden. Vor allem bei der Projektabschlussklausur, wo keine Entwicklungsumgebung zur Verfügung steht, kann das hilfreich sein. Die Begrenzung betrifft den erlaubten Umfang der Ausgabe, darüber hinausgehende Ausgaben werden abgeschnitten. 
 
Wenn auf std::cout oder std::cerr ausgegeben wird, wird der Unit-Test jedenfalls mit einem Fehler beendet. Die Ausgaben werden aber bis zum erlaubten Umfang gemeinsam mit der Fehlermeldung ausgegeben, und das ist ja schließlich das Ziel der Aktion. 
 
Variante 1 kann für den Unit-Test in ADS_set.h mittels 
 
#define DEBUG
 
aktiviert werden, Variante 2 durch Defaultwert true für die Instanzvariable debug. 

1
    Die Anfangsgröße der statischen Hashtabellen wird man in der Praxis kaum über einen Template-Parameter steuern, da dies keine Vorteile aber durchaus Nachteile mit sich bringt (bei std::unordered_set kann die Startgröße zB über einen Konstruktor-Parameter gesteuert werden). Dieser Templateparameter ist daher der Analogie zu den anderen Themen geschuldet. Auch bei den anderen Verfahren würde man diesen Wert in der Praxis eher nicht als Templateparameter realisieren. Da dieser Wert aber einerseits zu Testzwecken beim Erzeugen der Container konfigurierbar sein soll, und andererseits bei den dynamischen Hasverfahren und beim B+-Baum die Datenstruktur mit Hilfe des Template-Parameters (der ja im Template constexpr ist) zum Teil stark vereinfacht werden kann, haben wir uns für diese Variante entschieden.

2
    Eine bessere Laufzeitordnung ist erreichbar, aber nicht verpflichtend zu implementieren.

3
    Zur Erhöhung des Komfortfaktors ist die Verwendung von std::equal_to auch beim B+-Baum zulässig. In std::set wird jedoch keine Äquivalenzrelation vorausgesetzt. In std::set gelten zwei Schlüssel a und b sinngemäß dann als äquivalent, wenn gilt: !key_compare{}(a, b) && !key_compare{}(b, a).

4
    Dies ist eine Abweichung von der STL für die speziellen Zwecke dieser Lehrveranstaltung.

5
    Die STL setzt für diese Operation voraus, dass key_type die Anforderungen von «EqualityComparable» erfüllt (d.h. im wesentlichen, dass der operator == für key_type definiert sein muss. Wir tun das nicht und setzen aus Konsistenzgründen auch hier auf std::equal_to.

16
    Siehe auch undefined argument unter Beliebte Fragen und Fehler

17
    Die Implementierung des B+-Baum ist im Vergleich zu den anderen zur Wahl stehenden Datenstrukturen unverhältnismäßig aufwändig, schon allein vom Codeumfang her. Unter anderem ist beim Löschen auch das Verschmelzen unterbelegter Knoten zu implementieren, da andernfalls die B+-Baum-Eigenschaft nicht mehr erfüllt ist. Dieses Thema wird daher nur Studierenden mit Programmiererfahrung und Spass am Implementieren empfohlen.

Phase 1
    Die Implementierung dieser Methode/Funktion ist Bestandteil der 1. Projektphase.