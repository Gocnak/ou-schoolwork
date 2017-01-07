package sound;

import java.io.Closeable;
import java.io.File;
import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;

/**
 * A simple sound system.
 *
 * @author Dr. Kegel
 */
public final class SoundPlayer implements Closeable {

    /**
     * Provides strategies how to react, if being requested to play a sound file, which is already running.
     *
     * @author Dr. Kegel
     */
    public enum PlayMode {
        /**
         * Restarts the sound from the beginning.
         */
        Restart,
        /**
         * Ignores the second play request.
         */
        Ignore,
        /**
         * Stops the first sound.
         */
        Toggle,
        /**
         * Plays both sounds.
         */
        Force,
    }


    private static ConcurrentHashMap<String, SoundEntry> clips;

    public SoundPlayer() {
        clips = new ConcurrentHashMap<>();
    }

    @Override
    public void close() {
        clips.values().forEach(sound.SoundEntry::close);
        clips.clear();
    }

    /**
     * Returns a {@code SoundEntry} instance based on the source file and {@link PlayMode} or creates a new one.
     *
     * @param file The source file.
     * @return a {@code SoundEntry} instance.
     * @throws IOException
     */
    private SoundEntry getClip(Sound file) throws IOException {
        SoundEntry result = new SoundEntry(file.getFile(), clips.get(file.getFile()), clips);
        clips.put(file.getFile(), result);
        return result;
    }

    /**
     * Plays a sound file.
     *
     * @param s The sound file.
     * @param mode The strategy for handling the case that the sound is already playing.
     * @throws IOException
     */
    public void play(Sound s, PlayMode mode) throws IOException {
        if (s != null) getClip(s).play(mode);
    }


    /**
     * @param file The sound file.
     */
    public void stop(File file) {
        SoundEntry entry = clips.get(file);
        if (entry != null) {
            entry.stop();
        }
    }
}