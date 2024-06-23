import a12302260.HealthPotion;
import a12302260.MagicLevel;
import a12302260.Wizard;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
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
        Wizard dude = new Wizard("Dude", MagicLevel.NOOB, 10, 0, 50, 0,
                999, new HashSet<>(), new HashSet<>(), 999, new HashSet<>());
        pot.useOn(dude);
        dude.takeDamage(2);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }
}