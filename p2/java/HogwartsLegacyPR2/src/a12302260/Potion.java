package a12302260;

/**
 * A potion has a specific magic effect on its consumer
 */
public abstract class Potion extends MagicItem {
    /**
     * @param name   name
     * @param usages number of usages still left
     * @param price  price
     * @param weight weight
     */
    public Potion(String name, int usages, int price, int weight) {
        super(name, usages, price, weight);
    }

    /**
     * Delegates to method call useOn(drinker)
     *
     * @param drinker the consumer of the potion
     */
    public void drink(Wizard drinker) {
      useOn(drinker);
    }

    /**
     * returns "gulp" if usages is equal to 1, "gulps" otherwise
     *
     * @return "gulp" or "gulps" depending on number of usages left
     */
    @Override
    public String usageString() {
        return (getUsages() == 1) ? "gulp" : "gulps";
    }
}
