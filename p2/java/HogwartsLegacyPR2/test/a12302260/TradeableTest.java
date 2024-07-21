package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class TradeableTest {
    static TradeableTestClass item1 = new TradeableTestClass();
    static TradeableTestClass item2 = new TradeableTestClass();
    Wizard dude1;
    Wizard dude2;

    @BeforeEach
    void setUp() {
        dude1 = new WizardBuilder().setName("Dude").setLevel(MagicLevel.ADEPT).setBasicHP(10).setHP(3).setBasicMP(100).setMP(3).setMoney(3).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(3).setInventory(new HashSet<>()).createWizard();
        dude2 = new WizardBuilder().setName("Dude").setLevel(MagicLevel.ADEPT).setBasicHP(10).setHP(3).setBasicMP(100).setMP(3).setMoney(3).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(6).setInventory(new HashSet<>()).createWizard();
        dude2.addToInventory(item2);
    }

    @Test
    void give() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> item1.give(null, dude1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> item1.give(dude1, null));
        Assertions.assertThrows(IllegalArgumentException.class, () -> item1.give(dude1, dude1));
        Assertions.assertFalse(item1.give(dude2, dude1));
        Assertions.assertTrue(dude1.hasCapacity(3));
        Assertions.assertFalse(dude2.hasCapacity(4));
        Assertions.assertTrue(item2.give(dude2, dude1));
        Assertions.assertFalse(dude1.hasCapacity(1));
        Assertions.assertTrue(dude2.hasCapacity(6));
        dude2.addToInventory(item1);
        Assertions.assertFalse(item1.give(dude2, dude1));
        Assertions.assertFalse(dude1.hasCapacity(1));
        Assertions.assertFalse(dude2.hasCapacity(4));
    }

    @Test
    void purchase() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> item1.purchase(null, dude1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> item1.purchase(dude1, null));
        Assertions.assertThrows(IllegalArgumentException.class, () -> item1.purchase(dude1, dude1));
        dude2.removeFromInventory(item2);
        dude1.addToInventory(item2);
        Assertions.assertFalse(item1.purchase(dude1, dude2));
        Assertions.assertTrue(dude2.hasCapacity(3));
        Assertions.assertTrue(dude2.canAfford(3));
        Assertions.assertFalse(dude1.hasCapacity(4));
        Assertions.assertFalse(dude1.canAfford(6));
        Assertions.assertTrue(item2.purchase(dude1, dude2));
        Assertions.assertFalse(dude2.hasCapacity(4));
        Assertions.assertTrue(dude1.hasCapacity(3));
        Assertions.assertFalse(dude2.canAfford(1));
        Assertions.assertTrue(dude1.canAfford(6));
        dude1.addToInventory(item1);
        Assertions.assertFalse(item1.purchase(dude1, dude2));
        Assertions.assertFalse(dude2.hasCapacity(4));
        Assertions.assertFalse(dude1.hasCapacity(1));
        Assertions.assertFalse(dude2.canAfford(1));
        Assertions.assertTrue(dude1.canAfford(6));
        Assertions.assertFalse(item1.purchase(dude2, dude1));
        Assertions.assertFalse(dude2.hasCapacity(4));
        Assertions.assertFalse(dude1.hasCapacity(1));
        Assertions.assertFalse(dude2.canAfford(1));
        Assertions.assertTrue(dude1.canAfford(6));
    }

    static class TradeableTestClass implements Tradeable {

        @Override
        public int getPrice() {
            return 3;
        }

        @Override
        public int getWeight() {
            return 3;
        }

        @Override
        public void useOn(MagicEffectRealization target) {
            target.takeDamage(3);
        }

        @Override
        public String toString() {
            return "Item";
        }
    }
}