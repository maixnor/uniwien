package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.HashSet;

class ProtectingSpellTest {
    static AttackingSpell fireball = new AttackingSpell("Fire Ball", 3, MagicLevel.STUDENT, true, false, 3);
    static AttackingSpell poison = new AttackingSpell("Poison", 3, MagicLevel.STUDENT, true, true, 50);
    static AttackingSpell extraction = new AttackingSpell("Extraction", 3, MagicLevel.STUDENT, false, false, 3);
    static AttackingSpell timedextraction = new AttackingSpell("Timed Extraction", 3, MagicLevel.STUDENT, false, true, 50);
    static ProtectingSpell SP = new ProtectingSpell("Protector", 3, MagicLevel.NOOB, new HashSet<>(Arrays.asList(fireball, poison)));

    @Test
    void constructor() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            ProtectingSpell tmp = new ProtectingSpell("a", 3, MagicLevel.NOOB, null);
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            ProtectingSpell tmp = new ProtectingSpell("a", 3, MagicLevel.NOOB, new HashSet<>());
        });
        Assertions.assertDoesNotThrow(() -> {
            ProtectingSpell tmp = new ProtectingSpell("a", 3, MagicLevel.NOOB, new HashSet<>(Arrays.asList(fireball, poison)));
        });
    }

    @Test
    void doEffect() {
        Wizard dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(1).setBasicMP(50).setMP(0).setMoney(999).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(999).setInventory(new HashSet<>()).createWizard();
        SP.doEffect(dude);
        Assertions.assertTrue(dude.isProtected(fireball));
        Assertions.assertTrue(dude.isProtected(poison));
        Assertions.assertFalse(dude.isProtected(extraction));
        Assertions.assertFalse(dude.isProtected(timedextraction));
    }

    @Test
    void additionalOutputString() {
        HashSet<AttackingSpell> tmp = new HashSet<>(Arrays.asList(fireball, poison));
        Assertions.assertEquals("; protects against " + tmp.toString(), SP.additionalOutputString());
    }
}