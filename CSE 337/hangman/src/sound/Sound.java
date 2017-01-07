package sound;

/**
 * The Sound Wrapper Class
 * <p>
 * Constructed to make sound playing in Botnak a lot easier.
 */
public class Sound {
    private final String filePath;

    /**
     * Construct the sounds here. The Sound info itself should be stored here.
     *
     * @param file       The file path of the sound file.
     */
    public Sound(String file) {
        filePath = file;
    }

    /**
     * Gets the sound's path.
     *
     * @return One of the sounds in the array.
     */
    public String getFile() {
        return filePath;
    }

    @Override
    public String toString() {
        return "Sound found at " + filePath;
    }
}