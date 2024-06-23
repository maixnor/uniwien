package a12302260;

/**
 * A Scroll object contains a spell that can be read by someone. The scroll provides the
 * necessary mana and magic level even if the user's capabilities would not be sufficient
 * to cast the spell 
 */
public class Scroll extends MagicItem {
	/**
	 * Must not be null
	 */
	private Spell spell;
	
	/**
	 * @param name name
	 * @param usages number of usages still left
	 * @param price price
	 * @param weight weight
	 * @param spell spell that is written on the scroll and can therefore be cast
	 */
	public Scroll(String name, int usages, int price, int weight, Spell spell) {
	}
	  
	/**
	 * Returns "; casts 'spell'".
	 * e.g. (total result of toString)
	 * "[Scroll of doom; 1 g; 100 Knuts; 5 usages; casts [Bombarda(**): 20 mana; -50 % HP]]"
	 * @return "; casts 'spell'"
	 */
	@Override
	public String additionalOutputString() {
		
	}

	/**
	 * If usages is greater than 0 reduce usages by 1 (tryUsage method) and
	 * cast the spell using this as magic source and parameter target as target 
	 * @param target target of the spell cast by reading the scroll
	 */
	@Override  
	public void useOn(MagicEffectRealization target) {
	}
}