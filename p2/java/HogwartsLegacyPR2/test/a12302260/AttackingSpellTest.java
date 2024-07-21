package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.HashSet;

class AttackingSpellTest {
    static AttackingSpell fireball = new AttackingSpell("Fire Ball", 3, MagicLevel.STUDENT, true, false, 3);
    static AttackingSpell poison = new AttackingSpell("Poison", 3, MagicLevel.STUDENT, true, true, 50);
    static AttackingSpell extraction = new AttackingSpell("Extraction", 3, MagicLevel.STUDENT, false, false, 3);
    static AttackingSpell timedextraction = new AttackingSpell("Timed Extraction", 3, MagicLevel.STUDENT, false, true, 50);

    @Test
    void constructor() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, false, -1);
        });
        Assertions.assertDoesNotThrow(() -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, false, 0);
        });
        Assertions.assertDoesNotThrow(() -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, false, 101);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, -1);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, 101);
        });
        Assertions.assertDoesNotThrow(() -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, 100);
        });
        Assertions.assertDoesNotThrow(() -> {
            AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, 0);
        });
    }

    @Test
    void doEffect() {
        Wizard protector = new WizardBuilder().setName("Protector").setLevel(MagicLevel.STUDENT).setBasicHP(3).setHP(3).setBasicMP(999).setMP(999).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>(Arrays.asList(fireball, poison, extraction, timedextraction))).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        Wizard die = new WizardBuilder().setName("Die").setLevel(MagicLevel.STUDENT).setBasicHP(6).setHP(3).setBasicMP(999).setMP(999).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        Wizard manadude = new WizardBuilder().setName("Mana Dude").setLevel(MagicLevel.NOOB).setBasicHP(999).setHP(999).setBasicMP(50).setMP(50).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        fireball.doEffect(protector);
        Assertions.assertFalse(protector.isProtected(fireball));
        Assertions.assertFalse(protector.isDead());
        fireball.doEffect(protector);
        Assertions.assertTrue(protector.isDead());
        poison.doEffect(die);
        Assertions.assertTrue(protector.isDead());
        extraction.doEffect(manadude);
        Assertions.assertTrue(manadude.provideMana(MagicLevel.NOOB, 50 - 3));
        manadude.enforceMagic(50);
        timedextraction.doEffect(manadude);
        Assertions.assertTrue(manadude.provideMana(MagicLevel.NOOB, (50 - ((int) (50.0 * 50.0 / 100.0)))));
    }

    @Test
    void additionalOutputString() {
        String outfb = fireball.additionalOutputString();
        String outp = poison.additionalOutputString();
        String oute = extraction.additionalOutputString();
        String outte = timedextraction.additionalOutputString();
        Assertions.assertEquals("; -3 HP", outfb);
        Assertions.assertEquals("; -50 % HP", outp);
        Assertions.assertEquals("; -3 MP", oute);
        Assertions.assertEquals("; -50 % MP", outte);
    }
}