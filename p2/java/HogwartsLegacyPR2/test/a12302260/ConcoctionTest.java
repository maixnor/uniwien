package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;

class ConcoctionTest {
    static AttackingSpell fireball = new AttackingSpell("Fire Ball", 3, MagicLevel.STUDENT, true, false, 3);
    static Concoction con = new Concoction("Empty", 10, 1, 1, 0, 0, new ArrayList<>(List.of(fireball)));
    static Concoction plus = new Concoction("Plus", 10, 1, 1, 3, 10, new ArrayList<>());
    static Concoction minus = new Concoction("Minus", 10, 1, 1, -3, -10, new ArrayList<>());

    @Test
    void constructor() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Concoction tmp = new Concoction("a", 10, 1, 1, -3, -10, null);
        });
        Assertions.assertDoesNotThrow(() -> {
            Concoction tmp = new Concoction("a", 10, 1, 1, -3, -10, new ArrayList<>());
        });
        Assertions.assertDoesNotThrow(() -> {
            Concoction tmp = new Concoction("a", 10, 1, 1, 3, 10, new ArrayList<>());
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Concoction tmp = new Concoction("a", 10, 1, 1, 0, 0, new ArrayList<>());
        });
        Assertions.assertDoesNotThrow(() -> {
            Concoction tmp = new Concoction("a", 10, 1, 1, 3, 10, new ArrayList<>(Collections.singletonList(fireball)));
        });
    }

    @Test
    void additionalOutputString() {
        String out1 = con.additionalOutputString();
        String out2 = plus.additionalOutputString();
        String out3 = minus.additionalOutputString();
        Concoction tmp1 = new Concoction("a", 10, 1, 1, 1, 0, new ArrayList<>());
        Concoction tmp2 = new Concoction("a", 10, 1, 1, 0, 1, new ArrayList<>());
        Concoction tmp3 = new Concoction("a", 10, 1, 1, -1, 1, new ArrayList<>(Collections.singletonList(fireball)));
        String out4 = tmp1.additionalOutputString();
        String out5 = tmp2.additionalOutputString();
        String out6 = tmp3.additionalOutputString();
        Assertions.assertEquals("; cast [" + fireball.toString() + "]", out1);
        Assertions.assertEquals("; +3 HP; +10 MP", out2);
        Assertions.assertEquals("; -3 HP; -10 MP", out3);
        Assertions.assertEquals("; +1 HP", out4);
        Assertions.assertEquals("; +1 MP", out5);
        Assertions.assertEquals("; -1 HP; +1 MP; cast [" + fireball.toString() + "]", out6);
    }

    @Test
    void useOn() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.NOOB).setBasicHP(3).setHP(3).setBasicMP(50).setMP(50).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        con.useOn(dude);
        Assertions.assertTrue(dude.isDead());
        plus.useOn(dude);
        Assertions.assertFalse(dude.isDead());
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 60));
        dude.enforceMagic(50);
        minus.useOn(dude);
        Assertions.assertTrue(dude.isDead());
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 50));
    }
}