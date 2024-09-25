package a12302260;

import java.util.Set;

public class WizardBuilder {
    private String name;
    private MagicLevel level;
    private int basicHP;
    private int hp;
    private int basicMP;
    private int mp;
    private int money;
    private Set<Spell> knownSpells;
    private Set<AttackingSpell> protectedFrom;
    private int carryingCapacity;
    private Set<Tradeable> inventory;
    private Set<State> states;

    public WizardBuilder setName(String name) {
        this.name = name;
        return this;
    }

    public WizardBuilder setLevel(MagicLevel level) {
        this.level = level;
        return this;
    }

    public WizardBuilder setBasicHP(int basicHP) {
        this.basicHP = basicHP;
        return this;
    }

    public WizardBuilder setHP(int hp) {
        this.hp = hp;
        return this;
    }

    public WizardBuilder setBasicMP(int basicMP) {
        this.basicMP = basicMP;
        return this;
    }

    public WizardBuilder setMP(int mp) {
        this.mp = mp;
        return this;
    }

    public WizardBuilder setMoney(int money) {
        this.money = money;
        return this;
    }

    public WizardBuilder setKnownSpells(Set<Spell> knownSpells) {
        this.knownSpells = knownSpells;
        return this;
    }

    public WizardBuilder setProtectedFrom(Set<AttackingSpell> protectedFrom) {
        this.protectedFrom = protectedFrom;
        return this;
    }

    public WizardBuilder setCarryingCapacity(int carryingCapacity) {
        this.carryingCapacity = carryingCapacity;
        return this;
    }

    public WizardBuilder setInventory(Set<Tradeable> inventory) {
        this.inventory = inventory;
        return this;
    }

    public WizardBuilder setStates(Set<State> states) {
        this.states = states;
        return this;
    }

    public Wizard createWizard() {
        return new Wizard(name, level, basicHP, hp, basicMP, mp, money, knownSpells, protectedFrom, carryingCapacity, inventory, states);
    }
}