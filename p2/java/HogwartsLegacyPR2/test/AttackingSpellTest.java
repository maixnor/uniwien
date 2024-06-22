import a12224609.AttackingSpell;
import a12224609.MagicLevel;
import a12224609.Wizard;
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
        Assertions.assertThrows(IllegalArgumentException.class, () -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, false, -1);});
        Assertions.assertDoesNotThrow(() -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, false, 0);});
        Assertions.assertDoesNotThrow(() -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, false, 101);});
        Assertions.assertThrows(IllegalArgumentException.class, () -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, -1);});
        Assertions.assertThrows(IllegalArgumentException.class, () -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, 101);});
        Assertions.assertDoesNotThrow(() -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, 100);});
        Assertions.assertDoesNotThrow(() -> {AttackingSpell tmp = new AttackingSpell("a", 3, MagicLevel.NOOB, false, true, 0);});
    }

    @Test
    void doEffect() {
        Wizard protector = new Wizard("Protector", MagicLevel.STUDENT, 3, 3, 999, 999,
                999, new HashSet<>(), new HashSet<>(Arrays.asList(fireball, poison, extraction, timedextraction)),
                999, new HashSet<>());
        Wizard die = new Wizard("Die", MagicLevel.STUDENT, 6, 3, 999, 999,
                999, new HashSet<>(), new HashSet<>(), 999, new HashSet<>());
        Wizard manadude = new Wizard("Mana Dude", MagicLevel.NOOB, 999, 999, 50, 50,
                999, new HashSet<>(), new HashSet<>(), 999, new HashSet<>());
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
        Assertions.assertTrue(manadude.provideMana(MagicLevel.NOOB,  (50 - ((int)(50.0 * 50.0 / 100.0)))));
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