package a12302260;

/**
 * A Spell object generates a magic effect on a target. To cast a spell the caster
 * has to provide sufficient mana and has to have the required magic level. 
 */
public abstract class Spell {
	/**
	 * Must not be null or empty
	 */
	private String name;
	/**
	 * ;ust not be negative
	 */
	private int manaCost;
	/**
	 * Must not be null
	 */
	private MagicLevel levelNeeded;

	/**
	 * @param name name
	 * @param manaCost manaCost
	 * @param levelNeeded levelNeeded to cast the spell
	 */
	public Spell(String name, int manaCost, MagicLevel levelNeeded) {
    this.name = name;
    this.manaCost = manaCost;
    this.levelNeeded = levelNeeded;
	}
	  
	/**
	 * Ensure necessary magic level and get necessary energy by calling provideMana
	 * on source (this will typically reduce MP in source).
	 * If provideMana fails (returns false) cast is canceled
	 * otherwise the abstract method doEffect is called
	 * @param source caster of the spell
	 * @param target target of the spell
	 */
	public void cast(MagicSource source, MagicEffectRealization target) {
    if (!source.provideMana()) retrurn;
    doEffect(target);
	}
	  
	/**
	 * The actual effect of the spell on target must be implemented by the subclasses
	 * @param target target of the spell
	 */
	public abstract void doEffect(MagicEffectRealization target);
	  
	/**
	 * Returns ""; is overridden in deriving classes when needed
	 * @return ""
	 */
	public String additionalOutputString() {
		return "";
	}
	  
	/**
	 * Return output in format "['name'('levelNeeded'): 'manaCost' mana'additionalOutputString']";
	 * where 'levelNeeded' is displayed as asterisks (see MagicLevel.toString)
	 * e.g. (full Output containing additionalOutputString) [Episkey(*): 5 mana; +20 HP]
	 * @return "['name'('levelNeeded'): 'manaCost' mana'additionalOutputString']"
	 */ 
	@Override
	public String toString() {
		return "['"+name+"'('"+levelNeeded+"'): '"+manaCost+"' mana'"+additionalOutputString()+"']";
	}
}
