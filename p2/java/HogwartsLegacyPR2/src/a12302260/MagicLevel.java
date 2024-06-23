package a12302260;

/**
 * Defines the various magic levels. wizards have a magic level. in order to be
 * able to use specific spells a minimum magic level is necessary. Note: the
 * compiler generated default constructor may not be sufficient for your
 * implementation
 */
public enum MagicLevel {

    NOOB(50), ADEPT(100), STUDENT(200), EXPERT(500), MASTER(1000);

    private int level;

    MagicLevel(int i) {
        // TODO Auto-generated constructor stub
        level = i;
    }

    public int getLevel() {
        return level;
    }
}