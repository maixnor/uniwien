package a12302260;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class PotionTest {
    static PotionTestClass tmp;

    @BeforeEach
    void setUp() {
        tmp = new PotionTestClass("TMP", 1, 1, 1);
    }

    @AfterEach
    void tearDown() {
    }

    @Test
    void drink() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(3).setBasicMP(50).setMP(0).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        tmp.drink(dude);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void usageString() {
        PotionTestClass bigger = new PotionTestClass("a", 2, 1, 1);
        PotionTestClass smaller = new PotionTestClass("a", 0, 1, 1);
        Assertions.assertEquals("gulp", tmp.usageString());
        Assertions.assertEquals("gulps", bigger.usageString());
        Assertions.assertEquals("gulps", smaller.usageString());
    }

    static class PotionTestClass extends Potion {

        /**
         * @param name   name
         * @param usages number of usages still left
         * @param price  price
         * @param weight weight
         */
        public PotionTestClass(String name, int usages, int price, int weight) {
            super(name, usages, price, weight);
        }

        @Override
        public void useOn(MagicEffectRealization target) {
            target.takeDamage(3);
        }
    }
}