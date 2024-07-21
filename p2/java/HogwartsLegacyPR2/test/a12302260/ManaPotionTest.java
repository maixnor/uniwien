package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class ManaPotionTest {
    static ManaPotion pot = new ManaPotion("Potion", 10, 1, 1, 3);

    @Test
    void constructor() {
        Assertions.assertDoesNotThrow(() -> {
            ManaPotion tmp = new ManaPotion("Potion", 10, 1, 1, 0);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            ManaPotion tmp = new ManaPotion("Potion", 10, 1, 1, -1);
        });
    }

    @Test
    void additionalOutputString() {
        String out = pot.additionalOutputString();
        Assertions.assertEquals("; +3 MP", out);
    }

    @Test
    void useOn() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(1).setBasicMP(50).setMP(0).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        pot.useOn(dude);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 3));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
    }
}