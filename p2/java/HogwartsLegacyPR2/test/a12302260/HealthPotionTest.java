package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class HealthPotionTest {
    static HealthPotion pot = new HealthPotion("Potion", 10, 1, 1, 3);

    @Test
    void constructor() {
        Assertions.assertDoesNotThrow(() -> {
            HealthPotion tmp = new HealthPotion("Potion", 10, 1, 1, 0);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            HealthPotion tmp = new HealthPotion("Potion", 10, 1, 1, -1);
        });
    }

    @Test
    void additionalOutputString() {
        String out = pot.additionalOutputString();
        Assertions.assertEquals("; +3 HP", out);
    }

    @Test
    void useOn() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(0).setBasicMP(50).setMP(0).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        pot.useOn(dude);
        dude.takeDamage(2);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }
}