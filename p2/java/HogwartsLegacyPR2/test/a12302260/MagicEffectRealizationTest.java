package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class MagicEffectRealizationTest {
    static MagicEffectRealizationTestClass tmp = new MagicEffectRealizationTestClass();
    static HealingSpell HP = new HealingSpell("HP", 3, MagicLevel.NOOB, true, false, 3);

    @Test
    void takeDamage() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.takeDamage(-1);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.takeDamage(0);
        });
    }

    @Test
    void takeDamagePercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.takeDamagePercent(-1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.takeDamagePercent(101);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.takeDamagePercent(0);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.takeDamagePercent(100);
        });
    }

    @Test
    void weakenMagic() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.weakenMagic(-1);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.weakenMagic(0);
        });
    }

    @Test
    void weakenMagicPercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.weakenMagicPercent(-1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.weakenMagicPercent(101);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.weakenMagicPercent(0);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.weakenMagicPercent(100);
        });
    }

    @Test
    void heal() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.heal(-1);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.heal(0);
        });
    }

    @Test
    void healPercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.healPercent(-1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.healPercent(101);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.healPercent(0);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.healPercent(100);
        });
    }

    @Test
    void enforceMagic() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.enforceMagic(-1);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.enforceMagic(0);
        });
    }

    @Test
    void enforceMagicPercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.enforceMagicPercent(-1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.enforceMagicPercent(101);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.enforceMagicPercent(0);
        });
        Assertions.assertDoesNotThrow(() -> {
            tmp.enforceMagicPercent(100);
        });
    }

    @Test
    void isProtected() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.isProtected(null);
        });
        Assertions.assertFalse(tmp.isProtected(HP));
    }

    @Test
    void setProtection() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.setProtection(null);
        });
    }

    @Test
    void removeProtection() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            tmp.removeProtection(null);
        });
    }

    static class MagicEffectRealizationTestClass implements MagicEffectRealization {

    }
}