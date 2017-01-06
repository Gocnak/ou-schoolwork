package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.Collections;
import java.util.Deque;
import java.util.stream.Collectors;
/*
 * Created by JFormDesigner on Thu Jan 05 20:38:14 EST 2017
 */


/**
 * @author Nick K
 */
public class GUIMain extends JFrame {

    public static void log(Object mess){System.out.println(mess.toString());}

    private static boolean bPlaying;
    private static int iTries;
    private Deque<String> wordPool;
    private String currentWord;

    public GUIMain() {
        initComponents();
        setVisible(true);
        bPlaying = false;
        iTries = 0;
        currentWord = "";
        wordPool = new ArrayDeque<>(1000);
        loadWords();
    }

    private void loadWords()
    {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/words.txt"))))
        {
            java.util.List<String> words = br.lines().collect(Collectors.toList());
            Collections.shuffle(words); // Randomize the order for some more fun
            wordPool.addAll(words);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    private boolean checkDone()
    {
        return wordLabel.getText().equalsIgnoreCase(currentWord);
    }

    private void guess(char guessChar)
    {
        if (checkDone())
            return;

        String currentDisplay = wordLabel.getText().toLowerCase();
        GameButton.BUTTON_STATE guessState = getButtonState(guessChar);
        if (currentDisplay.contains("" + guessChar) ||
                guessState == GameButton.BUTTON_STATE.TRIED_FAIL ||
                guessState == GameButton.BUTTON_STATE.TRIED_SUCCESS)
        {
            // TODO: Play some sort of "you already guessed this" sound?
            return;
        }

        boolean successfulGuess = false;
        // Look at the string
        char[] beforeGuess = currentDisplay.toCharArray();
        for (int i = 0; i < currentWord.length(); i++)
        {
            if (currentWord.charAt(i) == guessChar && beforeGuess[i] == '-')
            {
                // Success! They hit a character in the word
                beforeGuess[i] = guessChar;
                successfulGuess = true;
            }
        }

        iTries++;
        setTries();

        setGameButtonState(guessChar, successfulGuess ? GameButton.BUTTON_STATE.TRIED_SUCCESS : GameButton.BUTTON_STATE.TRIED_FAIL);
        if (successfulGuess)
        {
            // TODO: Should we play some sort of "success!" sound?
        }
        else {
            // TODO: Should we play some sort of "FAIL!" sound?
        }

        // Show the updated guess
        wordLabel.setText(new String(beforeGuess).toUpperCase());

        // TODO: Should we check and see if they won here?
    }

    private void guess(JButton guess)
    {
        if (checkDone())
            return;

        guess(guess.getText().toLowerCase().charAt(0)); // Guess this button's text
    }

    // Loads a random word into the current word, and generates the label string
    private void loadNewGame()
    {
        // Get our word from our word pool
        currentWord = wordPool.pop();
        // Set our label
        wordLabel.setText("----------------".substring(0, currentWord.length()));
    }

    private void setTries()
    {
        triesLabel.setText(String.format("%d tries", iTries));
    }

    private void gameStateToggle() {
        // Toggle text, determined before playing bool toggle
        gameStateToggle.setText(bPlaying ? "Start Game" : "Stop Game");
        // Toggle game state
        bPlaying = !bPlaying;
        triesLabel.setVisible(bPlaying); // Toggle tries label visibility
        iTries = 0; // Reset our tries counter
        setTries(); // Reset the tries label
        setGameButtonState(bPlaying ? GameButton.BUTTON_STATE.ENABLED : GameButton.BUTTON_STATE.DISABLED); // Toggle game buttons
        wordLabel.setText("XXXXXXXXXXXXXXXX"); // Back to default, gets overridden if a new game
        // Load a new game if we went from not playing to playing
        if (bPlaying)
            loadNewGame();
    }

    private void setGameButtonState(GameButton.BUTTON_STATE state)
    {
        setGameButtonState('\0', state);
    }

    private void setGameButtonState(char buttonChar, GameButton.BUTTON_STATE state)
    {
        boolean hasLimiter = Character.isAlphabetic(buttonChar);
        for (Component c : getContentPane().getComponents())
        {
            if (c instanceof GameButton && !((GameButton) c).getText().contains("Game"))
            {
                boolean isTheButton = ((GameButton) c).getText().equalsIgnoreCase("" + buttonChar);
                if (hasLimiter && !isTheButton)
                    continue;

                ((GameButton)c).setButtonState(state);
                if (hasLimiter)
                    return;
            }
        }
    }


    private GameButton.BUTTON_STATE getButtonState(char toCheck)
    {
        for (Component comp : getContentPane().getComponents())
        {
            if (comp instanceof GameButton)
            {
                GameButton c = (GameButton)comp;
                if (!c.getText().contains("Game") && c.getText().equalsIgnoreCase("" + toCheck))
                {
                    return c.getButtonState();
                }
            }
        }
        return GameButton.BUTTON_STATE.DISABLED;
    }

    private void thisKeyReleased(KeyEvent e) {
        if (bPlaying)
        {
           if (e.getKeyCode() >= KeyEvent.VK_A && e.getKeyCode() <= KeyEvent.VK_Z)
           {
               // Get the typed key
               char guess = e.getKeyChar();
               // Guess that key
               guess(guess);
           }
        }

        // Space toggles game state
        if (e.getKeyCode() == KeyEvent.VK_SPACE)
            gameStateToggle();
    }

    private void gameButtonClicked(MouseEvent e) {
        guess((JButton)e.getSource());
    }

    private void initComponents() {
        // JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
        // Generated using JFormDesigner Evaluation license - Nick K.
        button1 = new GameButton();
        button2 = new GameButton();
        button3 = new GameButton();
        button4 = new GameButton();
        button5 = new GameButton();
        button6 = new GameButton();
        button7 = new GameButton();
        button8 = new GameButton();
        button9 = new GameButton();
        button10 = new GameButton();
        button11 = new GameButton();
        button12 = new GameButton();
        button13 = new GameButton();
        button14 = new GameButton();
        button15 = new GameButton();
        button16 = new GameButton();
        button17 = new GameButton();
        button18 = new GameButton();
        button19 = new GameButton();
        button20 = new GameButton();
        button21 = new GameButton();
        button22 = new GameButton();
        button23 = new GameButton();
        button24 = new GameButton();
        button25 = new GameButton();
        button26 = new GameButton();
        gameStateToggle = new JButton();
        label3 = new JLabel();
        wordLabel = new JLabel();
        triesLabel = new JLabel();

        //======== this ========
        setTitle("Hangman");
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        setResizable(false);
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyReleased(KeyEvent e) {
                thisKeyReleased(e);
            }
        });
        Container contentPane = getContentPane();

        //---- button1 ----
        button1.setText("A");
        button1.setFont(new Font("Arial", Font.BOLD, 20));
        button1.setHorizontalTextPosition(SwingConstants.CENTER);
        button1.setEnabled(false);
        button1.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button2 ----
        button2.setText("B");
        button2.setFont(new Font("Arial", Font.BOLD, 20));
        button2.setHorizontalTextPosition(SwingConstants.CENTER);
        button2.setEnabled(false);
        button2.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button3 ----
        button3.setText("C");
        button3.setFont(new Font("Arial", Font.BOLD, 20));
        button3.setHorizontalTextPosition(SwingConstants.CENTER);
        button3.setEnabled(false);
        button3.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button4 ----
        button4.setText("D");
        button4.setFont(new Font("Arial", Font.BOLD, 20));
        button4.setHorizontalTextPosition(SwingConstants.CENTER);
        button4.setEnabled(false);
        button4.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button5 ----
        button5.setText("E");
        button5.setFont(new Font("Arial", Font.BOLD, 20));
        button5.setHorizontalTextPosition(SwingConstants.CENTER);
        button5.setEnabled(false);
        button5.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button6 ----
        button6.setText("F");
        button6.setFont(new Font("Arial", Font.BOLD, 20));
        button6.setHorizontalTextPosition(SwingConstants.CENTER);
        button6.setEnabled(false);
        button6.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button7 ----
        button7.setText("G");
        button7.setFont(new Font("Arial", Font.BOLD, 20));
        button7.setHorizontalTextPosition(SwingConstants.CENTER);
        button7.setEnabled(false);
        button7.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button8 ----
        button8.setText("H");
        button8.setFont(new Font("Arial", Font.BOLD, 20));
        button8.setHorizontalTextPosition(SwingConstants.CENTER);
        button8.setEnabled(false);
        button8.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button9 ----
        button9.setText("I");
        button9.setFont(new Font("Arial", Font.BOLD, 20));
        button9.setHorizontalTextPosition(SwingConstants.CENTER);
        button9.setEnabled(false);
        button9.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button10 ----
        button10.setText("J");
        button10.setFont(new Font("Arial", Font.BOLD, 20));
        button10.setHorizontalTextPosition(SwingConstants.CENTER);
        button10.setEnabled(false);
        button10.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button11 ----
        button11.setText("K");
        button11.setFont(new Font("Arial", Font.BOLD, 20));
        button11.setHorizontalTextPosition(SwingConstants.CENTER);
        button11.setEnabled(false);
        button11.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button12 ----
        button12.setText("L");
        button12.setFont(new Font("Arial", Font.BOLD, 20));
        button12.setHorizontalTextPosition(SwingConstants.CENTER);
        button12.setEnabled(false);
        button12.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button13 ----
        button13.setText("M");
        button13.setFont(new Font("Arial", Font.BOLD, 20));
        button13.setHorizontalTextPosition(SwingConstants.CENTER);
        button13.setEnabled(false);
        button13.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button14 ----
        button14.setText("N");
        button14.setFont(new Font("Arial", Font.BOLD, 20));
        button14.setHorizontalTextPosition(SwingConstants.CENTER);
        button14.setEnabled(false);
        button14.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button15 ----
        button15.setText("O");
        button15.setFont(new Font("Arial", Font.BOLD, 20));
        button15.setHorizontalTextPosition(SwingConstants.CENTER);
        button15.setEnabled(false);
        button15.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button16 ----
        button16.setText("P");
        button16.setFont(new Font("Arial", Font.BOLD, 20));
        button16.setHorizontalTextPosition(SwingConstants.CENTER);
        button16.setEnabled(false);
        button16.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button17 ----
        button17.setText("Q");
        button17.setFont(new Font("Arial", Font.BOLD, 20));
        button17.setHorizontalTextPosition(SwingConstants.CENTER);
        button17.setEnabled(false);
        button17.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button18 ----
        button18.setText("R");
        button18.setFont(new Font("Arial", Font.BOLD, 20));
        button18.setHorizontalTextPosition(SwingConstants.CENTER);
        button18.setEnabled(false);
        button18.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button19 ----
        button19.setText("S");
        button19.setFont(new Font("Arial", Font.BOLD, 20));
        button19.setHorizontalTextPosition(SwingConstants.CENTER);
        button19.setEnabled(false);
        button19.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button20 ----
        button20.setText("T");
        button20.setFont(new Font("Arial", Font.BOLD, 20));
        button20.setHorizontalTextPosition(SwingConstants.CENTER);
        button20.setEnabled(false);
        button20.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button21 ----
        button21.setText("U");
        button21.setFont(new Font("Arial", Font.BOLD, 20));
        button21.setHorizontalTextPosition(SwingConstants.CENTER);
        button21.setEnabled(false);
        button21.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button22 ----
        button22.setText("V");
        button22.setFont(new Font("Arial", Font.BOLD, 20));
        button22.setHorizontalTextPosition(SwingConstants.CENTER);
        button22.setEnabled(false);
        button22.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button23 ----
        button23.setText("W");
        button23.setFont(new Font("Arial", Font.BOLD, 20));
        button23.setHorizontalTextPosition(SwingConstants.CENTER);
        button23.setEnabled(false);
        button23.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button24 ----
        button24.setText("X");
        button24.setFont(new Font("Arial", Font.BOLD, 20));
        button24.setHorizontalTextPosition(SwingConstants.CENTER);
        button24.setEnabled(false);
        button24.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button25 ----
        button25.setText("Y");
        button25.setFont(new Font("Arial", Font.BOLD, 20));
        button25.setHorizontalTextPosition(SwingConstants.CENTER);
        button25.setEnabled(false);
        button25.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- button26 ----
        button26.setText("Z");
        button26.setFont(new Font("Arial", Font.BOLD, 20));
        button26.setHorizontalTextPosition(SwingConstants.CENTER);
        button26.setEnabled(false);
        button26.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- gameStateToggle ----
        gameStateToggle.setText("Start Game");
        gameStateToggle.setFont(new Font("Arial", Font.BOLD, 18));
        gameStateToggle.setFocusPainted(false);
        gameStateToggle.setFocusable(false);
        gameStateToggle.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameStateToggle();
            }
        });

        //---- label3 ----
        label3.setText("Welcome to Hangman");
        label3.setHorizontalAlignment(SwingConstants.CENTER);
        label3.setFont(new Font("Arial", Font.BOLD, 26));

        //---- wordLabel ----
        wordLabel.setText("XXXXXXXXXXXXXXXX");
        wordLabel.setFont(new Font("Arial", Font.BOLD, 36));
        wordLabel.setHorizontalAlignment(SwingConstants.CENTER);

        //---- triesLabel ----
        triesLabel.setText("X tries");
        triesLabel.setFont(new Font("Arial", Font.BOLD, 30));
        triesLabel.setHorizontalAlignment(SwingConstants.RIGHT);

        GroupLayout contentPaneLayout = new GroupLayout(contentPane);
        contentPane.setLayout(contentPaneLayout);
        contentPaneLayout.setHorizontalGroup(
            contentPaneLayout.createParallelGroup()
                .addGroup(GroupLayout.Alignment.TRAILING, contentPaneLayout.createSequentialGroup()
                    .addGap(0, 30, Short.MAX_VALUE)
                    .addGroup(contentPaneLayout.createParallelGroup()
                        .addGroup(contentPaneLayout.createSequentialGroup()
                            .addComponent(button10, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button11, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button12, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button13, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button14, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button15, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button16, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button17, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button18, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE))
                        .addGroup(contentPaneLayout.createSequentialGroup()
                            .addComponent(button1, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button2, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button3, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button4, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button5, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button6, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button7, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button8, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button9, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE))
                        .addGroup(contentPaneLayout.createSequentialGroup()
                            .addGap(30, 30, 30)
                            .addComponent(button19, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button20, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button21, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button22, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button23, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button24, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button25, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(button26, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)))
                    .addGap(26, 26, 26))
                .addGroup(GroupLayout.Alignment.TRAILING, contentPaneLayout.createSequentialGroup()
                    .addGroup(contentPaneLayout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                        .addComponent(wordLabel, GroupLayout.Alignment.LEADING, GroupLayout.DEFAULT_SIZE, 638, Short.MAX_VALUE)
                        .addComponent(label3, GroupLayout.Alignment.LEADING, GroupLayout.DEFAULT_SIZE, 638, Short.MAX_VALUE))
                    .addContainerGap())
                .addGroup(contentPaneLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(gameStateToggle)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 364, Short.MAX_VALUE)
                    .addComponent(triesLabel, GroupLayout.PREFERRED_SIZE, 140, GroupLayout.PREFERRED_SIZE)
                    .addContainerGap())
        );
        contentPaneLayout.setVerticalGroup(
            contentPaneLayout.createParallelGroup()
                .addGroup(contentPaneLayout.createSequentialGroup()
                    .addComponent(label3, GroupLayout.PREFERRED_SIZE, 45, GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(wordLabel)
                    .addGap(24, 24, 24)
                    .addGroup(contentPaneLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(button1, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button2, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button3, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button4, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button5, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button6, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button7, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button8, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button9, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addGroup(contentPaneLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(button10, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button11, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button12, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button13, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button14, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button15, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button16, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button17, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button18, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addGroup(contentPaneLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(button19, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button20, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button21, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button22, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button23, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button24, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button25, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)
                        .addComponent(button26, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE))
                    .addGap(18, 18, 18)
                    .addGroup(contentPaneLayout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                        .addComponent(gameStateToggle, GroupLayout.PREFERRED_SIZE, 55, GroupLayout.PREFERRED_SIZE)
                        .addComponent(triesLabel, GroupLayout.PREFERRED_SIZE, 45, GroupLayout.PREFERRED_SIZE))
                    .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        pack();
        setLocationRelativeTo(getOwner());
        // JFormDesigner - End of component initialization  //GEN-END:initComponents
    }

    // JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
    // Generated using JFormDesigner Evaluation license - Nick K.
    private GameButton button1;
    private GameButton button2;
    private GameButton button3;
    private GameButton button4;
    private GameButton button5;
    private GameButton button6;
    private GameButton button7;
    private GameButton button8;
    private GameButton button9;
    private GameButton button10;
    private GameButton button11;
    private GameButton button12;
    private GameButton button13;
    private GameButton button14;
    private GameButton button15;
    private GameButton button16;
    private GameButton button17;
    private GameButton button18;
    private GameButton button19;
    private GameButton button20;
    private GameButton button21;
    private GameButton button22;
    private GameButton button23;
    private GameButton button24;
    private GameButton button25;
    private GameButton button26;
    private JButton gameStateToggle;
    private JLabel label3;
    private JLabel wordLabel;
    private JLabel triesLabel;
    // JFormDesigner - End of variables declaration  //GEN-END:variables
}