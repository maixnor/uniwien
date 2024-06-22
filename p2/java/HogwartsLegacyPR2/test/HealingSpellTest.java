import a12224609.HealingSpell;
import a12224609.MagicLevel;
import a12224609.Wizard;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.HashSet;

class HealingSpellTest {
    static HealingSpell HP = new HealingSpell("HP", 3, MagicLevel.NOOB, true, false, 3);
    static HealingSpell HPP = new HealingSpell("HPP", 3, MagicLevel.NOOB, true, true, 50);
    static HealingSpell MP = new HealingSpell("MP", 3, MagicLevel.NOOB, false, false, 3);
    static HealingSpell MPP = new HealingSpell("MPP", 3, MagicLevel.NOOB, false, true, 50);

    @Test
    void constructor() {
        Assertions.assertDoesNotThrow(() -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, false, 0);});
        Assertions.assertDoesNotThrow(() -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, false, 101);});
        Assertions.assertDoesNotThrow(() -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, true, 0);});
        Assertions.assertDoesNotThrow(() -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, true, 100);});
        Assertions.assertThrows(IllegalArgumentException.class, () -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, false, -1);});
        Assertions.assertThrows(IllegalArgumentException.class, () -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, true, -1);});
        Assertions.assertThrows(IllegalArgumentException.class, () -> {HealingSpell tmp = new HealingSpell("a", 3, MagicLevel.NOOB, false, true, 101);});
    }

    @Test
    void doEffect() {
        Wizard dude = new Wizard("Dude", MagicLevel.NOOB, 10, 0, 50, 0,
                999, new HashSet<>(), new HashSet<>(), 999, new HashSet<>());
        HP.doEffect(dude);
        dude.takeDamage(2);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
        HPP.doEffect(dude);
        dude.takeDamage(4);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
        dude.heal(1);
        MP.doEffect(dude);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 3));
        MPP.doEffect(dude);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 25));
    }

    @Test
    void additionalOutputString() {
        String out1 = HP.additionalOutputString();
        String out2 = HPP.additionalOutputString();
        String out3 = MP.additionalOutputString();
        String out4 = MPP.additionalOutputString();
        Assertions.assertEquals("; +3 HP", out1);
        Assertions.assertEquals("; +50 % HP", out2);
        Assertions.assertEquals("; +3 MP", out3);
        Assertions.assertEquals("; +50 % MP", out4);
    }
}