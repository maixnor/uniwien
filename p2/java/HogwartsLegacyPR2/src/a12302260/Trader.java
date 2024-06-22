package a12302260;

/**
 * Trader objects have an inventory in which they can store magic items.
 * They can trade and use these objects. Additionally they are able to
 * steal and loot objects from other traders. 
 */
public interface Trader {
	/**
	 * If item is null an IllegalArgumentException must be thrown;
	 * returns true if this object possesses the item, false otherwise.
	 * @param item test if this object possesses this item
	 * @return true if the item is in the object's possession, false otherwise
	 */
	boolean possesses(Tradeable item);

    /**
     * If amount is negative, an IllegalArgumentException must be thrown;
     * returns true if the object has enough money, false otherwise
     * @param amount amount to be tested for
     * @return true if the object has enough money, false otherwise
     */
	boolean canAfford(int amount);

    /**
     * If weight is negative, an IllegalArgumentException must be thrown;
     * returns true if the weight can be added to the object's inventory without exceeding
     * the maximum weight capacity.
     * @param weight weight to test for
     * @return true, if carrying capacity is sufficient, false otherwise 
     */
	boolean hasCapacity(int weight);

    /**
     * If amount is negative, an IllegalArgumentException must be thrown;
     * if this owns enough money, deduct amount from money and return true, return false
     * otherwise.
     * @param amount amount to be payed
     * @return true if payment succeeded, false otherwise
     */
	boolean pay(int amount);

    /**
     * If amount is negative, an IllegalArgumentException must be thrown;
     * add amount to this object's money and return true.
     * @param amount amount earned
     * @return true (always)
     */
	boolean earn(int amount);

    /**
     * If item is null, an IllegalArgumentException must be thrown;
     * if inventory capacity would be exceeded, return false.
     * adds item to the inventory and returns true on success, false if adding the item
     * failed
     * @param item item to be stored in inventory
     * @return true if storage was successful, false otherwise
     */
	boolean addToInventory(Tradeable item);

    /**
     * If item is null, an IllegalArgumentException must be thrown;
     * removes item from the inventory and returns true on success, false if removing
     * the item failed.
     * @param item to remove from inventory
     * @return true, if removal was successful, false otherwise
     */
	boolean removeFromInventory(Tradeable item);

    /**
     * Returns true if the object is capable to steal;
     * default implementation always returns false
     * this will be overridden for the class Wizard, so that only living Wizards can steal.
     * @return true, if object is able to steal, false otherwise
     */
	default boolean canSteal() {
	}

    /**
     * If thief is null, an IllegalArgumentException must be thrown;
     * if thief cannot steal (canSteal returns false) no action can be taken and false
     * is returned.
     * returns false if the object's inventory is empty
     * otherwise transfers a random item from the this object's inventory into the thief's
     * inventory; if the thief's inventory has not enough capacity, the object just vanishes
     * and false is returned. returns true if theft was successful
     * @param thief the one who steals the object
     * @return true, if theft was successful, false otherwise
     */
	boolean steal(Trader thief);
	
    /**
     * Returns true if the object can be looted;
     * default implementation always returns false.
     * This will be overridden for the class Wizard, so that dead Wizards may be looted
     * @return true if the object can be looted, false otherwise
     */
	default boolean isLootable() {
	}

    /**
     * Returns true if the object is capable to loot;
     * default implementation always returns false.
     * This will be overridden for the class Wizard, so that only living Wizards can loot
     * @return true if the object can loot another object, false otherwise
     */
	default boolean canLoot() {
	}
	
    /**
     * If looter is null, an IllegalArgumentException must be thrown;
     * if looter cannot loot (canLoot returns false) no action can be taken and false
     * is returned. If the object can be looted (isLootable), transfer all the items in
     * the object's inventory into the looter's inventory; items that don't fit in the
     * looter's inventory because of the weight limitation just vanish
     * returns true if at least one item was successfully transferred, false otherwise}
     * @param looter the one who loots the object
     * @return true, if at least one item could be successfully looted, false otherwise
     */
	boolean loot(Trader looter);
}