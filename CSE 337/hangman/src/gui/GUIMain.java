package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
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
    private String currentWord;

    public GUIMain() {
        initComponents();
        setVisible(true);
        bPlaying = false;
        iTries = 0;
    }


    public void guess(char guessChar)
    {
        // Look at the string



    }

    public void guess(JButton guess)
    {
        guess(guess.getText().charAt(0)); // Guess this button's text
        guess.setEnabled(false); // Disable it
    }


    private void gameStateToggle() {
        // Toggle text, determined before playing bool toggle
        gameStateToggle.setText(bPlaying ? "Start Game" : "Stop Game");
        // Toggle game state
        bPlaying = !bPlaying;
        triesLabel.setVisible(bPlaying); // Toggle tries label visibility
        iTries = 0; // Reset our tries counter
        setGameButtonState(bPlaying); // Toggle game buttons
    }

    private void setGameButtonState(boolean enabled)
    {
        setGameButtonState('\0', enabled);
    }

    private void setGameButtonState(char buttonChar, boolean enabled)
    {
        boolean bHasLimiter = buttonChar > '\0';
        for (Component c : getContentPane().getComponents())
        {
            if (c instanceof JButton && !((JButton) c).getText().contains("Game"))
            {
                if (bHasLimiter && ((JButton) c).getText().equalsIgnoreCase("" + buttonChar))
                {
                    c.setEnabled(enabled);
                    return;
                }
                else
                    c.setEnabled(enabled);

            }
        }
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
               // Disable the button correlated to this key
               setGameButtonState(guess, false);
           }
        }

        // Space toggles game state
        if (e.getKeyCode() == KeyEvent.VK_SPACE)
            gameStateToggle();
    }

    private void gameButtonClicked(MouseEvent e) {
        guess((JButton)e.getSource());
    }

    private void gameStateToggleMouseReleased(MouseEvent e) {
        // TODO add your code here
    }

    private void initComponents() {
        // JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
        // Generated using JFormDesigner Evaluation license - Nick K.
        wordLabel = new JLabel();
        label3 = new JLabel();
        button1 = new JButton();
        button2 = new JButton();
        button3 = new JButton();
        button4 = new JButton();
        button5 = new JButton();
        button6 = new JButton();
        button7 = new JButton();
        button8 = new JButton();
        button9 = new JButton();
        button10 = new JButton();
        button11 = new JButton();
        button12 = new JButton();
        button13 = new JButton();
        button14 = new JButton();
        button15 = new JButton();
        button16 = new JButton();
        button17 = new JButton();
        button18 = new JButton();
        button19 = new JButton();
        button20 = new JButton();
        button21 = new JButton();
        button22 = new JButton();
        button23 = new JButton();
        button24 = new JButton();
        button25 = new JButton();
        button26 = new JButton();
        triesLabel = new JLabel();
        gameStateToggle = new JButton();

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

        //---- wordLabel ----
        wordLabel.setText("XXXXXXXXXXXXXXXX");
        wordLabel.setFont(new Font("Arial", Font.BOLD, 36));
        wordLabel.setHorizontalAlignment(SwingConstants.CENTER);

        //---- label3 ----
        label3.setText("Welcome to Hangman");
        label3.setHorizontalAlignment(SwingConstants.CENTER);
        label3.setFont(new Font("Arial", Font.BOLD, 26));

        //---- button1 ----
        button1.setText("A");
        button1.setFont(new Font("Arial", Font.BOLD, 20));
        button1.setFocusable(false);
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
        button2.setFocusable(false);
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
        button3.setFocusable(false);
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
        button4.setFocusable(false);
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
        button5.setFocusable(false);
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
        button6.setFocusable(false);
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
        button7.setFocusable(false);
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
        button8.setFocusable(false);
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
        button9.setFocusable(false);
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
        button10.setFocusable(false);
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
        button11.setFocusable(false);
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
        button12.setFocusable(false);
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
        button13.setFocusable(false);
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
        button14.setFocusable(false);
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
        button15.setFocusable(false);
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
        button16.setFocusable(false);
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
        button17.setFocusable(false);
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
        button18.setFocusable(false);
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
        button19.setFocusable(false);
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
        button20.setFocusable(false);
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
        button21.setFocusable(false);
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
        button22.setFocusable(false);
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
        button23.setFocusable(false);
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
        button24.setFocusable(false);
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
        button25.setFocusable(false);
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
        button26.setFocusable(false);
        button26.setHorizontalTextPosition(SwingConstants.CENTER);
        button26.setEnabled(false);
        button26.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameButtonClicked(e);
            }
        });

        //---- triesLabel ----
        triesLabel.setText("X tries");
        triesLabel.setFont(new Font("Arial", Font.BOLD, 48));
        triesLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        triesLabel.setVisible(false);

        //---- gameStateToggle ----
        gameStateToggle.setText("Start Game");
        gameStateToggle.setFont(new Font("Arial", Font.BOLD, 18));
        gameStateToggle.setFocusPainted(false);
        gameStateToggle.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e) {
                gameStateToggleMouseReleased(e);
            }
        });

        GroupLayout contentPaneLayout = new GroupLayout(contentPane);
        contentPane.setLayout(contentPaneLayout);
        contentPaneLayout.setHorizontalGroup(
            contentPaneLayout.createParallelGroup()
                .addGroup(contentPaneLayout.createSequentialGroup()
                    .addContainerGap()
                    .addGroup(contentPaneLayout.createParallelGroup()
                        .addComponent(label3, GroupLayout.DEFAULT_SIZE, 638, Short.MAX_VALUE)
                        .addGroup(contentPaneLayout.createSequentialGroup()
                            .addComponent(gameStateToggle)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 510, Short.MAX_VALUE)
                            .addComponent(triesLabel, GroupLayout.PREFERRED_SIZE, 205, GroupLayout.PREFERRED_SIZE))
                        .addComponent(wordLabel, GroupLayout.DEFAULT_SIZE, 638, Short.MAX_VALUE))
                    .addContainerGap())
                .addGroup(GroupLayout.Alignment.TRAILING, contentPaneLayout.createSequentialGroup()
                    .addGap(0, 30, Short.MAX_VALUE)
                    .addGroup(contentPaneLayout.createParallelGroup()
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
                            .addComponent(button26, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE))
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
                            .addComponent(button9, GroupLayout.PREFERRED_SIZE, 60, GroupLayout.PREFERRED_SIZE)))
                    .addGap(26, 26, 26))
        );
        contentPaneLayout.setVerticalGroup(
            contentPaneLayout.createParallelGroup()
                .addGroup(contentPaneLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(label3, GroupLayout.PREFERRED_SIZE, 45, GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(wordLabel)
                    .addGap(18, 18, 18)
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
                    .addGroup(contentPaneLayout.createParallelGroup()
                        .addComponent(triesLabel, GroupLayout.PREFERRED_SIZE, 55, GroupLayout.PREFERRED_SIZE)
                        .addComponent(gameStateToggle, GroupLayout.PREFERRED_SIZE, 55, GroupLayout.PREFERRED_SIZE))
                    .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        pack();
        setLocationRelativeTo(getOwner());
        // JFormDesigner - End of component initialization  //GEN-END:initComponents
    }

    // JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
    // Generated using JFormDesigner Evaluation license - Nick K.
    private JLabel wordLabel;
    private JLabel label3;
    private JButton button1;
    private JButton button2;
    private JButton button3;
    private JButton button4;
    private JButton button5;
    private JButton button6;
    private JButton button7;
    private JButton button8;
    private JButton button9;
    private JButton button10;
    private JButton button11;
    private JButton button12;
    private JButton button13;
    private JButton button14;
    private JButton button15;
    private JButton button16;
    private JButton button17;
    private JButton button18;
    private JButton button19;
    private JButton button20;
    private JButton button21;
    private JButton button22;
    private JButton button23;
    private JButton button24;
    private JButton button25;
    private JButton button26;
    private JLabel triesLabel;
    private JButton gameStateToggle;
    // JFormDesigner - End of variables declaration  //GEN-END:variables
}