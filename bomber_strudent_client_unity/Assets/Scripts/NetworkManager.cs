using System.Net;
using System.Net.Sockets;
using UnityEngine;
using System.Threading;
using System.IO;

public class NetworkManager : MonoBehaviour
{
    private static NetworkManager instance;
    private UdpClient udpClient;
    private UdpClient udpListener;

    private TcpClient tcpClient;
    private TcpListener tcpListener;
    public int port;

    private bool isConnectedTCP = false;
    private bool isListeningUDP = false;

    private void Awake()
    {
        if(NetworkManager.instance != null)
        {
            GameObject.Destroy(this.gameObject);
        }
        else
        {
            DontDestroyOnLoad(this);
            NetworkManager.instance = this;
        }

    }
    /*private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            sendTCPMessage("Bonjour\n");
        }
    }*/
    /*private void Start()
    {
        startListeningUDP(42069);
        initTCPClient("127.0.0.1", 42070);
        sendTCPMessage("Ok");
        initTCPListener(42069);
        startTCPListen();
    }*/

    public void connectTCP(string ipAddress, int sendingPort, int listeningPort)
    {
        isConnectedTCP = true;
        initTCPClient(ipAddress, sendingPort);
        initTCPListener(listeningPort);
        startTCPListen();
    }

    public void startListeningUDP(int port)
    {
        Debug.Log("ok1");
        isListeningUDP = true;
        this.udpListener = new UdpClient(port);
        Thread thread = new Thread(() => ListenUDP());
        thread.Start();

        
    }

    private void ListenUDP()
    {
        Debug.Log("ok");
        IPEndPoint iPEndPoint = new IPEndPoint(IPAddress.Any, 42069);
        while (isListeningUDP)
        {
            byte[] data = this.udpListener.Receive(ref iPEndPoint);
            string message = System.Text.Encoding.ASCII.GetString(data, 0, data.Length);
            Debug.Log(message);

        }
    }

    public void initUpdClient(string addressIP)
    {
        this.udpClient = new UdpClient();
        udpClient.Connect(addressIP, port);
        udpClient.EnableBroadcast = true;
    }
    public static NetworkManager getInstance()
    {
        return instance;
    }

    public void sendUDPMessage(string message)
    {
        byte[] packetData = System.Text.Encoding.ASCII.GetBytes(message);
        /*IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(addressIP),port);
        Socket client = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);
        client.SendTo(packetData, endPoint);*/

        udpClient.Send(packetData, packetData.Length);
        udpClient.Send(packetData, packetData.Length);

    }

    public void initTCPClient(string ipAdress, int port)
    {
        this.tcpClient = new TcpClient(ipAdress, port);
    }

    public void sendTCPMessage(string message)
    {

        byte[] packetData = System.Text.Encoding.ASCII.GetBytes(message);
        if (tcpClient.Connected)
        {
            NetworkStream stream = this.tcpClient.GetStream();
            try
            {
                stream.Write(packetData);
            }
            catch (IOException)
            {
                Debug.Log("Fin de connexion inattendue");
            }
        }
    }

    public void initTCPListener(int port)
    {
        IPAddress localAddr = IPAddress.Parse("127.0.0.1");
        this.tcpListener = new TcpListener(localAddr, port);

    }

    private void startTCPListen()
    {
            Thread thread = new Thread(() => TCPListen());
            thread.Start();

    }
    private void TCPListen()
    {
        Debug.Log("ok listen");
        byte[] bytes = new byte[256];
        string data = null;
        tcpListener.Start();
        Debug.Log("Waiting for a connection... ");

        using TcpClient client = tcpListener.AcceptTcpClient();
        Debug.Log("Connected!");

        data = null;

        NetworkStream stream = client.GetStream();

        int i;
        try
        {
            while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
            {
                data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                Debug.Log("Received: " + data);


            }
        }
        catch (IOException e)
        {
            Debug.Log("Fin de connexion inattendue");
        }

    }

}

