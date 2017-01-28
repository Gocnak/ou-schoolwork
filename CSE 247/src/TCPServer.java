import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by Nick on 1/28/2017.
 */
public class TCPServer
{
   public static void main(String[] args) throws Exception
   {
       String clientSentence, capitalizedSentence;

       ServerSocket welcomeSocket = new ServerSocket(6789);

       while (true)
       {
           Socket connectionSocket = welcomeSocket.accept();

           try (InputStreamReader isr = new InputStreamReader(connectionSocket.getInputStream());
                BufferedReader inFromClient = new BufferedReader(isr);
                DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream()))
           {
                clientSentence = inFromClient.readLine();
                capitalizedSentence = clientSentence.toUpperCase() + '\n';
                outToClient.writeBytes(capitalizedSentence);
           }
           catch (Exception e)
           {
                e.printStackTrace();
           }
       }
   }
}