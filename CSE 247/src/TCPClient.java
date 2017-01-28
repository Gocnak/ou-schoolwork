import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * Created by Nick on 1/28/2017.
 */
public class TCPClient
{
    public static void main(String[] args) throws Exception
    {
        String sentence, modifiedSentence;

        Socket clientSocket = new Socket("localhost", 6789);

        try (InputStreamReader isr = new InputStreamReader(System.in);
             BufferedReader inFromUser = new BufferedReader(isr);
             DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
             InputStreamReader isr2 = new InputStreamReader(clientSocket.getInputStream());
             BufferedReader inFromServer = new BufferedReader(isr2))
        {
             sentence = inFromUser.readLine();
             outToServer.writeBytes(sentence + '\n');
             modifiedSentence = inFromServer.readLine();
             System.out.println("FROM SERVER: " + modifiedSentence);
             clientSocket.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
