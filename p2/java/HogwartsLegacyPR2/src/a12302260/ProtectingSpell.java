package a12302260;

import java.util.Set;

/**
 * ProtectingSpell objects grant protection against a number of specific
 * attacking spells
 */
public class ProtectingSpell extends Spell {
	/**
	 * Must not be null or empty; use HashSet as concrete type
	 */
	private Set<AttackingSpell> attacks;

	/**
	 * @param name        name
	 * @param manaCost    manaCost
	 * @param levelNeeded levelNeeded
	 * @param attacks     attacking spells against which protection is granted
	 */
	public ProtectingSpell(String name, int manaCost, MagicLevel levelNeeded, Set<AttackingSpell> attacks) {
	}

	/**
	 * Call setProtection method on target with attacks as parameter
	 * 
	 * @param target target for which protection is granted
	 */
	@Override
	public void doEffect(MagicEffectRealization target) {
	}

	/**
	 * Returns "; protects against 'listOfAttackSpells'" where 'listOfAttackSpells'
	 * is a bracketed list of all the attack spells (Java default toString method
	 * for sets) e. g. "; protects against [[Confringo(*): 10 mana; -20 HP],
	 * [Bombarda(**): 20 mana; -50 % HP]]"
	 * 
	 * @return "; protects against 'listOfAttackSpells'"
	 */
	@Override
	public String additionalOutputString() {
	}
}