package a12302260;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class Main {

	public static void main(String[] args) {
		System.out.println("Achtung: hier findet nur ein grober Funktionalitätscheck statt.");
		System.out.println("Die eigentliche Beurteilung wird zu einem späteren Zeitpunkt durchgeführt.");

		// Hier die Aufgaben dekommentieren, die implementiert wurden
		// und geprüft werden sollen.
		// Nur dekommentierte Aufgaben werden beurteilt!
		//checkTask1(); //Aufgabe 1
		//checkTask2(); //Aufgabe 2
		//checkTask3(); //Aufgabe 3
		//checkTask4(); //Aufgabe 4
	}

	// Methoden für Beispiel 1
	// Diese Methode muss für die Implementierung von Beispiel 1 dekommentiert werden
	/*
	public static boolean filterSelect(Selectable selectable, int digit) {
		return selectable.select(digit);
	}
	*/
	
	public static List<MagicItem> filterItems(List<MagicItem> items, int digit)	{
		return null;
	}
	// Methoden für Beispiel 1 Ende
	
	// Methoden für Beispiel 2
	public static Potion[] sortPotions(List<Potion> potions) {
		return null;
	}
	// Methoden für Beispiel 2 Ende

	// Methoden für Beispiel 3
	public static Map<Integer, Set<Wizard>>
			mapWizardsPerNoSpells(List<Wizard> wizards) {
		return null;
	}
	// Methoden für Beispiel 3 Ende
	
	//*************************************************************************
	//*************************************************************************
	// Weiterlesen auf eigene Gefahr ...
	// Hier befinden sich nur die für das Testen verwendeten Programmteile
	//*************************************************************************
	//*************************************************************************
	// Ab hier sind keine Änderungen des vorgegebenen Codes erlaubt
	// name manaCost levelNeeded
	private static ArrayList<Spell> spellsList = new ArrayList<>(
			Arrays.asList(
					new AttackingSpell("Attack", 10, MagicLevel.ADEPT,
							true, false, 10),
					new AttackingSpell("Attack 1", 20, MagicLevel.EXPERT,
							false, true, 30),
					new AttackingSpell("Attack 2", 30, MagicLevel.NOOB,
							false, false, 20),
					new AttackingSpell("Attack 3", 15, MagicLevel.STUDENT,
							true, true, 15),
					new AttackingSpell("Attack 4", 17, MagicLevel.ADEPT,
							true, false, 12),
					new AttackingSpell("Attack 5", 21, MagicLevel.EXPERT,
							false, true, 9),
					new AttackingSpell("Attack 6", 9, MagicLevel.NOOB,
							false, false, 17),
					new AttackingSpell("Attack 7", 13, MagicLevel.STUDENT,
							true, true, 8),
					new HealingSpell("Heal", 10, MagicLevel.ADEPT,
							true, false, 10),
					new HealingSpell("Heal 1", 20, MagicLevel.EXPERT,
							false, true, 30),
					new HealingSpell("Heal 2", 30, MagicLevel.NOOB,
							false, false, 20),
					new HealingSpell("Heal 3", 15, MagicLevel.STUDENT,
							true, true, 15),
					new HealingSpell("Heal 4", 17, MagicLevel.ADEPT,
							true, false, 12))
			);
	static {
		spellsList.add(new ProtectingSpell("Protect", 5, MagicLevel.NOOB,
				new HashSet<AttackingSpell>(Arrays.asList(
						(AttackingSpell)spellsList.get(0)))));
		spellsList.add(new ProtectingSpell("Protect 1", 10, MagicLevel.NOOB,
				new HashSet<AttackingSpell>(Arrays.asList(
						(AttackingSpell)spellsList.get(3),
						(AttackingSpell)spellsList.get(6),
						(AttackingSpell)spellsList.get(1)))));
	}
	//name usages price weight
	private static ArrayList<MagicItem> itemsList = new ArrayList<>(
			Arrays.asList(
					new HealthPotion("Health potion", 10, 25, 12, 20),
					new ManaPotion("Mana potion", 4, 3, 5, 7),
					new Concoction("Concoction", 7, 15, 1, 15, -3, 
							new ArrayList<Spell>()),
					new Scroll("Scroll", 15, 25, 2, spellsList.get(0)),
					new ManaPotion("Mana potion 1", 9, 13, 22, 50),
					new Scroll("Scroll 1", 21, 4, 7, spellsList.get(1)),
					new HealthPotion("Health potion 1", 10, 27, 19, 16))
			); 
	//[Mana potion 1; 13; 22], [Mana potion; 3; 5], [Health potion; 25; 12], [Concoction; 15; 1]
    private static ArrayList<Potion> additionalPotions = new ArrayList<>(
    		Arrays.asList(
    			new HealthPotion("Health potion", 10, 24, 14, 20),
				new ManaPotion("Mana potion", 4, 13, 2, 7),
				new HealthPotion("Health potion", 10, 26, 15, 20),
				new ManaPotion("Mana potion 1", 9, 4, 32, 50))
    		);
    //name level HP basicHP MP basicMP money knownSpells protectedFrom carryingCapacity inventory
    private static ArrayList<Wizard> wizardsList = new ArrayList<>(
    		Arrays.asList(
    				new Wizard("Harry", MagicLevel.EXPERT, 1000, 1000, 1000, 1000,
    						123, new HashSet<Spell>(spellsList),
    						new HashSet<AttackingSpell>(), 100,
    						new HashSet<Tradeable>()),
    				new Wizard("Hermione", MagicLevel.EXPERT, 1000, 1000, 1000, 1000,
    						123, new HashSet<Spell>(spellsList),
    						new HashSet<AttackingSpell>(), 100,
    						new HashSet<Tradeable>()),
    				new Wizard("Voldemort", MagicLevel.EXPERT, 1000, 1000, 1000, 1000,
    						123, new HashSet<Spell>(spellsList),
    						new HashSet<AttackingSpell>(), 100,
    						new HashSet<Tradeable>())
    		));
    
	private static void checkTask1() {
		System.out.println("\nÜberprüfung Aufgabe 1");
		Class<?> itemClass = itemsList.get(0).getClass();
		Field nameField = getFieldForClass(itemClass,"name");
		if (nameField==null)
			return;
		nameField.setAccessible(true);
		Field priceField = getFieldForClass(itemClass,"price");
		if (priceField==null)
			return;
		priceField.setAccessible(true);
		String inputList = itemsList.stream()
				.map(o->objFieldsToString(o, nameField, priceField))
				.collect(Collectors.joining(", "));
		String result = resultTask1ToString(filterItems(itemsList, 5), nameField,
				priceField);
		String expectedResult = "[Health potion; 25], [Concoction; 15], [Scroll; 25]";
		if (!checkTask1Result(inputList, 5, result, expectedResult))
			return;
		result = resultTask1ToString(filterItems(itemsList, 9), nameField,
				priceField);
		expectedResult = "";
		if (!checkTask1Result(inputList, 9, result, expectedResult))
			return;
		result = resultTask1ToString(filterItems(itemsList, 1), nameField,
				priceField);
		expectedResult = "[Concoction; 15], [Mana potion 1; 13]";
		if (!checkTask1Result(inputList, 1, result, expectedResult))
			return;
		result = resultTask1ToString(filterItems(itemsList, 2), nameField,
				priceField);
		expectedResult = "[Health potion; 25], [Scroll; 25], [Health potion 1; 27]";
		if (!checkTask1Result(inputList, 2, result, expectedResult))
			return;
		System.out.println("OK \u2713");
	}
	
	private static String resultTask1ToString(List<MagicItem> l, Field nameField,
			Field priceField) {
		return l.stream()
		/*
		.sorted(Comparator.comparing(o->{
			try {
				return (String)nameField.get(o);
			} catch (IllegalArgumentException | IllegalAccessException e) {
				return "";
			}
		}).thenComparingInt(o->{
			try {
				return (Integer)priceField.get(o);
			} catch (IllegalArgumentException | IllegalAccessException e) {
				return 0;
			}
		}))
		*/
		.map(o->objFieldsToString(o, nameField, priceField))
		.collect(Collectors.joining(", "));
	}

	private static boolean checkTask1Result(String inputList, int digit,
			String result, String expectedResult) {
		if (!expectedResult.equals(result)) {
			System.out.println("Aufruf der Methode filterItems mit den Parametern"
					+ " (nur die relevanten Werte 'name' und 'price' für"
					+ " MagicItems werden"
					+ " angezeigt)\nitems = ["+inputList+"] \nund\ndigit = "
					+ digit + "\n"
					+ "liefert:\n\t"+result+"\naber das erwartete Ergebnis ist\n\t"
					+expectedResult);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}
	
	private static void checkTask2() {
		System.out.println("\nÜberprüfung Aufgabe 2");
		Class<?> potionClass = Potion.class;
		Field nameField = getFieldForClass(potionClass,"name");
		if (nameField==null)
			return;
		nameField.setAccessible(true);
		Field priceField = getFieldForClass(potionClass,"price");
		if (priceField==null)
			return;
		priceField.setAccessible(true);
		Field weightField = getFieldForClass(potionClass,"weight");
		if (weightField==null)
			return;
		weightField.setAccessible(true);
		List<Potion> potionsList = itemsList.stream()
				.filter(o->o instanceof Potion).map(o->(Potion)o).toList();
		String inputList = potionsList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		String result = resultTask2ToString(sortPotions(potionsList), nameField,
				priceField, weightField);
		String expectedResult = "[Mana potion 1; 13; 22], [Mana potion; 3; 5], [Health potion 1; 27; 19], [Health potion; 25; 12], [Concoction; 15; 1]";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		potionsList = new ArrayList<Potion>();
		inputList = potionsList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask2ToString(sortPotions(potionsList), nameField,
				priceField, weightField);
		expectedResult = "";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		potionsList = itemsList.stream().
				filter(o->o instanceof Potion).limit(4).map(o->(Potion)o).toList();
		inputList = potionsList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask2ToString(sortPotions(potionsList), nameField,
				priceField, weightField);
		expectedResult = "[Mana potion 1; 13; 22], [Mana potion; 3; 5], [Health potion; 25; 12], [Concoction; 15; 1]";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		potionsList = new ArrayList<>(potionsList);
		potionsList.addAll(additionalPotions);
		inputList = potionsList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask2ToString(sortPotions(potionsList), nameField,
				priceField, weightField);
		expectedResult = "[Mana potion 1; 13; 22], [Mana potion 1; 4; 32], [Mana potion; 3; 5], [Mana potion; 13; 2], [Health potion; 25; 12], [Health potion; 24; 14], [Health potion; 26; 15], [Concoction; 15; 1]";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		System.out.println("OK \u2713");
	}
	
	private static String resultTask2ToString(Potion[] potions,
			Field nameField, Field priceField, Field weightField) {
		return Arrays.stream(potions)
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
	}
	
	private static boolean checkTask2Result(String inputList,
			String result, String expectedResult) {
		if (!expectedResult.equals(result)) {
			System.out.println("Aufruf der Methode sortPotions mit dem Parameter"
					+ " (nur die relevanten Werte 'name', 'price' und 'weight' für"
					+ " Potions werden"
					+ " angezeigt)\npotions = ["+inputList+"] \n"
					+ "liefert:\n\t"+result+"\naber das erwartete Ergebnis ist\n\t"
					+expectedResult);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}

	private static void checkTask3() {
		System.out.println("\nÜberprüfung Aufgabe 3");
		Class<?> wizardClass = Wizard.class;
		Field wizNameField = Main.getFieldForClass(wizardClass,"name");
		if (wizNameField==null)
			return;
		wizNameField.setAccessible(true);
		Field wizKnownSpells = Main.getFieldForClass(wizardClass,"knownSpells");
		if (wizKnownSpells==null)
			return;
		wizKnownSpells.setAccessible(true);
		Map<Integer, Set<Wizard>> tm = 
				new TreeMap<>(mapWizardsPerNoSpells(wizardsList));
		String result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+resultTask3ToString(o.getValue(), wizNameField,
				wizKnownSpells)).collect(Collectors.joining("\n\t"));
		String expectedResult = "15: [Harry; 15], [Hermione; 15], [Voldemort; 15]";
		if (!checkTask3Result(result, expectedResult))
			return;
		wizardsList.get(0).forget(spellsList.get(0));
		wizardsList.get(1).forget(spellsList.get(1));
		wizardsList.get(1).forget(spellsList.get(2));
		wizardsList.get(2).forget(spellsList.get(3));
		wizardsList.get(2).forget(spellsList.get(4));
		wizardsList.get(2).forget(spellsList.get(5));
		tm = new TreeMap<>(mapWizardsPerNoSpells(wizardsList));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+resultTask3ToString(o.getValue(), wizNameField,
				wizKnownSpells)).collect(Collectors.joining("\n\t"));
		expectedResult = "12: [Voldemort; 12]\n\t"
				+ "13: [Hermione; 13]\n\t"
				+ "14: [Harry; 14]";
		if (!checkTask3Result(result, expectedResult))
			return;
		wizardsList.get(2).learn(spellsList.get(4));
		tm = new TreeMap<>(mapWizardsPerNoSpells(wizardsList));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+resultTask3ToString(o.getValue(), wizNameField,
				wizKnownSpells)).collect(Collectors.joining("\n\t"));
		expectedResult = "13: [Hermione; 13], [Voldemort; 13]\n\t"
				+ "14: [Harry; 14]";
		if (!checkTask3Result(result, expectedResult))
			return;
		System.out.println("OK \u2713");
	}

	private static boolean checkTask3Result(String result,
			String expectedResult) {
		if (!expectedResult.equals(result)) {
			System.out.println("Aufruf der Methode mapWizardsPerNoSpells"
					+ " liefert das Ergebnis"
					+ " (nur die relevanten Werte 'Schlüssel': ['Wizardname',"
					+ " Anzahl bekannter Zauber'], ... werden"
					+ " angezeigt)\n\t"+result+"\naber das erwartete Ergebnis ist\n\t"
					+expectedResult);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}

	private static String resultTask3ToString(Set<Wizard> wizards,
			Field nameField, Field knownSpellsField) {
		return wizards.stream()
				.sorted(Comparator.comparing(o->{
					try {
						return (String)nameField.get(o);
					} catch (IllegalArgumentException | IllegalAccessException e) {
						return "";
					}
				}))
				.map(o->objFieldsToString(o, true, knownSpellsField, nameField))
				.collect(Collectors.joining(", "));
	}

	private static void checkTask4() {
		System.out.println("\nÜberprüfung Aufgabe 4");
		Wizard harry = new Wizardy("Harry", MagicLevel.EXPERT, 1000, 1000,
				1000, 1000,
				123, new HashSet<Spell>(spellsList),
				new HashSet<AttackingSpell>(), 100,
				new HashSet<Tradeable>());
		Wizard vold = new Wizardy("Voldemort", MagicLevel.EXPERT, 1000, 1000,
				1000, 1000,
				123, new HashSet<Spell>(spellsList),
				new HashSet<AttackingSpell>(), 100,
				new HashSet<Tradeable>());
		Class<?> spellClass = Spell.class;
		Field spellNameField = Main.getFieldForClass(spellClass,"name");
		if (spellNameField==null)
			return;
		spellNameField.setAccessible(true);
		Class<?> wizardClass = Wizard.class;
		Field wizNameField = Main.getFieldForClass(wizardClass,"name");
		if (wizNameField==null)
			return;
		wizNameField.setAccessible(true);
		Field wizKnownSpells = Main.getFieldForClass(wizardClass,"knownSpells");
		if (wizKnownSpells==null)
			return;
		wizKnownSpells.setAccessible(true);
		Field wizProtectedFrom = Main.getFieldForClass(wizardClass,"protectedFrom");
		if (wizProtectedFrom==null)
			return;
		wizProtectedFrom.setAccessible(true);
		String inputThis = getKnownSpells(harry, wizNameField, wizKnownSpells,
				spellNameField);
		String inputTarget = getCurProtections(vold, wizNameField,
				wizProtectedFrom, spellNameField);
		Method methodSenseAttack = null;
		try {
			methodSenseAttack = wizardClass.getMethod("senseAttack",
					Wizard.class);
		} catch (NoSuchMethodException | SecurityException e) {
		}
		if (methodSenseAttack==null) {
			System.out.println("Überprüfung nicht möglich.");
			System.out.println("Methode senseAttack in Wizard fehlt");
			System.out.println("Implementierung der Aufgabe nicht korrekt! ");
			System.out.println("Fehler \u2717");
		}
		try {
			methodSenseAttack.invoke(harry, vold);
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
		}
		String result = ((Wizardy)harry).castSpells.toString();
		String expectedResult = "{Attack=Voldemort, Attack 1=Voldemort, Attack 2=Voldemort, Attack 3=Voldemort, Attack 4=Voldemort, Attack 5=Voldemort, Attack 6=Voldemort, Attack 7=Voldemort}";
		if (!checkTask4Result(inputThis, inputTarget, result, expectedResult))
			return;
		harry = new Wizardy("Harry", MagicLevel.EXPERT, 1000, 1000,
				1000, 1000,
				123, new HashSet<Spell>(spellsList),
				new HashSet<AttackingSpell>(), 100,
				new HashSet<Tradeable>());
		vold = new Wizardy("Voldemort", MagicLevel.EXPERT, 1000, 1000,
				1000, 1000,
				123, new HashSet<Spell>(spellsList),
				new HashSet<AttackingSpell>(Arrays.asList(
						(AttackingSpell)spellsList.get(1),
						(AttackingSpell)spellsList.get(3),
						(AttackingSpell)spellsList.get(6),
						(AttackingSpell)spellsList.get(7))), 100,
				new HashSet<Tradeable>());
		inputThis = getKnownSpells(harry, wizNameField, wizKnownSpells,
				spellNameField);
		inputTarget = getCurProtections(vold, wizNameField,
				wizProtectedFrom, spellNameField);
		try {
			methodSenseAttack.invoke(harry, vold);
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
		}
		result = ((Wizardy)harry).castSpells.toString();
		expectedResult = "{Attack=Voldemort, Attack 2=Voldemort, Attack 4=Voldemort, Attack 5=Voldemort}";
		if (!checkTask4Result(inputThis, inputTarget, result, expectedResult))
			return;
		vold.setProtection(new HashSet<AttackingSpell>(Arrays.asList(
				(AttackingSpell)spellsList.get(0),
				(AttackingSpell)spellsList.get(2),
				(AttackingSpell)spellsList.get(4),
				(AttackingSpell)spellsList.get(5))));
		((Wizardy)harry).clearCastSpells();
		inputThis = getKnownSpells(harry, wizNameField, wizKnownSpells,
				spellNameField);
		inputTarget = getCurProtections(vold, wizNameField,
				wizProtectedFrom, spellNameField);
		try {
			methodSenseAttack.invoke(harry, vold);
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
		}
		result = ((Wizardy)harry).castSpells.toString();
		expectedResult = "{}";
		if (!checkTask4Result(inputThis, inputTarget, result, expectedResult))
			return;
		System.out.println("OK \u2713");
	}

	private static String getKnownSpells(Wizard w, Field wizNameField,
			Field wizKnownSpells, Field spellNameField) {
		StringBuilder b = new StringBuilder();
		try {
			b.append(wizNameField.get(w));
		} catch (IllegalArgumentException | IllegalAccessException e) {
			return "Error accessing wizard name";
		}
		b.append(" - ");
		Set<?> s = null;
		try {
			s = (Set<?>) wizKnownSpells.get(w);
		} catch (IllegalArgumentException | IllegalAccessException e) {
			return "Error accessing known spells";
		}
		b.append(s.stream().map(o->objFieldsToString(o, spellNameField))
				.collect(Collectors.joining(", ")));
		return b.toString();
	}
	
	private static String getCurProtections(Wizard w, Field wizNameField,
			Field wizProtectedFrom, Field spellNameField) {
		StringBuilder b = new StringBuilder();
		try {
			b.append(wizNameField.get(w));
		} catch (IllegalArgumentException | IllegalAccessException e) {
			return "Error accessing wizard name";
		}
		b.append(" - ");
		Set<?> s = null;
		try {
			s = (Set<?>) wizProtectedFrom.get(w);
		} catch (IllegalArgumentException | IllegalAccessException e) {
			return "Error accessing spells wizard is protected from";
		}
		b.append(s.stream().map(o->objFieldsToString(o, spellNameField))
				.collect(Collectors.joining(", ")));
		return b.toString();
	}

	private static boolean checkTask4Result(String inputThis, String inputTarget,
			String result, String expectedResult) {
		if (!expectedResult.equals(result)) {
			System.out.println("Aufruf der Methode senseAttack für das Objekt"
					+ " (nur die relevanten Werte 'name', und die Namen der"
					+ " bekannten Zauber"
					+ " werden angezeigt)\n\t"+inputThis+"\n"
					+ "mit dem Parameter Target (nur name und die Namen der"
					+ " Zauber gegen die ein Schutz besteht werden angezeigt)"
					+ "\n\t"
					+ inputTarget+"\n\nFolgende Attacken wurden durchgeführt"
					+ "(nicht unbedingt in dieser Reihenfolge, dargestellt "
					+ "in der Form: Name des "
					+ "Angriffszaubers = Name des Ziels)\n\t"+result+"\naber "
					+ "die erwarteten Attacken sind\n\t"
					+ expectedResult);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}

	
	static Field getFieldForClass(Class<?> c, String fieldName) {
		Field f = null;
		Class<?> curClass = c;
		for (curClass = c; f == null && curClass!=Object.class; 
				curClass = curClass.getSuperclass()) {
			try {
				f = curClass.getDeclaredField(fieldName);
			} catch (NoSuchFieldException | SecurityException e) {
			}
		}
		if (f==null) {
			System.out.println("Überprüfung nicht möglich.");
			System.out.println("Instanzvariable '"+fieldName+"' in Klasse '"+c.getName()+"' fehlt");
			System.out.println("Implementierung nicht spezifikationskonform! ");
			System.out.println("Fehler \u2717");
		}
		return f;
	}
	
	private static String objFieldsToString(Object obj, Field... fields) {
		StringBuilder b = new StringBuilder("[");
		for (int i=0; i<fields.length; ++i) {
			try {
				b.append(fields[i].get(obj));
			} catch (IllegalArgumentException | IllegalAccessException e) {
			}
			if (i!=fields.length-1) b.append("; ");
		}
		b.append("]");
		return b.toString();
	}

	private static String objFieldsToString(Object obj, boolean hasField,
			Field collectionField, Field... fields) {
		StringBuilder b = new StringBuilder("[");
		for (int i=0; i<fields.length; ++i) {
			try {
				b.append(fields[i].get(obj));
			} catch (IllegalArgumentException | IllegalAccessException e) {
			}
			b.append("; ");
		}
		try {
			b.append(((Collection<?>)collectionField.get(obj)).size());
		} catch (IllegalArgumentException | IllegalAccessException e) {
		}
		b.append("]");
		return b.toString();
	}
}

class Wizardy extends Wizard {
	Map<String, String> castSpells = new TreeMap<String,String>();
	Wizardy(String name, MagicLevel level, int basicHP, int HP, int basicMP,
			int MP, int money, Set<Spell> knownSpells,
			Set<AttackingSpell> protectedFrom, int carryingCapacity,
			Set<Tradeable> inventory) {
		super(name, level, basicHP, HP, basicMP, MP, money, knownSpells,
				protectedFrom, carryingCapacity, inventory);
	}
	
	@Override
	public boolean castSpell (Spell s , MagicEffectRealization target) {
		Class<?> spellClass = Spell.class;
		Field nameField = Main.getFieldForClass(spellClass,"name");
		if (nameField==null) {
			System.out.println("Keine Instanzvariable name in Spell");
			return false;
		}
		nameField.setAccessible(true);
		Class<?> wizardClass = Wizard.class;
		Field wizNameField = Main.getFieldForClass(wizardClass,"name");
		if (wizNameField==null) {
			System.out.println("Keine Instanzvariable name in Wizard");
			return false;
		}
		wizNameField.setAccessible(true);
		try {
			castSpells.put((String)nameField.get(s), (String)wizNameField.get(target));
		} catch (IllegalArgumentException | IllegalAccessException e) {
		}
		return super.castSpell(s, target);
	}
	
	public void clearCastSpells() {
		castSpells.clear();
	}
}
