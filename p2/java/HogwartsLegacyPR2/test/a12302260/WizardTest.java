package a12302260;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;

class WizardTest {
    static AttackingSpell fireball = new AttackingSpell("Fire Ball", 3, MagicLevel.ADEPT, true, false, 3);
    static AttackingSpell poison = new AttackingSpell("Poison", 3, MagicLevel.ADEPT, true, true, 50);
    static AttackingSpell extraction = new AttackingSpell("Extraction", 3, MagicLevel.ADEPT, false, false, 3);
    static AttackingSpell timedextraction = new AttackingSpell("Timed Extraction", 3, MagicLevel.ADEPT, false, true, 50);
    static HealthPotion potHP = new HealthPotion("Potion", 10, 1, 1, 3);
    static ManaPotion potMP = new ManaPotion("Mana Potion", 10, 1, 10, 3);
    static Wizard dude;
    static Wizard prey;     

    @BeforeEach
    void setUp() {
        dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.ADEPT).setBasicHP(100).setHP(3).setBasicMP(100).setMP(3).setMoney(100).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(poison))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        prey = new WizardBuilder().setName("Prey").setLevel(MagicLevel.ADEPT).setBasicHP(100).setHP(3).setBasicMP(100).setMP(3).setMoney(100).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(poison))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
    }

    @Test
    void constructor() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName(null).setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(null).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(-1).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(-1).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(-1).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.ADEPT).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(-1).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(-1).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(null).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(null).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(-1).setInventory(new HashSet<>()).createWizard();
        });
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(10).setHP(10).setBasicMP(50).setMP(50).setMoney(10).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(fireball))).setCarryingCapacity(10).setInventory(null).createWizard();
        });
        Assertions.assertDoesNotThrow(() -> {
            Wizard tmp = new WizardBuilder().setName("a").setLevel(MagicLevel.NOOB).setBasicHP(0).setHP(0).setBasicMP(50).setMP(0).setMoney(0).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>()).setCarryingCapacity(0).setInventory(new HashSet<>()).createWizard();
        });
    }

    @Test
    void isDead() {
        dude.takeDamage(999);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void learn() {
        Assertions.assertFalse(dude.learn(fireball));
        Assertions.assertTrue(dude.learn(poison));
        Assertions.assertFalse(dude.learn(poison));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.learn(null));
        dude.takeDamage(999);
        Assertions.assertFalse(dude.learn(extraction));
    }

    @Test
    void forget() {
        Assertions.assertTrue(dude.forget(fireball));
        Assertions.assertFalse(dude.forget(fireball));
        Assertions.assertFalse(dude.forget(poison));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.forget(null));
        dude.learn(fireball);
        dude.takeDamage(999);
        Assertions.assertFalse(dude.forget(fireball));
    }

    @Test
    void castSpell() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.castSpell(null, prey));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.castSpell(fireball, null));
        Assertions.assertFalse(dude.castSpell(poison, prey));
        Assertions.assertTrue(dude.castSpell(fireball, prey));
        Assertions.assertTrue(prey.isDead());
        Assertions.assertFalse(prey.castSpell(fireball, dude));
    }

    @Test
    void castRandomSpell() {
        Wizard clone = new WizardBuilder().setName("Clone").setLevel(MagicLevel.ADEPT).setBasicHP(100).setHP(3).setBasicMP(100).setMP(3).setMoney(100).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>(Collections.singleton(poison))).setCarryingCapacity(10).setInventory(new HashSet<>()).createWizard();
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.castRandomSpell(null));
        Assertions.assertFalse(clone.castRandomSpell(prey));
        Assertions.assertTrue(dude.castRandomSpell(prey));
        Assertions.assertTrue(prey.isDead());
        Assertions.assertFalse(prey.castRandomSpell(dude));
    }

    @Test
    void useItem() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.useItem(null, prey));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.useItem(potHP, null));
        Assertions.assertFalse(dude.useItem(potHP, prey));
        dude.addToInventory(potHP);
        Assertions.assertTrue(dude.useItem(potHP, dude));
        dude.takeDamage(5);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void useRandomItem() {
        Assertions.assertFalse(dude.useRandomItem(prey));
        dude.addToInventory(potHP);
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.useRandomItem(null));
        Assertions.assertTrue(dude.useRandomItem(dude));
        dude.takeDamage(5);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void sellItem() {
        dude.addToInventory(potHP);
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.sellItem(null, prey));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.sellItem(potHP, null));
        Assertions.assertTrue(dude.sellItem(potHP, prey));
        Assertions.assertTrue(prey.removeFromInventory(potHP));
        Assertions.assertTrue(dude.addToInventory(potHP));
        dude.takeDamage(999);
        Assertions.assertFalse(dude.sellItem(potHP, prey));
    }

    @Test
    void sellRandomItem() {
        dude.addToInventory(potHP);
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.sellRandomItem(null));
        Assertions.assertTrue(dude.sellRandomItem(prey));
        Assertions.assertTrue(prey.removeFromInventory(potHP));
        Assertions.assertTrue(dude.addToInventory(potHP));
        dude.takeDamage(999);
        Assertions.assertFalse(dude.sellRandomItem(prey));
    }

    @Test
    void testToString() {
        Assertions.assertEquals("[Dude(**): 3/100 3/100; 100 Knuts; knows [" + fireball.toString() + "]; carries []]", dude.toString());
        dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.ADEPT).setBasicHP(100).setHP(3).setBasicMP(100).setMP(3).setMoney(1).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(poison))).setCarryingCapacity(1).setInventory(new HashSet<>()).createWizard();
        Assertions.assertEquals("[Dude(**): 3/100 3/100; 1 Knut; knows [" + fireball.toString() + "]; carries []]", dude.toString());
        dude = new WizardBuilder().setName("Dude").setLevel(MagicLevel.ADEPT).setBasicHP(100).setHP(3).setBasicMP(100).setMP(3).setMoney(0).setKnownSpells(new HashSet<>(Collections.singleton(fireball))).setProtectedFrom(new HashSet<>(Collections.singleton(poison))).setCarryingCapacity(0).setInventory(new HashSet<>()).createWizard();
        Assertions.assertEquals("[Dude(**): 3/100 3/100; 0 Knuts; knows [" + fireball.toString() + "]; carries []]", dude.toString());
    }

    @Test
    void provideMana() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.provideMana(null, 1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.provideMana(MagicLevel.NOOB, -1));
        Assertions.assertFalse(dude.provideMana(MagicLevel.STUDENT, 2));
        Assertions.assertTrue(dude.provideMana(MagicLevel.ADEPT, 2));
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 1));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
        dude.enforceMagic(1);
        dude.takeDamage(999);
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
    }

    @Test
    void possesses() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.possesses(null));
        Assertions.assertFalse(dude.possesses(potHP));
        dude.addToInventory(potHP);
        Assertions.assertTrue(dude.possesses(potHP));
    }

    @Test
    void canAfford() {
        Assertions.assertTrue(dude.canAfford(100));
        Assertions.assertFalse(dude.canAfford(101));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.canAfford(-1));
    }

    @Test
    void hasCapacity() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.hasCapacity(-1));
        Assertions.assertTrue(dude.hasCapacity(10));
        Assertions.assertFalse(dude.hasCapacity(11));
        dude.addToInventory(potHP);
        Assertions.assertTrue(dude.hasCapacity(9));
        Assertions.assertFalse(dude.hasCapacity(10));
        dude.removeFromInventory(potHP);
        dude.addToInventory(potMP);
        Assertions.assertTrue(dude.hasCapacity(0));
        Assertions.assertFalse(dude.hasCapacity(1));
    }

    @Test
    void pay() {
        Assertions.assertTrue(dude.pay(100));
        Assertions.assertFalse(dude.pay(1));
        dude.earn(10);
        dude.takeDamage(999);
        Assertions.assertFalse(dude.pay(1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.pay(-1));
    }

    @Test
    void earn() {
        Assertions.assertTrue(dude.earn(100));
        Assertions.assertTrue(dude.canAfford(200));
        Assertions.assertFalse(dude.canAfford(201));
        dude.takeDamage(999);
        Assertions.assertFalse(dude.earn(1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.earn(-1));
    }

    @Test
    void addToInventory() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.addToInventory(null));
        Assertions.assertTrue(dude.addToInventory(potHP));
        Assertions.assertFalse(dude.addToInventory(potHP));
        Assertions.assertTrue(dude.possesses(potHP));
        Assertions.assertFalse(dude.addToInventory(potMP));
        Assertions.assertFalse(dude.possesses(potMP));
    }

    @Test
    void removeFromInventory() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.removeFromInventory(null));
        Assertions.assertTrue(dude.addToInventory(potHP));
        Assertions.assertTrue(dude.removeFromInventory(potHP));
        Assertions.assertFalse(dude.possesses(potHP));
        Assertions.assertFalse(dude.removeFromInventory(potHP));
    }

    @Test
    void canSteal() {
        Assertions.assertTrue(dude.canSteal());
        dude.takeDamage(999);
        Assertions.assertFalse(dude.canSteal());
    }

    @Test
    void steal() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> prey.steal(null));
        Assertions.assertFalse(prey.steal(dude));
        dude.takeDamage(999);
        prey.addToInventory(potHP);
        Assertions.assertFalse(prey.steal(dude));
        dude.heal(1);
        Assertions.assertTrue(prey.steal(dude));
        Assertions.assertFalse(prey.possesses(potHP));
        Assertions.assertTrue(dude.possesses(potHP));
        prey.addToInventory(potMP);
        Assertions.assertFalse(prey.steal(dude));
        Assertions.assertFalse(prey.possesses(potMP));
        Assertions.assertFalse(dude.possesses(potMP));
    }

    @Test
    void isLootable() {
        Assertions.assertFalse(dude.isLootable());
        dude.takeDamage(999);
        Assertions.assertTrue(dude.isLootable());
    }

    @Test
    void canLoot() {
        Assertions.assertTrue(dude.canLoot());
        dude.takeDamage(999);
        Assertions.assertFalse(dude.canLoot());
    }

    @Test
    void loot() {
        Wizard deaddude = new WizardBuilder().setName("Dead Dude").setLevel(MagicLevel.ADEPT).setBasicHP(100).setHP(3).setBasicMP(100).setMP(3).setMoney(100).setKnownSpells(new HashSet<>()).setProtectedFrom(new HashSet<>(Collections.singleton(poison))).setCarryingCapacity(12).setInventory(new HashSet<>()).createWizard();
        deaddude.addToInventory(potHP);
        deaddude.addToInventory(potMP);
        Assertions.assertThrows(IllegalArgumentException.class, () -> deaddude.loot(null));
        Assertions.assertFalse(deaddude.loot(dude));
        dude.takeDamage(999);
        Assertions.assertFalse(deaddude.loot(dude));
        dude.heal(1);
        deaddude.takeDamage(999);
        Assertions.assertTrue(deaddude.loot(dude));
        Assertions.assertTrue(deaddude.hasCapacity(12));
        if (dude.hasCapacity(1)) {
            Assertions.assertTrue(dude.possesses(potHP));
            Assertions.assertFalse(dude.possesses(potMP));
        } else {
            Assertions.assertFalse(dude.possesses(potHP));
            Assertions.assertTrue(dude.possesses(potMP));
        }
    }

    @Test
    void takeDamage() {
        Assertions.assertDoesNotThrow(() -> dude.takeDamage(0));
        Assertions.assertDoesNotThrow(() -> dude.takeDamage(101));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.takeDamage(-1));
        dude.takeDamage(101);
        Assertions.assertTrue(dude.isDead());
        dude.heal(10);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(9);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void takeDamagePercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.takeDamagePercent(-1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.takeDamagePercent(101));
        Assertions.assertDoesNotThrow(() -> dude.takeDamagePercent(0));
        Assertions.assertDoesNotThrow(() -> dude.takeDamagePercent(100));
        Assertions.assertTrue(dude.isDead());
        dude.heal(50);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamagePercent(25);
        dude.takeDamagePercent(25);
        Assertions.assertTrue(dude.isDead());
        dude.heal(150);
        dude.takeDamagePercent(100);
        Assertions.assertFalse(dude.isDead());
    }

    @Test
    void weakenMagic() {
        Assertions.assertDoesNotThrow(() -> dude.weakenMagic(0));
        Assertions.assertDoesNotThrow(() -> dude.weakenMagic(101));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.weakenMagic(-1));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
        dude.enforceMagic(10);
        dude.weakenMagic(9);
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 2));
    }

    @Test
    void weakenMagicPercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.weakenMagicPercent(-1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.weakenMagicPercent(101));
        Assertions.assertDoesNotThrow(() -> dude.weakenMagicPercent(0));
        Assertions.assertDoesNotThrow(() -> dude.weakenMagicPercent(100));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
        dude.enforceMagic(50);
        dude.weakenMagicPercent(25);
        dude.weakenMagicPercent(25);
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
        dude.enforceMagic(150);
        dude.weakenMagicPercent(100);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 50));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
    }

    @Test
    void heal() {
        Assertions.assertDoesNotThrow(() -> dude.heal(0));
        Assertions.assertDoesNotThrow(() -> dude.heal(101));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.heal(-1));
        dude.takeDamage(999);
        Assertions.assertTrue(dude.isDead());
        dude.heal(5);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(4);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void healPercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.healPercent(-1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.healPercent(101));
        Assertions.assertDoesNotThrow(() -> dude.healPercent(0));
        Assertions.assertDoesNotThrow(() -> dude.healPercent(100));
        dude.takeDamage(999);
        dude.healPercent(50);
        dude.takeDamage(49);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
        dude.healPercent(50);
        dude.healPercent(20);
        dude.takeDamage(69);
        Assertions.assertFalse(dude.isDead());
        dude.takeDamage(1);
        Assertions.assertTrue(dude.isDead());
    }

    @Test
    void enforceMagic() {
        Assertions.assertDoesNotThrow(() -> dude.enforceMagic(0));
        Assertions.assertDoesNotThrow(() -> dude.enforceMagic(101));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.enforceMagic(-1));
        dude.weakenMagic(999);
        dude.enforceMagic(10);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 10));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
    }

    @Test
    void enforceMagicPercent() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.enforceMagicPercent(-1));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.enforceMagicPercent(101));
        Assertions.assertDoesNotThrow(() -> dude.enforceMagicPercent(0));
        Assertions.assertDoesNotThrow(() -> dude.enforceMagicPercent(100));
        dude.weakenMagic(999);
        dude.enforceMagicPercent(10);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 10));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
        dude.enforceMagicPercent(50);
        dude.enforceMagicPercent(20);
        Assertions.assertTrue(dude.provideMana(MagicLevel.NOOB, 70));
        Assertions.assertFalse(dude.provideMana(MagicLevel.NOOB, 1));
    }

    @Test
    void isProtected() {
        Assertions.assertTrue(dude.isProtected(poison));
        Assertions.assertFalse(dude.isProtected(fireball));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.isProtected(null));
        dude.takeDamage(999);
        Assertions.assertTrue(dude.isProtected(poison));
        Assertions.assertFalse(dude.isProtected(fireball));
    }

    @Test
    void setProtection() {
        dude.setProtection(new HashSet<>(Arrays.asList(extraction, timedextraction)));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.setProtection(null));
        Assertions.assertTrue(dude.isProtected(extraction));
        Assertions.assertTrue(dude.isProtected(timedextraction));
    }

    @Test
    void removeProtection() {
        dude.setProtection(new HashSet<>(Arrays.asList(extraction, timedextraction)));
        dude.removeProtection(new HashSet<>(Arrays.asList(fireball, timedextraction)));
        Assertions.assertThrows(IllegalArgumentException.class, () -> dude.removeProtection(null));
        Assertions.assertFalse(dude.isProtected(fireball));
        Assertions.assertFalse(dude.isProtected(timedextraction));
        Assertions.assertTrue(dude.isProtected(extraction));
    }

    @Test
    void clumsyState() {
        dude.addEffect(State.CLUMSY);
        Assertions.assertFalse(dude.castSpell(fireball, prey));
        Assertions.assertFalse(dude.forget(fireball));
    }

    @Test
    void determinedStat() {
        dude.addEffect(State.DETERMINED);
        Assertions.assertFalse(dude.castRandomSpell(prey));
        Assertions.assertFalse(dude.sellRandomItem(prey));
        Assertions.assertFalse(dude.useRandomItem(prey));
    }
}