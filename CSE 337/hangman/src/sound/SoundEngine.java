package sound;

/**
 * Created by Nick on 12/20/13.
 */
public class SoundEngine {

    private static SoundEngine engine = null;
    private static SoundPlayer player = null;

    public static SoundEngine getEngine() {
        return engine;
    }

    public static void init() {
        engine = new SoundEngine();
    }

    public SoundEngine() {
        player = new SoundPlayer();
    }

    /**
     * Plays a sound.
     *
     * @param s The sound to play.
     */
    public void playSound(Sound s) {
        try
        {
            player.play(s, SoundPlayer.PlayMode.Force);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void close() {
        player.close();
    }
}