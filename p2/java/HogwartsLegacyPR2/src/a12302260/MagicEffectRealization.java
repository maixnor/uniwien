package a12302260;

import java.util.Set;

/**
 * This interface contains all the methods to realize various magic effects on an object.
 * Most methods default to doing nothing and should be overriden for classes that can be
 * influenced by magic. The overrides define what exactly will happen given a specific
 * magic effect on the specific object.
 */
public interface MagicEffectRealization {
    /**
     * Negative amount must throw IllegalArgumentException;
     * a typical implementation will reduce the object's HP by amount ensuring however
     * that HP does not become negative.
     * 
     * @param amount amount of damage done
     */
	default void takeDamage(int amount) {}

    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will reduce the object's HP by the percentage given of the
     * object's basic HP value ensuring however, that HP does not become negative.
     * calculations must be done in double data type converting back to int only in the
     * last step
     * 
     * @param percentage percentage of damage relative to object's basic HP value
     */
	default void takeDamagePercent(int percentage) {}

    /**
     * Negative amount must throw IllegalArgumentException;
     * a typical implementation will reduce the object's MP by amount ensuring however
     * that MP does not become negative.
     * 
     * @param amount amount of damage done
     */
	default void weakenMagic(int amount) {}

    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will reduce the object's MP by the percentage given of the
     * object's basic MP value value ensuring however, that MP does not become negative..
     * calculations must be done in double data type converting back to int only in the last step
     * 
     * @param percentage percentage of damage relative to object's basic MP value
     */
	default void weakenMagicPercent(int percentage) {}

	/**
	 * Negative amount must throw IllegalArgumentException;
	 * a typical implementation will increase the object's HP by the amount given.
	 * 
     * @param amount amount of healing done
	 */
	default void heal(int amount) {}

    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will increase the object's HP by the percentage given of the
     * object's basic HP value.
     * calculations must be done in double data type converting back to int only in the last step
     * 
     * @param percentage percentage of healing relative to object's basic MP value
     */
	default void healPercent(int percentage) {}

    /**
     * Negative amount must throw IllegalArgumentException;
     * a typical implementation will increase the object's MP by the amount given.
     * 
     * @param amount amount to increase mana
     */
	default void enforceMagic(int amount) {}

    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will increase the object's MP by the percentage given of the
     * object's basic MP value
     * calculations must be done in double data type converting back to int only in the last
     * step
     * 
     * @param percentage percentage of mana increase relative to object's basic MP value
     */
	default void enforceMagicPercent(int percentage) {}

    /**
     * If s is null, an IllegalArgumentException must be thrown;
     * an implementation returns true if the object is protected against the spell s, false
     * otherwise.
     * 
     * @param s spell to test for 
     * @return true if object is protected against spell s
     */
	default boolean isProtected(Spell s) {return false;}

    /**
     * If attacks is null an IllegalArgumentException must be thrown;
     * a typical implementation will register the object as protected against all the spells
     * in attacks
     * 
     * @param attacks list of attacking spells that the object gets protected against
     */
	default void setProtection(Set<AttackingSpell> attacks) {}

    /**
     * If attacks is null an IllegalArgumentException must be thrown;
     * a typical implementation will register the object as not protected against all the spells
     * in attacks
     * 
     * @param attacks list of attacking spells that the object loses protection against
     */
	default void removeProtection(Set<AttackingSpell> attacks) {}
}