package a12302260;

/**
 * A MagicSource object can provide mana necesary to cause a magic effect
 */
public interface MagicSource {
	/**
	 * levelNeeded==null or negative manaAmount must throw IllegalArgumentException;
	 * returns true if the object has at least the required level and can provide
	 * enough mana, false otherwise. A typical implementation will check if the
	 * objects level is high enough, returning false if not. Otherwise it reduces
	 * the object's MP by manaAmount. There may be exceptions though, like objects
	 * with infinite mana or supporting all levels for example
	 * 
	 * @param levelNeeded mana can only be provided if the object at least has magic
	 *                    level levelNeeded
	 * @param manaAmount  amount of mana to provide
	 * @return true, if mana could be successfully provided, false otherwise
	 */
	boolean provideMana(MagicLevel levelNeeded, int manaAmount);
}