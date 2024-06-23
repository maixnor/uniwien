import a12302260.MagicEffectRealization;
import a12302260.MagicLevel;
import a12302260.Tradeable;
import a12302260.Wizard;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class TradeableTest {
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
    }
    static TradeableTestClass item1 = new TradeableTestClass();
    static TradeableTestClass item2 = new TradeableTestClass();
    Wizard dude1;
    Wizard dude2;

    @BeforeEach
    void setUp() {
        dude1 = new Wizard("Dude", MagicLevel.ADEPT, 10, 3, 100, 3,
                3, new HashSet<>(), new HashSet<>(), 3, new HashSet<>());
        dude2 = new Wizard("Dude", MagicLevel.ADEPT, 10, 3, 100, 3,
                3, new HashSet<>(), new HashSet<>(), 6, new HashSet<>());
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
}