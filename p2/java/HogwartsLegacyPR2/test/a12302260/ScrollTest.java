package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class ScrollTest {
    static AttackingSpell fireball = new AttackingSpell("Fire Ball", 3, MagicLevel.STUDENT, true, false, 3);
    static Scroll S;

    @BeforeEach
    void setUp() {
        S = new Scroll("Scroll", 1, 1, 1, fireball);
    }

    @Test
    void constructor() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Scroll tmp = new Scroll("a", 3, 1, 1, null);
        });
        Assertions.assertDoesNotThrow(() -> {
            Scroll tmp = new Scroll("a", 3, 1, 1, fireball);
        });
    }

    @Test
    void additionalOutputString() {
        Assertions.assertEquals("; casts " + fireball.toString(), S.additionalOutputString());
    }

    @Test
    void useOn() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(3).setBasicMP(50).setMP(0).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        S.useOn(dude);
        Assertions.assertTrue(dude.isDead());
    }
}