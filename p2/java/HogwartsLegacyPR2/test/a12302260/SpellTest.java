package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class SpellTest {
    static SpellTestClass tmp = new SpellTestClass("TMP", 3, MagicLevel.ADEPT);

    @Test
    void constructor() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            SpellTestClass tmp = new SpellTestClass(null, 3, MagicLevel.ADEPT);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            SpellTestClass tmp = new SpellTestClass("", 3, MagicLevel.ADEPT);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            SpellTestClass tmp = new SpellTestClass("a", -1, MagicLevel.ADEPT);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            SpellTestClass tmp = new SpellTestClass("a", 3, null);
        });
        Assertions.assertDoesNotThrow(() -> {
            SpellTestClass tmp = new SpellTestClass("a", 0, MagicLevel.NOOB);
        });
    }

    @Test
    void cast() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.ADEPT).setBasicHP(10).setHP(3).setBasicMP(100).setMP(3).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        Assertions.assertDoesNotThrow(() -> tmp.cast(dude, dude));
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void additionalOutputString() {
        Assertions.assertEquals("", tmp.additionalOutputString());
    }

    @Test
    void testToString() {
        Assertions.assertEquals("[TMP(**): 3 mana]", tmp.toString());
    }

    static class SpellTestClass extends Spell {

        /**
         * @param name        name
         * @param manaCost    manaCost
         * @param levelNeeded levelNeeded to cast the spell
         */
        public SpellTestClass(String name, int manaCost, MagicLevel levelNeeded) {
            super(name, manaCost, levelNeeded);
        }

        @Override
        public void doEffect(MagicEffectRealization target) {
            target.takeDamage(3);
        }
    }
}