package sound;

import javax.sound.sampled.*;
import java.io.Closeable;
import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Represents a sound with its source and use counter.
 *
 * @author Dr. Kegel
 */
public class SoundEntry implements Closeable {
    private final String key;
    private SoundEntry previous;
    private final AudioInputStream source;
    private final Clip clip;

    /**
     * Instantiates a new {@link SoundEntry} based on a file.
     *
     * @param file The sound file.
     * @throws java.io.IOException
     */
    public SoundEntry(String file, SoundEntry previous, ConcurrentHashMap<String, SoundEntry> map) throws IOException {
        try {
            key = file;
            source = AudioSystem.getAudioInputStream(getClass().getResourceAsStream(file));
            this.previous = previous;
            DataLine.Info info = new DataLine.Info(Clip.class, source.getFormat());

            clip = (Clip) AudioSystem.getLine(info);

            clip.addLineListener(new Closer(this, map));
            clip.open(source);
        } catch (UnsupportedAudioFileException | LineUnavailableException e) {
            throw new IOException(e);
        }
    }

    @Override
    public void close() {
        if (clip.isActive()) {
            clip.stop();
        }
        if (clip.isOpen()) {
            clip.flush();
            clip.drain();
            clip.close();
        }
        try {
            source.close();
        } catch (Exception ignored) {
        }

        if (previous != null) {
            previous.close();
            previous = null;
        }
    }

    /**
     * Returns the audio clip.
     *
     * @return the audio clip.
     */
    public Clip getClip() {
        return this.clip;
    }

    /**
     * Returns the file.
     *
     * @return the file.
     */
    public String getKey() {
        return this.key;
    }

    /**
     * Plays this sound.
     *
     * @param mode Strategy for handling the case that the sound is already playing.
     */
    public void play(final SoundPlayer.PlayMode mode) {
        if (this.clip.isRunning()) {
            switch (mode) {
                case Ignore:
                    return;
                case Restart:
                    this.stop();
                    break;
                case Toggle:
                    this.stop();
                    return;
                default:
                    break;
            }
        } else {
            this.clip.setFramePosition(0);
        }
        FloatControl volume = (FloatControl) this.clip.getControl(FloatControl.Type.MASTER_GAIN);
        volume.setValue(-5.0f);
        this.clip.start();
    }

    /**
     * Stops this sound.
     */
    public void stop() {
        this.clip.stop();
        this.clip.flush();
        this.clip.setFramePosition(0);
    }

}