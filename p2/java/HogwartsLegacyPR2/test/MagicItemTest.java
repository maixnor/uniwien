import a12302260.MagicEffectRealization;
import a12302260.MagicItem;
import a12302260.MagicLevel;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class MagicItemTest {

    static MagicItemTestClass tmp;

    @BeforeEach
    void setUp() {
        tmp = new MagicItemTestClass("TMP", 1, 1, 1);
    }

    @Test
    void constructor() {
        Assertions.assertDoesNotThrow(() -> {
            MagicItemTestClass tmp = new MagicItemTestClass("Potion", 0, 0, 0);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            MagicItemTestClass tmp = new MagicItemTestClass("", 10, 1, 1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            MagicItemTestClass tmp = new MagicItemTestClass(null, 10, 1, 1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            MagicItemTestClass tmp = new MagicItemTestClass("a", -1, 1, 1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            MagicItemTestClass tmp = new MagicItemTestClass("a", 10, -1, 1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            MagicItemTestClass tmp = new MagicItemTestClass("a", 10, 1, -1);
        });
    }

    @Test
    void getUsages() {
        Assertions.assertEquals(1, tmp.getUsages());
    }

    @Test
    void tryUsage() {
        Assertions.assertTrue(tmp.tryUsage());
        Assertions.assertFalse(tmp.tryUsage());
        Assertions.assertEquals(0, tmp.getUsages());
    }

    @Test
    void usageString() {
        MagicItemTestClass bigger = new MagicItemTestClass("a", 2, 1, 1);
        MagicItemTestClass smaller = new MagicItemTestClass("a", 0, 1, 1);
        Assertions.assertEquals("use", tmp.usageString());
        Assertions.assertEquals("uses", bigger.usageString());
        Assertions.assertEquals("uses", smaller.usageString());
    }

    @Test
    void additionalOutputString() {
        Assertions.assertEquals("", tmp.additionalOutputString());
    }

    @Test
    void testToString() {
        MagicItemTestClass bigger = new MagicItemTestClass("Bigger", 2, 2, 2);
        MagicItemTestClass smaller = new MagicItemTestClass("Smaller", 0, 0, 2);
        Assertions.assertEquals("[TMP; 1 g; 1 Knut; 1 use]", tmp.toString());
        Assertions.assertEquals("[Bigger; 2 g; 2 Knuts; 2 uses]", bigger.toString());
        Assertions.assertEquals("[Smaller; 2 g; 0 Knuts; 0 uses]", smaller.toString());
    }

    @Test
    void getPrice() {
        Assertions.assertEquals(1, tmp.getPrice());
    }

    @Test
    void getWeight() {
        Assertions.assertEquals(1, tmp.getWeight());
    }

    @Test
    void provideMana() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> tmp.provideMana(null, 1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> tmp.provideMana(MagicLevel.NOOB, -1));
        Assertions.assertTrue(tmp.provideMana(MagicLevel.NOOB, 1));
    }

    @Test
    void takeDamagePercent() {
        MagicItemTestClass bigger = new MagicItemTestClass("a", 10, 1, 1);
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.takeDamagePercent(-1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.takeDamagePercent(101);
        });
        Assertions.assertDoesNotThrow(() -> {
            bigger.takeDamagePercent(0);
        });
        Assertions.assertEquals(10, bigger.getUsages());
        Assertions.assertDoesNotThrow(() -> {
            bigger.takeDamagePercent(20);
        });
        Assertions.assertEquals(8, bigger.getUsages());
        Assertions.assertDoesNotThrow(() -> {
            bigger.takeDamagePercent(50);
        });
        Assertions.assertEquals(4, bigger.getUsages());
        Assertions.assertDoesNotThrow(() -> {
            bigger.takeDamagePercent(100);
        });
        Assertions.assertEquals(0, bigger.getUsages());
    }

    static class MagicItemTestClass extends MagicItem {

        /**
         * @param name   name
         * @param usages number of usages still left
         * @param price  price
         * @param weight weight
         */
        public MagicItemTestClass(String name, int usages, int price, int weight) {
            super(name, usages, price, weight);
        }

        @Override
        public void useOn(MagicEffectRealization target) {
        }
    }
}